#include "logger_creator.hpp"
#include "logger.hpp"
#include "handlers/cerr_handler.hpp"
#include <memory>
using namespace al;

int main(){
  logger_creator factory;
  factory.add_handler(std::make_shared<cerr_handler>());

  auto log = factory.spawn("test");

  log<<end();
  log<<"Messages"<<endl;
  log<<end();
  log<<"More Messages"<<endl;
  log<<end();
}
