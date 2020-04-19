#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h>
using namespace std;
#define CMN 10
#define p 0.6

void printout(int carFlow[4][CMN]){
    char symbol[4]={'E', 'W', 'S', 'N'};
    for(int i=0;i<4;i++){
        printf("%c ", symbol[i]);
        for(int j=0;j<CMN;j++){
            printf("%d ",carFlow[i][j]);
        }
        printf("\n");
    }
}

bool determineSeq1(const int carFlow[4][CMN]){   //binary //EW->true
    int sum[4]={0};
    for(int i=0;i<4;i++){
        for(int j=0;j<CMN;j++){
            if(carFlow[i][j]==1)
                sum[i]=sum[i]+pow(2,9-j);
        }
    }
    if((sum[0]+sum[1])>(sum[2]+sum[3])){
        return true;    //EW green
    }  
    else{
        return false;
    }
}

bool determineSeq2(const int carFlow[4][CMN]){   //linear
    int sum[4]={0};
    for(int i=0;i<3;i++){
        for(int j=0;j<CMN;j++){
            sum[i]=sum[i]+(10-j)*carFlow[i][j];
        }
    }
    if((sum[0]+sum[1])>(sum[2]+sum[3])){
        return true;    //EW green
    }  
    else{
        return false;
    }
}

int determineLen(const int carFlow[4][CMN], bool LEW){
    int sum[4]={0};
    for(int i=0; i<4; i++){
        bool flag = true;
        for(int j=0;j<CMN;j++){
            if(carFlow[i][j]==1){
                sum[i] += 1;
                flag = false;
            }
            else if(flag)
                sum[i] += 1;
            else
                break;
        }
    }
    if(LEW){
        printf("lightLength = %2d \n",(sum[0]+sum[1])/2);
        return (sum[0]+sum[1])/2;
    }  
    else{
        printf("lightLength = %2d \n",(sum[2]+sum[3])/2);
        return (sum[2]+sum[3])/2;
    }
        
}

int waitingTime(int carFlow[4][CMN], bool LEW){
    int sum=0;
    if(LEW){    //NS stop
        for(int i=2;i<4;i++){
            for(int j=0;j<CMN;j++){
                if(carFlow[i][j]==1)
                    sum++;
                else
                    break;
            }
        }
    }
    else{
        for(int i=0;i<2;i++){
            for(int j=0;j<CMN;j++){
                if(carFlow[i][j]==1)
                    sum++;
                else
                    break;
            }
        }
    }
    return sum;
}