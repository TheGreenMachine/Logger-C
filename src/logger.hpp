#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <string>
#include <memory>
#include "levels.hpp"
#include "handlers/handler.hpp"

namespace al{

  /**
   * A simple empty class that should be used to signal the end of a log entry
   */
  class end{} endl;

  /**
   *logger is a class which accepts log messages with the << operator or through
   *a member function called log. It then passes the message off to its predetermined handlers.
   */
  class logger{
    public:
      /**
       * This constructs a logger with a list of handlers, an ignore level
       * and a name.
       */
      logger(const std::list<std::shared_ptr<handler>>& handlers, level ignore,
          const std::string& logger_name):
        ignore_level(ignore), handler_list(handlers), name(logger_name), current_level(level::info){}

      /**
       * Logs the message with all of the registered handlers
       */
      void log(level, const std::string&);

      /**
       * Sets the level of the current message to a new level
       */
      logger& operator<<(level);

      /**
       * Appends the string to the current message
       */
      logger& operator<<(const std::string&);

      /**
       * logs the current message
       */
      logger& operator<<(end);

      virtual ~logger(){}
    private:
        level ignore_level;
        const std::list<std::shared_ptr<handler>>& handler_list;
        const std::string name;

        std::string message;
        level current_level;
  };
}

#endif
