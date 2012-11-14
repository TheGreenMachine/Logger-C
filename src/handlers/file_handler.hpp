#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <fstream>
#include <string>
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

  #include <stdexcept>


  file_handler::file_handler(const std::string& file):stream(file.c_str()){
    if(!stream)
      throw std::runtime_error("Unable to open file: " + file);
  }

  void file_handler::handle(level l, const std::string& name, const std::string& message){
    stream<<to_string(l)<<','<<name<<','<<message<<std::endl;
  }

  void file_handler::handle(level l, const std::string& time, const std::string& name, const std::string& message){
    stream<<to_string(l)<<','<<time<<','<<name<<','<<message<<std::endl;
  }

  void file_handler::handle(const std::string& message){
    stream<<message<<std::endl;
  }

}

#endif
