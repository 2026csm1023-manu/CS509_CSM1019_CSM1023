#include "timer.h"
#include <chrono>

using namespace std;
using namespace chrono;

high_resolution_clock::time_point start_time;

void start_timer()
{
    start_time=high_resolution_clock::now();
}

double stop_timer()
{
    auto end_time=high_resolution_clock::now();
    return duration<double,milli>(end_time-start_time).count();
}
