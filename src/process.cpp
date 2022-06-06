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

int16_t Process::Pid() const { return pid_; }

float Process::CpuUtilization() const {
    return LinuxParser::CpuUtilization(Pid());
}

string Process::Command() { return LinuxParser::Command(Pid()); }

string Process::Ram() { return LinuxParser::Ram(Pid()); }

string Process::User() { return LinuxParser::User(Pid()); }

int32_t Process::UpTime() { return LinuxParser::UpTime(Pid()); }

bool Process::operator<(Process const& a) const {
    return a.CpuUtilization() < CpuUtilization();
}
