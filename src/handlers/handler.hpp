#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "../levels.hpp"

namespace al{
  
  /**
   * An abstract base class for all handler classes.
   */
  class handler{
    public:
      /**
       * This is the method called to handle a log entry.
       * level is the level of the entry.
       * name is the name of the logger that generated it.
       * message is the actual text of the entry
       */
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
