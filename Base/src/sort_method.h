#ifndef SORT_METHOD_H_
#define SORT_METHOD_H_

#include "sequence.h"
#include "sort_functions.h"

template <class Key>
class SortMethod {
 public:
  SortMethod(const staticSequence<Key>& seq, bool trace)
      : seq_(seq), trace_(trace) {}

  virtual ~SortMethod() = default;
  virtual void Sort() = 0;

  const staticSequence<Key>& GetSequence() const {
    return seq_;
  }

 protected:
  staticSequence<Key> seq_;
  bool trace_;
};

template <class Key>
class SelectionSortMethod : public SortMethod<Key> {
 public:
  SelectionSortMethod(const staticSequence<Key>& seq, bool trace)
      : SortMethod<Key>(seq, trace) {}

  void Sort() override {
    SelectionSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

template <class Key>
class BubbleSortMethod : public SortMethod<Key> {
 public:
  BubbleSortMethod(const staticSequence<Key>& seq, bool trace)
      : SortMethod<Key>(seq, trace) {}

  void Sort() override {
    BubbleSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

template <class Key>
class HeapSortMethod : public SortMethod<Key> {
 public:
  HeapSortMethod(const staticSequence<Key>& seq, bool trace)
      : SortMethod<Key>(seq, trace) {}

  void Sort() override {
    HeapSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

template <class Key>
class MergeSortMethod : public SortMethod<Key> {
 public:
  MergeSortMethod(const staticSequence<Key>& seq, bool trace)
      : SortMethod<Key>(seq, trace) {}

  void Sort() override {
    if (this->seq_.size() > 0) {
      MergeSort(this->seq_, 0, this->seq_.size() - 1, this->trace_);
    }
  }
};

template <class Key>
class ShellSortMethod : public SortMethod<Key> {
 public:
  ShellSortMethod(const staticSequence<Key>& seq, bool trace, double alpha)
      : SortMethod<Key>(seq, trace), alpha_(alpha) {}

  void Sort() override {
    ShellSort(this->seq_, this->seq_.size(), alpha_, this->trace_);
  }

 private:
  double alpha_;
};

#endif