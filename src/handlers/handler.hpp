#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "../levels.hpp"

namespace al{
  
  /**
   * @Class handler
   * @brief An abstract base class for all handler classes.
   */
  class handler{
    public:
      /**
       * This is the method called to handle a log entry.
       * @param l The level of the entry.
       * @param name The name of the logger that generated it.
       * @param message The actual text of the entry
       */
      virtual void handle(level l, const std::string& name, const std::string& message)=0;

      virtual ~handler(){}
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
