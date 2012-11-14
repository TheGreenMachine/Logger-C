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
       * Appends the long to the current message
       */
      virtual logger& operator<<(const int&);
      /**
       * Appends the long to the current message
       */
      virtual logger& operator<<(const long&);
      /**
       * Appends the double to the current message
       */
      virtual logger& operator<<(const double&);
      /**
       * Appends the char to the current message
       */
      virtual logger& operator<<(const char&);

      /**
       * Appends the T instance to the current message
       * This uses a string stream to convert it.
       * IT WILL FAIL FOR TYPES WITHOUT AN operator<<(stringstream&, T) of some type
       */

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
        const std::list<std::shared_ptr<handler>> handler_list;
        const std::string name;
        const bool is_timestamped;

        std::string message;
        level current_level;

        template<typename T>
        logger& add_input(const T&);
  };

  #include <ctime>
  #include <sstream>

  al::end al::endl;

  void logger::log( level l, const std::string& message){
    if(l<ignore_level){
      return;
    }

    for(auto h : handler_list){
      if(is_timestamped){
        h->handle(l,get_timestamp(), name, message);
      }
      else{
        h->handle(l, name, message);
      }
    }
  }

  logger& logger::operator<<(level l){
    current_level = l;
    return *this;
  }

  template<typename T>
  logger& logger::add_input(const T& t){
    std::stringstream ss;
    ss<<t;
    return operator<<(ss.str());
  }

  logger& logger::operator<<(const int& input){
    return add_input(input);
  }
  logger& logger::operator<<(const double& input){
    return add_input(input);
  }
  logger& logger::operator<<(const char& input){
    return add_input(input);
  }
  logger& logger::operator<<(const long& input){
    return add_input(input);
  }
  logger& logger::operator<<(const std::string& input){
    message+=input;
    return *this;
  }

  logger& logger::operator<<(end){
    log(current_level, message);
    current_level = level::info;
    message = "";
    return *this;
  }

  const std::string logger::get_timestamp(){
    time_t now;
    time(&now);
    std::string time(ctime(&now));
    return time.substr(0, time.length()-1); //remove the trailing (and annoying) newline
  }

}

#endif
