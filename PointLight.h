#ifndef PointLight_h
#define PointLight_h

#include "Color.h"
#include "Light.h"
#include "Vector.h"

class PointLight : public Light
{
  public:
    PointLight(const Vector& location, const Color& color);
    virtual ~PointLight();

    virtual double getLight(Color& light_color, Vector& light_dir, const RenderContext& context, const Vector& hPos) const;

  private:
    Color color;
    Vector location;
};

#endif
