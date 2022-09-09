#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  float agg_cpu;
  
  totjiff_ = LinuxParser::Jiffies();
  actjiff_ = LinuxParser::ActiveJiffies();
  idlejiff_ = LinuxParser::IdleJiffies();
  
  //float diff = float(totjiff_) - (float(actjiff_) + float(idlejiff_));
  
  agg_cpu = (float(actjiff_) + float(idlejiff_)) / float(totjiff_);
  //agg_cpu = diff / float(totjiff_); 
  
  return agg_cpu;
}