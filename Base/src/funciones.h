#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <string>
#include "sequence.h"
#include "nif.h"

void FillSequenceManual(staticSequence<nif>& seq, unsigned size);
void FillSequenceRandom(staticSequence<nif>& seq, unsigned size);
void FillSequenceFromFile(staticSequence<nif>& seq, unsigned size, const std::string& filename);

#endif