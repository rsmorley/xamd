
#include "MetalMaterial.h"
#include "Background.h"
#include "HitRecord.h"
#include "Light.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"

#include <float.h>
#include <iostream>
using namespace std;

MetalMaterial::MetalMaterial(const Color& color, int exponent)
  :color(color), exponent(exponent)
{
}

MetalMaterial::~MetalMaterial()
{
}

void MetalMaterial::shade(Color& result, RenderContext& context,
                               const Ray& ray, const HitRecord& hit, int depth) const
{
  if(depth > 5)
  {
    result = Color(0,0,0);
    return;
  }

  const Scene* scene = context.getScene();
  const vector<Light*>& lights = scene->getLights();
  Vector hitpos = ray.origin()+ray.direction()*hit.getMax();
  Vector normal;
  normal = hit.getNormal();
  double costheta = normal.dot(ray.direction());
  if(costheta > 0)
    normal = -normal;
  Vector R = ray.direction()-2*costheta*normal;

  const Object* world = scene->getObject();

  // Cast reflection rays...
  Color reflectionResult;
  HitRecord reflectionHit(DBL_MAX);
  Ray reflectionRay(hitpos, R);
  world->intersect(reflectionHit, context, reflectionRay);
  if(!reflectionHit.getPrimitive())
  {
    // No intersection...
    Background* background = scene->getBackground();
    background->getBackgroundColor(reflectionResult, context, reflectionRay);
  }
  else
  {
    const Material* matl = reflectionHit.getMaterial();
    matl->shade(reflectionResult, context, reflectionRay, reflectionHit, depth+1);
  }

  Color light = Color(0,0,0);
  Light*const* begin = &lights[0];
  Light*const* end = &lights[0]+lights.size();
  while(begin != end)
  {

    Color light_color;
    Vector to_light;
    (*begin++)->getLight(light_color, to_light, context, hitpos);
    double l_dist = to_light.length();
    to_light *= 1.0/l_dist;
    double cosphi = normal.dot( to_light );
    if(cosphi > 0){
      // Cast shadow rays...
      HitRecord shadowhit(l_dist);
      Ray shadowray(hitpos, to_light);
      world->intersect(shadowhit, context, shadowray);
      if(!shadowhit.getPrimitive())
	// No shadows...
	light += light_color*cosphi*pow(cosphi,exponent);
    }

  }
  
  result = color * (reflectionResult + light);
}
