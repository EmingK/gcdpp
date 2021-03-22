// -*- mode: c++; -*-

#ifndef __GROUP_H_
#define __GROUP_H_

#include "common.h"
#include "object.h"
#include "queue.h"
#include "time.h"

GCDPP_NS_BEGIN

struct DispatchGroup : public DispatchObject<dispatch_group_t> {
    using Base = DispatchObject<dispatch_group_t>;
public:
    using Base::Base;

    DispatchGroup();

    void enter() const;

    void leave() const;

    void notify(DispatchQueue const &dq, DispatchWork &&work) const;

    void async(DispatchQueue const &dq, DispatchWork &&work) const;

    /// @returns true if timeout
    ///
    /// Warning: this method is synchornous
    bool wait(DispatchTime timeout) const;
};

GCDPP_NS_END

#endif // __GROUP_H_
