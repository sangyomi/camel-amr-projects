//
// Created by sangjun on 23. 8. 29.
//

#include "ClusteringDynamicObs/ClusteringDynamicObs.hpp"
#include "ClusteringDynamicObs/DBSCAN.hpp"
#define RR 0.00436332313
#define grid 100

extern pSHM sharedMemory;
extern DSHM dynamicSharedMemory;

ClusteringDynamicObs::ClusteringDynamicObs()
        : SavedMatrix(grid, std::vector<int>(grid, 0)),
          DynamicMatrix(grid, std::vector<int>(grid, 0)),
          ClusteringMatrix(grid, std::vector<int>(grid, 0))
{
    ObstacleLabel = 4;
}

void ClusteringDynamicObs::UpdateDynamicObstacle(std::vector<float> &scanarray, std::vector<std::vector<int>> &Mapmatrix, int MapCounter)
{
    int globalX_pos;
    int globalY_pos;
    for (int i = 0 ; i < 720 ; i++)
    {
        globalX_pos = int(((scanarray[i]*cos((sharedMemory->heading+(RR*(i-359)))) + sharedMemory->xpos)+10)*(grid/20));
        globalY_pos = int(((scanarray[i]*sin((sharedMemory->heading+(RR*(i-359)))) + sharedMemory->ypos)+10)*(grid/20));
        if(globalX_pos >= 0 && globalX_pos < 100 && globalY_pos >= 0 && globalY_pos < 100) {
            ClusteringMatrix[x_spot[i]][y_spot[i]] = 1;
        }
    }

    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            std::cout << ClusteringMatrix[i][j];
        }
        std::cout << "\n";
    }
}

void ClusteringDynamicObs::ClusteringDynamicObstacle(int xPos, int yPos)
{
    int ChangeObstacle = 5;
    for (int i = 0; i < grid; ++i)
    {
        for (int j = 0; j < grid; ++j)
        {
            if(DynamicMatrix[i][j] == 1)
            {
                int SizeCount = 0;
                std::vector<std::pair<int, int>> ClusteringInfo;

                CheckObstacle(i,j,ChangeObstacle,SizeCount, ClusteringInfo);

                if (SizeCount > 5)
                {
                    int sumX = 0;
                    int sumY = 0;
                    int numPoints = ClusteringInfo.size();

                    for (const std::pair<int, int>& point : ClusteringInfo) {
                        sumX += point.first;
                        sumY += point.second;
                    }
                    if (numPoints > 0) {
                        sumX = sumX / numPoints;
                        sumY = sumY / numPoints;
                    }

                    double rad = std::atan2(sumY - yPos, sumX - xPos);

                    sumX = sumX + int((SizeCount * 0.01)*(std::cos(rad)));
                    sumY = sumY + int((SizeCount * 0.01)*(std::sin(rad)));

                    ConnectObs(sumX, sumY);
                }
            }
        }
    }
    for (int i = 0 ; i < LabelingStack.size() ; i++)
    {
        if(LabelingStack[i] == dynamicSharedMemory.LabelingArray[i].first.second)
        {
            dynamicSharedMemory.LabelingArray.erase(dynamicSharedMemory.LabelingArray.begin() + i);
        }
    }
    LabelingStack.clear();
    for (int i = 0 ; i < dynamicSharedMemory.LabelingArray.size() ; i++)
    {
        LabelingStack.push_back(dynamicSharedMemory.LabelingArray[i].first.second);
    }
}

void ClusteringDynamicObs::CheckObstacle(int i, int j, int ChangeObstacle, int& SizeCount, std::vector<std::pair<int, int>>& ClusteringInfo)
{
    if(( 0<=i && i<grid ) && ( 0<=j && j<grid ) && (DynamicMatrix[i][j] == 1))
    {
        SizeCount++;
        DynamicMatrix[i][j] = ChangeObstacle;
        ClusteringInfo.push_back(std::make_pair(i,j));
        CheckObstacle(i-1,j,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i+1,j,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i,j-1,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i,j+1,ChangeObstacle,SizeCount,ClusteringInfo);
    }
    else
    {
        return;
    }
}

void ClusteringDynamicObs::ConnectObs(int avgX, int avgY)
{
    double distance = 7;
    int temp = -1;

    for (int i = 0 ; i < dynamicSharedMemory.LabelingArray.size() ; i++)
    {
        int t = std::sqrt(std::pow(avgX-dynamicSharedMemory.LabelingArray[i].second.first,2) + std::pow(avgY-dynamicSharedMemory.LabelingArray[i].second.second,2));

        if(distance > t)
        {
            distance = t;
            ClusteringMatrix[avgX][avgY] = dynamicSharedMemory.LabelingArray[i].first.first;
            temp = i;
        }
    }

    if (temp != -1) // 기존 노드 업데이트
    {
        dynamicSharedMemory.LabelingArray[temp] = std::make_pair(std::make_pair(dynamicSharedMemory.LabelingArray[temp].first.first, dynamicSharedMemory.
                LabelingArray[temp].first.second + 1), std::make_pair(avgX, avgY));
    }
    else // 새로운 노드 생성
    {
        ObstacleLabel++;
        ClusteringMatrix[avgX][avgY] = ObstacleLabel;
        dynamicSharedMemory.LabelingArray.push_back(std::make_pair(std::make_pair(ObstacleLabel, 1), std::make_pair(avgX, avgY)));
    }
}

void ClusteringDynamicObs::PrintMap()
{
    std::cout<< "\n";
    for (int i = 0; i < grid; ++i) {
        for (int j = 0; j < grid; ++j) {
//            std::cout << ClusteringMatrix[i][j];
//            std::cout << SavedMatrix[i][j];
            std::cout << DynamicMatrix[i][j];
        }
        std::cout << '\n';
    }
}

ClusteringDynamicObs::~ClusteringDynamicObs()
{

}