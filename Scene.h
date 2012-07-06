#ifndef Scene_h
#define Scene_h

#include "Color.h"
#include <vector>

class Background;
class Camera;
class Image;
class Light;
class Object;
class Ray;
class RenderContext;

using namespace std;

class Scene
{
  public:
    Scene();
    ~Scene();

    void preprocess();
    void render();
    void traceRay(Color& pixel, const RenderContext& context, const Ray& ray, int depth) const;

    int getMaxDepth() const
    { return maxDepth; }

    inline Background* getBackground() const
    { return background; }

    inline Camera* getCamera() const 
    { return camera; }

    inline Color getAmbient() const
    { return ambient; }

    inline Image* getImage() const
    { return image; }

    inline Object* getObject() const
    { return object; }

    void setMaxRayDepth(int depth)
    { maxDepth = depth; }

    void setMinAttenuation(int value)
    { attenuation = value; }
    
    const std::vector<Light*>& getLights() const 
    { return lights; }

    void setBackground(Background* bg)
    { background = bg; }

    void setCamera(Camera* c)
    { camera = c; }

    void setAmbient(const Color& color)
    { ambient = color; }

    void setImage(Image* i)
    { image = i; }

    void setObject(Object* o)
    { object = o; }

    void addLight(Light* light)
    { lights.push_back(light); }


  private:
    int maxDepth;
    int attenuation;
    Background* background;
    Camera* camera;
    Color ambient;
    Image* image;
    Object* object;
    std::vector<Light*> lights;
  
};

#endif
