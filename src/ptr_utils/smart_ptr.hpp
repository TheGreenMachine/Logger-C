#ifndef SMART_PTR_H
#define SMART_PTR_H

namespace al{

  template<typename T>
  class smart_ptr{
    public:

      //Constructors
      smart_ptr(T* p):copies(new int(1)), ptr(p)
      {}
      smart_ptr(const T& ins):copies(new int(1)), ptr(new T(ins))
      {}
      smart_ptr(const smart_ptr<T>& cp):copies(cp.copies),
                                      ptr(cp.ptr)
      {
        ++(*copies);
      }

      //Operators
      smart_ptr& operator=(const smart_ptr<T>& cp){
        handle_destruction();
        copies = cp.copies;
        ++(*copies);
        ptr = cp.ptr;
        return *this;
      }

      T& operator*() const{
        return *ptr;
      }

      T* operator->() const{
        return ptr;
      }

      //Functions
      operator bool(){
        return ptr;
      }

      int instances(){
        return *copies;
      }

      ~smart_ptr(){
        handle_destruction();
      }

    private:
      int* copies;
      T* ptr;

      void handle_destruction(){
        if(--(*copies) == 0){
          delete ptr;
          delete copies;
        }
      }
  };
}
#endif
