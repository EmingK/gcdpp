// -*- mode: c++; -*-

#ifndef __WORK_PRIVATE_H_
#define __WORK_PRIVATE_H_

#include <gcdpp/common.h>

GCDPP_NS_BEGIN

struct DispatchWorkWrapper {
    DispatchWork _dw;
    DispatchWorkWrapper(DispatchWork&& dw): _dw(std::move(dw)) {}
};

void DispatchWorkWrapperInvokeAndDelete(void *);

GCDPP_NS_END

#endif // __WORK_PRIVATE_H_
