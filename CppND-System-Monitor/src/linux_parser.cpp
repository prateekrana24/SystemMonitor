#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;

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
  string line, name;
  float mem_value, memTotal, memFree, memAvailable;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> name >> mem_value;
      if (name == "MemTotal:") {
      	memTotal = mem_value;
      }
      if (name == "MemFree:") {
      	memFree = mem_value;
      }
      if (name == "MemAvailable:") {
      	memAvailable = mem_value;
      }   
  	 }
 	}
   return (memAvailable - memFree) / memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long uptime1, uptime2;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> uptime1 >> uptime2;
      
  	 }
 	}
   return uptime1 + uptime2;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  string line, cpu;
  long user, nice, system, idle, iowait, irq, softirq, total_jiff;
  std::ifstream filestream(kProcDirectory + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
      total_jiff = user + nice + system + idle + iowait + irq + softirq;
  	 }
 	}
   return total_jiff;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  long utime, stime, cutime, cstime, pid_activejiff;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
   
      if (linestream >> line[15]) {
        utime = line[15];
      }
      
      if (linestream >> line[16]) {
        stime = line[16];
      }
      
      if (linestream >> line[17]) {
        cutime = line[17];
      }
      
      if (linestream >> line[18]) {
        cstime = line[18];
      }
      
  	 }
 	}
   pid_activejiff = utime + stime + cutime + cstime;
   return pid_activejiff;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line, cpu;
  long user, nice, system, active_jiff;
  std::ifstream filestream(kProcDirectory + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> cpu >> user >> nice >> system;
      active_jiff = user + nice + system;
  	 }
 	}
   return active_jiff;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line, cpu;
  long user, nice, system, idle, iowait, irq, softirq, idle_jiff;
  std::ifstream filestream(kProcDirectory + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
      idle_jiff = idle + iowait;
  	 }
 	}
   return idle_jiff; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> contain;
  string line, cpu_name, cpu_data;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> cpu_name;
  	  
      while (linestream >> cpu_data) {
      	contain.emplace_back(cpu_data);
      }
     
  	 }
 	}
  return contain;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string process, line;
  int process_value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> process;
      if (process == "processess") {
      	linestream >> process_value;
      }
  	 }
 	}
   return process_value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string process_running, line;
  int process_running_val;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
  	  linestream >> process_running;
      if (process_running == "procs_running") {
      	linestream >> process_running_val;
      }
  	 }
 	}
   return process_running_val;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line, address;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> address;
    }
  }
  return address;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, address, proc_mem;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> address;
      if (address == "VmSize:") {
      	linestream >> proc_mem; 
      }
    }
  }
  return proc_mem;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, uid_name, address;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> address;
      if (address == "Uid:") {
      	linestream >> uid_name; 
      }
    }
  }
  return uid_name;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, username, address;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> address;
      if (address == "Name:") {
      	linestream >> username; 
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, username, address;
  long proc_uptime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> address;
      if (linestream >> line[24]) {
      	proc_uptime = line[24];
      }
    }
  }
  return proc_uptime;
}
