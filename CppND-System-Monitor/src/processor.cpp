#include "processor.h"
#include "linux_parser.h"

using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
//get linux_parser vector and do stuff with the data from vector
std::vector<std::string> newData = LinuxParser::CpuUtilization();

//user(0), nice(1), system(2) idle(3), iowait(4), irq(5), softirq(6), steal(7), guest(8), guest_nice(9);
//Copied comment from stack overflow and just created variables for each 
PrevIdle = previdle + previowait;
Idle = stof(newData.at(3)) + stof(newData.at(4));
PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
NonIdle = stof(newData.at(0)) + stof(newData.at(1)) + stof(newData.at(2)) + stof(newData.at(5)) + stof(newData.at(6)) + stof(newData.at(7));
PrevTotal = PrevIdle + PrevNonIdle;
Total = Idle + NonIdle;
//# differentiate: actual value minus the previous one
totald = Total - PrevTotal;
idled = Idle - PrevIdle;
CPU_Percentage = (totald - idled)/totald;

//Now should load the current data to previous after calculations are done
prevuser = stof(newData.at(0));
prevnice = stof(newData.at(1));
prevsystem = stof(newData.at(2));
previdle = stof(newData.at(3));
previowait = stof(newData.at(4));
previrq = stof(newData.at(5));
prevsoftirq = stof(newData.at(6));
prevsteal = stof(newData.at(7));

//this is the return value that will set the monitor tool
return CPU_Percentage;
    
}