#ifndef __FG_RAWOBJ_H__
#define __FG_RAWOBJ_H__

#include "obj.h"

enum {
    FG_RAW_OBJ_FLAG_CONST_RAW       = 0x00000001,
    FG_RAW_OBJ_FLAG_RO_RAW          = 0x00000002,
};

typedef struct {
    FgObj base;
    FgSize occupied;
    uint8_t *raw;
    uint32_t flag;
} FgRawObj;

extern FgObjType rawObjType;

FgRawObj *FgRawObj_NewFromAlloc(void *mem, bool dup);

FgRawObj *FgRawObj_NewFromAllocWithSize(void *mem, bool dup, size_t size);

FgRawObj *FgRawObj_NewFromConst(const char *mem, bool dup);

FgRawObj *FgRawObj_NewFromConstAndSize(const char *mem, bool dup, size_t size);

void __FgRawObj_PrintDetail__(FgRawObj *obj);

FgObj *FgRawObj_Repr(FgObj *obj);

void FgRawObj_Del(FgRawObj *obj);

#endif
