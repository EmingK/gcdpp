#include <gcdpp/common.h>
#include "work_private.h"

GCDPP_NS_BEGIN

void DispatchWorkWrapperInvokeAndDelete(void *ctx) {
    DispatchWorkWrapper *dww = reinterpret_cast<DispatchWorkWrapper *>(ctx);
    if (dww != nullptr) {
        dww->_dw();
        delete dww;
    }
}

GCDPP_NS_END
