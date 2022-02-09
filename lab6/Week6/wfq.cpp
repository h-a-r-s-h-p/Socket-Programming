#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    float service_rate= atof(argv[1]);
    float weights[5];
    weights[1]=atof(argv[2]);
    weights[2]=atof(argv[3]);
    weights[3]=atof(argv[4]);
    weights[4]=atof(argv[5]);
    float que_prev_time[5]={};                                         // previous packet's virtual finishing time for each queue
    priority_queue<vector<float>> pq;                                  // priority queue according to virtual finish time
    float arrival_time, id, length;
    int que_id;
    while(scanf("%f%f%d%f",&arrival_time, &id, &que_id, &length)==4){
        float virtual_finish_time=max(que_prev_time[que_id],arrival_time)+length/weights[que_id];        
        pq.push({-1*virtual_finish_time, arrival_time, length, id , (float)que_id});                  // multiplied by -1 to make it minimum priority queue
        que_prev_time[que_id]=virtual_finish_time;                                                    // updating the previous packet's finishing time for the queue
    }

    float prev_finish_time=0;                                                                         
    while(!pq.empty()){
        vector<float> curr_packet= pq.top();                                                                  // extracting packets one by one
        float curr_packet_finish_time= max(prev_finish_time, curr_packet[1])+ curr_packet[2]/service_rate;    
        printf("%0.2f %0.0f %0.0f\n",curr_packet_finish_time, curr_packet[3], curr_packet[4]);
        prev_finish_time=curr_packet_finish_time;                                                             // updating the previous finish time
        pq.pop();
    }
    return 0;
}