//
// Created by sangjun on 23. 8. 29.
//

#include "ClusteringDynamicObs/ClusteringDynamicObs.hpp"
#define RR 0.00436332313
#define grid 100

ClusteringDynamicObs::ClusteringDynamicObs()
: SavedMatrix(grid, std::vector<int>(grid, 0)),
  DynamicMatrix(grid, std::vector<int>(grid, 0)),
  ClusteringMatrix(grid, std::vector<int>(grid, 0))
{
    ObstacleLabel = 4;
}

void ClusteringDynamicObs::UpdateDynamicObstacle(std::vector<float> &scanarray, std::vector<std::vector<int>> &Mapmatrix, double heading, double xpos, double ypos, int MapCounter)
{
    for (int i=0 ; i<720 ; i++)
    {
        x_spot[i] = int(((scanarray[i]*cos((heading+(RR*(i-359)))) + xpos)+10)*(grid/20));
        y_spot[i] = int(((scanarray[i]*sin((heading+(RR*(i-359)))) + ypos)+10)*(grid/20));
    }
    for (int i = 0; i < 720; ++i)
    {
        if ((0<=x_spot[i]&&x_spot[i]<grid) && (0<=y_spot[i]&&y_spot[i]<grid))
        {
            Mapmatrix[x_spot[i]][y_spot[i]] = 1;
            SavedMatrix[x_spot[i]][y_spot[i]] += 1;
        }
    }
    if(MapCounter%30 == 0)
    {
        for (int i = 0; i < grid; ++i)
        {
            for(int j = 0 ; j < grid ; ++j)
            {
                if (SavedMatrix[i][j] != 0 && SavedMatrix[i][j] != 30)
                {
                    Mapmatrix[i][j] = 0;
                    DynamicMatrix[i][j] = 1;
                }
                else
                {
                    DynamicMatrix[i][j] = 0;
                }
                SavedMatrix[i][j] = 0;
                ClusteringMatrix[i][j] = 0;
            }
        }
        ClusteringDynamicObstacle();
    }
    PrintMap();
}

void ClusteringDynamicObs::ClusteringDynamicObstacle()
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
                    ConnectObs(sumX, sumY);
                }
            }
        }
    }
    for (int i = 0 ; i < LabelingStack.size() ; i++)
    {
        if(LabelingStack[i] == LabelingArray[i].first.second)
        {
            LabelingArray.erase(LabelingArray.begin() + i);
        }
    }
    LabelingStack.clear();
    for (int i = 0 ; i < LabelingArray.size() ; i++)
    {
        LabelingStack.push_back(LabelingArray[i].first.second);
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

    for (int i = 0 ; i < LabelingArray.size() ; i++)
    {
        int t = std::sqrt(std::pow(avgX-LabelingArray[i].second.first,2) + std::pow(avgY-LabelingArray[i].second.second,2));

        if(distance > t)
        {
            distance = t;
            ClusteringMatrix[avgX][avgY] = LabelingArray[i].first.first;
            temp = i;
        }
    }

    if (temp != -1) // 기존 노드 업데이트
    {
        LabelingArray[temp] = std::make_pair(std::make_pair(LabelingArray[temp].first.first, LabelingArray[temp].first.second + 1), std::make_pair(avgX, avgY));
    }
    else // 새로운 노드 생성
    {
        ObstacleLabel++;
        ClusteringMatrix[avgX][avgY] = ObstacleLabel;
        LabelingArray.push_back(std::make_pair(std::make_pair(ObstacleLabel, 1), std::make_pair(avgX, avgY)));
    }



}

void ClusteringDynamicObs::PrintMap()
{
    std::cout<< "\n";
    for (int i = 0; i < grid; ++i) {
        for (int j = 0; j < grid; ++j) {
//            std::cout << MapMatrix[i][j];
            std::cout << ClusteringMatrix[i][j];
//            std::cout << SavedMatrix[i][j];
//            std::cout << DynamicMatrix[i][j];
        }
        std::cout << '\n';
    }
}

ClusteringDynamicObs::~ClusteringDynamicObs()
{

}