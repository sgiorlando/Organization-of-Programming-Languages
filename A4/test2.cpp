#include <iostream>
#include <cstdlib>
#include <string>
#include "tombstones.h"

using namespace std;

void error() {
  exit(1);
}

int main(int argc, char* argv[]) {
  Pointer<int> p;
  p = new int(6);
  Pointer<int> x(p);

  if(x == 0) {
    cout << "x should not be NULL" << endl;
    error();
  }

  if(p != x) {
    cout << "Error: p and x are not separate pointers" << endl;
    error();
  }

  if(*p != *x) {
    cout << "Error: p and x should not have the same values" << endl;
    error();
  }

  *p = 18;

  if(*x != 18) {
    cout << "Error: x should still be the same as p" << endl;
    error();
  }

  free(p);
  free(x);
  cout << "Test successful." << endl;

  return 0;
}
