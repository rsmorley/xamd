#ifndef Vector2_h
#define Vector2_h

#include <math.h>
#include <iosfwd>

class Vector2
{
  public:

    Vector2() {}

    Vector2(double x, double y)
    {
      data[0] = x;
      data[1] = y;
    }

    double x() const
    {
      return data[0];
    }
      
    double y() const
    {
      return data[1];
    }

    void setX(int value)
    {
      data[0] = value;
    }

    void setY(int value)
    {
      data[1] = value;
    }

    Vector2 operator+ (const Vector2& v) const
    {
      return Vector2(data[0] + v.data[0], data[1] + v.data[1]);
    }

    Vector2& operator+= (const Vector2& v) 
    {
      data[0] += v.data[0]; 
      data[1] += v.data[1]; 
      return *this;
    }
	  
    Vector2 operator- (const Vector2& v) const
    {
      return Vector2(data[0] - v.data[0], data[1] - v.data[1]);
    }

    Vector2 operator- () const
    {
      return Vector2(-data[0], -data[1]);
    }

    Vector2& operator-= (const Vector2& v) 
    {
      data[0] -= v.data[0]; 
      data[1] -= v.data[1]; 
      return *this;
    }

    Vector2 operator* (double f) const
    {
      return Vector2(data[0] * f, data[1] * f);
    }

    Vector2& operator*= (double f)
    {
      data[0] *= f;
      data[1] *= f;
      return *this;
    }

    Vector2 operator/ (double f) const
    {
      f = 1/f;
      return Vector2(data[0] * f, data[1] * f);
    }

    Vector2& operator/= (double f)
    {
      f = 1./f;
      data[0] *= f;
      data[1] *= f;
      return *this;
    }

    Vector2& operator= (const Vector2& v)
    {
      data[0] = v.data[0];
      data[1] = v.data[1];
      return *this;
    }

    friend Vector2 operator* (double f, const Vector2& v); 

    double operator[] (int i) const
    {
      return data[i];
    }

    double& operator[] (int i)
    {
      return data[i];
    }

  private:
    double data[2];
};


std::ostream& operator<< (std::ostream&, const Vector2& v);

#endif
