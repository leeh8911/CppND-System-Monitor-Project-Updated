/* Copyright */
#include "include/system.h"

#include <unistd.h>

#include <cstddef>
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
float System::MemoryUtilization() { return 0.0; }

// TODO(@sangwon): Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO(@sangwon): Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO(@sangwon): Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO(@sangwon): Return the number of seconds since the system started running
long int System::UpTime() { return 0; }

System::System() {}