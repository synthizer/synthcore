#pragma once

namespace synthcore {

template <typename CALLABLE> class AtScopeExit {
public:
  AtScopeExit(CALLABLE callable) : callable(callable) {}
  ~AtScopeExit() { callable(); }

private:
  CALLABLE callable;
};

} // namespace synthizer