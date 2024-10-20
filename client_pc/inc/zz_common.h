#ifndef __ZZ_COMMON_H__
#define __ZZ_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#ifndef ZZ_RET_OK
#define ZZ_RET_OK  (0)
#endif

#ifndef ZZ_RET_ERR
#define ZZ_RET_ERR  (1)
#endif

#ifndef TRUE
#define TRUE  (1)
#endif
#ifndef FALSE
#define FALSE  (0)
#endif
                                                  
#ifndef likely                                
#define likely(x)   __builtin_expect((x), 1)  
#endif                                        
                                                  
#ifndef unlikely                              
#define unlikely(x)   __builtin_expect((x), 0)  
#endif                                        

#define ZZ_LOG(string, args...) \
    printf(string , ##args)

#define ZZ_INFO(string, args...) \
        printf("\033[32m" string "\033[0m ", ##args)

#define ZZ_DBG(string, args...) \
        printf("\033[34m" string "\033[0m ", ##args)

#define ZZ_WARN(string, args...) \
        printf("\033[33m" "[WARN: %s:%d ]" string "\033[0m ", __func__, __LINE__, ##args)

#define ZZ_ERR(string, args...) \
        printf("\033[31m" "[ERR: %s:%d ]" string "\033[0m ",   __func__, __LINE__, ##args)

#define ZZ_WASSERT(b, action) if(unlikely(!(b))) {ZZ_WARN("%s \n\r", #b); action;} 

#define ZZ_ASSERT(b, action) if(unlikely(!(b))) {ZZ_ERR("%s \n\r", #b); action;}   

#define ZZ_ALIGN_DOWN(x, a)  ((x) & ~(a - 1))                                      

#define ZZ_ALIGN_UP(x, a) ((x + a - 1) & ~(a - 1))                                 

#ifndef ARRARY_SIZE                                                                
#define ARRARY_SIZE(a) ((sizeof(a) / sizeof(a[0])))                                
#endif

#ifndef CEILING_2_POWER                                          
#define CEILING_2_POWER(x,a) (((x) + ((a) - 1)) & (~((a) - 1)))  
#endif                                                           

#ifndef FLOOR_2_POWER                                            
#define FLOOR_2_POWER(x,a)       (  (x) & (~((a) - 1) ) )        
#endif                                                           

#ifdef __cplusplus
}
#endif
#endif
