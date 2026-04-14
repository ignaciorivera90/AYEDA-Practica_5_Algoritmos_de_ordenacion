#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
#include <string>
#include "sequence.h"
#include "nif.h"

enum LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR
};

void FillSequenceManual(staticSequence<nif>& seq, unsigned size);
void FillSequenceRandom(staticSequence<nif>& seq, unsigned size);
void FillSequenceFromFile(staticSequence<nif>& seq, unsigned size, const std::string& filename);
void Log(LogLevel level, const std::string& msg);

#endif