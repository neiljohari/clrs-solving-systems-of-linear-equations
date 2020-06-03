#pragma once

#include "AlmostEquals.h"

template <typename T>
class AlmostEqualsComparator {
public:
  bool operator()(const T& rhs, const T& lhs) const {
    return AlmostEquals(rhs, lhs);
  }
};
