#include "../al.hpp"
using namespace al;

logger foo(){
  std_creator factory;

  factory.add_handler(smart_ptr<handler>(new cerr_handler()));
  smart_ptr<handler> h = smart_ptr<handler>(new file_handler("log"));
  factory.add_handler(h);
  factory.add_handler(smart_ptr<handler>(new memory_handler(10, h)));
  factory.add_handler(smart_ptr<handler>(new rolling_handler("logs", 3, 2)));
  factory.spawn("temp")<<"Hello from a temporary"<<endl;
  factory.timestamped(false);
  return factory.spawn("test");
}

int main(){
 
  logger log = foo();

  for(int i = 0; i<25; ++i)
    log<<i<<endl;
}
