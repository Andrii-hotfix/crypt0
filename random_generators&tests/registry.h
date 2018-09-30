#include <string.h>
#include <stdint.h>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

class L
{
public:
  virtual int shift() = 0;
};

class L20 : public L
{
private:
  bitset<20> state;

public:
  L20(unsigned init_state) : state(init_state) {}

  int shift()
  {
    int new_bit = ((state[17] ^ state[15]) ^ state[11]) ^ state[0];
    int out = state[0];
    state >>= 1;
    state[19] = new_bit;
    return out;
  }
};

class L89 : public L
{
private:
  bitset<89> state;

public:
  L89(vector<unsigned char> init_bytes)
  {
    for (unsigned char byte: init_bytes) {
      for (int i = 0; i < 8; i++) {
        state[0] = byte & 0x1;
        byte >>= 1;
        state <<= 1;
      }
    }
  }

  int shift()
  {
    int new_bit = state[51] ^ state[0];
    int out = state[0];
    state >>= 1;
    state[88] = new_bit;
    return out;
  }
};

class L11 : public L
{
private:
  bitset<11> state;

public:
  L11(unsigned init_state) : state(init_state) {}

  int shift()
  {
    int new_bit = state[0] ^ state[2];
    int out = state[0];
    state >>= 1;
    state[10] = new_bit;
    return out;
  }
};

class L9 : public L
{
private:
  bitset<9> state;

public:
  L9(unsigned init_state) : state(init_state) {}

  int shift()
  {
      int new_bit = ((state[0] ^ state[1]) ^ state[3]) ^ state[4];
      int out = state[0];
      state >>= 1;
      state[8] = new_bit;
      return out;
  }
};

class L10 : public L
{
private:
  bitset<10> state;

public:
  L10(unsigned init_state) : state(init_state) {}

  int shift()
  {
      int new_bit = state[0] ^ state[3];
      int out = state[0];
      state >>= 1;
      state[9] = new_bit;
      return out;
  }
};

class Geffe
{
private:
    L11 reg1;
    L9  reg2;
    L10 reg3;

public:
    Geffe(unsigned init1, unsigned init2, unsigned init3) :
      reg1(init1), reg2(init2), reg3(init3) {}

    int get_bit()
    {
        int x = reg1.shift();
        int y = reg2.shift();
        int s = reg3.shift();

        return ((s * x) ^ ((1 ^ s) * y));
    }
};
