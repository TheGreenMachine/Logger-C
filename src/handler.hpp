#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "levels.hpp"

namespace al{
  
  class handler{
    public:
      virtual void handle(level, const string& name, const string& message)=0;
  };
}

#endif
