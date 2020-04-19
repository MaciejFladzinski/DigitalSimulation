#include "logger.h"

#include <iostream>
#include <fstream>

Logger::Logger()
{
  
}

Logger::~Logger()
{
  
}

void Logger::Info(std::string message)
{
  // add better text format (sprintf etc.)

  // write to file
  std::ofstream save("Save.txt");

  if (level_ != Level::Error)
  {
    std::cout << "[Info] " << message << std::endl;

    save << "[Info] " << message << std::endl;
    save.close();
  }
}

void Logger::Debug(std::string message)
{
  
}

void Logger::Error(std::string message)
{
  // add to file
  std::ofstream save("Save.txt", std::ios_base::app);

  std::cout << "[Error] " << message << std::endl;

  save << "[Error] " << message << std::endl;
  save.close();
}
