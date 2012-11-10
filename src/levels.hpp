#ifndef LEVELS_H
#define LEVELS_H
namespace al{

  enum class level{
    none,
    debug,
    info,
    warning,
    nonfatal_error,
    fatal_error,
    all
  };
}

#endif