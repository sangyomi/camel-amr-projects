//
// Created by 최영수 on 2023/08/01.
//
#include "ObsDetection/ObsDetection.hpp"

void ObsDetection::SaveObsInfo(std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> &LidarData, int time) { // 라벨링, 카운팅된 횟수, 좌표(x,y)
bool checklist = false; /// 라이다 라벨이 실제 배열안에 있는 건지 확인
if(ObsLog.empty()){ //
for(int i=0; i<LidarData.size(); i++ ){
obs_info temp;
temp.timepos.push(std::make_pair(time, LidarData[i].second));
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
if((ObsLog[j].timepos.top().second.first!=LidarData[i].second.first) || (ObsLog[j].timepos.top().second.second!=LidarData[i].second.second)){ ///좌표값이 다를때만 pos에 저장
ObsLog[j].timepos.push(std::make_pair(time,LidarData[i].second));
}
}
}
if(checklist ==  false){ ///new label detected from lidar
obs_info newinfo;
newinfo.timepos.push(std::make_pair(time,LidarData[i].second));
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
        std::stack<std::pair<double, coordinate>> temp = ObsLog[i].timepos;

        std::cout << "장애물" << ObsLog[i].label << "의 좌표 : ";
        while(!temp.empty()){
            std::cout << "(" << temp.top().second.first << "," << temp.top().second.second << ")" << " ";
            temp.pop();
        }
        std::cout << "\n";
        temp = ObsLog[i].timepos;
        std::cout << "장애물" << ObsLog[i].label << "의 절대시간 : ";
        while(!temp.empty()){
            std::cout << temp.top().first << "  ";
            temp.pop();
        }

        std::cout << "\n\n";
    }
}

void ObsDetection::Prediction(){
    if(ObsLog.empty()) return;
    for(int i = 0; i < ObsLog.size(); i++){
        int n_samples = ObsLog[i].timepos.size();
        Eigen::MatrixXd X(n_samples, 2); // 독립 변수 (시간과 상수항)
        Eigen::VectorXd y_x(n_samples);   // 종속 변수 (x)
        Eigen::VectorXd y_y(n_samples);
        std::stack<TimeLoc> temp = ObsLog[i].timepos; // t, (x, y)
        for (int j = 0; j < n_samples; ++j) {
            double t = temp.top().first; // 시간 데이터
            double x = temp.top().second.first; // 가상의 x 데이터
            double y = temp.top().second.second; // 가상의 y 데이터
            X(j, 0) = 1.0; // 상수항 (Intercept)을 위한 열 추가
            X(j, 1) = t;   // 시간
            y_x(j) = x;    // x를 종속 변수로 저장
            y_y(j) = y;    // y를 종속 변수로 저장
            temp.pop();
        }
        Eigen::VectorXd coefficients_x = X.colPivHouseholderQr().solve(y_x); // 회귀계수 계산 (x)
        Eigen::VectorXd coefficients_y = X.colPivHouseholderQr().solve(y_y); // 회귀계수 계산 (y)

        Eigen::VectorXd y_pred_x = X * coefficients_x;
        Eigen::VectorXd y_pred_y = X * coefficients_y;

        double loss_x = (y_pred_x - y_x).squaredNorm() / n_samples;
        double loss_y = (y_pred_y - y_y).squaredNorm() / n_samples;

        double total_loss = loss_x + loss_y;
        double Time = ObsLog[i].timepos.top().first;

        obs_info temp2;
        temp2.loss = total_loss;
        temp2.label = ObsLog[i].label;
        temp2.labelcheck = false;
        for(int i = 0; i < 5; i++) { // 5스탭 미래 예측
            Time += 1000;
            TimeLoc NTP;
            NTP.first = Time;
            NTP.second.first = coefficients_x(0) + coefficients_x(1) * Time;
            NTP.second.second = coefficients_y(0) + coefficients_y(1) * Time;
            temp2.timepos.push(NTP);
        }
        ObsPredPoint.push_back(temp2);
    }
}

void ObsDetection::Pred_Print(){
    std::cout << "======================" << std::endl;
    for(int i=0; i<ObsPredPoint.size(); i++){
        std::stack<TimeLoc> temp = ObsPredPoint[i].timepos;
        std::cout << "장애물" << ObsPredPoint[i].label << "의 좌표 및 시간 : ";

        while(!temp.empty()){
            std::cout <<"["<< temp.top().first << ": (" << temp.top().second.first << "," << temp.top().second.second << ")], ";
            temp.pop();
        }
        std::cout << "\n\n";
    }
}