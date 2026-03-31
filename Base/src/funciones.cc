#include "funciones.h"

void FillSequenceManual(staticSequence<Nif>& seq, unsigned size) {
  std::cout << "Introduzca " << size << " elementos:\n";
  for (unsigned i = 0; i < size; ++i) {
    Nif value;
    std::cout << "Elemento [" << i << "]: ";
    std::cin >> value;
    seq[i] = value;
  }
}

void FillSequenceRandom(staticSequence<Nif>& seq, unsigned size) {
  for (unsigned i = 0; i < size; ++i) {
    seq[i] = Nif();
  }
}

void FillSequenceFromFile(staticSequence<Nif>& seq, unsigned size, const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("No se pudo abrir el fichero de entrada: " + filename);
  }

  for (unsigned i = 0; i < size; ++i) {
    if (!(file >> seq[i])) {
      throw std::runtime_error("El fichero no contiene suficientes elementos.");
    }
  }
}

void PrintSequence(const staticSequence<Nif>& seq) {
  seq.print(std::cout);
  std::cout << "\n";
}