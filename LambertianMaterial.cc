
#include "LambertianMaterial.h"
#include "HitRecord.h"
#include "Light.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include <iostream>
using namespace std;

LambertianMaterial::LambertianMaterial(const Color& color, float Kd, float Ka)
  :color(color), Kd(Kd), Ka(Ka)
{
}

LambertianMaterial::~LambertianMaterial()
{
}

void LambertianMaterial::shade(Color& result, RenderContext& context,
                               const Ray& ray, const HitRecord& hit, int depth) const
{
  const Scene* scene = context.getScene();
  const vector<Light*>& lights = scene->getLights();
  Vector hitpos = ray.origin()+ray.direction()*hit.getMax();
  Vector normal;
  normal = hit.getNormal();
  //cerr << "normal" << normal << "\n";
  //result = Color(normal.x()+1, normal.y()+1, normal.z()+1);
  //result *= 0.5;
  //return;

  double costheta = normal.dot(ray.direction());
  if(costheta > 0)
    normal = -normal;

  const Object* world = scene->getObject();
  Color light = scene->getAmbient()*Ka;

    Light*const* begin = &lights[0];
    Light*const* end = &lights[0]+lights.size();
    while(begin != end)
    {
      Color light_color;
      Vector to_light;
      double dist = (*begin++)->getLight(light_color, to_light, context, hitpos);
      double inverse_dist = 1.0 / dist;
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
	  light += light_color*(Kd*cosphi);
      }
    }
  result = light*color;
  //normal = (normal + Vector( 1, 1, 1 ) ) * 0.5f;
  //result = Color( normal.x(), normal.y(), normal.z() );
}
