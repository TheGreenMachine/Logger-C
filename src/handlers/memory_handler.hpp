#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H

#include <memory>
#include <deque>
#include "handler.hpp"

namespace al{

  /**
   * @Class memory_handler
   * @brief An in memory handler that flushes its entries to a specified handler on its destruction.
   */
  class memory_handler :public handler{
    public:
      /**
       * @param bsize The maximum number of entries to store in memory.
       * @param exit The handler which should be invoked on this objects destruction.
       */
      memory_handler(size_t bsize,std::shared_ptr<handler> exit);

      /**
       * @param bsize The maximum number of entries to store in memory.
       * @param exit The handler which should be invoked on this objects destruction.
       */
      memory_handler(size_t bsize,handler* exit);

      /**
       * Stores the entry in memory (currently a std::deque).
       * If the number of entries exceeds the expected maximum amount, the oldest is deleted.
       */
      void handle(const std::string&);
      /**
       * Stores the entry in memory (currently a std::deque).
       * If the number of entries exceeds the expected maximum amount, the oldest is deleted.
       */
      void handle(level,const std::string&,const std::string&,const std::string&);
      /**
       * Stores the entry in memory (currently a std::deque).
       * If the number of entries exceeds the expected maximum amount, the oldest is deleted.
       */
      void handle(level,const std::string&,const std::string&);

      /**
       * Passes every entry in the buffer to the specified handler.
       *
       * If an exception is thrown, it is caught silently and the destructor returns.
       */
      ~memory_handler();
    private:

      struct log_entry{

        log_entry(level lev, const std::string& n, const std::string& m)
          :type(message_type::name_stamped), l(lev), name(n), message(m) {}

        log_entry(level lev, const std::string& t, const std::string& n, const std::string& m)
          :type(message_type::time_stamped), l(lev),time(t), name(n), message(m) {}

        log_entry(const std::string& m)
          :type(message_type::raw), message(m) {}

        enum class message_type {
          name_stamped,
          time_stamped,
          raw
        } type;

        level l;
        const std::string time;
        const std::string name;
        const std::string message;
      };

      std::shared_ptr<handler> exit_handler;
      size_t size;
      std::deque<log_entry> buffer;
  };
}
#endif
