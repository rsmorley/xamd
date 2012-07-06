#ifndef Color_h
#define Color_h

class Color
{
  public:
    Color()
    {}

    ~Color()
    {}

    Color(float r, float g, float b)
    {
      data[0] = r;
      data[1] = g;
      data[2] = b;
    }

    float r() const 
    {
      return data[0];
    }

    float g() const 
    {
      return data[1];
    }

    float b() const 
    {
      return data[2];
    }

    Color operator+ (const Color& c) const
    {
      return Color(data[0] + c.data[0], data[1] + c.data[1], data[2] + c.data[2]);
    }

    Color& operator+= (const Color& c)
    {
      data[0] += c.data[0];
      data[1] += c.data[1]; 
      data[2] += c.data[2];
      return *this;
    }

    Color operator- (const Color& c) const
    {
      return Color(data[0] - c.data[0], data[1] - c.data[1], data[2] - c.data[2]);
    }

    Color& operator-= (const Color& c)
    {
      data[0] -= c.data[0];
      data[1] -= c.data[1]; 
      data[2] -= c.data[2];
      return *this;
    }

    Color operator* (const Color& c) const
    {
      return Color(data[0] * c.data[0], data[1] * c.data[1], data[2] * c.data[2]);
    }

    Color& operator*= (const Color& c)
    {
      data[0] *= c.data[0];
      data[1] *= c.data[1]; 
      data[2] *= c.data[2];
      return *this;
    }

    Color operator* (float f) const
    {
      return Color(data[0] * f, data[1] * f, data[2] * f);
    }

    Color& operator*= (float f)
    {
      data[0] *= f;
      data[1] *= f;
      data[2] *= f;
      return *this;
    }

    Color operator* (double d) const
    {
      return Color(data[0] * d, data[1] * d, data[2] * d);
    }

    Color& operator*= (double d)
    {
      data[0] *= d;
      data[1] *= d;
      data[2] *= d;
      return *this;
    }

    Color& operator= (const Color& c)
    {
      data[0] = c.data[0];
      data[1] = c.data[1];
      data[2] = c.data[2];
      return *this;
    }


  private:
    float data[3];
};
#endif
