#include "logger.h"

#include <iostream>
#include <fstream>

Logger::Logger()
{
  // open file
  std::ofstream save("Save.txt");
  printf("Logger has been created \n");
}

Logger::~Logger()
{
  printf("Logger has been removed \n");
}

void Logger::set_level()
{
  // user will choose the logger type, but for now this option will not be called
  int logger_type = 0;
  printf("Choose: 1. Info, 2. Error, 3. Info & Error \n");
  std::cin >> logger_type;
  std::cout << std::endl;

  switch (logger_type)
  {
  case 1:
    level_ = Level::Info;
    break;
  case 2:
    level_ = Level::Error;
    break;
  case 3:
    level_ = Level::Debug;
    break;
  default:
    printf("Wrong value selected ! \n");
    set_level();  // try again
  }
}

void Logger::Info(std::string message)
{
  // add to file
  std::ofstream save("Save.txt", std::ios_base::app);

  if (level_ != Level::Error)
  {
    std::cout << "[Info] " << message << std::endl;

    save << "[Info] " << message << std::endl;
    save.close();
  }
}

void Logger::Debug(std::string message)
{
  // add to file
  std::ofstream save("Save.txt", std::ios_base::app);

  if (level_ != Level::Error)
  {
    std::cout << "[Info] " << message << std::endl;

    save << "[Info] " << message << std::endl;
  }
  else
  {
    std::cout << "[Error] " << message << std::endl;

    save << "[Error] " << message << std::endl;
  }

  save.close();
}

void Logger::Error(std::string message)
{
  // add to file
  std::ofstream save("Save.txt", std::ios_base::app);

  std::cout << "[Error] " << message << std::endl;

  save << "[Error] " << message << std::endl;
  save.close();
}
