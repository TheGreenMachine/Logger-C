#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <string>
#include <memory>
#include "levels.hpp"
#include "handlers/handler.hpp"

namespace al{

  class end{};

  class logger{
    public:
      logger(const std::list<std::shared_ptr<handler>>& handlers, level ignore,
          const std::string& logger_name):
        ignore_level(ignore), handler_list(handlers), name(logger_name), current_level(level::info){}

      void log(level, const std::string&);

      logger& operator<<(level);
      logger& operator<<(const std::string&);
      logger& operator<<(end);

    private:
        level ignore_level;
        const std::list<std::shared_ptr<handler>>& handler_list;
        const std::string name;

        std::string message;
        level current_level;
  };
}

#endif
