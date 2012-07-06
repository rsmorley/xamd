#include "Triangle.h"
#include "HitRecord.h"
#include "Math.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Vector.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Triangle::Triangle(Material* material, const Vector& c1, const Vector& c2, const Vector& c3)
  : Primitive(material), c1(c1), c2(c2), c3(c3)
{
}

Triangle::~Triangle()
{
}

void Triangle::getBounds(BoundingBox& bbox) const
{ 
  cerr <<  "Triangle::getBounds() called!" << endl;
  exit( 1 );
}

void Triangle::intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const
{
  double t;
  double A = c1[0] - c2[0];
  double B = c1[1] - c2[1];
  double C = c1[2] - c2[2];

  double D = c1[0] - c3[0];
  double E = c1[1] - c3[1];
  double F = c1[2] - c3[2];

  double G = ray.direction().x();
  double H = ray.direction().y();
  double I = ray.direction().z();

  double J = c1[0] - ray.origin().x();
  double K = c1[1] - ray.origin().y();
  double L = c1[2] - ray.origin().z();

  double EIHF = E*I-H*F;
  double GFDI = G*F-D*I;
  double DHEG = D*H-E*G;

  double denom = (A*EIHF + B*GFDI + C*DHEG);

  if (denom == 0.0) {
    return;
  }
  denom = 1.0 / denom;
  double beta = (J*EIHF + K*GFDI + L*DHEG) * denom;
  if (beta <0.0 || beta > 1.0) {
    return;
  }

  double AKJB = A*K - J*B;
  double JCAL = J*C - A*L;
  double BLKC = B*L - K*C;

  double gamma = (I*AKJB + H*JCAL + G*BLKC) * denom;
  if (gamma < 0.0 || beta + gamma > 1.0) {
    return;
  }

  t = -(F*AKJB + E*JCAL + D*BLKC) * denom;
  Vector normal = (c3 - c2).cross(c1 - c2);
  h.hit(t, this, material, normal); // Tests t interval
}


