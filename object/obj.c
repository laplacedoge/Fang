#include "obj.h"

void __FgObj_InitObj(FgObj *obj, FgObjType *type) {
    assert(obj != NULL);
    assert(type != NULL);
    obj->refcnt = 0;
    obj->size = 0;
    obj->type = type;
    return;
}
