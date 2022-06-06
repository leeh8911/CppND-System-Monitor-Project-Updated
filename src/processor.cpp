/* Copyright */
#include "include/processor.h"

#include <string>

#include "include/linux_parser.h"

using std::stof;

float Processor::Utilization() {
  return stof(LinuxParser::CpuUtilization()[0]);
}