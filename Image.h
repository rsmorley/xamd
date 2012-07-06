
#ifndef Image_h
#define Image_h

#include "Color.h"
#include "Math.h"
#include <string>

struct Pixel {
  unsigned char r, g, b;
};

class Image {
 public:
  Image(const std::string& name);
  Image(int xres, int yres);
  ~Image();
  void set(int x, int y, const Color& c) {
    data[y][x] = c;
  }
  void write(const std::string& filename, const float gamma) const;
  double aspect_ratio() const {
    return double(xres)/double(yres);
  }
  int getXresolution() {
    return xres;
  }
  int getYresolution() {
    return yres;
  }
  Color interpolate(float x, float y) const {
    x *= xres; y *= yres;
    int ix = Floor(x)%xres;
    if(ix<0)
      ix += xres;
    int ix1 = (ix+1)%xres;
    int iy = Floor(y)%yres;
    if(iy<0)
      iy += yres;
    int iy1 = (iy+1)%yres;
    float fx = x-ix;
    float fy = y-iy;

    Color c00 = data[iy][ix];
    Color c01 = data[iy][ix1];
    Color c10 = data[iy1][ix];
    Color c11 = data[iy1][ix1];
    Color c = c00*(1-fx)*(1-fy) + c01*fx*(1-fy) + c10*(1-fx)*fy + c11*fx*fy;
    return c*(1./255);
  }
 protected:
  Color** data;
  int xres, yres;
  Image(const Image&);
  Image& operator=(const Image&);
};

#endif
