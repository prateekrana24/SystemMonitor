#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid(int pid) {
  p_ = pid;
  return p_;
}

// TODO: Return this process's ID
int Process::Pid() {
  return p_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  cpuUtil_ = float(LinuxParser::ActiveJiffies(p_)) / (float(LinuxParser::UpTime()) - float(LinuxParser::UpTime(p_)));
  return cpuUtil_; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
  s_ = LinuxParser::Command(p_);
  return s_; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  r_ = LinuxParser::Ram(p_);
  return r_;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  u_ = LinuxParser::User(p_);
  return u_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  up_ = LinuxParser::UpTime(p_);
  return up_; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return a.p_ < p_;
}