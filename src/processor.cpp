/* Copyright */
#include "include/processor.h"

#include <string>

#include "include/linux_parser.h"

using std::stof;
// TODO(@sangwon): Return the aggregate CPU utilization
float Processor::Utilization() {
  return stof(LinuxParser::CpuUtilization()[0]);
}