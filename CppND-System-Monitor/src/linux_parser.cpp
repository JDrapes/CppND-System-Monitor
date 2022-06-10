#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "format.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using namespace Format;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, key, memVal;
  float memTotal = 0;
  float memFree = 0;
  std::ifstream stream(kProcDirectory + kMeminfoFilename); //memory info file
  //If we are able to open the file
  if(stream.is_open()){
   while(std::getline(stream, line)){
    std::istringstream linestream(line);
    while(linestream >> key >> memVal) {
      //If we find the key get string to float
      if(key == "MemTotal:"){
      memTotal = std::stof(memVal);
    }
    //If we find the key get string to float
    else if (key == "MemFree:"){
    memFree = std::stof(memVal);
        }
      }
    } 
  }
  //Return the memory usage as a percentage of the total (gives it out of 100)
  //When checking the file was MemTotal: 7648760 kB MemFree: 2946004 kB
  return ((memTotal - memFree)/memTotal); 
  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long time = 0;
  string line, uptimeVal;
  std::ifstream stream(kProcDirectory + kUptimeFilename); //uptime file
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
      //In uptime file, the first value is the uptime in seconds, second value is sum time of each core being idle, so ideally want the first number
    linestream >> uptimeVal; 
  }
  time = std::stol(uptimeVal);
  return time; 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
//Here we should get the line of CPU utilization, load it to a vector that can be passed to processor class later
  std::vector<string> data;
  string line;
  string key;
  std::ifstream stream(kProcDirectory+kStatFilename); //stat
  //If we are able to open the file
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      
      int user, nice, idle, iowait, irq, softirq, steal, guest, guest_nice;
      //Uise enum maybe  from header ?
      while(linestream >> key >> user >> nice >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice){
        if(key == "cpu"){
          //Done this a really horrible way, a nice for loop of some kind would be ideal but can't think how to do it...
          data.emplace_back(std::to_string(user));
          data.emplace_back(std::to_string(nice));
          data.emplace_back(std::to_string(idle));
          data.emplace_back(std::to_string(iowait));
          data.emplace_back(std::to_string(irq));
          data.emplace_back(std::to_string(softirq));
          data.emplace_back(std::to_string(steal));
          data.emplace_back(std::to_string(guest));
          data.emplace_back(std::to_string(guest_nice));
        } 
      }
    }
  }
  //returns vector to be used in processor.cpp
return data;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int processes = 0;
  string line, key, processesVal;
  std::ifstream stream(kProcDirectory + kStatFilename); //stat file
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> processesVal){
        if(key == "processes"){
          processes = std::stol(processesVal);
        }
      }
    }
  }
  return processes; 

 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

  int processes = 0;
  string line, key, processesVal;
  std::ifstream stream(kProcDirectory + kStatFilename); //stat file
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> processesVal){
        if(key == "procs_running"){
          processes = std::stol(processesVal);
        }
      }
    }
  }
  return processes; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
   //return string(); 
   string value;
   std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
   if(filestream.is_open()){
     std::getline(filestream, value);
     return value;
   }
   return value;
   }

   vector<float> LinuxParser::CpuUtilization(int pid){
     vector<float> cpuValues{};
     string line, value;
     float time;
     std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
     if(filestream.is_open()){
       while(std::getline(filestream, line)){
         std::istringstream linestream(line);
         for(int i = 1; i <= kStarttime;i++){
           linestream>>value;

           if(i == kUtime||i == kStime||i == kCutime||i == kCstime||i == kStarttime){
             time = std::stof(value)/sysconf(_SC_CLK_TCK);
             cpuValues.emplace_back(time);
           }
         }
       }
     }
     return cpuValues;
   }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
   //return string(); 
   string line,key,value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){

      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream>>key>>value){
        if(key=="VmSize"){
          return value;
        }
      }
    }
  }
    return value;
   }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
   //return string();
  //declare vars
   string line,key,value;
   //path
   std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
   if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::replace(line.begin(),line.end(), ':', ' ');
       std::istringstream linestream(line);
       while(linestream>>key>>value){
         if(key=="Uid"){
           return value;
         }
       }
     }
   } 
   return value;
   }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
   //return string(); 
   string uid = Uid(pid);
   string line,key,value,blank;
   std::ifstream filestream(kPasswordPath);
   if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::replace(line.begin(), line.end(), ':', ' ');
       std::istringstream linestream(line);
       while(linestream>>value>>blank>>key){
         if(key == uid){
           return value;
         }
       }
     }
   }
return value;
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
   //return 0;
   string line, value;
   long time;
   vector<string> vals;
   std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
   if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream>>value){
vals.push_back(value);
    }
         }

         try{
           //Need to subtract the value from the system uptime
           long computerTimeSeconds = UpTime();

           time = stol(vals[21])/sysconf(_SC_CLK_TCK); //in seconds

           time = computerTimeSeconds - time;
           
         } catch(...){
           time = 0;
         }
       return time;
       
     
   }
