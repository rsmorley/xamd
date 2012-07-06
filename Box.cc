#include "Box.h"
#include "HitRecord.h"
#include "Math.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Vector.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Box::Box(Material* material, const Vector& min, const Vector& max)
  : Primitive(material), min(min), max(max)
{
}

Box::~Box()
{
}

void Box::getBounds(BoundingBox& bbox) const
{ 
  cerr <<  "Box::getBounds() called!" << endl;
  exit( 1 );
}

void Box::intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const
{
  float tmin, tmax, tymin, tymax, tzmin, tzmax;
  Vector n;
  if(ray.direction().x() >= 0)
  {
    tmin = (min.x() - ray.origin().x()) / ray.direction().x();
    tmax = (max.x() - ray.origin().x()) / ray.direction().x();
    n = Vector(-1,0,0);
  }
  else
  {
    tmin = (max.x() - ray.origin().x()) / ray.direction().x();
    tmax = (min.x() - ray.origin().x()) / ray.direction().x();
    n = Vector(1,0,0);
  }
  if(ray.direction().y() >= 0)
  {
    tymin = (min.y() - ray.origin().y()) / ray.direction().y();
    tymax = (max.y() - ray.origin().y()) / ray.direction().y();
  }
  else
  {
    tymin = (max.y() - ray.origin().y()) / ray.direction().y();
    tymax = (min.y() - ray.origin().y()) / ray.direction().y();
  }

  if((tmin > tymax) || (tymin > tmax)) { return; }
  if(tymin > tmin) { 
    tmin = tymin;
    n = Vector(0,-1,0);
  }
  if(tymax < tmax) { 
    tmax = tymax; 
    n = Vector(0,1,0);
  }

  if(ray.direction().z() >= 0)
  {
    tzmin = (min.z() - ray.origin().z()) / ray.direction().z();
    tzmax = (max.z() - ray.origin().z()) / ray.direction().z();
  }
  else
  {
    tzmin = (max.z() - ray.origin().z()) / ray.direction().z();
    tzmax = (min.z() - ray.origin().z()) / ray.direction().z();
  }

  if((tmin > tzmax) || (tzmin > tmax)) { return; }
  if(tzmin > tmin) { 
    tmin = tzmin; 
    n = Vector(0,0,-1);
  }
  if(tzmax < tmax) { 
    tmax = tzmax; 
    n = Vector(0,0,1);
  }

  if(tmax < tmin)
    cerr << "tmax: " << tmax << "tmin: " << tmin << "\n";

  h.hit(tmax, this, material, n); // Tests t interval

}
