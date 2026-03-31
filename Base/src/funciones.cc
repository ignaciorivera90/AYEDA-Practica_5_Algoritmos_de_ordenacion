#include "funciones.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

void FillSequenceManual(staticSequence<nif>& seq, unsigned size) {
  std::cout << "Introduzca " << size << " NIFs:\n";
  for (unsigned i = 0; i < size; ++i) {
    std::cout << "Elemento [" << i << "]: ";
    std::cin >> seq[i];
  }
}

void FillSequenceRandom(staticSequence<nif>& seq, unsigned size) {
  for (unsigned i = 0; i < size; ++i) {
    seq[i] = nif();
  }
}

void FillSequenceFromFile(staticSequence<nif>& seq, unsigned size, const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("No se pudo abrir el fichero: " + filename);
  }

  for (unsigned i = 0; i < size; ++i) {
    if (!(file >> seq[i])) {
      throw std::runtime_error("El fichero no contiene suficientes elementos.");
    }
  }
}