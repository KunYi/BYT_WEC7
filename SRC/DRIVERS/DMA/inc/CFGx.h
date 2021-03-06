
#ifndef _CFGX_H_
#define _CFGX_H_
#include "RegCommonDef.h"


#define REGISTER_ALL_ITEMS\
/* 4:0 Undefined */                                     \
/* 7:5 CH_PRIOR */      REGISTER_ADD_ITEM(CFGX,CH_PRIOR, 7, 5)\
/* 8 CH_SUSP */         REGISTER_ADD_ITEM(CFGX,CH_SUSP, 8, 8)\
/* 9 FIFO_EMPTY */      REGISTER_ADD_ITEM(CFGX,FIFO_EMPTY, 9, 9)\
/* 10 HS_SEL_DST */     REGISTER_ADD_ITEM(CFGX,HS_SEL_DST, 10, 10)\
/* 11 HS_SEL_SRC */     REGISTER_ADD_ITEM(CFGX,HS_SEL_SRC, 11, 11)\
/* 13:12 LOCK_CH_L */   REGISTER_ADD_ITEM(CFGX,LOCK_CH_L, 13, 12)\
/* 15:14 LOCK_B_L */    REGISTER_ADD_ITEM(CFGX,LOCK_B_L, 15, 14)\
/* 16 LOCK_CH */        REGISTER_ADD_ITEM(CFGX,LOCK_CH, 16, 16)\
/* 17 LOCK_B */         REGISTER_ADD_ITEM(CFGX,LOCK_B, 17, 17)\
/* 18 DST_HS_POL */     REGISTER_ADD_ITEM(CFGX,DST_HS_POL, 18, 18)\
/* 19 SRC_HS_POL */     REGISTER_ADD_ITEM(CFGX,SRC_HS_POL, 19, 19)\
/* 29:20 MAX_ABRST */   REGISTER_ADD_ITEM(CFGX,MAX_ABRST, 29, 20)\
/* 30 RELOAD_SRC */     REGISTER_ADD_ITEM(CFGX,RELOAD_SRC, 30, 30)\
/* 31 RELOAD_DST */     REGISTER_ADD_ITEM(CFGX,RELOAD_DST, 31, 31)\
/* 32 FCMODE */         REGISTER_ADD_ITEM(CFGX,FCMODE, 32, 32)\
/* 33 FIFO_MODE */      REGISTER_ADD_ITEM(CFGX,FIFO_MODE, 33, 33)\
/* 36:34 PROTCTL */     REGISTER_ADD_ITEM(CFGX,PROTCTL, 36, 36)\
/* 37 DS_UPD_EN */      REGISTER_ADD_ITEM(CFGX,DS_UPD_EN, 37, 37)\
/* 38 SS_UPD_EN */      REGISTER_ADD_ITEM(CFGX,SS_UPD_EN, 38, 38)\
/* 42:39 SRC_PER */     REGISTER_ADD_ITEM(CFGX,SRC_PER, 42, 39)\
/* 46:43 DEST_PER */    REGISTER_ADD_ITEM(CFGX,DEST_PER, 46, 43)\
/* 63:47 Undefined */

#define REGISTER_ADD_ITEM REGISTER_ADD_REG_ENUM
DEF_REG_ENUM_TYPE(CFGX)
#undef REGISTER_ADD_ITEM

#define REGISTER_ADD_ITEM REGISTER_ADD_REG_FIELD
DEF_REG_FIELD_TYPE(CFGX)
#undef REGISTER_ADD_ITEM

#define REGISTER_ADD_ITEM REGISTER_FORMAT_REG_BY_STRUCT
DEF_FORMAT_REG_BY_STRUCT_FUNC(CFGX)
#undef REGISTER_ADD_ITEM

#define REGISTER_ADD_ITEM REGISTER_FORMAT_STRUCT_BY_REG
DEF_FORMAT_STRUCT_BY_REG_FUNC(CFGX)
#undef REGISTER_ADD_ITEM

#undef REGISTER_ALL_ITEMS

typedef enum _CFGX_CH_SUSP_ENUM
{
    CFGX_CH_SUSP_NotSuspended = 0,
    CFGX_CH_SUSP_Suspended = 1,
}CFGX_CH_SUSP_ENUM;

typedef enum _CFGX_FIFO_EMPTY_ENUM
{
    CFGX_FIFO_EMPTY_NotEmpty = 0,
    CFGX_FIFO_EMPTY_Empty = 1,
}CFGX_FIFO_EMPTY_ENUM;
#endif