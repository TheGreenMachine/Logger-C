#ifndef LOGGER_CREATOR_H
#define LOGGER_CREATOR_H

#include <vector>
#include "logger.hpp"
#include "handlers/handler.hpp"
#include "levels.hpp"
#include "ptr_utils/smart_ptr.hpp"

namespace al{
  
  /**
   * @Class logger_creator
   * @brief This class should be used to specify the settings of a logger or loggers and then to generate them.
   */
  template<typename T>
  class logger_creator{
    public:
      /**
       * creates a default logger, the initial ignore level is none
       * 
       */
      logger_creator():
        ignore_level(none),
        is_timestamped(true) {}

      /**
       * This adds a new handler to the list of handlers. This will NOT
       * affect previously generated loggers, but will affect any loggers
       * generated after this call.
       *
       * @param new_handler The handler that will be added.
       */
      logger_creator& add_handler(const smart_ptr<handler>& new_handler){
        handler_list.push_back(new_handler);
        return *this;
      }

      /**
       * This adds a new handler to the list of handlers. This will NOT
       * affect previously generated loggers, but will affect any loggers
       * generated after this call.
       *
       * @param new_handler The handler that will be added.
       */
      logger_creator& add_handler(handler* new_handler){
        handler_list.push_back(smart_ptr<handler>(new_handler));
        return *this;
      }

      /**
       * Decides whether log entries should have a time stamp on any loggers generated after this call.
       * It will NOT affect any previously created loggers.
       *
       * @param t true if there should be a timestamp
       */
      logger_creator& timestamped(bool t){
        is_timestamped = t;
        return *this;
      }

      /**
       * This sets the ignore level on any loggers generated after this call.
       * It will NOT affect any previously created loggers.
       *
       * @param l The level that will be the new ignore level.
       */
      logger_creator& set_ignore(const level& l){
        ignore_level = l;
        return *this;
      }

      /**
       * Generates a new logger with the current list of handlers, the current
       * ignore level and the suppplied name
       */
      T spawn(const std::string& name){
        return T(handler_list, ignore_level, name, is_timestamped); 
      }


      virtual ~logger_creator(){}
    protected:
      std::vector<smart_ptr<handler> > handler_list;
      level ignore_level;
      bool is_timestamped;
  };

  /**
   * Defines std_creator to be the normal logger_creator
   */
  typedef logger_creator<logger> std_creator;
}
#endif
