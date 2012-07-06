#ifndef Camera_h
#define Camera_h

class RenderContext;
class Ray;

class Camera
{
  public: 
    Camera();
    virtual ~Camera();

    virtual void preprocess(double aspectRatio) = 0;
    virtual void generateRay(Ray& ray, const RenderContext& context, double x, double y) const = 0;

  private:


};

#endif
