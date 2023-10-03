//
// Created by 최영수 on 2023/08/01.
//
#include "ObsDetection/ObsDetection.hpp"

extern pSHM sharedMemory;
extern DSHM dynamicSharedMemory;

ObsDetection::ObsDetection()
{
    CollisionDetectionCheck = false;
}

void ObsDetection::SaveObsInfo(std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> &LidarData, double time) { // 라벨링, 카운팅된 횟수, 좌표(x,y)
    bool checklist = false; /// 라이다 라벨이 실제 배열안에 있는 건지 확인
    if(dynamicSharedMemory.obsLog.empty()){ //
        for(int i=0; i < LidarData.size(); i++ ){
            OBSINFO temp;
            temp.obsLocationLog.push_back(std::make_pair(time, LidarData[i].second));
            temp.label = LidarData[i].first.first;
            temp.labelcheck = false;
            temp.loss = 0;
            temp.regDataCheck = false;
            dynamicSharedMemory.obsLog.push_back(temp);
        }
        return;
    }
    for(int i=0; i<LidarData.size(); i++ ){
        for(int j=0; j<dynamicSharedMemory.obsLog.size(); j++){
            if(LidarData[i].first.first == dynamicSharedMemory.obsLog[j].label){ ///Label is in the vector
                checklist = true;
                dynamicSharedMemory.obsLog[j].labelcheck = true;
                if((dynamicSharedMemory.obsLog[j].obsLocationLog.back().second.first!=LidarData[i].second.first) || (dynamicSharedMemory.obsLog[j].obsLocationLog.back().second.second!=LidarData[i].second.second)){ ///좌표값이 다를때만 pos에 저장
                    dynamicSharedMemory.obsLog[j].obsLocationLog.push_back(std::make_pair(time,LidarData[i].second));
                }
            }
        }
        if(checklist ==  false){ ///new label detected from lidar
            OBSINFO temp;
            temp.obsLocationLog.push_back(std::make_pair(time,LidarData[i].second));
            temp.label = LidarData[i].first.first;
            temp.labelcheck = true;
            temp.loss = 0;
            temp.regDataCheck = false;
            dynamicSharedMemory.obsLog.push_back(temp);
        }
        checklist = false; ///should be changed to false for checking in next Lidar label
    }
    for(int i=0; i<dynamicSharedMemory.obsLog.size(); i++){
        if(dynamicSharedMemory.obsLog[i].labelcheck == false){
            dynamicSharedMemory.obsLog.erase(dynamicSharedMemory.obsLog.begin()+i); /// label that is not in the lidar should be removed
        }
        else{
            dynamicSharedMemory.obsLog[i].labelcheck = false; /// labelcheck should be changed to false for checking in future loop
        }
    }
}

