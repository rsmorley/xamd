#include "DielectricMaterial.h"
#include "Background.h"
#include "HitRecord.h"
#include "Light.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"

#include <algorithm>
#include <float.h>
#include <iostream>
using namespace std;

DielectricMaterial::DielectricMaterial(const Color& color, float eta1, float eta2)
  :color(color), eta1(eta1), eta2(eta2)
{
}

DielectricMaterial::~DielectricMaterial()
{
}

void DielectricMaterial::shade(Color& result, RenderContext& context,
                               const Ray& ray, const HitRecord& hit, int depth) const
{
  if(depth > 5)
  {
    result = Color(0,0,0);
  //  cerr << "depth: " << depth << "\n";
    return;
  }


  const Scene* scene = context.getScene();
  //const vector<Light*>& lights = scene->getLights();
  Vector hitpos = ray.origin()+ray.direction()*hit.getMax();
  Vector normal;
  normal = hit.getNormal();
  double costheta = normal.dot(-ray.direction());
  const Object* world = scene->getObject();

  float costhetaT;
  float R;
  Vector tVec;

  if(costheta < 0) //incoming
  {
    costhetaT = sqrt(1-pow(eta1/eta2,2)*(1-pow(costheta,2)));
    R = pow((eta1*costheta-eta2*costhetaT)/(eta1*costheta+eta2*costhetaT),2);
    tVec = eta1/eta2*ray.direction()+(eta1/eta2*costheta+costhetaT)*normal;
  }
  else
  {
    costhetaT = sqrt(1-pow(eta2/eta1,2)*(1-pow(costheta,2)));
    R = pow((eta2*costheta-eta1*costhetaT)/(eta2*costheta+eta1*costhetaT),2);
    tVec = eta2/eta1*ray.direction()+(eta2/eta1*costheta-costhetaT)*normal;
  }

  float T = 1-R;
  //cerr << "costheta: " << costheta << "T: " << T << " R: " << R << "\n";
  costheta = normal.dot(ray.direction());
  //cast reflection ray
  if(costheta > 0)
    normal = -normal;
  Vector rVec = ray.direction()-2*costheta*normal;
  Color reflectionResult(0.0,0.0,0.0);
  HitRecord reflectionHit(DBL_MAX);
  Ray reflectionRay(hitpos, rVec);
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
  result = reflectionResult*R;

  //cast transmitted ray
  Color transResult(0.0,0.0,0.0);
  HitRecord transHit(DBL_MAX);
  Ray transRay(hitpos, tVec);
  world->intersect(transHit, context, transRay);
  if(!transHit.getPrimitive())
  {
    // No intersection...
    Background* background = scene->getBackground();
    background->getBackgroundColor(transResult, context, transRay);
  }
  else
  {
    const Material* matl = transHit.getMaterial();
    matl->shade(transResult, context, transRay, transHit, depth+1);
  }
  //result += transResult*T;
}
