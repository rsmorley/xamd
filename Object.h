#ifndef Object_h
#define Object_h

#include "BoundingBox.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Ray.h"
#include <string>

class Object
{
  public:
    Object();
    virtual ~Object();

    virtual std::string type() { return "unimplemented"; }
    virtual void preprocess();
    virtual void getBounds(BoundingBox& bbox) const = 0;
    virtual void intersect(HitRecord& h, const RenderContext& context, const Ray& ray) const = 0;

};

#endif
