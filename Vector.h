#ifndef Vector_h
#define Vector_h

#include <math.h>
#include <iosfwd>

class Vector
{
  public:

    Vector() {}

    Vector(double x, double y, double z)
    {
      data[0] = x;
      data[1] = y;
      data[2] = z;
    }

    double x() const
    {
      return data[0];
    }
      
    double y() const
    {
      return data[1];
    }

    double z() const
    {
      return data[2];
    }

    Vector operator+ (const Vector& v) const
    {
      return Vector(data[0] + v.data[0], data[1] + v.data[1], data[2] + v.data[2]);
    }

    Vector& operator+= (const Vector& v) 
    {
      data[0] += v.data[0]; 
      data[1] += v.data[1]; 
      data[2] += v.data[2];
      return *this;
    }
	  
    Vector operator- (const Vector& v) const
    {
      return Vector(data[0] - v.data[0], data[1] - v.data[1], data[2] - v.data[2]);
    }

    Vector operator- () const
    {
      return Vector(-data[0], -data[1], -data[2]);
    }

    Vector& operator-= (const Vector& v) 
    {
      data[0] -= v.data[0]; 
      data[1] -= v.data[1]; 
      data[2] -= v.data[2];
      return *this;
    }

    Vector operator* (double f) const
    {
      return Vector(data[0] * f, data[1] * f, data[2] * f);
    }

    Vector& operator*= (double f)
    {
      data[0] *= f;
      data[1] *= f;
      data[2] *= f;
      return *this;
    }

    Vector operator/ (double f) const
    {
      f = 1/f;
      return Vector(data[0] * f, data[1] * f, data[2] * f);
    }

    Vector& operator/= (double f)
    {
      f = 1./f;
      data[0] *= f;
      data[1] *= f;
      data[2] *= f;
      return *this;
    }

    Vector& operator= (const Vector& v)
    {
      data[0] = v.data[0];
      data[1] = v.data[1];
      data[2] = v.data[2];
      return *this;
    }

    friend Vector operator* (double f, const Vector& v); 

    double operator[] (int i) const
    {
      return data[i];
    }

    double& operator[] (int i)
    {
      return data[i];
    }

    inline Vector cross(const Vector& v);
    inline double dot(const Vector& v) const;
    inline void normalize();
    inline double length() const;
    inline double lengthSquared() const;


  private:
    double data[3];
};

Vector Vector::cross(const Vector& v)
{
  return Vector(
      data[1] * v[2] - data[2] * v[1],
      data[2] * v[0] - data[0] * v[2],
      data[0] * v[1] - data[1] * v[0]
      );
}

double Vector::dot(const Vector& v) const
{
  return data[0] * v[0] + data[1] * v[1] + data[2] * v[2];
}

void Vector::normalize()
{
  double length = this->length();
  data[0] /= length;
  data[1] /= length;
  data[2] /= length;
}

double Vector::length() const
{
  return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
}

double Vector::lengthSquared() const
{
  return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

std::ostream& operator<< (std::ostream&, const Vector& v);

#endif
