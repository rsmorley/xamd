#include "Parser.h"
#include "PinholeCamera.h"
#include "ConstantBackground.h"
#include "PointLight.h"
#include "DielectricMaterial.h"
#include "LambertianMaterial.h"
#include "PhongMaterial.h"
#include "MetalMaterial.h"
#include "Group.h"
#include "Box.h"
#include "Sphere.h"
//#include "Disk.h"
//#include "Ring.h"
#include "Plane.h"
#include "Triangle.h"
#include "Scene.h"
#include "Image.h"
#include <cmath>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

void Parser::throwParseException(
    string const &message ) const
{
  cerr << next_token.line_number << ":" << next_token.column_number << ": " << message << endl;
  exit( 1 );
}

void Parser::readNextToken()
{
  int state = 0;
  long long mantissa = 0;
  int exponent = 0;
  int exponent_adjustment = 0;
  bool negative_mantissa = false;
  bool negative_exponent = false;
  for ( ; ; ) {
    int character = input.get();
    switch ( state ) {
      case 0:
        next_token.line_number = line_number;
        next_token.column_number = column_number;
        if ( input.eof() ) {
          next_token.token_type = Token::end_of_file;
          return;
        } else if ( character == ' ' || character == '\t' ||
                    character == '\r' || character == '\n' )
          state = 0;
        else if ( character == '/' )
          state = 1;
        else if ( character == '+' || character == '-' ) {
          negative_mantissa = character == '-';
          state = 3;
        } else if ( character >= '0' && character <= '9' ) {
          mantissa = character - '0';
          state = 4;
        } else if ( character == '.' )
          state = 5;
        else if ( character == '"' ) {
          next_token.string_value.clear();
          state = 10;
        } else if ( character >= 'A' && character <= 'Z' ||
                    character >= 'a' && character <= 'z' ||
                    character == '_' ) {
          next_token.string_value = static_cast< char >( character );
          state = 12;
        } else if ( character == ',' ) {
          ++column_number;
          next_token.token_type = Token::comma;
          return;
        } else if ( character == '{' ) {
          ++column_number;
          next_token.token_type = Token::left_brace;
          return;
        } else if ( character == '}' ) {
          ++column_number;
          next_token.token_type = Token::right_brace;
          return;
        } else if ( character == '[' ) {
          ++column_number;
          next_token.token_type = Token::left_bracket;
          return;
        } else if ( character == ']' ) {
          ++column_number;
          next_token.token_type = Token::right_bracket;
          return;
        } else
          throwParseException( "Unexpected character" );
        break;
      case 1:
        if ( character == '/' )
          state = 2;
        else
          throwParseException( "Malformed comment" );
        break;
      case 2:
        if ( character == '\n' || input.eof() )
          state = 0;
        break;
      case 3:
        if ( character >= '0' && character <= '9' ) {
          mantissa = character - '0';
          state = 4;
        } else if ( character == '.' )
          state = 5;
        else
          throwParseException( "Invalid number" );
        break;
      case 4:
        if ( character >= '0' && character <= '9' )
          mantissa = mantissa * 10 + character - '0';
        else if ( character == '.' )
          state = 6;
        else if ( character == 'E' || character == 'e' )
          state = 7;
        else {
          input.putback( static_cast< char >( character ) );
          next_token.integer_value = ( static_cast< int >( mantissa ) *
                                       ( negative_mantissa ? -1 : 1 ) );
          next_token.token_type = Token::integer;
          return;
        }
        break;
      case 5:
        if ( character >= '0' && character <= '9' ) {
          mantissa = character - '0';
          exponent_adjustment = 1;
          state = 6;
        } else
          throwParseException( "Invalid number" );
        break;
      case 6:
        if ( character >= '0' && character <= '9' ) {
          mantissa = mantissa * 10 + character - '0';
          ++exponent_adjustment;
        } else if ( character == 'E' || character == 'e' )
          state = 7;
        else {
          input.putback( static_cast< char >( character ) );
          next_token.real_value = ( mantissa * ( negative_mantissa ? -1 : 1 ) *
                                    pow( 10.0, -exponent_adjustment ) );
          next_token.token_type = Token::real;
          return;
        }
        break;
      case 7:
        if ( character == '+' || character == '-' ) {
          negative_exponent = character == '-';
          state = 8;
        } else if ( character >= '0' && character <= '9' ) {
          exponent = character - '0';
          state = 9;
        } else
          throwParseException( "Invalid number" );
        break;
      case 8:
        if ( character >= '0' && character <= '9' ) {
          exponent = character - '0';
          state = 9;
        } else
          throwParseException( "Invalid number" );
        break;
      case 9:
        if ( character >= '0' && character <= '9' )
          exponent = exponent * 10 + character - '0';
        else {
          input.putback( static_cast< char >( character ) );
          next_token.real_value = ( mantissa * ( negative_mantissa ? -1 : 1 ) *
                                    pow( 10.0, ( exponent * ( negative_exponent ? -1 : 1 ) -
                                                 exponent_adjustment ) ) );
          next_token.token_type = Token::real;
          return;
        }
        break;
      case 10:
        if ( input.eof() || character == '\n' )
          throwParseException( "Unterminated string" );
        else if ( character == '\\' )
          state = 11;
        else if ( character == '"' ) {
          ++column_number;
          next_token.token_type = Token::string;
          return;
        } else
          next_token.string_value.push_back( static_cast< char >( character ) );
        break;
      case 11:
        if ( input.eof() )
          throwParseException( "Unterminated string" );
        else if ( character == '\n' )
          next_token.string_value.push_back( '\n' );
        else if ( character == '\\' )
          next_token.string_value.push_back( '\\' );
        else if ( character == '"' )
          next_token.string_value.push_back( '"' );
        else
          next_token.string_value.push_back( static_cast< char >( character ) );
        state = 10;
        break;
      case 12:
        if ( character >= '0' && character <= '9' ||
             character >= 'A' && character <= 'Z' ||
             character >= 'a' && character <= 'z' ||
             character == '_' )
          next_token.string_value.push_back( static_cast< char >( character ) );
        else {
          input.putback( static_cast< char >( character ) );
          next_token.token_type = Token::string;
          return;
        }
        break;
    }
    if ( character == '\n' ) {
      ++line_number;
      column_number = 0;
    }
    else if ( character == '\t' )
      column_number = ( column_number + 8 ) / 8 * 8;
    else
      ++column_number;
  }
}

