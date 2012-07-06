
#include "Image.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
using namespace std;

static void error(const std::string& filename, const std::string& errtext)
{
  cerr << "Error reading image: " << filename << ": " << errtext << '\n';
  exit(1);
}

/* needs to be adjusted to convert Pixels to Colors */
/*
Image::Image(const std::string& filename)
{
  cerr << "Reading " << filename << "...";
  ifstream in(filename.c_str(), ios::in | ios::binary);
  if(!in)
    error(filename, "Error opening file");
  if(in.get() != 'P' || !in)
    error(filename, "Error reading magic number (1st digit)");
  if(in.get() != '6' || !in)
    error(filename, "Error reading magic number (2nd digit)");
  int maxValue;
  in >> xres >> yres >> maxValue;
  in.get();
  cerr << " " << xres << "x" << yres << "...";
  if(!in)
    error(filename, "Error reading metadaa");
  data = new Color*[yres];
  Color* c = new Color[xres*yres];
  for(int i=0;i<yres;i++)
    data[i] = c + i*xres;
  for(int i=yres-1;i>=0;i--)
    in.read(reinterpret_cast<char*>(data[i]), sizeof(Color)*xres);
  if(!in)
    error(filename, "Error reading pixels");
  cerr << " done\n";
}
*/

Image::Image(int xres, int yres)
  : xres(xres), yres(yres)
{
  data = new Color*[yres];
  Color* c = new Color[xres*yres];
  for(int i=0;i<yres;i++)
    data[i] = c + i*xres;
}

Image::~Image()
{
  delete[] data[0];
  delete[] data;
}

void Image::write(const std::string& filename, const float gamma) const
{
  std::ofstream out(filename.c_str(), std::ios::out);
  out << "P3 " << xres << " " << yres << " 255\n";
  int red, green, blue;
  for(int i = xres-1;i > -1; i--) {
    for(int j =yres-1;j > -1; j--) {
      Pixel p;
      Color c = data[i][j];
      float gcRed = pow(c.r(), 1/gamma);
      float gcGreen = pow(c.g(), 1/gamma);
      float gcBlue = pow(c.b(), 1/gamma);
      p.r = gcRed < 0.f? 0: gcRed >= 1.f? 255 : (int)(gcRed * 255.f);
      p.g = gcGreen < 0.f? 0: gcGreen >= 1.f? 255 : (int)(gcGreen * 255.f);
      p.b = gcBlue < 0.f? 0: gcBlue >= 1.f? 255 : (int)(gcBlue * 255.f);
      red = p.r;
      green = p.g;
      blue = p.b;
      out << setw(4) << red
          << setw(4) << green
          << setw(4) << blue
          << endl;
    }
  }
}
/*
void Image::write(const std::string& filename) const
{
  std::ofstream out(filename.c_str(), std::ios::out);
  out << "P6 " << xres << " " << yres << " 255\n";
  for(int i=yres-1;i>=0;i--)
    out.write(reinterpret_cast<char*>(data[i]), sizeof(Pixel)*xres);
}
*/
