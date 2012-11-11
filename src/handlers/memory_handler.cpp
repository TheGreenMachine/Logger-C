#include "memory_handler.hpp"

using namespace al;

memory_handler::memory_handler(size_t bsize, std::shared_ptr<handler> exit)
  :exit_handler(exit), size(bsize){}

memory_handler::memory_handler(size_t bsize, handler* exit)
  :exit_handler(exit), size(bsize){}

//name
void memory_handler::handle(level l,const std::string& name,const std::string& message){
  if(size == buffer.size()){
    buffer.pop_front();
  }
  buffer.emplace_back(l, name, message);
}

//time
void memory_handler::handle(level l,const std::string& time,const std::string& name,const std::string& message){
  if(size == buffer.size()){
    buffer.pop_front();
  }
  buffer.emplace_back(l, time, name, message);
}

//raw
void memory_handler::handle(const std::string& message){
  if(size == buffer.size()){
    buffer.pop_front();
  }
  buffer.emplace_back(message);
}

memory_handler::~memory_handler(){
  for(const auto& entry : buffer){
    try{
      switch(entry.type){
        case log_entry::message_type::name_stamped: 
          exit_handler->handle(entry.l, entry.name, entry.message);
          break;
        case  log_entry::message_type::time_stamped:
          exit_handler->handle(entry.l,entry.time, entry.name, entry.message);
          break;
        case  log_entry::message_type::raw:
          exit_handler->handle(entry.message);
          break;
      }
    }
    catch(...){
      return; //Exception thrown! bail out!
    }
  }
}
