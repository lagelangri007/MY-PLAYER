#include <inc/PlayerControler.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

namespace android{
PlayerControler::PlayerControler()
{
    mForceExit == false;
    memset(mCMD,0,32);
}
PlayerControler::~PlayerControler()
{
    requestExitAndWait();
}
void PlayerControler::ForceExit()
{
    mForceExit = true;
}
char* PlayerControler::GetCmd()
{
    return mCMD;
}
bool PlayerControler::threadLoop()
{
     while(mForceExit == false && !exitPending())
    {
        memset(mCMD,0,30);
        mCMD[31]='\0';
        scanf("%s",mCMD);
        usleep(100000);
    }
    return false;
}
};
