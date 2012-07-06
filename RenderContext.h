#ifndef RenderContext_h
#define RenderContext_h

class Scene;

class RenderContext
{
  public:
    RenderContext(const Scene* scene)
    : scene(scene)
    {}

    ~RenderContext() {}

    const Scene* getScene()
    {
      return scene;
    }

  private:
    const Scene* scene;

};

#endif
