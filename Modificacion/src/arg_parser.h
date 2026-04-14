#ifndef ARG_PARSER_H_
#define ARG_PARSER_H_

#include <string>

struct ProgramOptions {
  unsigned size = 0;
  char ord_method = '\0';
  std::string init_mode;
  std::string filename;
  bool trace = false;
  double alpha = 0.5;
};

class ArgParser {
 public:
  static ProgramOptions Parse(int argc, char* argv[]);
  static void PrintUsage(const char* progname);
  static void PrintHelp(const char* progname);

 private:
  ArgParser() = delete;
};

#endif