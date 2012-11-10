#ifndef LEVELS_H
#define LEVELS_H
namespace al{

  /**
   * levels is the enum class representing the different levels of severity
   * possible to express with all.
   *
   * They range from most minor, debug, to most severe, fatal_error.
   *
   * none shouldn't be used to log error messages per se, it is more suited for
   * setting the ignore level on a logger_creator
   */
  enum class level{
    none,
    debug,
    info,
    warning,
    nonfatal_error,
    fatal_error,
  };
}

#endif
