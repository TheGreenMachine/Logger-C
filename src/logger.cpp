#include "logger.hpp"
using namespace al;

void logger::log( level l, const std::string& message){
  if(l<ignore_level){
    return;
  }

  for(auto h : handler_list){
    h->handle(l, name, message);
  }
}

logger& logger::operator<<(level l){
  current_level = l;
  return *this;
}

logger& logger::operator<<(const std::string& input){
  message+=input;
  return *this;
}

logger& logger::operator<<(end){
  log(current_level, message);
  current_level = level::info;
  message = "";
  return *this;
}
