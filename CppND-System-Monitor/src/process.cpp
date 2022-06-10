#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

Process::Process(int pid) : processId(pid) {
    //Init anything here
    getCpuUtilization();
    getCommand();
    getRam();
    getUser();
    getUpTime();
}

// TODO: Return this process's ID
int Process::Pid() {
    return processId;   
    }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return CpuUtilizationdata;
    //return 0; 
    }

// TODO: Return the command that generated this process
string Process::Command() {
     return Commanddata;
     //return string(); 
     }

// TODO: Return this process's memory utilization
string Process::Ram() {
    return Ramdata;
     //return string(); 
     }

// TODO: Return the user (name) that generated this process
string Process::User() {
     return Userdata;
     //return string(); 
     }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
     return UpTimedata;
     //return 0; 
     }


//wrote my own function for this in system.cpp as didn't realise this was here until after.
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { 
    return true; 
    }


//My impl functions that get called in the constructor and assign their values 

void Process::getCpuUtilization(){
    long uptime = LinuxParser::UpTime();
    vector<float> value = LinuxParser::CpuUtilization(Pid());
    if(value.size() == 5){
         float totalTime = value[kUtime] + value[kStime] + value[kCutime] + value[kCstime];
         float seconds = uptime - value[kStarttime];
         CpuUtilizationdata = totalTime/seconds;
        
    } else {
        CpuUtilizationdata = 0;
    }
}
void Process::getCommand(){
Commanddata = LinuxParser::Command(Pid());
}

void Process::getRam(){
string temp = LinuxParser::Ram(Pid());
//need in MB
try { //using a try so when an exception gets thrown it still works
long mb = std::stol(temp)/1000;
Ramdata = std::to_string(mb);
} catch (const std::invalid_argument& arg){
    Ramdata = "0";
}

}

void Process::getUser(){
Userdata = LinuxParser::User(Pid());
}

void Process::getUpTime(){
UpTimedata = LinuxParser::UpTime(Pid());
}