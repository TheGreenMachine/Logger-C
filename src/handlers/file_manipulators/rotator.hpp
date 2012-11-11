#ifndef ROTATOR_H
#define ROTATOR_H
#include <string>
#include <fstream>

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
}
#endif
