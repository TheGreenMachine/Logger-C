#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "../levels.hpp"

namespace al{
  
  class handler{
    public:
      virtual void handle(level, const std::string& name, const std::string& message)=0;
    protected:
      virtual std::string to_string(level l){
        switch(l){
          case level::none: return "none";
          case level::info: return "info";
          case level::debug: return "debug";
          case level::warning: return "warning";
          case level::nonfatal_error: return "nonfatal_error";
          case level::fatal_error: return "fatal_error";
        }
      }
  };
}

#endif
