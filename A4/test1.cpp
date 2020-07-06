#include <iostream>
#include <cstdlib>
#include <string>
#include "tombstones.h"

using namespace std;

int main(int argc, char* argv[]) {
  Pointer<int> p(new int(6));
  Pointer<int> t((int*)NULL);
  Pointer<int> x = t;

  if(p == 0) {
    cout << "p should have a value, not NULL" << endl;
    exit(1);
  }
  if(x != 0) {
    cout << "x should not contain any values" << endl;
    exit(1);
  }
  x = new int(6);

  if(p == x) {
    cout << "p and x are there own entities" << endl;
    exit(1);
  }

  if(*p == *x) {
    free(p);
    free(x);
  }
  else {
      cout << "p and x should have equal values" << endl;
      exit(1);
  }

  cout << "Test successful." << endl;
  return 0;
}
