#ifndef SORT_FUNCTIONS_H_
#define SORT_FUNCTIONS_H_

#include <iostream>
#include <vector>
#include "sequence.h"

template <class Key>
void Swap(Key& a, Key& b) {
  Key aux = a;
  a = b;
  b = aux;
}

template <class Key>
void baja(staticSequence<Key>& seq, int size, int i) {
  while (2 * i + 1 < size) {
    int h1 = 2 * i + 1;
    int h2 = h1 + 1;
    int h = h1;

    if (h2 < size && seq[h2] > seq[h1]) {
      h = h2;
    }

    if (seq[h] <= seq[i]) {
      break;
    } else {
      Swap(seq[i], seq[h]);
      i = h;
    }
  }
}

template <class Key>
void Mezcla(staticSequence<Key>& seq, unsigned ini, unsigned mid, unsigned fin) {
  unsigned i = ini;
  unsigned j = mid + 1;
  unsigned k = 0;

  staticSequence<Key> aux(fin - ini + 1);

  while ((i <= mid) && (j <= fin)) {
    if (seq[i] < seq[j]) {
      aux[k] = seq[i];
      ++i;
    } else {
      aux[k] = seq[j];
      ++j;
    }
    ++k;
  }

  while (i <= mid) {
    aux[k] = seq[i];
    ++i;
    ++k;
  }

  while (j <= fin) {
    aux[k] = seq[j];
    ++j;
    ++k;
  }

  for (unsigned t = 0; t < fin - ini + 1; ++t) {
    seq[ini + t] = aux[t];
  }
}

template <class Key>
void DeltaSort(staticSequence<Key>& seq, unsigned size, int delta) {
  if (delta <= 0) return;

  for (int i = delta; i < static_cast<int>(size); ++i) {
    Key x = seq[i];
    int j = i;

    while ((j >= delta) && (x < seq[j - delta])) {
      seq[j] = seq[j - delta];
      j -= delta;
    }

    seq[j] = x;
  }
}

template <class Key>
void SelectionSort(staticSequence<Key>& seq, unsigned size) {
  if (size < 2) return;

  for (unsigned i = 0; i < size - 1; ++i) {
    unsigned min = i;
    for (unsigned j = i + 1; j < size; ++j) {
      if (seq[j] < seq[min]) {
        min = j;
      }
    }

    if (min != i) {
      Key x = seq[min];
      seq[min] = seq[i];
      seq[i] = x;
    }
  }
}

template <class Key>
void BubbleSort(staticSequence<Key>& seq, unsigned size) {
  if (size < 2) return;

  for (unsigned i = 1; i < size; ++i) {
    bool swapped = false;

    for (int j = static_cast<int>(size) - 1; j >= static_cast<int>(i); --j) {
      if (seq[j] < seq[j - 1]) {
        Swap(seq[j - 1], seq[j]);
        swapped = true;
      }
    }

    if (!swapped) {
      break;
    }
  }
}

template <class Key>
void HeapSort(staticSequence<Key>& seq, unsigned size) {
  if (size < 2) return;

  for (int i = static_cast<int>(size) / 2 - 1; i >= 0; --i) {
    baja(seq, static_cast<int>(size), i);
  }

  for (int i = static_cast<int>(size) - 1; i > 0; --i) {
    Swap(seq[0], seq[i]);
    baja(seq, i, 0);
  }
}

template <class Key>
void MergeSort(staticSequence<Key>& seq, unsigned ini, unsigned fin) {
  if (ini < fin) {
    unsigned mid = (ini + fin) / 2;
    MergeSort(seq, ini, mid);
    MergeSort(seq, mid + 1, fin);
    Mezcla(seq, ini, mid, fin);
  }
}

template <class Key>
void ShellSort(staticSequence<Key>& seq, unsigned size) {
  if (size < 2) return;

  unsigned delta = size;
  while (delta > 1) {
    delta = delta / 2;
    DeltaSort(seq, size, static_cast<int>(delta));
  }
}

#endif