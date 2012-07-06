#include "Primitive.h"
#include "Material.h"

Primitive::Primitive(Material* material)
  :material(material)
{
}

Primitive::~Primitive()
{
}

void Primitive::preprocess()
{
  material->preprocess();
}

