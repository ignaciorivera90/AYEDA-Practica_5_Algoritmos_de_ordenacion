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
void PrintSequence(const staticSequence<Key>& seq) {
  seq.print(std::cout);
  std::cout << std::endl;
}

template <class Key>
void SelectionSort(staticSequence<Key>& seq, unsigned size, bool trace) {
  for (unsigned i = 0; i < size - 1; ++i) {
    unsigned min = i;
    for (unsigned j = i + 1; j < size; ++j) {
      if (seq[j] < seq[min]) {
        min = j;
      }
    }
    if (min != i) {
      Swap(seq[i], seq[min]);
    }
    if (trace) {
      PrintSequence(seq);
    }
  }
}

template <class Key>
void BubbleSort(staticSequence<Key>& seq, unsigned size, bool trace) {
  for (unsigned i = 1; i < size; ++i) {
    bool swapped = false;
    for (int j = size - 1; j >= static_cast<int>(i); --j) {
      if (seq[j] < seq[j - 1]) {
        Swap(seq[j], seq[j - 1]);
        swapped = true;
      }
    }
    if (trace) {
      PrintSequence(seq);
    }
    if (!swapped) {
      break;
    }
  }
}

template <class Key>
void Merge(staticSequence<Key>& seq, unsigned ini, unsigned mid, unsigned fin) {
  std::vector<Key> aux(fin - ini + 1);

  unsigned i = ini;
  unsigned j = mid + 1;
  unsigned k = 0;

  while (i <= mid && j <= fin) {
    if (seq[i] < seq[j]) {
      aux[k++] = seq[i++];
    } else {
      aux[k++] = seq[j++];
    }
  }

  while (i <= mid) {
    aux[k++] = seq[i++];
  }

  while (j <= fin) {
    aux[k++] = seq[j++];
  }

  for (unsigned t = 0; t < aux.size(); ++t) {
    seq[ini + t] = aux[t];
  }
}

template <class Key>
void MergeSort(staticSequence<Key>& seq, unsigned ini, unsigned fin, bool trace) {
  if (ini >= fin) {
    return;
  }

  unsigned mid = (ini + fin) / 2;
  MergeSort(seq, ini, mid, trace);
  MergeSort(seq, mid + 1, fin, trace);
  Merge(seq, ini, mid, fin);

  if (trace) {
    PrintSequence(seq);
  }
}

template <class Key>
void BajaHeap(staticSequence<Key>& seq, unsigned i, unsigned n) {
  while (2 * i + 1 < n) {
    unsigned h1 = 2 * i + 1;
    unsigned h2 = h1 + 1;
    unsigned h = h1;

    if (h2 < n && seq[h2] > seq[h1]) {
      h = h2;
    }

    if (seq[h] <= seq[i]) {
      break;
    }

    Swap(seq[i], seq[h]);
    i = h;
  }
}

template <class Key>
void HeapSort(staticSequence<Key>& seq, unsigned size, bool trace) {
  for (int i = size / 2 - 1; i >= 0; --i) {
    BajaHeap(seq, i, size);
  }

  if (trace) {
    PrintSequence(seq);
  }

  for (int i = size - 1; i > 0; --i) {
    Swap(seq[0], seq[i]);
    BajaHeap(seq, 0, i);

    if (trace) {
      PrintSequence(seq);
    }
  }
}

template <class Key>
void DeltaSort(staticSequence<Key>& seq, unsigned size, unsigned delta) {
  for (unsigned i = delta; i < size; ++i) {
    Key x = seq[i];
    int j = i;

    while (j >= static_cast<int>(delta) && x < seq[j - delta]) {
      seq[j] = seq[j - delta];
      j -= delta;
    }
    seq[j] = x;
  }
}

template <class Key>
void ShellSort(staticSequence<Key>& seq, unsigned size, double alpha, bool trace) {
  if (alpha <= 0.0 || alpha >= 1.0) {
    throw std::invalid_argument("alpha debe cumplir 0 < alpha < 1");
  }

  unsigned delta = size;
  while (delta > 1) {
    delta = static_cast<unsigned>(delta * alpha);
    if (delta < 1) {
      delta = 1;
    }

    DeltaSort(seq, size, delta);

    if (trace) {
      PrintSequence(seq);
    }

    if (delta == 1) {
      break;
    }
  }
}

#endif