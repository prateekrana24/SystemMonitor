#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int p_;
  float cpuUtil_;
  std::string s_;
  std::string r_;
  std::string u_;
  long int up_;
};

#endif