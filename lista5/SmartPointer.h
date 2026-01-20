#ifndef TEPSEM3_SMARTPOINTER_H
#define TEPSEM3_SMARTPOINTER_H

#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T>
class BorrowingPointer;

template <typename T>
class RefCounter {
public:
  RefCounter() : count(0) {}
  int addRef() { return ++count; }
  int decRef() { return --count; }
  int getCounter() const { return count; }

  void borrow(BorrowingPointer<T>* pointer) {
    pointers.push_back(pointer);
  }

  void unborrow(BorrowingPointer<T>* pointer) {
    pointers.erase(std::remove(pointers.begin(), pointers.end(), pointer), pointers.end());
  }

  void notifyObjectDeleted();
private:
  int count;
  std::vector<BorrowingPointer<T>*> pointers;
};

template<typename T>
class SmartPointer {
  friend class BorrowingPointer<T>;
public:
  SmartPointer(T *pointer) {
    this->pointer = pointer;
    counter = new RefCounter<T>();
    counter->addRef();
  }

  SmartPointer(const SmartPointer &other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->addRef();
  }

  ~SmartPointer() {
    if (counter->decRef() == 0) {
      counter->notifyObjectDeleted();
      delete pointer;
      delete counter;
    }
  }

  SmartPointer& operator=(const SmartPointer &other) {
    if (this != &other) {
      if (counter->decRef() == 0) {
        counter->notifyObjectDeleted();
        delete pointer;
        delete counter;
      }
      pointer = other.pointer;
      counter = other.counter;
      counter->addRef();
    }
    return *this;
  }

  T& operator*() {
    return *pointer;
  }

  T* operator->() {
    return pointer;
  }

  BorrowingPointer<T> getBorrowingPointer() {
    return BorrowingPointer<T>(*this);
  }

private:
  T *pointer;
  RefCounter<T> *counter;
};

template<typename T>
class BorrowingPointer {
  friend class RefCounter<T>;

public:
  BorrowingPointer(SmartPointer<T>& smartPointer) {
    this->pointer = smartPointer.pointer;
    this->counter = smartPointer.counter;
    if (this->counter)
      this->counter->borrow(this);
  }

  BorrowingPointer(const BorrowingPointer &other) {
    pointer = other.pointer;
    counter = other.counter;
    if (counter)
      counter->borrow(this);
  }

  ~BorrowingPointer() {
    if (counter)
      counter->unborrow(this);
  }

  BorrowingPointer& operator=(const BorrowingPointer &other) {
    if (this != &other) {
      if (counter)
        counter->unborrow(this);
      pointer = other.pointer;
      counter = other.counter;
      if (counter)
        counter->borrow(this);
    }
    return *this;
  }

  bool isValid() {
    return pointer != nullptr;
  }


  T* operator->() {
    if (!pointer)
      throw std::invalid_argument("pointer is null");
    return pointer;
  }

  T& operator*() {
    if (!pointer)
      throw std::invalid_argument("pointer is null");
    return *pointer;
  }

private:
  T *pointer;
  RefCounter<T> *counter;

  void reset() {
    pointer = nullptr;
    counter = nullptr;
  }
};

template <typename T>
void RefCounter<T>::notifyObjectDeleted() {
  for (auto ptr : pointers)
    ptr->reset();
  pointers.clear();
}

#endif  // TEPSEM3_SMARTPOINTER_H
