#include "nvimfy.hpp"

int main( int argc, char **argv ){
  auto nvimfy = std::make_shared<NVimfy>();
  nvimfy->run();
  return 0;
}