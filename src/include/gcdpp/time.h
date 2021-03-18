// -*- mode: c++; -*-

#ifndef __TIME_H_
#define __TIME_H_

#include "common.h"

#include <chrono>

GCDPP_NS_BEGIN

struct DispatchTime {
    dispatch_time_t _dt;

    DispatchTime(dispatch_time_t dt) {
        _dt = dt;
    }

    static DispatchTime now() {
        return DispatchTime(DISPATCH_TIME_NOW);
    }

    static DispatchTime forever() {
        return DispatchTime(DISPATCH_TIME_FOREVER);
    }

    template<typename Rep, typename Period>
    DispatchTime operator+(std::chrono::duration<Rep, Period> const &duration) {
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        return DispatchTime(dispatch_time(_dt, ns.count()));
    }
};

GCDPP_NS_END

#endif // __TIME_H_
