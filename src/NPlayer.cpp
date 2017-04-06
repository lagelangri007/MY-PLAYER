
#include <stdio.h>

#include <inc/Player.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/MemoryHeapBase.h>
#include <binder/MemoryBase.h>

#include <inc/PlayerControler.h>

using namespace android;


static bool DebugMode = false;

#define DEBUG_ERR(X,...) printf("[%s][%d]"X,__func__,__LINE__,##__VA_ARGS__)
#define DEBUG_LOG(X,args...) \
             ( (DebugMode) ? \
              printf("DEBUG:"X,##args)\
              : ((int)0))

void ShowHelpInfomation()
{
    printf("\n==============HELP INFO======================\n");
    printf("you can use NPlayer <filename> to play a stream \n");
    printf("you can set pos size zorder NPlayer <filename> x y w h z \n");
    printf("\n=================ENd=========================\n");
}

#define BUFFER_SIZE (1024*10)
#define CPU_INFO ("top -m 10 -d 1 -t -n 1")
#define MEM_INFO ("free")

static bool ExecuteShellCmd(char* cmd,char** result,int len)
{
    FILE* fStream = NULL;
    fStream = popen(cmd,"r");
    if(fStream == NULL)
    {
        DEBUG_ERR("execute %s failed (%s) \n",cmd,strerror(errno));
        return false;
    }
    char aLine[128] = {0};
    while(fgets(aLine,128,fStream))
    {
        strcat(*result,aLine);
    }
    pclose(fStream);
    return true;
}
static void ShowShellInfo(char* cmd)
{
    char* ret = new char[BUFFER_SIZE];
    memset(ret,0,BUFFER_SIZE);
    if(ExecuteShellCmd(cmd,&ret,BUFFER_SIZE));
    {
        printf("%s \n",ret);
    }
    delete [] ret;
}



int x = 0;
int y = 0;
int w = 1280;
int h = 720;
int z = 90000;
int main(int argc, char** argv)
{
    sp < ProcessState > proc(ProcessState::self());
    ProcessState::self()->startThreadPool();

    ShowHelpInfomation();
    if(argc<2)
    {
        return 0;
    }
    const char* StreamName = argv[1];
    if(argc >= 7)
    {
        x = atoi(argv[2]);
        y = atoi(argv[3]);
        w = atoi(argv[4]);
        h = atoi(argv[5]);
        z = atoi(argv[6]);
    }
    Player mPLayer;
    mPLayer.SetDataSource(StreamName);
    if(!mPLayer.SetSurface(x,y,w,h,z))
    {
        exit(EXIT_FAILURE);
    }
    mPLayer.Prepare();

    PlayerControler Control;
    Control.run("NPlayer Controler");
    while(1)
    {
        char* cmd = Control.GetCmd();
        if(strcasestr(cmd,"exit"))
        {
            printf("\n==============exit player======================\n");
            mPLayer.stop();
            Control.ForceExit();
            exit(0);
        }
        else if (strcasestr(cmd,"seek"))
        {
            int time = atoi(strstr(cmd,"seek")+4)*1000;
            printf("\n============== player seekto %d======================\n",time);
            mPLayer.seek(time);
        }
        else if(strcasestr(cmd,"cpu"))
        {
            ShowShellInfo(CPU_INFO);
        }
        else if(strcasestr(cmd,"mem"))
        {
            ShowShellInfo(MEM_INFO);
        }
        else if(strcasestr(cmd,"CMD_"))
        {
            char* exeCmd = cmd + 4;
            ShowShellInfo(exeCmd);
        }
        usleep(100000);
    }
    
    exit(0);
}