bool Parser::peek(
  Token::type const type )
{
  bool matched = next_token.token_type == type;
  if ( matched )
    readNextToken();
  return matched;
}

bool Parser::peek(
  string const &keyword )
{
  bool matched = ( next_token.token_type == Token::string &&
                   next_token.string_value == keyword );
  if ( matched )
    readNextToken();
  return matched;
}

Parser::Token Parser::match(
  Token::type const type,
  string const &failure_message )
{
  if ( next_token.token_type != type )
    throwParseException( failure_message );
  Token current_token( next_token );
  readNextToken();
  return current_token;
}

Parser::Token Parser::match(
  string const &keyword,
  string const &failure_message )
{
  if ( next_token.token_type != Token::string ||
       next_token.string_value != keyword )
    throwParseException( failure_message );
  Token current_token( next_token );
  readNextToken();
  return current_token;
}

string Parser::parseString()
{
  Token next( match( Token::string, "Expected a string" ) );
  return next.string_value;
}

bool Parser::parseBoolean()
{
  if ( peek( "true" ) )
    return true;
  else if ( peek( "false" ) )
    return false;
  else
    throwParseException( "Expected `true' or `false'." );
  return false;
}

int Parser::parseInteger()
{
  Token next( match( Token::integer, "Expected an integer" ) );
  return next.integer_value;
}

double Parser::parseReal()
{
  if ( next_token.token_type == Token::integer ) {
    Token next( match( Token::integer, "Expected an integer or real" ) );
    return static_cast< double >( next.integer_value );
  }
  Token next( match( Token::real, "Expected an integer or real" ) );
  return next.real_value;
}

Vector const Parser::parseVector()
{
  match( Token::left_bracket, "Expected a left bracket" );
  double x = parseReal();
  match( Token::comma, "Expected a comma" );
  double y = parseReal();
  match( Token::comma, "Expected a comma" );
  double z = parseReal();
  match( Token::right_bracket, "Expected a right bracket" );
  return Vector( x, y, z );
}

Color const Parser::parseColor()
{
  if ( peek( Token::left_bracket ) ) {
    double r = parseReal();
    match( Token::comma, "Expected a comma" );
    double g = parseReal();
    match( Token::comma, "Expected a comma" );
    double b = parseReal();
    match( Token::right_bracket, "Expected a right bracket" );
    return Color( r, g, b );
  }
  double v = parseReal();
  return Color( v, v, v );
}

Camera *Parser::parsePinholeCamera()
{
  Vector eye( 0.0, 0.0, 0.0 );
  Vector lookat( 0.0, 1.0, 0.0 );
  Vector up( 0.0, 0.0, 1.0 );
  double hfov = 90.0;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "eye" ) )
        eye = parseVector();
      else if ( peek( "lookat" ) )
        lookat = parseVector();
      else if ( peek( "up" ) )
        up = parseVector();
      else if ( peek( "hfov" ) )
        hfov = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `eye', `lookat', `up', `hfov' or }." );
    }
  return new PinholeCamera( eye, lookat, up, hfov );
}

Camera *Parser::parseCamera()
{
    if ( peek( "pinhole" ) )
        return parsePinholeCamera();
    throwParseException( "Expected a camera type." );
    return 0;
}

Background *Parser::parseConstantBackground()
{
  Color color( 0.0, 0.0, 0.0 );
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `color' or }." );
    }
  return new ConstantBackground( color );
}

