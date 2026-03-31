#ifndef SORT_METHOD_H_
#define SORT_METHOD_H_

#include "sequence.h"
#include "sort_functions.h"

template <class Key>
class SortMethod {
 public:
  explicit SortMethod(const staticSequence<Key>& seq) : seq_(seq) {}
  virtual ~SortMethod() = default;

  virtual void Sort() = 0;

  const staticSequence<Key>& GetSequence() const { return seq_; }

 protected:
  staticSequence<Key> seq_;
};

template <class Key>
class SelectionSortMethod : public SortMethod<Key> {
 public:
  explicit SelectionSortMethod(const staticSequence<Key>& seq) : SortMethod<Key>(seq) {}

  void Sort() override { SelectionSort(this->seq_, this->seq_.size()); }
};

template <class Key>
class BubbleSortMethod : public SortMethod<Key> {
 public:
  explicit BubbleSortMethod(const staticSequence<Key>& seq) : SortMethod<Key>(seq) {}

  void Sort() override { BubbleSort(this->seq_, this->seq_.size()); }
};

template <class Key>
class HeapSortMethod : public SortMethod<Key> {
 public:
  explicit HeapSortMethod(const staticSequence<Key>& seq) : SortMethod<Key>(seq) {}

  void Sort() override { HeapSort(this->seq_, this->seq_.size()); }
};

template <class Key>
class MergeSortMethod : public SortMethod<Key> {
 public:
  explicit MergeSortMethod(const staticSequence<Key>& seq) : SortMethod<Key>(seq) {}

  void Sort() override {
    if (this->seq_.size() > 0) {
      MergeSort(this->seq_, 0, this->seq_.size() - 1);
    }
  }
};

template <class Key>
class ShellSortMethod : public SortMethod<Key> {
 public:
  explicit ShellSortMethod(const staticSequence<Key>& seq) : SortMethod<Key>(seq) {}

  void Sort() override { ShellSort(this->seq_, this->seq_.size()); }
};

#endif