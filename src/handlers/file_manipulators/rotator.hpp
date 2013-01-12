#ifndef ROTATOR_H
#define ROTATOR_H
#include <string>
#include <fstream>
#include <sstream>

namespace al{
  namespace file_manipulator{

    /**
     * @Class rotator
     * @brief A simple class designed so that a circular buffer can be imitated with reasonable speed.
     *
     * This takes in strings and writes them into the files
     * name name1 name2 ... namen
     * such that if enough elements are written everything will be renamed and namen will be overwritten with new entries.
     */
    class rotator{
      public:
        /**
         * @param name The name that files will formed on.
         * @param max_e The maximum number of entries in 1 file.
         * @param max_f The maximum number of files.
         */
        rotator(const std::string& name, size_t max_e, size_t max_f);

        /**
         * Takes in a string and writes it to the correct file. Renaming files as needed.
         * @param entry The string which will be written to the appropriate file.
         */
        void write(const std::string& entry);


      private:
        std::string file_root;
        size_t entries;
        size_t files;
        size_t curr_entry;
        size_t curr_file;
        std::ofstream stream;
        void rotate();
    };
  }
  #include "rotator.hpp"
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
      stream<<entry<<"\n";
  }

  void rotator::rotate(){
    using std::string; //Saving some finger work
    using std::stringstream;
    using std::rename;
    using std::remove;
    using std::runtime_error;

    stream.close();

    ++curr_file;
    curr_file = (curr_file>files-1) ? (files-1) : curr_file;

    for(size_t file_n=curr_file-1; file_n>0; --file_n){
      stringstream converter;
      converter<<file_n+1;
      string future = file_root + converter.str();

      if(file_n == files){
        future = file_root;
      }

      converter.ignore();
      converter << file_n;
      string original = file_root+converter.str();
      if( rename(original.c_str(), future.c_str()) )//A zero return is success.
        throw runtime_error("Unable to rename "+original+" to "+future);
    }

    string future = file_root + "1";

    if( rename(file_root.c_str(), future.c_str()) ) 
      throw runtime_error("Unable to rename "+file_root+" to "+future);

    stream.open(file_root.c_str());
  }
}
#endif
