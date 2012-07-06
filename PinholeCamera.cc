#include "PinholeCamera.h"

#include "Ray.h"
#include "Vector.h"
#include <math.h>

PinholeCamera::PinholeCamera(const Vector& eye, const Vector& lookat, const Vector& up, double hfov)
  : eye(eye), lookat(lookat), up(up), hfov(hfov)
{
}

PinholeCamera::~PinholeCamera()
{
}

void PinholeCamera::preprocess(double aspectRatio)
{
  lookdir = lookat-eye;
  lookdir.normalize();
  u = lookdir.cross(up);
  v = u.cross(lookdir);
  double length = tan(hfov/2.*M_PI/180.);
  u.normalize();
  u *= length;
  v.normalize();
  v *= (length/aspectRatio);
}

void PinholeCamera::generateRay(Ray& ray, const RenderContext& context, double x, double y) const
{
  Vector direction = lookdir+u*x+v*y;
  direction.normalize();
  ray = Ray(eye, direction);
}
