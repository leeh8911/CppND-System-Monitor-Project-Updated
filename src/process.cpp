/* Copyright */
#include "include/process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// TODO(@sangwon): Return this process's ID
int Process::Pid() { return 0; }

// TODO(@sangwon): Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO(@sangwon): Return the command that generated this process
string Process::Command() { return string(); }

// TODO(@sangwon): Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO(@sangwon): Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO(@sangwon): Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO(@sangwon): Overload the "less than" comparison operator for Process
// objects REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}