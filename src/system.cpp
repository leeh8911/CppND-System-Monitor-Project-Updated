/* Copyright */
#include "include/system.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "include/linux_parser.h"
#include "include/process.h"
#include "include/processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO(@sangwon): Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO(@sangwon): Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO(@sangwon): Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO(@sangwon): Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO(@sangwon): Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO(@sangwon): Return the number of processes actively running on the system
int16_t System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO(@sangwon): Return the total number of processes on the system
int16_t System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO(@sangwon): Return the number of seconds since the system started running
int32_t System::UpTime() { return LinuxParser::UpTime(); }

System::System() {}