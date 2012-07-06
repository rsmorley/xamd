/* This code taken from Realistic Ray Tracing 
 * by Pete Shirley and R. Keith Morley 
 */

#include "Sample.h"
#include "Vector2.h"
#include <math.h>
#include <stdlib.h>

void Sample::jitter(Vector2* samples, int num_samples)
{
  int sqrt_samples = (int)(sqrt(num_samples));
  for (int i=0; i < sqrt_samples; i++)
    for (int j=0; j < sqrt_samples; j++)
    {
      float x = ((double)i + drand48()) / (double)sqrt_samples;
      float y = ((double)j + drand48()) / (double)sqrt_samples;
      Vector2 tVec2 = Vector2(x,y);
      samples[i*sqrt_samples+j] = tVec2;
    }
}


void Sample::boxFilter(Vector2* samples, int num_samples)
{
  for (int i=0; i < num_samples; i++)
  {
    Vector2 tVec2 = Vector2(samples[i].x()-0.5f, samples[i].y()-0.5f);
    samples[i] = tVec2;
  }
}

void Sample::tentFilter(Vector2* samples, int num_samples)
{
  for (int i=0; i < num_samples; i++)
  {
    float x = samples[i].x();
    float y = samples[i].y();

    if(x < 0.5f) samples[i].setX((float)sqrt(2.0+(double)x)-1.0f);
    else samples[i].setX(1.0f-(float)sqrt(2.0-2.0*(double)x));

    if(y < 0.5f) samples[i].setY((float)sqrt(2.0+(double)y)-1.0f);
    else samples[i].setY(1.0f-(float)sqrt(2.0-2.0*(double)y));
  }
}


void Sample::jitter(float* samples, int num_samples)
{
  for (int i=0; i < num_samples; i++)
    samples[i] = ((double)i + drand48()) / (double)num_samples;
}

