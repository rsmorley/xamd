
#ifndef DielectricMaterial_h
#define DielectricMaterial_h

#include "Material.h"
#include "Color.h"

class DielectricMaterial : public Material {
 public:
  DielectricMaterial(const Color& color, float eta1, float eta2);
  virtual ~DielectricMaterial();

  virtual void shade(Color& result, RenderContext& context, const Ray& ray,
                     const HitRecord& hit, int depth) const;

 private:
  DielectricMaterial(const DielectricMaterial&);
  DielectricMaterial& operator=(const DielectricMaterial&);

  Color color;
  float eta1;
  float eta2;
};

#endif
