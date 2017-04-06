#include <inc/NSurface.h>

namespace android {
NSurface::NSurface()
{
    mSurfaceCreated = false;
    //mInstance = NULL;
}
#if 0
NSurface* NSurface::GetInstance()
{
    if(mInstance == NULL)
    {
        mInstance = new NSurface();
    }
    return mInstance;
}
#endif
sp<IGraphicBufferProducer> NSurface::SurfaceCreater(int x,int y,int w,int h,int Z)
{
    if(mSurfaceCreated)
    {
        return mSurfacetexture;
    }
    mClient = new SurfaceComposerClient();
    mClient->initCheck();
    mSurfaceControl = mClient->createSurface(String8("SurfaceView"), w, h,
                       PIXEL_FORMAT_RGBA_8888, 0x400); //PIXEL_FORMAT_RGBA_8888

    if (mSurfaceControl == NULL)
    {
        ALOGE("mSurfaceControl is NULL\n");
        return NULL;
    }

    ALOGE("Setting surface area [%d, %d, %d, %d]\n", x, y, w, h);
    SurfaceComposerClient::openGlobalTransaction();
    mSurfaceControl->setSize(w, h);
    mSurfaceControl->setPosition(x, y);
    mSurfaceControl->setLayer(Z);
    mSurfaceControl->show();
    SurfaceComposerClient::closeGlobalTransaction();

    mSurface = mSurfaceControl->getSurface();
    mSurfacetexture = mSurface->getIGraphicBufferProducer();
    if (mSurfacetexture == NULL)
    {
       ALOGE("mSurfacetexture is NULL");
       return NULL;
    }
    mSurfaceCreated = true;
    return mSurfacetexture;
}


void NSurface::DestorySurface()
{
    mClient.clear();
    mSurface.clear();
    SurfaceComposerClient::openGlobalTransaction();
    mSurfaceControl->hide();
    mSurfaceControl->clear();
    SurfaceComposerClient::closeGlobalTransaction();
    mSurfaceControl.clear();
}
NSurface::~NSurface()
{
    if(mSurfaceCreated)
    {
        DestorySurface();
    }
}

};
