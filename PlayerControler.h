#ifndef __PLAYERCONTROLER__
#define __PLAYERCONTROLER__
#include <utils/threads.h>
namespace android{
class PlayerControler:public Thread
{
public:
    PlayerControler();
    virtual ~PlayerControler();
    virtual bool threadLoop();
    void ForceExit();
    char* GetCmd();
private:
    bool mForceExit;
    char mCMD[32];
};
};
#endif
