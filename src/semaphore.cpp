#include <gcdpp/common.h>
#include <gcdpp/semaphore.h>

GCDPP_NS_BEGIN

DispatchSemaphore::DispatchSemaphore(intptr_t value)
    : Base(dispatch_semaphore_create(value)) {}

bool DispatchSemaphore::singal() {
    return dispatch_semaphore_signal(_dobject) != 0;
}

bool DispatchSemaphore::wait(DispatchTime dt) {
    return dispatch_semaphore_wait(_dobject, dt._dt) != 0;
}

GCDPP_NS_END
