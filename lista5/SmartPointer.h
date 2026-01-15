#ifndef TEPSEM3_SMARTPOINTER_H
#define TEPSEM3_SMARTPOINTER_H



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
    counter = new RefCounter();
    counter->addRef();
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
    }
  }

  SmartPointer& operator=(const SmartPointer &other) {
    if (this != &other) {
      if (counter->decRef() == 0) {
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

private:
  T *pointer;
  RefCounter *counter;
};



#endif  // TEPSEM3_SMARTPOINTER_H
