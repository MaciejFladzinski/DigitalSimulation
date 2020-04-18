#include "logger.h"

#include <iostream>

Logger::Logger()
{
  
}

Logger::~Logger()
{
  
}

void Logger::Info(std::string message)
{
  // login in to file
  // add better text format (sprintf etc.)

  if (level_ != Level::Error)
  {
    std::cout << "[Info] " << message << std::endl;
  }
}

void Logger::Debug(std::string message)
{
  
}

void Logger::Error(std::string message)
{
  if (level_ != Level::Error)
  {
    std::cout << "[Error] " << message << std::endl;
  }
}
