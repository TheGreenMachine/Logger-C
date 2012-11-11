#include "memory_handler.hpp"

using namespace al;

memory_handler::memory_handler(size_t bsize, std::shared_ptr<handler> exit)
  :exit_handler(exit), size(bsize){}

memory_handler::memory_handler(size_t bsize, handler* exit)
  :exit_handler(exit), size(bsize){}

void memory_handler::handle(level l,const std::string& name,const std::string& message){
  if(size == buffer.size()){
    buffer.pop_front();
  }
  buffer.push_back(std::move(log_entry(l, name, message)));
}

memory_handler::~memory_handler(){
  for(const auto& entry : buffer){
    try{
      exit_handler->handle(entry.l, entry.name, entry.message);
    }
    catch(...){
      return; //Exception thrown! bail out!
    }
  }
}
