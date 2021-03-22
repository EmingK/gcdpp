// -*- mode: c++; -*-

#ifndef __SOURCE_H_
#define __SOURCE_H_

#include "common.h"
#include "object.h"
#include "queue.h"
#include "time.h"

GCDPP_NS_BEGIN

struct DispatchSource : public DispatchObject<dispatch_source_t> {
    using Base = DispatchObject<dispatch_source_t>;
public:
    using Base::Base;

    void setRegistrationHandler(DispatchWork handler);

    void setEventHandler(DispatchWork handler);

    void setCancelHandler(DispatchWork handler);

    void activate() const;

    void cancel() const;

    bool isCancelled() const;

    uintptr_t data() const;

    uintptr_t handle() const;
protected:
    DispatchSource(dispatch_source_type_t type, uintptr_t handle, uintptr_t mask, DispatchQueue const &dq);
};

struct DispatchSourceTimer : public DispatchSource {
public:
    DispatchSourceTimer(DispatchQueue const &targetQueue);

    template<typename Rep1, typename Period1, typename Rep2, typename Period2>
    void setTimer(DispatchTime start, std::chrono::duration<Rep1, Period1> const &interval, std::chrono::duration<Rep2, Period2> const &leeway) {
        setTimer(
            start,
            std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count,
            std::chrono::duration_cast<std::chrono::nanoseconds>(leeway).count
        );
    }

    void setTimer(DispatchTime start, uint64_t interval, uint64_t leeway);
};

GCDPP_NS_END

#endif // __SOURCE_H_
