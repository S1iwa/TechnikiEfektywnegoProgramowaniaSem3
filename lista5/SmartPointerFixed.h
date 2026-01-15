#ifndef TEPSEM3_SMARTPOINTER_H
#define TEPSEM3_SMARTPOINTER_H

#include <map>

class RefCounter {
public:
  RefCounter() : count(0) {}
  int addRef() { return ++count; }
  int decRef() { return --count; }
  int getCounter() const { return count; }
private:
  int count;
};

template<typename T>
class SmartPointer {
public:
  SmartPointer(T *pointer) {
    this->pointer = pointer;

    auto it = tracked_pointers.find(pointer);
    if (it != tracked_pointers.end()) {
      counter = it->second;
      counter->addRef();
    } else {
      counter = new RefCounter();
      counter->addRef();
      tracked_pointers[pointer] = counter;
    }
  }

  SmartPointer(const SmartPointer &other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->addRef();
  }

  ~SmartPointer() {
    if (counter->decRef() == 0) {
      delete pointer;
      delete counter;
      tracked_pointers.erase(pointer);
    }
  }

  SmartPointer& operator=(const SmartPointer &other) {
    if (this != &other) {
      if (counter->decRef() == 0) {
        delete pointer;
        delete counter;
        tracked_pointers.erase(pointer);
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

private:
  T *pointer;
  RefCounter *counter;
  static std::map<T*, RefCounter*> tracked_pointers;
};

template<typename T>
std::map<T*, RefCounter*> SmartPointer<T>::tracked_pointers;

#endif  // TEPSEM3_SMARTPOINTER_H