#include "Camera.h"
#include "Image.h"
#include "LambertianMaterial.h"
#include "Material.h"
#include "Parser.h"
#include "Plane.h"
#include "PointLight.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#define GAMMA (2.2)

using namespace std;

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cerr << "Usage: xamd sceneFile" << endl;
    return 1;
  }

  ifstream sceneFile(argv[1]);
  if(!sceneFile.good())
  {
    cerr << "cannot open file " << argv[1] << endl;
    return 1;
  }

  Parser p(sceneFile);
  string outputFile = "image.ppm";
  Scene* scene = p.parseScene(outputFile);

  scene->preprocess();
  scene->render();
  scene->getImage()->write(outputFile, GAMMA);

  return 0;
}
