#include <stdlib.h>

#include <iostream>

#include "builder.hpp"

int main() {
  Product product = Product::Builder("ball", 99.99, 100).build();
  std::cout << product.is_available() << std::endl;

  return EXIT_SUCCESS;
}
