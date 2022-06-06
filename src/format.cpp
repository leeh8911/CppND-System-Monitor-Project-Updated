/* Copyright */
#include "include/format.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(int32_t seconds) {
  int32_t second = seconds % 60;
  seconds /= 60;
  int32_t minute = seconds % 60;
  int32_t hour = seconds / 60;

  stringstream ss("");
  ss << std::setfill('0') << std::setw(2) << hour << ":" << minute << ":"
     << second;

  return ss.str();
}
