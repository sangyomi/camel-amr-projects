//
// Created by 최영수 on 2023/08/01.
//
#include "ObsDetection/ObsDetection.hpp"

ObsDetection::ObsDetection()
{
    CollisionDetectionCheck = false;
}

void ObsDetection::SaveObsInfo(std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> &LidarData, double time) { // 라벨링, 카운팅된 횟수, 좌표(x,y)
bool checklist = false; /// 라이다 라벨이 실제 배열안에 있는 건지 확인
if(ObsLog.empty()){ //
for(int i=0; i < LidarData.size(); i++ ){
obs_info temp;
temp.timepos.push_back(std::make_pair(time, LidarData[i].second));
temp.label = LidarData[i].first.first;
temp.labelcheck = false;
temp.loss = 0;
ObsLog.push_back(temp);
}
return;
}
for(int i=0; i<LidarData.size(); i++ ){
for(int j=0; j<ObsLog.size(); j++){
if(LidarData[i].first.first == ObsLog[j].label){ ///Label is in the vector
checklist = true;
ObsLog[j].labelcheck = true;
if((ObsLog[j].timepos.back().second.first!=LidarData[i].second.first) || (ObsLog[j].timepos.back().second.second!=LidarData[i].second.second)){ ///좌표값이 다를때만 pos에 저장
ObsLog[j].timepos.push_back(std::make_pair(time,LidarData[i].second));
}
}
}
if(checklist ==  false){ ///new label detected from lidar
obs_info newinfo;
newinfo.timepos.push_back(std::make_pair(time,LidarData[i].second));
newinfo.label = LidarData[i].first.first;
newinfo.labelcheck = true;
newinfo.loss = 0;
ObsLog.push_back(newinfo);
}
checklist = false; ///should be changed to false for checking in next Lidar label
}
for(int i=0; i<ObsLog.size(); i++){
if(ObsLog[i].labelcheck == false){
ObsLog.erase(ObsLog.begin()+i); /// label that is not in the lidar should be removed
}
else{
ObsLog[i].labelcheck = false; /// labelcheck should be changed to false for checking in future loop
}
}
}

void ObsDetection::Print(){
    std::cout << "======================" << std::endl;
    for(int i=0; i<ObsLog.size(); i++){
        std::vector<std::pair<double, coordinate>> temp = ObsLog[i].timepos;

        std::cout << "장애물" << ObsLog[i].label << "의 좌표 : ";
        while(!temp.empty()){
            std::cout << "(" << temp.back().second.first << "," << temp.back().second.second << ")" << " ";
            temp.pop_back();
        }
        std::cout << "\n";
        temp = ObsLog[i].timepos;
        std::cout << "장애물" << ObsLog[i].label << "의 절대시간 : ";
        while(!temp.empty()){
            std::cout << temp.back().first << "  ";
            temp.pop_back();
        }

        std::cout << "\n\n";
    }
}

void ObsDetection::LinearRegression(){
    if (ObsLog.empty()) return;
    ObsPredPoint.clear();
    coeff_data.clear();
    for (int i = 0; i < ObsLog.size(); i++) {
        int n_samples = ObsLog[i].timepos.size();
        if (n_samples < 3) return;
        Eigen::MatrixXd X(n_samples, 2); // 독립 변수 (시간과 상수항)
        Eigen::VectorXd y_x(n_samples);   // 종속 변수 (x)
        Eigen::VectorXd y_y(n_samples);
        std::vector <TimeLoc> temp = ObsLog[i].timepos; // t, (x, y)
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

        coeff_data.push_back(std::make_pair(std::make_pair(coefficients_x(0), coefficients_x(1)) , std::make_pair(coefficients_y(0), coefficients_y(1))));
        Eigen::VectorXd y_pred_x = X * coefficients_x;
        Eigen::VectorXd y_pred_y = X * coefficients_y;
        double loss_x = (y_pred_x - y_x).squaredNorm() / n_samples;
        double loss_y = (y_pred_y - y_y).squaredNorm() / n_samples;

        double total_loss = loss_x + loss_y;

        double Time = ObsLog[i].timepos.back().first;

        obs_info temp2;
        temp2.loss = total_loss;
        temp2.label = ObsLog[i].label;
        temp2.labelcheck = false;
        temp2.timepos.push_back(std::make_pair(Time,std::make_pair(0,0)));
        ObsPredPoint.push_back(temp2);
    }
}
void ObsDetection::Prediction(int step, int stepsize){
    if(ObsPredPoint.empty()) return;
    for(int i = 0; i < ObsPredPoint.size(); i++){
        double Time = ObsPredPoint[i].timepos.front().first;
        ObsPredPoint[i].timepos.clear();
        for (int j = 0; j <= step; j++) { // n스탭 미래 예측
            TimeLoc NTP;
            NTP.first = Time;
            NTP.second.first = coeff_data[i].first.first + coeff_data[i].first.second * Time;
            NTP.second.second = coeff_data[i].second.first + coeff_data[i].second.second * Time;
            if ((NTP.second.first >= 100 || NTP.second.first <= 0) ||
                (NTP.second.second >= 100 || NTP.second.second <= 0)) {
                ObsPredPoint[i].timepos.push_back(NTP);
                break;
            } else {
                ObsPredPoint[i].timepos.push_back(NTP);
            }
            Time += stepsize;
        }
    }
}

void ObsDetection::Pred_Print(){
    if(ObsPredPoint.empty()) return;
    std::cout << "==============================" << std::endl;
    for(int i=0; i<ObsPredPoint.size(); i++){
        std::vector<TimeLoc> temp = ObsPredPoint[i].timepos;
        std::cout << "예측된 장애물" << ObsPredPoint[i].label << "의 시간 및 좌표\n";

        while(!temp.empty()){
            std::cout <<"["<< temp.back().first << "[ms]: (" << temp.back().second.first << "," << temp.back().second.second << ")]\n";
            temp.pop_back();
            if(temp.empty()) std::cout << "^ 현재 추정 위치 ^\n";
        }
        std::cout << "\n\n";
    }
}
int ObsDetection::GetNum_ObsPredPoint(){
    return ObsPredPoint.size();
}
std::vector<coordinate> ObsDetection::GetObsPredPoint(int &num) {
    std::vector<coordinate> temp;
    auto temp2 = ObsPredPoint[num].timepos;
    while(!temp2.empty()){
        temp.push_back(temp2.back().second);
        temp2.pop_back();
    }
    std::reverse(temp.begin(), temp.end());
    return temp;
}
ObsDetection::~ObsDetection()
{

}