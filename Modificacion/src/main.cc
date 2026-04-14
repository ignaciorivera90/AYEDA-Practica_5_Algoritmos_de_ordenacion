#include <iostream>
#include <memory>

#include "arg_parser.h"
#include "sort_method.h"
#include "nif.h"
#include "funciones.h"

int main(int argc, char* argv[]) {
  Log(INFO, "Programa iniciado");
  try {
    Log(INFO, "Procesando Argumentos");
    ProgramOptions options = ArgParser::Parse(argc, argv);
    Log(INFO, "Argumentos procesados correctamente");

    staticSequence<nif> seq(options.size);

    if (options.init_mode == "manual") {
      FillSequenceManual(seq, options.size);
      Log(INFO, "Inicializacion manual");
    } else if (options.init_mode == "random") {
      FillSequenceRandom(seq, options.size);
      Log(INFO, "Inicializacion aleatoria");
    } else if (options.init_mode == "file") {
      FillSequenceFromFile(seq, options.size, options.filename);
      Log(INFO, "Inicializacion desde fichero: " + options.filename);
    }

    std::cout << "Secuencia original:\n";
    seq.print(std::cout);
    std::cout << "\n";

    std::unique_ptr<SortMethod<nif>> method;

    switch (options.ord_method) {
      case 's':
        method = std::make_unique<SelectionSortMethod<nif>>(seq, options.trace);
        Log(INFO, "Metodo: SelectionSort");
        break;
      case 'b':
        method = std::make_unique<BubbleSortMethod<nif>>(seq, options.trace);
        Log(INFO, "Metodo: BubbleSort");
        break;
      case 'h':
        method = std::make_unique<HeapSortMethod<nif>>(seq, options.trace);
        Log(INFO, "Metodo: HeapSort");
        break;
      case 'm':
        method = std::make_unique<MergeSortMethod<nif>>(seq, options.trace);
        Log(INFO, "Metodo: MergeSort");
        break;
      case 'i':
        method = std::make_unique<ShellSortMethod<nif>>(seq, options.trace, options.alpha);
        Log(INFO, "Metodo: ShellSort");
        break;
      default:
        throw std::invalid_argument("Metodo de ordenacion no valido.");
    }
    Log(INFO, "Comenzando ordenacion");
    method->Sort();

    std::cout << "Secuencia ordenada:\n";
    method->GetSequence().print(std::cout);
    std::cout << "\n";

  } catch (const std::exception& e) {
    Log(ERROR, e.what());
    return 1;
  }
  Log(INFO, "Ordenacion finalizada");
  return 0;
}