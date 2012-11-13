#include <string>
#include "logger_creator.hpp"
#include "logger.hpp"
#include "handlers/cerr_handler.hpp"
#include "handlers/file_handler.hpp"
#include "handlers/memory_handler.hpp"
#include "handlers/rolling_handler.hpp"
#include <memory>
using namespace al;

logger foo(){

  std_creator factory;
  //factory.add_handler(std::make_shared<cerr_handler>());
  //auto h = std::make_shared<file_handler>("log");
  //factory.add_handler(h);
  //factory.add_handler(std::make_shared<memory_handler>(10, h));
  factory.add_handler(std::make_shared<rolling_handler>("logs", 3, 2));
  return factory.spawn("test");
}

int main(){
 
  auto log = foo();

  for(int i = 0; i<25; ++i)
    log<<std::to_string(i)<<endl;
}
