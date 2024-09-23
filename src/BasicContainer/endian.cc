#include <iostream>

using namespace std;

union endianTest {
    [[maybe_unused]] unsigned int b;
  unsigned char c;
} endian_test = {1};

int main() {
  if (endian_test.c == 1) {
    std::cout << "little" << std::endl;
  } else {
    std::cout << "big" << std::endl;
  }

  return 0;
}