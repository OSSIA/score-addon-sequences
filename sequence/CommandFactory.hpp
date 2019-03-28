#pragma once
#include <score/command/Command.hpp>

namespace sequence
{
inline const CommandGroupKey& CommandFactoryName()
{
  static const CommandGroupKey key{"sequence"};
  return key;
}
}
