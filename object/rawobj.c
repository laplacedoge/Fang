#include "rawobj.h"

FgObjType rawObjType = {
    .name = "raw",
    .reprfunc = FgRawObj_Repr,
};

void __FgRawObj_SetFlag(FgRawObj *obj, uint32_t flag) {
    assert(obj != NULL);
    ((FgRawObj *)obj)->flag |= flag;
    return;
}

void __FgRawObj_ResetFlag(FgRawObj *obj, uint32_t flag) {
    assert(obj != NULL);
    ((FgRawObj *)obj)->flag &= ~flag;
    return;
}

FgRawObj *__FgRawObj_New(const void *mem, size_t size, bool dup, uint32_t flag) {
    assert(mem != NULL);

    FgRawObj *obj = NULL;
    uint8_t *raw = NULL;

    obj = (FgRawObj *)malloc(sizeof(FgRawObj));
    if(obj == NULL) {
        goto exit_err;
    }
    __FgObj_InitObj(&obj->base, &rawObjType);
    obj->base.size = size;
    if(dup) {
        assert(!(obj->flag & FG_RAW_OBJ_FLAG_CONST_RAW));
        obj->occupied = (((size >> 3) + 1) << 1) << 3;
        obj->raw = (uint8_t *)malloc(obj->occupied);
        if(obj->raw == NULL) {
            goto exit_err;
        }
        memcpy(obj->raw, mem, size);
    } else {
        obj->occupied = 0;
        obj->raw = (uint8_t *)mem;
    }
    obj->flag = flag;
    goto exit_ok;

exit_ok:
    return obj;
exit_err:
    if(obj) free(obj);
    if(raw) free(raw);
    return NULL;
}

FgRawObj *FgRawObj_NewFromAlloc(void *mem, bool dup) {
    assert(mem != NULL);
    return __FgRawObj_New(mem, strlen((char *)mem), dup, (uint32_t)FG_RAW_OBJ_FLAG_RO_RAW);
}

FgRawObj *FgRawObj_NewFromAllocWithSize(void *mem, bool dup, size_t size) {
    assert(mem != NULL);
    return __FgRawObj_New(mem, size, dup, (uint32_t)FG_RAW_OBJ_FLAG_RO_RAW);
}

FgRawObj *FgRawObj_NewFromConst(const char *mem, bool dup) {
    assert(mem != NULL);
    return __FgRawObj_New(mem, strlen((char *)mem), dup, (uint32_t)(FG_RAW_OBJ_FLAG_CONST_RAW|FG_RAW_OBJ_FLAG_RO_RAW));
}

FgRawObj *FgRawObj_NewFromConstAndSize(const char *mem, bool dup, size_t size) {
    assert(mem != NULL);
    return __FgRawObj_New(mem, size, dup, (uint32_t)(FG_RAW_OBJ_FLAG_CONST_RAW|FG_RAW_OBJ_FLAG_RO_RAW));
}

FgObj *FgRawObj_Repr(FgObj *obj) {

}

void FgRawObj_Del(FgRawObj *obj) {
    assert(obj != NULL);
    if(obj->occupied > 0) {
        free(obj->raw);
    }
    free(obj);
    return;
}

void __FgRawObj_PrintDetail__(FgRawObj *obj) {
    printf("[obj.%s] C: %ld, S: %ld, O: %ld, R: %p, F: 0x%08X\n", obj->base.type->name, obj->base.refcnt, obj->base.size, obj->occupied, obj->raw, obj->flag);
}
