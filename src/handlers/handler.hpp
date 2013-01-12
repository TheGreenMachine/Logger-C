#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <stdexcept>
#include "../levels.hpp"
#include "../ptr_utils/smart_ptr.hpp"

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

      /**
       * This is the method called to handle a log entry. It handles timestamps.
       * @param l The level of the entry.
       * @param name The name of the logger that generated it.
       * @param timestamp The time indicating when the log message was entered.
       * @param message The actual text of the entry
       */
      virtual void handle(level l, const std::string& name,
          const std::string& timestamp, const std::string& message)=0;

      /**
       * This is the method called to handle a log entry. It is meant for people who want a custom log format.
       * @param message The raw text of the entry
       */
      virtual void handle(const std::string& message)=0;


      virtual ~handler(){}
    protected:
      /**
       * Potentially throws runtime_error if an unrecognized option is passed.
       * Should be impossible
       */
      virtual std::string to_string(level l){
        switch(l){
          case none          : return "          none";
          case info          : return "          info";
          case debug         : return "         debug";
          case warning       : return "       warning";
          case nonfatal_error: return "nonfatal_error";
          case fatal_error   : return "   fatal_error";
          default: throw std::runtime_error("Unrecognized type");
        }
        return "";
      }
  };
}
#endif
