#ifndef PinholeCamera_h
#define PinholeCamera_h

#include "Camera.h"
#include "Vector.h"

class RenderContext;
class Ray;

class PinholeCamera: public Camera
{
  public: 
    PinholeCamera(const Vector& eye, const Vector& lookat, const Vector& up, double hfov);
    virtual ~PinholeCamera();

    virtual void preprocess(double aspectRatio);
    virtual void generateRay(Ray& ray, const RenderContext& context, double x, double y) const;

  private:
    double hfov;
    Vector eye;
    Vector lookat;
    Vector up;

    Vector u;
    Vector v;
    Vector lookdir;
};

#endif
