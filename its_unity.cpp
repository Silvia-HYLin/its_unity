#include "its_unity.h"

int main(){
    srand(time(NULL));
    int carFlow[4][CMN];    //carFlow[] = {East, West, South, North}
    bool LEW = true;        //if LEW = true([0][1] pass);-->LightSN = false
    int lightLength = -1;   //green light length
    int waitTimeSum = 0; //count for efficiency
    int waitTimeLight = 0;  //waiting time sum before change light
    int waitTimePerSec = 0; //waiting time every second
    int t = 0;              //time counter
    for(int i=0;i<4;i++){   //carFlow initialization at t = 0
        for(int j=0;j<CMN;j++){
            if((double)rand()/(RAND_MAX+1.0) >= p)
                carFlow[i][j] = 1;
            else
                carFlow[i][j] = 0;
        }
    }
    
    //print out initial car flow
    // printf("initial\n");
    // printout(carFlow);
    // printf("\n");
    while(t<1000000){
        if(lightLength<=0){ //determine which side turn when lightLength==0
            bool temp_LEW = determineSeq8(carFlow);
            if(LEW!=temp_LEW&&(lightLength!=-1)){    //if change the light, then waitTimeLight = 0
                // printf("waiting time before light change = %d \n", waitTimeLight);
                // printf("average waiting time before light change per car = %lf \n===light change===\n", double(waitTimeLight)/waitTimePerSec);
                waitTimeLight = 0;
            }
            LEW = temp_LEW;
            // if(LEW)
            //     // printf("East West go with ");
            // else
            //     // printf("South North go with ");
            lightLength = determineLen(carFlow, LEW);
            // printf("===============\n");
        }
        //calculate waitingTime
        waitTimePerSec = waitingTime(carFlow, LEW);
        waitTimeLight += waitTimePerSec;
        waitTimeSum += waitTimePerSec;
        //car move
        if(LEW){    //EW pass, SN stop
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
        t++;
        // printout(carFlow);
        // printf("finish this round\nt = %2d end, lightLength left %d, waitTimePerSec = %d \n", t, lightLength, waitTimePerSec);
        // cin.get();
    }
    printf("determineSeq8: %7d\n",waitTimeSum);
    return 0;
}