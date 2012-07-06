
#ifndef BoundingBox_h
#define BoundingBox_h

#include "Vector.h"

class BoundingBox {
 public:
  BoundingBox();
  ~BoundingBox();

  void reset();
  void extend(const Vector&);

  Vector getMin() const {
    return min;
  }
  Vector getMax() const {
    return max;
  }
 private:
  Vector min, max;
};

#endif
