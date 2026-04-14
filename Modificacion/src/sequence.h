#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <vector>
#include <iostream>
#include <stdexcept>

template <class Key>
class Sequence {
 public:
  virtual ~Sequence() = default;

  virtual void print(std::ostream& os) const = 0;
  virtual const Key& operator[](unsigned index) const = 0;
  virtual Key& operator[](unsigned index) = 0;
  virtual unsigned size() const = 0;
};

template <class Key>
class staticSequence : public Sequence<Key> {
 public:
  explicit staticSequence(unsigned block_size)
      : block_size_(block_size), data_(block_size) {}

  void print(std::ostream& os) const override {
    os << "[ ";
    for (unsigned i = 0; i < block_size_; ++i) {
      os << data_[i] << " ";
    }
    os << "]";
  }

  const Key& operator[](unsigned index) const override {
    return data_.at(index);
  }

  Key& operator[](unsigned index) override {
    return data_.at(index);
  }

  unsigned size() const override {
    return block_size_;
  }

 private:
  unsigned block_size_;
  std::vector<Key> data_;
};

#endif