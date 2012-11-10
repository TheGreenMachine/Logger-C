#ifndef LOGGER_CREATOR_H
#define LOGGER_CREATOR_H

#include <list>
#include <memory>
#include "logger.hpp"
#include "handler.hpp"
#include "levels.hpp"

namespace al{
  
  class logger_creator{
    public:
      logger_creator():ignore_level(level::none) {}

      logger_creator& add_handler(std::shared_ptr<handler> new_handler){
        handler_list.push_back(new_handler);
        return *this;
      }

      logger_creator& set_ignore(level level){
        ignore_level = level;
        return *this;
      }

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