Background *Parser::parseBackground()
{
    if ( peek( "constant" ) )
        return parseConstantBackground();
    throwParseException( "Expected a background type." );
    return 0;
}

Light *Parser::parsePointLight()
{
  Vector position( 0.0, 0.0, 10.0 );
  Color color( 1.0, 1.0, 1.0 );
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "position" ) )
        position = parseVector();
      else if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `position', `color' or }." );
    }
  return new PointLight( position, color );
}

Light *Parser::parseLight()
{
    if ( peek( "point" ) )
      return parsePointLight();
    throwParseException( "Expected a light type." );
    return 0;
}

Material *Parser::parseLambertianMaterial()
{
  Color color( 1.0, 1.0, 1.0 );
  double Kd = 0.6;
  double Ka = 0.3;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( "Kd" ) )
        Kd = parseReal();
      else if ( peek( "Ka" ) )
        Ka = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `color', `Kd', `Ka' or }." );
    }
  return new LambertianMaterial( color, Kd, Ka );
}

Material *Parser::parsePhongMaterial()
{
  Color color( 1.0, 1.0, 1.0 );
  double Kd = 0.6;
  double Ka = 0.3;
  Color highlight( 1.0, 1.0, 1.0 );
  int exponent = 100;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( "Kd" ) )
        Kd = parseReal();
      else if ( peek( "Ka" ) )
        Ka = parseReal();
      else if ( peek( "highlight" ) )
        highlight = parseColor();
      else if ( peek( "exponent" ) )
        exponent = parseInteger();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `color', `Kd', `Ka', `highlight', `exponent' or }." );
    }
  return new PhongMaterial( color, Kd, Ka, highlight, exponent );
}

Material *Parser::parseMetalMaterial()
{
  Color color( 1.0, 1.0, 1.0 );
  int exponent = 100;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( "exponent" ) )
        exponent = parseInteger();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `color', `exponent' or }." );
    }
  return new MetalMaterial( color, exponent );
}

Material *Parser::parseDielectricMaterial()
{
  Color color( 1.0, 1.0, 1.0 );
  float eta1 = 1;
  float eta2 = 1.33;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "color" ) )
        color = parseColor();
      else if ( peek( "eta1" ) )
        eta1 = parseReal();
      else if ( peek( "eta2" ) )
        eta2 = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `color', `eta1', `eta2' or }." );
    }
  return new DielectricMaterial( color, eta1, eta2 );
}

Material *Parser::parseMaterial()
{
    if ( peek( "lambertian" ) )
      return parseLambertianMaterial();
    else if ( peek( "phong" ) )
      return parsePhongMaterial();
    else if ( peek( "metal" ) )
      return parseMetalMaterial();
    else if ( peek( "dielectric") )
      return parseDielectricMaterial();
    else if ( next_token.token_type == Token::string ) {
        map< string, Material * >::iterator found = defined_materials.find( parseString() );
        if ( found != defined_materials.end() )
            return ( *found ).second;
    }
    throwParseException( "Expected a material type." );
    return 0;
}

Object *Parser::parseGroupObject()
{
    Group *group = new Group();
    match( Token::left_brace, "Expected a left brace" );
    while ( !peek( Token::right_brace ) )
        group->addObject( parseObject() );
    return group;
}
Object *Parser::parsePlaneObject()
{
  Material *material = default_material;
  Vector normal( 0.0, 0.0, 1.0 );
  Vector point( 0.0, 0.0, 0.0 );
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "normal" ) )
        normal = parseVector();
      else if ( peek( "point" ) )
        point = parseVector();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `point', `normal' or }." );
    }
  return new Plane( material, normal, point );
}

Object *Parser::parseSphereObject()
{
  Material *material = default_material;
  Vector center( 0.0, 0.0, 0.0 );
  double radius = 0.5;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "center" ) )
        center = parseVector();
      else if ( peek( "radius" ) )
        radius = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `center', `radius' or }." );
    }
  return new Sphere( material, center, radius );
}


Object *Parser::parseBoxObject()
{
  Material *material = default_material;
  Vector corner1( -0.5, -0.5, 0.0 );
  Vector corner2( 0.5, 0.5, 1.0 );
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "corner1" ) )
        corner1 = parseVector();
      else if ( peek( "corner2" ) )
        corner2 = parseVector();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `corner1', `corner2' or }." );
    }
  return new Box( material, corner1, corner2 );
}

