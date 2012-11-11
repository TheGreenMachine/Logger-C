#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <fstream> //A simple header which has forward declarations of all streams
#include "handler.hpp"

namespace al{

  /**
   * @Class file_handler
   * @brief The classic file logger, based on std::ofstream
   */
  class file_handler : public handler{
    public:
      /**
       * @param file The file name for the log file.
       * @exception std::runtime_error If the file is unable to be opened.
       */
      file_handler(const std::string& file);

      /**
       * Prints the message to the log file in csv form.
       *
       * "level,time,name,message"
       */
      void handle(level, const std::string&, const std::string&, const std::string&);

      /**
       * Prints the message to the log file in csv form.
       *
       * "level,name,message"
       */
      void handle(level, const std::string&, const std::string&);

      /**
       * Prints the message to the log file in csv form.
       *
       * "message"
       */
      void handle(const std::string&);

    private:
      std::ofstream stream;
  };
}

#endif
