#ifndef LOGGER_CREATOR_H
#define LOGGER_CREATOR_H

#include <list>
#include <memory>
#include "logger.hpp"
#include "handlers/handler.hpp"
#include "levels.hpp"

namespace al{
  
  /**
   * This class should be used to specify the settings of a logger or loggers
   * and then to generate them.
   */
  class logger_creator{
    public:
      /**
       * creates a default logger, the initial ignore level is none
       */
      logger_creator():ignore_level(level::none) {}

      /**
       * This adds a new handler to the list of handlers. This will NOT
       * affect previously generated loggers, but will affect any loggers
       * generated after this call.
       */
      logger_creator& add_handler(handler *new_handler){
        handler_list.push_back(std::shared_ptr<handle>(new_handler));
        return *this;
      }

      /**
       * This sets the ignore level on any loggers generated after this call.
       * It will NOT affect any previously created loggers.
       */
      logger_creator& set_ignore(level level){
        ignore_level = level;
        return *this;
      }

      /**
       * Generates a new logger with the current list of handlers, the current
       * ignore level and the suppplied name
       */
      logger spawn(std::string&& name){
        return logger(handler_list, ignore_level, name); 
      }


      virtual ~logger_creator(){}
    protected:
      std::list<std::shared_ptr<handler>> handler_list;
      level ignore_level;
  };
}
#endif
