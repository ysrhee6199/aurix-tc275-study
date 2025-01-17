#ifndef APPMODE
#define APPMODE

/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Ifx_Types.h"

/***********************************************************************/
/*Typedef*/ 
/***********************************************************************/
typedef enum
{
    INIT_MODE = 0u,
    IDLE_MODE,
    OPER_MODE,
    ERROR_MODE,
    MAX_MODE
} MODE;

typedef struct
{
    MODE enuCurMode;
    unsigned int u8nuTestModeTrigger;
    unsigned long u32nuModeCnt;
} ModeInfo;

/***********************************************************************/
/*Define*/ 
/***********************************************************************/

/***********************************************************************/
/*External Variable*/ 
/***********************************************************************/


/***********************************************************************/
/*Global Function Prototype*/ 
/***********************************************************************/
extern void Unit_Mode(void);



#endif /* DRIVER_STM */
