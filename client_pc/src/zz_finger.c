#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/time.h>

#include "zkinterface.h"
#include "libzkfperrdef.h"
#include "libzkfptype.h"
#include "libzkfp.h"

#include "zz_common.h"
#include "zz_finger.h"

static HANDLE m_libHandle = NULL;
static HANDLE m_hDevice = NULL;
static HANDLE m_hDBCache = NULL;
static int m_imgFPWidth = 0;
static int m_imgFPHeight = 0;
static int imageBufferSize = 0;
static unsigned char *m_pImgBuf = NULL;

static void *LoadSym(void *pHandle, const char *pSymbol)
{
        void *pAPI = NULL;
        char *pErrMsg = NULL;

        pAPI = dlsym(pHandle, pSymbol);
        pErrMsg = dlerror();
        if (NULL != pErrMsg) {
                printf("Load function error: %s\n", pErrMsg);
                return NULL;
        }

        return pAPI;
}
static int finger_loadlib(void)
{
    m_libHandle = dlopen("libzkfp.so", RTLD_NOW);
    ZZ_ASSERT(m_libHandle, return ZZ_RET_ERR);

    ZKFPM_Init = (T_ZKFPM_Init)LoadSym(m_libHandle, "ZKFPM_Init");
    ZZ_ASSERT(ZKFPM_Init, return ZZ_RET_ERR);

    ZKFPM_Terminate = (T_ZKFPM_Terminate)LoadSym(m_libHandle, "ZKFPM_Terminate");
    ZKFPM_GetDeviceCount = (T_ZKFPM_GetDeviceCount)LoadSym(m_libHandle, "ZKFPM_GetDeviceCount");
    ZKFPM_OpenDevice = (T_ZKFPM_OpenDevice)LoadSym(m_libHandle, "ZKFPM_OpenDevice");
    ZKFPM_CloseDevice = (T_ZKFPM_CloseDevice)LoadSym(m_libHandle, "ZKFPM_CloseDevice");
    ZKFPM_SetParameters = (T_ZKFPM_SetParameters)LoadSym(m_libHandle, "ZKFPM_SetParameters");
    ZKFPM_GetParameters = (T_ZKFPM_GetParameters)LoadSym(m_libHandle, "ZKFPM_GetParameters");
    ZKFPM_AcquireFingerprint = (T_ZKFPM_AcquireFingerprint)LoadSym(m_libHandle, "ZKFPM_AcquireFingerprint");
    ZKFPM_DBInit = (T_ZKFPM_DBInit)LoadSym(m_libHandle, "ZKFPM_DBInit");
    ZKFPM_DBFree = (T_ZKFPM_DBFree)LoadSym(m_libHandle, "ZKFPM_DBFree");
    ZKFPM_DBMerge = (T_ZKFPM_DBMerge)LoadSym(m_libHandle, "ZKFPM_DBMerge");
    ZKFPM_DBDel = (T_ZKFPM_DBDel)LoadSym(m_libHandle, "ZKFPM_DBDel");
    ZKFPM_DBAdd = (T_ZKFPM_DBAdd)LoadSym(m_libHandle, "ZKFPM_DBAdd");
    ZKFPM_DBClear = (T_ZKFPM_DBClear)LoadSym(m_libHandle, "ZKFPM_DBClear");
    ZKFPM_DBCount = (T_ZKFPM_DBCount)LoadSym(m_libHandle, "ZKFPM_DBCount");
    ZKFPM_DBIdentify = (T_ZKFPM_DBIdentify)LoadSym(m_libHandle, "ZKFPM_DBIdentify");
    ZKFPM_DBMatch = (T_ZKFPM_DBMatch)LoadSym(m_libHandle, "ZKFPM_DBMatch");

    return ZZ_RET_OK;
}

int zz_finger_init(void)
{
    int ret = ZZ_RET_ERR;

    ZZ_ASSERT(!finger_loadlib(), return ZZ_RET_ERR);
    
    ZZ_ASSERT(!ZKFPM_Init(), return ZZ_RET_ERR);

    ZZ_DBG("finger device count=%d\n", ZKFPM_GetDeviceCount());
    
    m_hDevice = ZKFPM_OpenDevice(0);
    ZZ_ASSERT(m_hDevice, goto __ret);
    //?? 是否必要，数据库
    m_hDBCache = ZKFPM_DBInit();
    ZZ_ASSERT(m_hDBCache, return ZZ_RET_ERR); //错误处理

    char paramValue[4] = {0x0};
    unsigned int cbParamValue = 4;
    ZKFPM_GetParameters(m_hDevice, 1, (unsigned char*)paramValue, &cbParamValue);
    m_imgFPWidth=*((int *)paramValue);
    ZZ_DBG("width=%d\n",m_imgFPWidth);

    memset(paramValue, 0x0, 4);
    cbParamValue =4;
    ZKFPM_GetParameters(m_hDevice, 2, (unsigned char*)paramValue, &cbParamValue);
    m_imgFPHeight=*((int *)paramValue);
    ZZ_DBG("height=%d\n",m_imgFPHeight);

    memset(paramValue, 0x0, 4);
    cbParamValue = 4;
    ZKFPM_GetParameters(m_hDevice, 106, (unsigned char*)paramValue, &cbParamValue);
    imageBufferSize = *((int *)paramValue);
    ZZ_DBG("imgaeWidth=%d,imageHeight=%d,imageBurrfersize=%d\n",m_imgFPWidth,m_imgFPHeight,imageBufferSize);

    m_pImgBuf = (unsigned char *)malloc(imageBufferSize);
    //memset(&m_szLastRegTemplate, 0x0, sizeof(m_szLastRegTemplate));

    ZZ_DBG("Init Succ\n");
__ret:

    return ret;
}

static unsigned int GetTickCount()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

int zz_finger_get_temp(void)
{
    unsigned char szTemplate[MAX_TEMPLATE_SIZE];
    unsigned int tempLen = MAX_TEMPLATE_SIZE;
    int nTick = 0;
    nTick = GetTickCount();
    return ZZ_RET_OK;
}


void zz_finger_exit(void)
{
    if(m_pImgBuf) {
        free(m_pImgBuf);
        m_pImgBuf = NULL;
    }
    if(m_hDevice) {
        ZKFPM_CloseDevice(m_hDevice);
        ZKFPM_Terminate();
    }
}

