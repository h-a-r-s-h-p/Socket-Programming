#include<bits/stdc++.h>
using namespace std;

void counting_curr_token(int capacity, float rate, float& arrival_time, float& prev_exit_time, float &curr_time, int &curr_token_count){          // finds the token count at current time 
    /* when any packet arrives, the current_token_count would have increased by (curr_time-prev_time)*rate */
    if(arrival_time <= prev_exit_time) curr_time=prev_exit_time;          // the previous packet has not yet terminated/finished
    else{
        curr_token_count+= (arrival_time-prev_exit_time)*rate;            // from previous exit time to current arrival time, this much tokens would have been added.
        curr_time=arrival_time;
    }

        curr_token_count=min(capacity,curr_token_count);                 // the number of tokens cannot be more than the maximum capacity
}

int main(int argc, char *argv[]){
    int capacity=atoi(argv[1]);   
    // cout<<"capacity= "<<capacity<<endl;                   
    float rate = atof(argv[2]);
    // cout<<capacity<<endl<<rate<<endl;
    int curr_token_count=capacity;                   //initially the bucket is empty, so token count=0
    float prev_time=0;                          // initially time is 0
    float arrival_time, curr_exit;                        
    int id, length;
    float prev_exit_time=0,curr_time;
    float waiting_time,extra_required;
    // printf("Transmission time\t\tpacketID\t\tlength\n");
    while(scanf("%f%d%d", &arrival_time, &id, &length)==3){        //reading input line by line
        
        // printf("check1\n");
        counting_curr_token(capacity, rate, arrival_time,prev_exit_time,curr_time, curr_token_count);
        extra_required=length-curr_token_count;                             // extra required tokens

        if(extra_required<=0){                                               // if bucket has more tokens than required
            curr_exit= curr_time;
            curr_token_count= -1 * extra_required;                                // curr_token_count would be decreased by extra_required tokens
        }
        else{
            waiting_time=extra_required/rate;                                // else the curr packet has to wait for bucket to fill
            curr_exit=curr_time+waiting_time;
            curr_token_count=0;
        }
        curr_time = curr_exit;
        prev_exit_time=curr_exit;
        printf("%0.2f %d %d\n", curr_exit,id,length);
    }
    return 0;
}