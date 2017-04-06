#ifndef __PLAYER__
#define __PLAYER__
#include <media/mediaplayer.h>
#include <inc/NSurface.h>
namespace android {
class PlayerListener;
class Player
{
public:
    Player();
    ~Player();

    bool SetDataSource(const char* StreamName);
    bool Prepare();
    bool SetSurface(int x, int y, int w, int h,int Z);
    bool start();
    bool stop();
    bool seek(const int SeekTime);
public:
    void notify(int msg, int ext1, int ext2, const Parcel *obj);
private:
    MediaPlayer mPlayer;
    NSurface* mSurfaceCreater;
    PlayerListener* mListener;
};
class PlayerListener: public MediaPlayerListener {
public:
    PlayerListener( Player* PPlayer);
    ~PlayerListener( );
    void notify(int msg, int ext1, int ext2, const Parcel *obj);

private:
    Player*mPlayer;
};
};

#endif
