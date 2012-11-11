#include "logger.hpp"
#include <ctime>
using namespace al;

al::end al::endl;

void logger::log( level l, const std::string& message){
  if(l<ignore_level){
    return;
  }

  for(auto h : handler_list){
    if(is_timestamped){
      h->handle(l,get_timestamp(), name, message);
    }
    else{
      h->handle(l, name, message);
    }
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

const std::string logger::get_timestamp(){
  time_t now;
  time(&now);
  std::string time(ctime(&now));
  return time.substr(0, time.length()-1); //remove the trailing (and annoying) newline
}
