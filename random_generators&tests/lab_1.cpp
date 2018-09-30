#include <iostream>
#include "generators.h"

using namespace std;

void print_bytes(vector<unsigned char> bytes);

int main()
{
  print_bytes(geffe_gen(10));
  return 0;
}

void print_bytes(vector<unsigned char> bytes)
{
  for (unsigned char byte: bytes) {
    cout << "0x" << hex << (int) byte << " ";
  }
  cout << endl;
}
