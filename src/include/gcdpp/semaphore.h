// -*- mode: c++; -*-

#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

#include "common.h"
#include "object.h"
#include "time.h"

#include <cstdint>

GCDPP_NS_BEGIN

struct DispatchSemaphore : public DispatchObject<dispatch_semaphore_t> {
    using Base = DispatchObject<dispatch_semaphore_t>;
public:
    using Base::Base;

    DispatchSemaphore(intptr_t value);

    /// @returns true if another thread is awoken
    bool singal();

    /// @returns true if timed out
    bool wait(DispatchTime dt = DispatchTime::forever());
};

GCDPP_NS_END

#endif // __SEMAPHORE_H_
