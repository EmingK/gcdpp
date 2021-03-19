// -*- mode: c++; -*-

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "common.h"
#include "object.h"
#include "time.h"

#include <string>
#include <type_traits>

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

template<typename T>
struct DispatchSpecificKey {
    bool _unused;

    DispatchSpecificKey(DispatchSpecificKey const &) = delete;
    DispatchSpecificKey(DispatchSpecificKey &&) = delete;
};

template<typename T>
void DispatchSpecificContextDestroy(void *ctx) {
    T *object = reinterpret_cast<T *>(ctx);
    delete object;
}

struct DispatchQueue : public DispatchObject<dispatch_queue_t> {
    using Base = DispatchObject<dispatch_queue_t>;
public:
    using Base::Base;

    DispatchQueue(std::string const &label, DispatchQueueAttribute attr = DispatchQueueAttribute::Serial);

    static DispatchQueue main();

    static DispatchQueue global(DispatchQueuePriority priority = DispatchQueuePriority::Default);

    void sync(DispatchWork &&work) const;

    void async(DispatchWork &&work) const;

    void asyncAfter(DispatchTime dt, DispatchWork&& work) const;

    void barrierSync(DispatchWork &&work) const;

    void barrierAsync(DispatchWork &&work) const;

    std::string const *label() const;

    template<typename T>
    static T &getCurrentSpecific(DispatchSpecificKey<T> const &key) {
        return *(reinterpret_cast<T *>(dispatch_get_specific(&key)));
    }

    template<typename T>
    T &getSpecific(DispatchSpecificKey<T> const &key) const {
        return *(reinterpret_cast<T *>(dispatch_queue_get_specific(_dobject, &key)));
    }

    /// Copy the input value
    template<typename T>
    void setSpecific(DispatchSpecificKey<T> const &key, T const &value) const {
        static_assert(std::is_copy_constructible<T>::value, "DispatchSpecific value should be copy-constructible");

        T *ctx = new T(value);
        dispatch_queue_set_specific(_dobject, &key, ctx, &DispatchSpecificContextDestroy<T>);
    }

    /// Move the input value
    template<typename T>
    void setSpecific(DispatchSpecificKey<T> const &key, T &&value) const {
        static_assert(std::is_move_constructible<T>::value, "DispatchSpecific value should be move-constructible");

        T *ctx = new T(std::move(value));
        dispatch_queue_set_specific(_dobject, &key, ctx, &DispatchSpecificContextDestroy<T>);
    }
};

GCDPP_NS_END

#endif // __QUEUE_H_