void ObsDetection::LinearRegression(){
    if (dynamicSharedMemory.obsLog.empty()) return;
    ObsPredPoint.clear();
    dynamicSharedMemory.coeff_data.clear();
    for (int i = 0; i < dynamicSharedMemory.obsLog.size(); i++) {
        int n_samples = dynamicSharedMemory.obsLog[i].obsLocationLog.size();
        if (n_samples < 3) return;
        Eigen::MatrixXd X(n_samples, 2); // 독립 변수 (시간과 상수항)
        Eigen::VectorXd y_x(n_samples);   // 종속 변수 (x)
        Eigen::VectorXd y_y(n_samples);
        std::vector <TimeLoc> temp = dynamicSharedMemory.obsLog[i].obsLocationLog; // t, (x, y)
        for (int j = 0; j < n_samples; ++j) {
            double t = temp.back().first; // 시간 데이터
            double x = temp.back().second.first; // 가상의 x 데이터
            double y = temp.back().second.second; // 가상의 y 데이터
            X(j, 0) = 1.0; // 상수항 (Intercept)을 위한 열 추가
            X(j, 1) = t;   // 시간
            y_x(j) = x;    // x를 종속 변수로 저장
            y_y(j) = y;    // y를 종속 변수로 저장
            temp.pop_back();
        }
        Eigen::VectorXd coefficients_x = X.colPivHouseholderQr().solve(y_x); // 회귀계수 계산 (x)
        Eigen::VectorXd coefficients_y = X.colPivHouseholderQr().solve(y_y); // 회귀계수 계산 (y)

        COEFF tempCOF;
        tempCOF.a = coefficients_x(1);
        tempCOF.c1 = coefficients_x(0);
        tempCOF.b = coefficients_y(1);
        tempCOF.c2 = coefficients_y(0);

        Eigen::VectorXd y_pred_x = X * coefficients_x;
        Eigen::VectorXd y_pred_y = X * coefficients_y;
        double loss_x = (y_pred_x - y_x).squaredNorm() / n_samples;
        double loss_y = (y_pred_y - y_y).squaredNorm() / n_samples;
        double total_loss = loss_x + loss_y;

        dynamicSharedMemory.coeff_data.push_back(tempCOF);
        dynamicSharedMemory.obsLog[i].coeff_data = tempCOF;
        dynamicSharedMemory.obsLog[i].loss = total_loss;
        dynamicSharedMemory.obsLog[i].regDataCheck = true;

    }
}
void ObsDetection::Prediction(int step, int stepsize){
    if(dynamicSharedMemory.obsLog.empty()) return;
    for(int i = 0; i < dynamicSharedMemory.obsLog.size(); i++){
        if(dynamicSharedMemory.obsLog[i].regDataCheck){
            double Time = dynamicSharedMemory.obsLog[i].obsLocationLog.back().first;
            dynamicSharedMemory.obsLog[i].obsPredLoc.clear();
            for (int j = 0; j <= step; j++) { // n스탭 미래 예측
                TimeLoc temp;
                temp.first = Time;
                temp.second.first =
                        dynamicSharedMemory.obsLog[i].coeff_data.c1 + dynamicSharedMemory.obsLog[i].coeff_data.a * Time;
                temp.second.second =
                        dynamicSharedMemory.obsLog[i].coeff_data.c2 + dynamicSharedMemory.obsLog[i].coeff_data.b * Time;
                if ((temp.second.first >= 100 || temp.second.first <= 0) ||
                    (temp.second.second >= 100 || temp.second.second <= 0)) {
                    dynamicSharedMemory.obsLog[i].obsPredLoc.push_back(temp);
                    break;
                } else {
                    dynamicSharedMemory.obsLog[i].obsPredLoc.push_back(temp);
                }
                Time += stepsize;
            }
        }
    }
}

std::vector<coordinate> ObsDetection::GetObsPredPoint(int &num) {
    std::vector<coordinate> temp;
    auto temp2 = dynamicSharedMemory.obsLog[num].obsPredLoc;
    while(!temp2.empty()){
        temp.push_back(temp2.back().second);
        temp2.pop_back();
    }
    std::reverse(temp.begin(), temp.end());
    return temp;
}

int ObsDetection::GetNum_ObsPredPoint() {
    int count = 0;
    for(int i = 0; i < dynamicSharedMemory.obsLog.size(); i++){
        if(!dynamicSharedMemory.obsLog[i].obsPredLoc.empty())
            count++;
    }
    return count;
}

void ObsDetection::Pred_Print(){
    if(GetNum_ObsPredPoint() == 0) return;
    std::cout << "==============================" << std::endl;
    for(int i=0; i<dynamicSharedMemory.obsLog.size(); i++){
        std::vector<TimeLoc> temp = dynamicSharedMemory.obsLog[i].obsPredLoc;
        std::cout << "예측된 장애물" << dynamicSharedMemory.obsLog[i].label << "의 시간 및 좌표\n";

        while(!temp.empty()){
            std::cout <<"["<< temp.back().first << "[ms]: (" << temp.back().second.first << "," << temp.back().second.second << ")]\n";
            temp.pop_back();
            if(temp.empty()) std::cout << "^ 현재 추정 위치 ^\n";
        }
        std::cout << "\n\n";
    }
}

ObsDetection::~ObsDetection()
{
}