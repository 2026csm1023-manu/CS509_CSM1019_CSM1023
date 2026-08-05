#include "timer.h"
#include <chrono>

using namespace std;

//Chrono is a time related lib of cpp, high resolution is a type of time measurement which is very precise, time_point stores time like timestamp
chrono::high_resolution_clock::time_point start_time;

void start_timer(){

    start_time=chrono::high_resolution_clock::now();
}

double stop_timer(){
     
    auto stop_time=chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(stop_time-start_time).count();
    
}
