#include "src/logger_creator.hpp"
#include "src/logger.hpp"
#include "src/handlers/cerr_handler.hpp"
#include "src/handlers/file_handler.hpp"
#include "src/handlers/memory_handler.hpp"
#include "src/handlers/rolling_handler.hpp"
#include <memory>
using namespace al;

logger foo(){
  std_creator factory;

  factory.add_handler(smart_ptr<handler>(new cerr_handler()));
  smart_ptr<handler> h = smart_ptr<handler>(new file_handler("log"));
  factory.add_handler(h);
  factory.add_handler(smart_ptr<handler>(new memory_handler(10, h)));
  factory.add_handler(smart_ptr<handler>(new rolling_handler("logs", 3, 2)));
  factory.spawn("temp")<<"Hello from a temporary"<<endl();
  return factory.spawn("test");
}

int main(){
 
  logger log = foo();

  for(int i = 0; i<25; ++i)
    log<<i<<endl();
}
