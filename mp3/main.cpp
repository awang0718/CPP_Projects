#include "List.h"

#include <iostream>

using namespace std;

int main() {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i);}

  List<unsigned> list2;
  for (unsigned i = 9; i > 0; i--) { list.insertFront(i);}

  list.reverse();

  for (unsigned i = 0; i < 10; i++) {

  }

  return 0;
}
