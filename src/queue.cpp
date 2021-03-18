#include "work_private.h"
#include <gcdpp/queue.h>

GCDPP_NS_BEGIN

static dispatch_queue_attr_t unwrappedAttr(DispatchQueueAttribute attr) {
    switch (attr) {
        case DispatchQueueAttribute::Serial:
            return DISPATCH_QUEUE_SERIAL;
        case DispatchQueueAttribute::Concurrent:
            return DISPATCH_QUEUE_CONCURRENT;
    }
}

DispatchQueue::DispatchQueue(std::string const &label, DispatchQueueAttribute attr)
    : Base(dispatch_queue_create(label.c_str(), unwrappedAttr(attr))) {}

DispatchQueue DispatchQueue::main() {
    return DispatchQueue(dispatch_get_main_queue());
}

DispatchQueue DispatchQueue::global(DispatchQueuePriority priority) {
    return DispatchQueue(dispatch_get_global_queue((dispatch_queue_priority_t)priority, 0));
}

void DispatchQueue::sync(DispatchWork&& work) const {
    DispatchWorkWrapper *wrapper = new DispatchWorkWrapper(std::move(work));
    dispatch_sync_f(_dobject, wrapper, &DispatchWorkWrapperInvokeAndDelete);
}

void DispatchQueue::async(DispatchWork&& work) const {
    DispatchWorkWrapper *wrapper = new DispatchWorkWrapper(std::move(work));
    dispatch_async_f(_dobject, wrapper, &DispatchWorkWrapperInvokeAndDelete);
}

void DispatchQueue::asyncAfter(DispatchTime dt, DispatchWork&& work) const {
    DispatchWorkWrapper *wrapper = new DispatchWorkWrapper(std::move(work));
    dispatch_after_f(dt._dt, _dobject, wrapper, &DispatchWorkWrapperInvokeAndDelete);
}

GCDPP_NS_END
