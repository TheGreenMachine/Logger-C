#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <string>
#include <memory>
#include "levels.hpp"
#include "handlers/handler.hpp"

namespace al{

  /**
   * @Class end
   * @brief A simple empty class that should be used to signal the end of a log entry
   */
  class end{};

  extern end endl;

  /**
   * @Class logger
   *@brief logger is a class which accepts log messages with the << operator or through a member function called log. It then passes the message off to its predetermined handlers.
   */
  class logger{
    public:
      /**
       * This constructs a logger with a list of handlers, an ignore level
       * and a name.
       *
       * @param handlers The list of handlers to be attached to this logger.
       * @param ignore The ignore level for the logger.
       * @param logger_name The name that will appear in logs to identify this class.
       * @param t Determines whether the logger is timestamped.
       */
      logger(const std::list<std::shared_ptr<handler>>& handlers, level ignore,
          const std::string& logger_name, bool t):
        ignore_level(ignore), handler_list(handlers), name(logger_name),
        is_timestamped(t), current_level(level::info){}

      /**
       * Logs the message with all of the registered handlers
       */
      virtual void log(level, const std::string&);

      /**
       * Sets the level of the current message to a new level
       */
      virtual logger& operator<<(level);

      /**
       * Appends the string to the current message
       */
      virtual logger& operator<<(const std::string&);

      /**
       * Logs the current message
       *
       * Note that here the end object **is a dummy**. It has no intrinsic meaning other than to
       * ensure that this overload is called.
       */
      virtual logger& operator<<(end);

      virtual ~logger(){}
    protected: 

      const std::string get_timestamp();

    private:
        const level ignore_level;
        const std::list<std::shared_ptr<handler>>& handler_list;
        const std::string name;
        const bool is_timestamped;

        std::string message;
        level current_level;
  };
}

#endif
