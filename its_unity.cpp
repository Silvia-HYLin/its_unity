#include "20200417.h"

int main(){
    srand(time(NULL));
    int carFlow[4][CMN];    //carFlow[] = {East, West, South, North}
    bool LEW = true;    //if LEW = true([0][1] pass);-->LightSN = false
    int lightLength = -1;    //green light length
    int waitingTimeSum = 0;
    int waitTime = 0;
    int t = 1;
    for(int i=0;i<4;i++){
        for(int j=0;j<CMN;j++){
            if((double)rand()/(RAND_MAX+1.0)>=p)
                carFlow[i][j]=1;
            else
                carFlow[i][j]=0;
        }
    }
    
    while(1){
        if(lightLength==0){
            if(LEW)
                printf("South North Stop AVWT %3lf \n",((double)waitTime));
            else
                printf("East West Stop AVWT %3lf \n",((double)waitTime));
        }
        printout(carFlow);
        if(lightLength<=0){
            LEW = determineSeq1(carFlow);
            lightLength = determineLen(carFlow, LEW);
            waitTime = 0;
        }
        t = waitingTime(carFlow, LEW);
        waitingTimeSum = waitingTimeSum + t;
        if(LEW){    //EW pass, SN stop
            printf("East and West go %2d \n",lightLength);
            waitTime = waitTime+t;
            for(int i=0;i<2;i++){   //EW move forward directly
                for(int j=0;j<CMN-1;j++){
                    carFlow[i][j]=carFlow[i][j+1];
                }
                if((double)rand()/(RAND_MAX+1.0)>=p)
                    carFlow[i][CMN-1]=1;
                else
                    carFlow[i][CMN-1]=0;
            }
            for(int i=2;i<4;i++){
                bool moveNext = false;
                for(int j=0;j<CMN;j++){
                    if(carFlow[i][j]==0)
                        moveNext = true;
                    if((moveNext==true)&&(j<CMN-1))
                        carFlow[i][j]=carFlow[i][j+1];
                }
                if(moveNext)
                    if((double)rand()/(RAND_MAX+1.0)>=p)
                        carFlow[i][CMN-1]=1;
                    else
                        carFlow[i][CMN-1]=0;
            }
        }
        else{           //EW stop, SN pass
            printf("South and North go %2d \n",lightLength);
            for(int i=2;i<4;i++){   //SN move forward directly
                for(int j=0;j<CMN-1;j++){
                    carFlow[i][j]=carFlow[i][j+1];
                }
                if((double)rand()/(RAND_MAX+1.0)>=p)
                    carFlow[i][CMN-1]=1;
                else
                    carFlow[i][CMN-1]=0;
            }
            for(int i=0;i<2;i++){
                bool moveNext = false;
                for(int j=0;j<CMN;j++){
                    if(carFlow[i][j]==0)
                        moveNext = true;
                    if((moveNext==true)&&(j<CMN-1))
                        carFlow[i][j]=carFlow[i][j+1];
                }
                if(moveNext)
                    if((double)rand()/(RAND_MAX+1.0)>=p)
                        carFlow[i][CMN-1]=1;
                    else
                        carFlow[i][CMN-1]=0;
            }
        }
        lightLength = lightLength-1;
        cin.get();
    }
    
    return 0;
}