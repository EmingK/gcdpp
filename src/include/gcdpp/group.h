// -*- mode: c++; -*-

#ifndef __GROUP_H_
#define __GROUP_H_

#include "common.h"
#include "object.h"
#include "queue.h"

GCDPP_NS_BEGIN

struct DispatchGroup : DispatchObject<dispatch_group_t> {
    using Base = DispatchObject<dispatch_group_t>;
public:
    DispatchGroup();

    void enter() const;

    void leave() const;

    void notify(DispatchQueue const &dq, DispatchWork&& work) const;
};

GCDPP_NS_END

#endif // __GROUP_H_
