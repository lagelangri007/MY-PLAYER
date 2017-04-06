#include <inc/Player.h>
#define DEBUG_ERR(X,...) printf("[%s][%d]"X,__func__,__LINE__,##__VA_ARGS__)
#define PLAYER_INFO(X,...) printf("\n+++++++++++++++++++++"X,##__VA_ARGS__)

namespace android {

Player::Player()
{
    mSurfaceCreater = new NSurface();
    mListener = new PlayerListener(this);
}
Player::~Player()
{
    delete mSurfaceCreater;
    delete mListener;
}

bool Player::SetDataSource(const char* StreamName)
{
    if(strstr(StreamName,"mnt") != NULL)
    {
        FILE* fp = NULL;
        fp = fopen(StreamName,"r");
        if(fp != NULL)
        {
            int fno = fileno(fp);
            
            fseek (fp, 0, SEEK_END);   ///将文件指针移动文件结尾
            long size= ftell (fp); ///求出当前文件指针距离文件开始的字节数
            fseek (fp, 0, SEEK_SET);
            mPlayer.setDataSource(fno,0,size);
        }
        else
        {
            DEBUG_ERR("%s  open failed!!!",StreamName);
        }
    }
    else
    {
        mPlayer.setDataSource(StreamName,NULL);
    }
    return true;
}

bool Player::Prepare()
{   
    mPlayer.setListener(mListener);
    mPlayer.prepareAsync();
    return true;
}

bool Player::SetSurface(int x, int y, int w, int h,int Z)
{
    sp<IGraphicBufferProducer> Surface = mSurfaceCreater->SurfaceCreater(x,y,w,h,Z);
    if(Surface == NULL)
    {
        DEBUG_ERR("surface create failed!!!");
        return false;
    }
    mPlayer.setVideoSurfaceTexture(Surface);
    return true;
}

bool Player::start()
{
    return true;
}

bool Player::stop()
{
    mPlayer.stop();
    return true;
}

bool Player::seek(const int SeekTime)
{
    mPlayer.seekTo(SeekTime);
    return true;
}

void Player::notify(int msg, int ext1, int ext2, const Parcel *obj)
{
    //DEBUG_ERR("notify msg is %d!!!",msg);
    switch(msg)
    {
        case MEDIA_PREPARED:
            PLAYER_INFO("start play \n");
            mPlayer.start();
            break;
        case MEDIA_ERROR:
            PLAYER_INFO("play error,stop play \n");
            mPlayer.stop();
            break;
        case MEDIA_PLAYBACK_COMPLETE:
            PLAYER_INFO("stop play \n");
            mPlayer.stop();
            break;
        case MEDIA_SEEK_COMPLETE:
            {
                int msec = 0;
                mPlayer.getCurrentPosition(&msec);
                PLAYER_INFO("seek complete,pos is %d \n",msec);
            }
            break;
        case MEDIA_INFO:
            {
                switch (ext1)
                {
                    case MEDIA_INFO_RENDERING_START:
                    PLAYER_INFO("render start \n");
                    break;
                    case MEDIA_INFO_AUDIO_UNSUPPORT:
                    PLAYER_INFO("audop unsupport \n");
                    break;
                    case MEDIA_INFO_VIDEO_UNSUPPORT:
                    PLAYER_INFO("video unsupport \n");
                    break;
                    default:
                    break;
                }
            }
            break;
        default:
            break;
    }
}

PlayerListener::PlayerListener( Player* PPlayer)
{   
    mPlayer = PPlayer;
}
PlayerListener::~PlayerListener( )
{
}
void PlayerListener::notify(int msg, int ext1, int ext2, const Parcel *obj)
{
    mPlayer->notify(msg, ext1, ext2, obj);
}

};
