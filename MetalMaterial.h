
#ifndef MetalMaterial_h
#define MetalMaterial_h

#include "Material.h"
#include "Color.h"

class MetalMaterial : public Material {
 public:
  MetalMaterial(const Color& color, int exponent);
  virtual ~MetalMaterial();

  virtual void shade(Color& result, RenderContext& context, const Ray& ray,
                     const HitRecord& hit, int depth) const;

 private:
  MetalMaterial(const MetalMaterial&);
  MetalMaterial& operator=(const MetalMaterial&);

  Color color;
  int exponent;
};

#endif
