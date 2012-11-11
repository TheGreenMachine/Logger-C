#ifndef CERR_HANDLER_H
#define CERR_HANDLER_H

#include "handler.hpp"
#include <iostream>

namespace al{
  /**
   * @Class cerr_handle
   * @brief A simple handler, it prints all log entries to cerr.
   *
   * The messages are of the form "(level) time, name : message" for easy readability.
   */
  class cerr_handler : public handler{
    public: 
      void handle(level l, const std::string& name, const std::string& message){
        std::cerr<<"("<< to_string(l) << ") "<<name<<" : "<<message<<std::endl;
      }

      void handle(level l, const std::string& time, const std::string& name, const std::string& message){
        std::cerr<<"("<< to_string(l) << ") "<<time<<", "<<name<<" : "<<message<<std::endl;
      }

      void handle(const std::string& message){
        std::cerr<<message<<std::endl;
      }
  };
}
#endif
