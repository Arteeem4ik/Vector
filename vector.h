#ifndef VECTOR__VECTOR_H_
#define VECTOR__VECTOR_H_
#include <iostream>
#include <iterator>
#include <exception>

template <class T>
    class Vector {
 private:
  T* buffer_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  using Iterator = T*;
  using ConstIterator = const T*;
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using ReverseIterator = std::reverse_iterator<T*>;
  using ConstReverseIterator = std::reverse_iterator<const T*>;

  Vector() : buffer_(nullptr), size_(0), capacity_(0) {
  }

  explicit Vector(size_t size) : buffer_(new T[size]), size_(size), capacity_(size) {
  }

  Vector(size_t size, T value) {
    if (size > 0) {
      buffer_ = new T[size];
    }
    size_ = size;
    capacity_ = size;
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = value;
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
      std::forward_iterator_tag,
      typename std::iterator_traits<Iterator>::iterator_category>>>  //
      // forward
      Vector(Iterator first, Iterator last) {
    size_t size = std::distance(first, last);
    size_ = size;
    capacity_ = size_;
    if (size_ > 0) {
      buffer_ = new T[size_];
    }
    int idx = 0;
    for (auto it = first; it != last; ++it) {
      buffer_[idx] = *it;
      ++idx;
    }
  }

  Vector(std::initializer_list<T> list) {
    size_t size = list.size();
    size_ = size;
    capacity_ = size;
    buffer_ = new T[size];
    int idx = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
      buffer_[idx] = *it;
      ++idx;
    }
  }

  Vector(const Vector& other) {
    if (other.capacity_ != 0) {
      try {
        buffer_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
          buffer_[i] = other.buffer_[i];
        }
      } catch (...) {
        delete[] buffer_;
        buffer_ = nullptr;
        throw;
        return;
      }
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
  }

  Vector(Vector&& other) noexcept {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (capacity_ != 0) {
      buffer_ = std::move(other.buffer_);
    }
    other.buffer_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  bool operator<(const Vector& other) const {
    size_t size = std::max(size_, other.size_);
    for (size_t i = 0; i < size; ++i) {
      if ((i < size_ && i < other.size_ && buffer_[i] < other.buffer_[i]) || (i >= size_ && i < other.size_)) {
        return true;
      }
      if ((i < size_ && i < other.size_ && buffer_[i] > other.buffer_[i]) || (i < size_ && i >= other.size_)) {
        return false;
      }
    }
    return false;
  }

  bool operator==(const Vector& other) const {
    return !(*this < other || other < *this);
  }

  bool operator<=(const Vector& other) const {
    return *this < other || *this == other;
  }

  bool operator>(const Vector& other) const {
    return !(*this < other || *this == other);
  }

  bool operator>=(const Vector& other) const {
    return *this > other || *this == other;
  }

  bool operator!=(const Vector& other) const {
    return !(*this == other);
  }

  Vector& operator=(const Vector& other) {
    if (buffer_ != other.buffer_) {
      if (other.capacity_ != 0) {
        auto tmp = new T[1];
        delete[] tmp;
        tmp = nullptr;
        try {
          tmp = new T[other.capacity_];
          for (size_t i = 0; i < other.size_; ++i) {
            tmp[i] = other.buffer_[i];
          }
        } catch (...) {
          delete[] tmp;
          throw;
          return *this;
        }
        delete[] buffer_;
        buffer_ = std::move(tmp);
      }
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (buffer_ != other.buffer_) {
      delete[] buffer_;
      buffer_ = nullptr;
      size_ = other.size_;
      capacity_ = other.capacity_;
      if (capacity_ != 0) {
        buffer_ = std::move(other.buffer_);
      }
      other.buffer_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  ConstReference operator[](size_t idx) const {
    return buffer_[idx];
  }

  Reference operator[](size_t idx) {
    return buffer_[idx];
  }

  ConstReference At(size_t idx) const {
    if (idx < 0 || idx >= size_) {
      throw std::out_of_range("std::out_of_range");
    }
    return buffer_[idx];
  }

  Reference At(size_t idx) {
    if (idx < 0 || idx >= size_) {
      throw std::out_of_range("std::out_of_range");
    }
    return buffer_[idx];
  }

  ConstReference Front() const {
    return buffer_[0];
  }

  Reference Front() {
    return buffer_[0];
  }

  ConstReference Back() const {
    return buffer_[size_ - 1];
  }

  Reference Back() {
    return buffer_[size_ - 1];
  }

  ConstPointer Data() const {
    return buffer_;
  }

  Pointer Data() {
    return buffer_;
  }

  void Swap(Vector& other) {
    Vector<T> tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }

  void Resize(size_t new_size) {
    if (new_size < capacity_) {
      size_ = new_size;
      return;
    }
    if (new_size > capacity_) {
      auto tmp = new T[new_size];
      delete[] tmp;
      tmp = nullptr;
      try {
        tmp = new T[new_size];
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move(buffer_[i]);
        }
      } catch (...) {
        delete[] tmp;
        return;
      }
      delete[] buffer_;
      capacity_ = new_size;
      buffer_ = std::move(tmp);
      size_ = new_size;
    }
  }

  void Resize(size_t new_size, T value) {
    size_t old_size = size_;
    Resize(new_size);
    for (size_t i = old_size; i < size_; ++i) {
      buffer_[i] = value;
    }
  }

  void Reserve(size_t new_cap) {
    if (new_cap > capacity_) {
      auto tmp = new T[1];
      delete[] tmp;
      tmp = nullptr;
      try {
        tmp = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move(buffer_[i]);
        }
      } catch (...) {
        delete[] tmp;
        return;
      }
      delete[] buffer_;
      capacity_ = new_cap;
      buffer_ = std::move(tmp);
    }
  }

  void ShrinkToFit() {
    auto tmp = new T[size_];
    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = std::move(buffer_[i]);
    }
    delete[] buffer_;
    buffer_ = std::move(tmp);
    capacity_ = size_;
    if (capacity_ == 0) {
      delete[] buffer_;
      buffer_ = nullptr;
    }
  }

  void Clear() {
    size_ = 0;
  }

  void PushBack(const T& value) {
    if (size_ == 0) {
      Reserve(1);
    } else if (size_ == capacity_) {
      Reserve(2 * size_);
    }
    buffer_[size_] = value;
    ++size_;
  }

  void PushBack(T&& value) {
    if (size_ == 0) {
      Reserve(1);
    } else if (size_ == capacity_) {
      Reserve(2 * size_);
    }
    buffer_[size_] = std::move(value);
    ++size_;
  }

  void PopBack() {
    if (size_ > 0) {
      --size_;
    }
  }

  Iterator begin() {  // NOLINT
    return buffer_;
  }

  Iterator end() {  // NOLINT
    return buffer_ + size_;
  }

  ConstIterator begin() const {  // NOLINT
    return buffer_;
  }

  ConstIterator end() const {  // NOLINT
    return buffer_ + size_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return buffer_;
  }

  ConstIterator cend() const {  // NOLINT
    return buffer_ + size_;
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::make_reverse_iterator(buffer_ + size_);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::make_reverse_iterator(buffer_);
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::make_reverse_iterator(buffer_ + size_);
  }

  ReverseIterator rend() {  // NOLINT
    return std::make_reverse_iterator(buffer_);
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::make_reverse_iterator(buffer_ + size_);
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::make_reverse_iterator(buffer_);
  }

  ~Vector() {
    delete[] buffer_;
  }
};

#endif  // VECTOR__VECTOR_H_