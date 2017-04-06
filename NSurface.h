#ifndef __SURFACE__
#define __SURFACE__
#include <gui/SurfaceComposerClient.h>
#include <gui/Surface.h>

namespace android {
class NSurface
{
public:
    //NSurface* GetInstance();
     sp<IGraphicBufferProducer> SurfaceCreater(int x,int y,int w,int h,int Z);
//private:
     NSurface();
    ~NSurface();
private:
    void DestorySurface();
    
private:
     sp<SurfaceComposerClient> mClient ;
     sp<SurfaceControl>  mSurfaceControl;
     sp<Surface> mSurface;
     sp<IGraphicBufferProducer> mSurfacetexture;
     bool mSurfaceCreated;

     //static NSurface* mInstance;
};
};
#endif
