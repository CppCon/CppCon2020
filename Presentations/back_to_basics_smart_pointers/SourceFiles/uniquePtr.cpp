#include <iostream>
#include <memory>
#include <utility>

struct MyInt {
  MyInt(int i) : i_(i) {}
  ~MyInt() {
    std::cout << "Good bye from " << i_ << std::endl;
  }
  int i_;
};


int main() {

  std::cout << std::endl;

  MyInt* myInt15 = new MyInt(15);
  std::unique_ptr<MyInt> uniquePtr1(myInt15);
  std::unique_ptr<MyInt> uniquePtr15(myInt15);

  std::cout << "uniquePtr1.get(): " << uniquePtr1.get() << std::endl;

  std::unique_ptr<MyInt> uniquePtr2{std::move(uniquePtr1)};
  std::cout << "uniquePtr1.get(): " << uniquePtr1.get() << std::endl;
  std::cout << "uniquePtr2.get(): " << uniquePtr2.get() << std::endl;

  std::cout << std::endl;


  {
    std::unique_ptr<MyInt> localPtr{new MyInt(2003)};
  }

  std::cout << std::endl;

  uniquePtr2.reset(new MyInt(2011));
  MyInt* myInt= uniquePtr2.release();
  delete myInt;

  std::cout << std::endl;

}
