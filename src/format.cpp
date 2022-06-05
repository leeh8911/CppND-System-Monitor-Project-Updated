/* Copyright */
#include "include/format.h"

#include <iostream>
#include <string>

using std::string;
using std::to_string;

// TODO(@sangwon): Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(int32_t seconds) {
  int32_t second = seconds % 60;
  seconds /= 60;
  int32_t minute = seconds % 60;
  int32_t hour = seconds / 60;

  string res =
      "" + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);

  return res;
}