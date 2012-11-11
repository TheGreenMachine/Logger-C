#include <string>
#include <stdexcept>
#include "file_handler.hpp"

using namespace al;

file_handler::file_handler(const std::string& file):stream(file.c_str()){
  if(!stream)
    throw std::runtime_error("Unable to open file: " + file);
}

void file_handler::handle(level l, const std::string& name, const std::string& message){
  stream<<to_string(l)<<','<<name<<','<<message<<std::endl;
}

void file_handler::handle(level l, const std::string& time, const std::string& name, const std::string& message){
  stream<<to_string(l)<<','<<time<<','<<name<<','<<message<<std::endl;
}

void file_handler::handle(const std::string& message){
  stream<<message<<std::endl;
}
