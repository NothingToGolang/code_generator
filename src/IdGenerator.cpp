#include "code_generator/IdGenerator.hpp"
#include <atomic>

uint32_t IdGenerator::nextID()
{
  static std::atomic_uint_fast32_t idSerial(0);
  return idSerial.fetch_add(1);
}