Object *Parser::parseDiskObject()
{
  Material *material = default_material;
  Vector center( 0.0, 0.0, 0.0 );
  Vector normal( 0.0, 0.0, 1.0 );
  double radius = 0.5;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "center" ) )
        center = parseVector();
      else if ( peek( "normal" ) )
        normal = parseVector();
      else if ( peek( "radius" ) )
        radius = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `center', `normal', `radius' or }." );
    }
  return NULL;
  //return new Disk( material, center, normal, radius );
}

Object *Parser::parseRingObject()
{
  Material *material = default_material;
  Vector center( 0.0, 0.0, 0.0 );
  Vector normal( 0.0, 0.0, 1.0 );
  double radius1 = 0.5;
  double radius2 = 1.0;
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "center" ) )
        center = parseVector();
      else if ( peek( "normal" ) )
        normal = parseVector();
      else if ( peek( "radius1" ) )
        radius1 = parseReal();
      else if ( peek( "radius2" ) )
        radius2 = parseReal();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `center', `normal', `radius1', `radius2' or }." );
    }
  return NULL;
  //return new Ring( material, center, normal, radius1, radius2 );
}

Object *Parser::parseTriangleObject()
{
  Material *material = default_material;
  Vector corner1( -0.5, 0.0, 0.0 );
  Vector corner2( 0.0, 0.0, 1.0 );
  Vector corner3( 0.5, 0.0, 0.0 );
  if ( peek( Token::left_brace ) )
    for ( ; ; ) {
      if ( peek( "material" ) )
        material = parseMaterial();
      else if ( peek( "corner1" ) )
        corner1 = parseVector();
      else if ( peek( "corner2" ) )
        corner2 = parseVector();
      else if ( peek( "corner3" ) )
        corner3 = parseVector();
      else if ( peek( Token::right_brace ) )
        break;
      else
        throwParseException( "Expected `material', `corner1', `corner2', `corner3' or }." );
    }
  return new Triangle( material, corner1, corner2, corner3 );
}

Object *Parser::parseObject()
{
    if ( peek( "group" ) )
      return parseGroupObject();
    else if ( peek( "plane" ) )
        return parsePlaneObject();
    else if ( peek( "sphere" ) )
        return parseSphereObject();
    else if ( peek( "box" ) )
        return parseBoxObject();
    else if ( peek( "disk" ) )
        return parseDiskObject();
    else if ( peek( "ring" ) )
        return parseRingObject();
    else if ( peek( "triangle" ) )
        return parseTriangleObject();
    else if ( next_token.token_type == Token::string ) {
        map< string, Object * >::iterator found = defined_objects.find( parseString() );
        if ( found != defined_objects.end() )
            return ( *found ).second;
    }
    throwParseException( "Expected an object type." );
    return 0;
}

Parser::Parser(
  istream &input )
  : input( input ),
    line_number( 1 ),
    column_number( 0 ),
    default_material( new LambertianMaterial( Color( 1.0, 1.0, 1.0 ), 0.6, 0.3 ) )
{
  readNextToken();
}

Scene *Parser::parseScene(
  string &filename )
{
  filename = "image.ppm";
  int xres = 512;
  int yres = 512;
  Scene *scene = new Scene();
  for ( ; ; ) {
    if ( peek( "filename" ) )
      filename = parseString();
    else if ( peek( "xres" ) )
      xres = parseInteger();
    else if ( peek( "yres" ) )
      yres = parseInteger();
    else if ( peek( "maxraydepth" ) )
      scene->setMaxRayDepth( parseInteger() );
    else if ( peek( "minattenuation" ) )
      scene->setMinAttenuation( parseReal() );
    else if ( peek( "camera" ) )
      scene->setCamera( parseCamera() );
    else if ( peek( "background" ) )
      scene->setBackground( parseBackground() );
    else if ( peek( "ambient" ) )
      scene->setAmbient( parseColor() );
    else if ( peek( "light" ) )
      scene->addLight( parseLight() );
    else if ( peek( "scene" ) )
      scene->setObject( parseObject() );
    else if ( peek( "define" ) ) {
      if ( peek( "material" ) ) {
        string name( parseString() );
        defined_materials.insert( pair< string, Material * >( name, parseMaterial() ) );
      } else if ( peek( "object" ) ) {
        string name( parseString() );
        defined_objects.insert( pair< string, Object * >( name, parseObject() ) );
      } else
        throwParseException( "Expected `material', or `object'" );
    }
    else if ( peek( Token::end_of_file ) )
        break;
    else
        throwParseException( "Expected `filename', `xres', `yres', `maxraydepth', `minattenuation', "
                             "`camera', `background', `ambient', `light', `scene', or `define'." );
  }
  scene->setImage( new Image( xres, yres ) );
  return scene;
}
