
GCC = g++
INCLUDE_FLAGS =
LING_FLAGS = -lm
OPT_FLAGS = -O3
DEBUG_FLAGS = -g
FLAGS = $(DEBUG_FLAGS)
#FLAGS = $(OPT_FLAGS)

HEADERS = Background.h \
					BoundingBox.h \
					Box.h \
					Camera.h \
					Color.h \
					ConstantBackground.h \
					DielectricMaterial.h \
					Group.h \
					HitRecord.h \
					Image.h \
					LambertianMaterial.h \
					Light.h \
					Material.h \
					Math.h \
					MetalMaterial.h \
					Object.h \
					Parser.h \
					PhongMaterial.h \
					PinholeCamera.h \
					Plane.h \
					PointLight.h \
					Primitive.h \
					Ray.h \
					RenderContext.h \
					Sample.h \
					Scene.h \
					Sphere.h \
					Triangle.h \
					Vector.h \
					Vector2.h

SOURCES = Background.cc \
					BoundingBox.cc \
					Box.cc \
					Camera.cc \
					ConstantBackground.cc \
					DielectricMaterial.cc \
					Group.cc \
					Image.cc \
					LambertianMaterial.cc \
					Light.cc \
					Material.cc \
					MetalMaterial.cc \
					Object.cc \
					Parser.cc \
					PhongMaterial.cc \
					PinholeCamera.cc \
					Plane.cc \
					PointLight.cc \
					Primitive.cc \
					Sample.cc \
					Scene.cc \
					Sphere.cc \
					Triangle.cc \
					Vector.cc \
					Vector2.cc \
					xamd.cc

OBJECTS = $(SOURCES:.cc=.o)

all: $(OBJECTS) $(HEADERS)
	$(GCC) $(OBJECTS) -o xamd -lm

%.o: %.cc $(HEADERS)
	$(GCC) -c $(FLAGS) $(INCLUDE_FLAGS) $< -o $@
