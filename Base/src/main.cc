#include <iostream>
#include <memory>

#include "arg_parser.h"
#include "sort_method.h"
#include "nif.h"
#include "funciones.h"

int main(int argc, char* argv[]) {
  try {
    ProgramOptions options = ArgParser::Parse(argc, argv);

    staticSequence<nif> seq(options.size);

    if (options.init_mode == "manual") {
      FillSequenceManual(seq, options.size);
    } else if (options.init_mode == "random") {
      FillSequenceRandom(seq, options.size);
    } else if (options.init_mode == "file") {
      FillSequenceFromFile(seq, options.size, options.filename);
    }

    std::cout << "Secuencia original:\n";
    seq.print(std::cout);
    std::cout << "\n";

    std::unique_ptr<SortMethod<nif>> method;

    switch (options.ord_method) {
      case 's':
        method = std::make_unique<SelectionSortMethod<nif>>(seq, options.trace);
        break;
      case 'b':
        method = std::make_unique<BubbleSortMethod<nif>>(seq, options.trace);
        break;
      case 'h':
        method = std::make_unique<HeapSortMethod<nif>>(seq, options.trace);
        break;
      case 'm':
        method = std::make_unique<MergeSortMethod<nif>>(seq, options.trace);
        break;
      case 'i':
        method = std::make_unique<ShellSortMethod<nif>>(seq, options.trace, options.alpha);
        break;
      default:
        throw std::invalid_argument("Metodo de ordenacion no valido.");
    }

    method->Sort();

    std::cout << "Secuencia ordenada:\n";
    method->GetSequence().print(std::cout);
    std::cout << "\n";

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}