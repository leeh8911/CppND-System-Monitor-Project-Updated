/* Copyright */
#include "include/process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "include/linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int16_t pid) : pid_(pid) {}

// TODO(@sangwon): Return this process's ID
int16_t Process::Pid() const { return pid_; }

// TODO(@sangwon): Return this process's CPU utilization
float Process::CpuUtilization() const {
  return LinuxParser::CpuUtilization(Pid());
}

// TODO(@sangwon): Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO(@sangwon): Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO(@sangwon): Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO(@sangwon): Return the age of this process (in seconds)
int32_t Process::UpTime() { return 0; }

// TODO(@sangwon): Overload the "less than" comparison operator for Process
// objects REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}