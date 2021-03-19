#include <gcdpp/group.h>
#include "work_private.h"

GCDPP_NS_BEGIN

DispatchGroup::DispatchGroup()
    : Base(dispatch_group_create()) {}

void DispatchGroup::enter() const {
    dispatch_group_enter(_dobject);
}

void DispatchGroup::leave() const {
    dispatch_group_leave(_dobject);
}

void DispatchGroup::notify(DispatchQueue const &dq, DispatchWork&& work) const {
    DispatchWorkWrapper *wrapper = new DispatchWorkWrapper(std::move(work));
    dispatch_group_notify_f(_dobject, dq.nativeHandle(), wrapper, &DispatchWorkWrapperInvokeAndDelete);
}

void DispatchGroup::async(DispatchQueue const &dq, DispatchWork &&work) const {
    DispatchWorkWrapper *wrapper = new DispatchWorkWrapper(std::move(work));
    dispatch_group_async_f(_dobject, dq.nativeHandle(), wrapper, &DispatchWorkWrapperInvokeAndDelete);
}

bool DispatchGroup::wait(DispatchTime timeout) const {
    return dispatch_group_wait(_dobject, timeout._dt) != 0;
}

GCDPP_NS_END
