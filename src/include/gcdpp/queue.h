// -*- mode: c++; -*-

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "common.h"
#include "object.h"
#include "time.h"

#include <string>

GCDPP_NS_BEGIN

enum class DispatchQueueAttribute {
Serial,
Concurrent
};

enum class DispatchQueuePriority: dispatch_queue_priority_t {
High = DISPATCH_QUEUE_PRIORITY_HIGH,
Default = DISPATCH_QUEUE_PRIORITY_DEFAULT,
Low = DISPATCH_QUEUE_PRIORITY_LOW,
Background = DISPATCH_QUEUE_PRIORITY_BACKGROUND
};

struct DispatchQueue : public DispatchObject<dispatch_queue_t> {
        using Base = DispatchObject<dispatch_queue_t>;
    public:
        using Base::Base;

        DispatchQueue(std::string const &label, DispatchQueueAttribute attr = DispatchQueueAttribute::Serial);

        static DispatchQueue main();

        static DispatchQueue global(DispatchQueuePriority priority = DispatchQueuePriority::Default);

        void sync(DispatchWork&& work) const;

        void async(DispatchWork&& work) const;

        void asyncAfter(DispatchTime dt, DispatchWork&& work) const;

};

GCDPP_NS_END

#endif // __QUEUE_H_
