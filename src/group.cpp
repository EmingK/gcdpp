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

GCDPP_NS_END
