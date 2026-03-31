#include "staticSequence.h"
#include "nif.h"

void FillSequenceManual(staticSequence<Nif>& seq, unsigned size);
void FillSequenceRandom(staticSequence<Nif>& seq, unsigned size);
void FillSequenceFromFile(staticSequence<Nif>& seq, unsigned size, const std::string& filename);
void PrintSequence(const staticSequence<Nif>& seq);