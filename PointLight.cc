#include "PointLight.h"

PointLight::PointLight(const Vector& location, const Color& color)
  : color(color), location(location)
{
}

PointLight::~PointLight()
{
}

double PointLight::getLight(Color& light_color, Vector& light_dir, const RenderContext& context, const Vector& hPos) const
{
  light_color = color;
  Vector dir = location-hPos;
  double len = dir.length();
  light_dir = dir;
  return len;
}
