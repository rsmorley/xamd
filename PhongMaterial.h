
#ifndef PhongMaterial_h
#define PhongMaterial_h

#include "Material.h"
#include "Color.h"

class PhongMaterial : public Material {
 public:
  PhongMaterial(const Color& color, float Kd, float Ka, const Color& highlight, int exponent);
  virtual ~PhongMaterial();

  virtual void shade(Color& result, RenderContext& context, const Ray& ray,
                     const HitRecord& hit, int depth) const;

 private:
  PhongMaterial(const PhongMaterial&);
  PhongMaterial& operator=(const PhongMaterial&);

  Color color;
  Color highlight;
  float Kd;
  float Ka;
  int exponent;
};

#endif
