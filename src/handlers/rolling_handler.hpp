#ifndef ROLLING_HANDLER_H
#define ROLLING_HANDLER_H
#include "handler.hpp"
#include "file_manipulators/rotator.hpp"

namespace al{
  
  /**
   * @Class rolling_handler
   * @brief A handler front end for the rotator class
   */
  class rolling_handler : public handler{
    public:

      /**
       * @param name The base name for the log files.
       * @param max_e The maximum number of entries per file.
       * @param max_f the maximum number of files.
       */
      rolling_handler(const std::string& name, size_t max_e, size_t max_f)
        :rotate(name, max_e, max_f) {}

      /**
       * Writes the appropriate information in csv form using a rotator.
       * @param l The level of the entry.
       * @param name The name of the logger which created it.
       * @param message The actual message.
       */
      void handle(level l, const std::string& name, const std::string& message){
        rotate.write(to_string(l)+","+name+","+message);
      }
      
    private:
      file_manipulator::rotator rotate;

  };
}

#endif
