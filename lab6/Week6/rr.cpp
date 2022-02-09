#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    float service_rate= stof(argv[1]);
    float arrival_time;
    float id,length, que_id;
    map<int,queue<vector<float>>> que;                      // stores all the queues
    float first_packet_at=1e8;                              // first_packet_at will be one with minimum arrival time
    int curr_que;                                           // curr_que number
    float no_packets=0;                                     // total number of incoming packets
    while(scanf("%f%f%f%f",&arrival_time,&id,&que_id,&length)==4){    // first I am pushing all the packets in the respecctive queue
        no_packets++;
        que[que_id].push({arrival_time,id,length});         // pushing the packet in queue que_id
        if(arrival_time<first_packet_at){                   // finding the packet with minimum time
            first_packet_at=arrival_time;
            curr_que=(int)que_id;                           // curr_que would be the queue with minimum arrival time packet
        }
    }
    int number_of_queues=que.size();                        // total number of queue
    float curr_time=first_packet_at;
    while(no_packets){                                      // while all the packets are not processed
        int flag=0;                                         // to check if arriving time of front packets of all the queues is greater than the curr_time, i.e. we have to wait
        for(int i=1;i<number_of_queues+1;i++){
            if(!que[i].empty() and que[i].front()[0]<=curr_time) {     // if any of the queue's front packet's arriving time is less than or equal to curr_time then we don't have to wait, so flag=1
                flag=1;
                break;
            }
        }
        if(flag){                                            // if we don't have to wait
            if(que[curr_que].empty() or que[curr_que].front()[0] > curr_time) {     //if the curr_que's front packet's arriving time is more than curr_time, then we will go and check the que, so curr_que++
                curr_que++;
                curr_que=curr_que%(number_of_queues+1);
                continue;
            }
            
            no_packets--;                                     
            vector<float> curr_packet=que[curr_que].front();   //curr_packet
            que[curr_que++].pop();                             
            curr_que%=(number_of_queues+1);
            printf("%0.2f %d\n",curr_time+curr_packet[2]/service_rate, (int)curr_packet[1]);    //the finishing time of curr_packet is curr_time+curr_packet[2]/service_rate.
            curr_time=curr_time+curr_packet[2]/service_rate;
        }
        else{                                               // if we have to wait
            float waiting_time=1e8;                         // wait until the minimum arriving time of front packet of any queue
            for(int i=1;i<number_of_queues+1;i++){
                if(!que[i].empty() and que[i].front()[0]<waiting_time){
                    waiting_time=que[i].front()[0];
                    curr_que=i;                             // curr_que would be minimum arriving time
                }
            }
            curr_time=waiting_time;
        }
    }

    return 0;
}