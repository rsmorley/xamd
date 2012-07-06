#ifndef Sample_h
#define Sample_h

#include <math.h>

class Vector2;

class Sample
{
  public:

    void jitter(Vector2* samples, int num_samples);

    void boxFilter(Vector2* samples, int num_samples);

    void tentFilter(Vector2* samples, int num_samples);

    void jitter(float* samples, int num_samples);


};


#endif
