#ifndef CERR_HANDLER_H
#define CERR_HANDLER_H

#include "handler.hpp"
#include <iostream>

namespace al{
  class cerr_handler : public handler{
    void handle(level l, const std::string& name, const std::string& message){
      std::cerr<<"("<< to_string(l) << ") "<<name<<" : "<<message<<std::endl;
    }
  };
}

#endif
