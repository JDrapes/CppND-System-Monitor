#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "process.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace LinuxParser;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
    }

bool compareProc(Process& lhs, Process& rhs){
    return lhs.CpuUtilization() > rhs.CpuUtilization();
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    //Need to get a vector of process objects from linux_parser function
    vector<Process> listProcesses{};
    vector<int> listIds = LinuxParser::Pids();
    for (int i : listIds) {
        Process proc{i};
        listProcesses.emplace_back(proc);
  }
    
    //sort by something?
    
    std::sort(listProcesses.begin(), listProcesses.end(), compareProc);

    //assign
    processes_ = listProcesses;
     return processes_; 
     
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
    }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
    }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
    }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
    }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
    }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
     return LinuxParser::UpTime(); 
     }
