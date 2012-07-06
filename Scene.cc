#include "Scene.h"

#include "Background.h"
#include "Camera.h"
#include "Color.h"
#include "Image.h"
#include "Light.h"
#include "Material.h"
#include "Object.h"
#include "Sample.h"
#include "Vector2.h"

#include <float.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#define NUM_SAMPLES (9)
Scene::Scene()
{
  ambient = Color(0,0,0);
  background = 0;
  camera = 0;
  image = 0;
  object = 0;
}

Scene::~Scene()
{
  delete background;
  delete camera;
  delete image;
  for(int i=0; i < lights.size(); i++)
  {
    Light* light = lights[i];
    delete light;
  }
  delete object;
}
  
void Scene::preprocess()
{
  background->preprocess();
  double temp = image->aspect_ratio();
  camera->preprocess(temp);
  for(int i=0; i<lights.size(); i++)
  {
    Light* light = lights[i];
    light->preprocess();
  }
  object->preprocess();
}

void Scene::render()
{
  if(!object || !background || !camera || !image){
    cerr << "Incomplete scene, cannot render!\n";
  }
  Vector2* samples = new Vector2[NUM_SAMPLES];
  Sample sampler = Sample();
  sampler.jitter(samples, NUM_SAMPLES);
  sampler.boxFilter(samples, NUM_SAMPLES);
  int xres = image->getXresolution();
  int yres = image->getYresolution();
  RenderContext context(this);
  double dx = 2./xres;
  double xmin = -1. + dx/2.;
  double dy = 2./yres;
  double ymin = -1. + dy/2.;
  Color atten(1,1,1);
  for(int i=0;i<yres;i++){
    //cerr << "y=" << i << '\n';
    double y = ymin + i*dy;
    for(int j=0;j<xres;j++){
      double x = xmin + j*dx;
      //cerr << "x=" << j << ", y=" << i << '\n';
      float r,g,b;
      r=g=b=0;
      for(int k=0;k<NUM_SAMPLES;k++)
      {
	Ray ray;
	camera->generateRay(ray, context, x+samples[k].x()*dx, y+samples[k].y()*dy);
	HitRecord hit(DBL_MAX);
	object->intersect(hit, context, ray);
	Color result;
	if(hit.getPrimitive()){
	  // Ray hit something...
	  const Material* matl = hit.getMaterial();
	  matl->shade(result, context, ray, hit, 0);
	} else {
	  background->getBackgroundColor(result, context, ray);
	}
	r += result.r();
	g += result.g();
	b += result.b();
      }
      r /= (float)NUM_SAMPLES;
      g /= (float)NUM_SAMPLES;
      b /= (float)NUM_SAMPLES;
      image->set(j, i, Color(r,g,b));
    }
  }
}




