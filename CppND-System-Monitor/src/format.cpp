#include <string>
#include <iostream>
#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
  long hour, min;
  string final_hour, final_min, final_seconds, final_time;
  
  hour = seconds / 3600; //seconds = 9630; hour = 2.675
  seconds = seconds % 3600; //seconds = 2430
  min = seconds / 60; //min = 40.5
  seconds = seconds % 60; //seconds = 30
  
  
  final_hour = to_string(hour);
  final_min = to_string(min);
  final_seconds = to_string(seconds);
  
  
  final_hour = (hour < 10) ? "0" + final_hour : final_hour;
  final_min = (min < 10) ? "0" + final_min : final_min;
  final_seconds = (seconds < 10) ? "0" + final_seconds : final_seconds;
  
  
  final_time = final_hour + ":" + final_min + ":" + final_seconds + "\n";
  
  
  return final_time;
}