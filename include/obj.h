#ifndef __FG_OBJ_H__
#define __FG_OBJ_H__

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef size_t FgSize;

struct FgObj;

typedef struct FgObj *(* FgReprFunc)(struct FgObj *);

typedef struct {
    const char *name;
    FgReprFunc reprfunc;
} FgObjType;

typedef struct {
    FgObjType *type;
    FgSize refcnt;
    FgSize size;
} FgObj;

void __FgObj_InitObj(FgObj *obj, FgObjType *type);

#endif
