
#include "Group.h"

/* added for debugging one object at a time */
#include "Box.h"
#include "Plane.h"
#include "PointLight.h"
#include "Sphere.h" 
#include "Triangle.h" 

#include <iostream>

using namespace std;

Group::Group()
{
}

Group::~Group()
{
}

void Group::addObject(Object* object)
{
  //we only have some primitives implemented
  if(dynamic_cast<Plane*>(object))
  {
    cerr << endl << "Added plane" << endl;
    objects.push_back(object);
  }
  else if(dynamic_cast<PointLight*>(object))
  {
    cerr << endl << "Added PointLight" << endl;
    objects.push_back(object);
  }
  else if(dynamic_cast<Sphere*>(object))
  {
    cerr << endl << "Added sphere" << endl;
    objects.push_back(object);
  }
  else if(dynamic_cast<Triangle*>(object))
  {
    cerr << endl << "Added triangle" << endl;
    objects.push_back(object);
  }
  else if(dynamic_cast<Box*>(object))
  {
    cerr << endl << "Added box" << endl;
    objects.push_back(object);
  }
}

void Group::preprocess()
{
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  while (begin != end)
    (*begin++)->preprocess();
}


void Group::getBounds(BoundingBox& bbox) const
{
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  while (begin != end)
    (*begin++)->getBounds(bbox);
}


void Group::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  while (begin != end) {
    //std::cerr << "intersecting '" << (*begin)->type() << "'"  << std::endl;
    (*begin++)->intersect(hit, context, ray);
  }
}
