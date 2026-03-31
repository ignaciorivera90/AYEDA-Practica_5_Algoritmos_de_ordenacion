#include "arg_parser.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

ProgramOptions ArgParser::Parse(int argc, char* argv[]) {
  ProgramOptions options;
  bool trace_specified = false;

  if (argc == 1) {
    PrintUsage(argv[0]);
    throw std::invalid_argument("No se han proporcionado argumentos.");
  }

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
      PrintHelp(argv[0]);
      std::exit(0);
    }

    if (std::strcmp(argv[i], "-size") == 0) {
      if (i + 1 >= argc) {
        throw std::invalid_argument("Falta el valor de -size.");
      }
      options.size = std::stoul(argv[++i]);
      continue;
    }

    if (std::strcmp(argv[i], "-ord") == 0) {
      if (i + 1 >= argc) {
        throw std::invalid_argument("Falta el valor de -ord.");
      }
      std::string method = argv[++i];
      if (method.size() != 1) {
        throw std::invalid_argument("El codigo de -ord debe ser una sola letra.");
      }
      options.ord_method = method[0];
      continue;
    }

    if (std::strcmp(argv[i], "-init") == 0) {
      if (i + 1 >= argc) {
        throw std::invalid_argument("Falta el valor de -init.");
      }

      options.init_mode = argv[++i];

      if (options.init_mode == "file") {
        if (i + 1 >= argc) {
          throw std::invalid_argument("Falta el nombre del fichero tras -init file.");
        }
        options.filename = argv[++i];
      } else if (options.init_mode != "manual" && options.init_mode != "random") {
        throw std::invalid_argument("Modo de inicializacion no valido.");
      }
      continue;
    }

    if (std::strcmp(argv[i], "-trace") == 0) {
      if (i + 1 >= argc) {
        throw std::invalid_argument("Falta el valor de -trace.");
      }

      std::string value = argv[++i];
      trace_specified = true;

      if (value == "y") {
        options.trace = true;
      } else if (value == "n") {
        options.trace = false;
      } else {
        throw std::invalid_argument("El valor de -trace debe ser y o n.");
      }
      continue;
    }

    if (std::strcmp(argv[i], "-alpha") == 0) {
      if (i + 1 >= argc) {
        throw std::invalid_argument("Falta el valor de -alpha.");
      }
      options.alpha = std::stod(argv[++i]);
      if (options.alpha <= 0.0 || options.alpha >= 1.0) {
        throw std::invalid_argument("alpha debe cumplir 0 < alpha < 1.");
      }
      continue;
    }

    throw std::invalid_argument(std::string("Argumento desconocido: ") + argv[i]);
  }

  if (options.size == 0) {
    throw std::invalid_argument("Debe indicar -size <s> con s > 0.");
  }

  if (options.ord_method == '\0') {
    throw std::invalid_argument("Debe indicar -ord <m>.");
  }

  if (options.init_mode.empty()) {
    throw std::invalid_argument("Debe indicar -init <manual|random|file>.");
  }

  if (!trace_specified) {
    throw std::invalid_argument("Debe indicar -trace <y|n>.");
  }

  return options;
}

void ArgParser::PrintUsage(const char* progname) {
  std::cout << "Uso:\n"
            << progname
            << " -size <s> -ord <m> -init <manual|random|file [f]> -trace <y|n> [-alpha <a>]\n"
            << "Pruebe con --help o -h para mas informacion.\n";
}

void ArgParser::PrintHelp(const char* progname) {
  std::cout << "Practica 5 - Algoritmos de ordenacion\n\n";
  std::cout << "Uso:\n";
  std::cout << "  " << progname
            << " -size <s> -ord <m> -init <i> [f] -trace <y|n> [-alpha <a>]\n\n";

  std::cout << "Opciones:\n";
  std::cout << "  -size <s>      Tamano de la secuencia\n";
  std::cout << "  -ord <m>       Metodo de ordenacion:\n";
  std::cout << "                   s : seleccion\n";
  std::cout << "                   b : burbuja\n";
  std::cout << "                   m : merge sort\n";
  std::cout << "                   h : heap sort\n";
  std::cout << "                   i : incrementos decrecientes\n";
  std::cout << "  -init <i>      Modo de inicializacion:\n";
  std::cout << "                   manual\n";
  std::cout << "                   random\n";
  std::cout << "                   file <f>\n";
  std::cout << "  -trace <y|n>   Mostrar traza\n";
  std::cout << "  -alpha <a>     Valor alfa para incrementos decrecientes\n\n";

  std::cout << "Ejemplos:\n";
  std::cout << "  " << progname << " -size 10 -ord s -init random -trace n\n";
  std::cout << "  " << progname << " -size 8 -ord m -init file datos.txt -trace y\n";
  std::cout << "  " << progname << " -size 12 -ord i -init random -trace y -alpha 0.5\n";
}