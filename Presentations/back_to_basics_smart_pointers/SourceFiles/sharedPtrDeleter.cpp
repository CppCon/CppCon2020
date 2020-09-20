#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <typeinfo>

template <typename T>
class Deleter {
public:
  void operator()(T *ptr) {
    ++Deleter::count;
    delete ptr;
  }
  void getInfo() {
    std::string typeId{typeid(T).name()};
    size_t sz= Deleter::count * sizeof(T);
    std::cout << "Deleted " << Deleter::count << " objects of type: " << typeId << std::endl;
    std::cout <<"Freed size in bytes: "  << sz << "." <<  std::endl;
    std::cout << std::endl;

  }
private:
  static int count;
};

template <typename T>
int Deleter<T>::count = 0;

typedef Deleter<int> IntDeleter;

void createRandomNumbers() {

  std::random_device seed;

  // generator
  std::mt19937 engine(seed());

  // distribution
  std::uniform_int_distribution<int> thousand(1, 1000);
  int ranNumber= thousand(engine);
  for ( int i=0 ; i <= ranNumber; ++i) std::shared_ptr<int>(new int(i), IntDeleter());

}

int main() {

  std::cout << std::endl;

  // define a local scope
  {
    std::shared_ptr<int> sharedPtr1(new int, IntDeleter());
    std::shared_ptr<int> sharedPtr2(new int, IntDeleter());
    auto intDeleter= std::get_deleter<IntDeleter>(sharedPtr1);
    intDeleter->getInfo();
    sharedPtr2.reset();
    intDeleter->getInfo();

  }
  // create up to 1000 std::shared_ptr of type int
  createRandomNumbers();
  IntDeleter().getInfo();

}

