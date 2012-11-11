#include "rotator.hpp"
#include <string>
#include <stdexcept>
#include <cstdio> //Awaiting std::file_system
#include <sstream>

using namespace al::file_manipulator;

rotator::rotator(const std::string& name, size_t max_e, size_t max_f)
  :file_root(name), entries(max_e), files(max_f), curr_entry(0),
   curr_file(0), stream(name.c_str()){

    if(!stream)
      throw std::runtime_error("Unable to open file " +file_root);
  }

void rotator::write(const std::string& entry){
  if(++curr_entry>=entries){
    curr_entry = 0;
    rotate();
  }
    stream<<entry;
}

void rotator::rotate(){
  using std::string; //Saving some finger work
  using std::rename;
  using std::remove;
  using std::to_string;
  using std::runtime_error;

  stream.close();

  ++curr_file;
  curr_file = (curr_file>files-1) ? (files-1) : curr_file;

  for(size_t file_n=curr_file-1; file_n>0; --file_n){
    string future = file_root + to_string(file_n+1);

    if(file_n == files){
      future = file_root;
    }

    string original = file_root+to_string(file_n);
    if( rename(original.c_str(), future.c_str()) )//A zero return is success.
      throw runtime_error("Unable to rename "+original+" to "+future);
  }

  string future = file_root + to_string(1);

  if( rename(file_root.c_str(), future.c_str()) ) 
    throw runtime_error("Unable to rename "+file_root+" to "+future);

  stream.open(file_root);
}
