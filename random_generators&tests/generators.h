#include <random>
#include <chrono>
#include <iostream>
#include "registry.h"

const int int_bits = 32;
const long max_int = (long) pow(2, int_bits) - 1;

std::vector<unsigned char> cxx_gen(int n_bytes)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned> distribution(0, max_int);
  std::vector<unsigned char> result;
  for (int i = 0; i < n_bytes; i++) {
    result.push_back(distribution(generator) & 0xFF);
  }
  return result;
}

std::vector<unsigned char> lemmer_gen(int n_bytes, char mode)
{
  const unsigned long m = (long) pow(2, 32);
  const unsigned a = (unsigned) pow(2, 16) + 1;
  const unsigned c = 119;
  unsigned x = std::chrono::system_clock::now().time_since_epoch().count();
  std::vector<unsigned char> result;
  for (int i = 0; i < n_bytes; i++) {
    x = (a * x + c) % m;
    if (mode == 'h') {
      result.push_back(
        (x >> (8 * (sizeof(unsigned) - sizeof(unsigned char)))) & 0xFF
      );
    } else if (mode == 'l') {
      result.push_back(x & 0xFF);
    } else {
      throw "unknown mode\n";
    }
  }
  return result;
}

std::vector<unsigned char> registry_gen(int n_bytes, int reg_size)
{
  L* registry = nullptr;
  if (reg_size == 20) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    registry = new L20(seed);
  } else if (reg_size == 89) {
    registry = new L89(cxx_gen(((int) 89 / 8) + 1));
  } else {
    throw "unsupported registry size\n";
  }

  std::vector<unsigned char> result;
  for (int i = 0; i < n_bytes; i++) {
    unsigned char byte = 0x0;
    for (int j = 0; j < 8; j++) {
      byte |= registry->shift();
      byte <<= 1;
    }
    result.push_back(byte);
  }
  delete registry;
  return result;
}

std::vector<unsigned char> geffe_gen(int n_bytes)
{
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
  unsigned seed3 = std::chrono::system_clock::now().time_since_epoch().count();
  Geffe generator(seed1, seed2, seed3);
  std::vector<unsigned char> result;
  for (int i = 0; i < n_bytes; i++) {
    unsigned char byte = 0x0;
    for (int j = 0; j < 8; j++) {
      byte |= generator.get_bit();
      byte <<= 1;
    }
    result.push_back(byte);
  }
  return result;
}
