#include "nvimfy.hpp"

int main( int argc, char **argv ){
  if ( argc > 1 ){
    auto nvimfy = std::make_shared<NVimfy>(argv[1]);
    nvimfy->run();
  } else {
    auto nvimfy = std::make_shared<NVimfy>("");
    nvimfy->run();
  }
  
  return 0;
}