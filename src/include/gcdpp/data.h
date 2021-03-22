// -*- mode: c++; -*-

#ifndef __DATA_H_
#define __DATA_H_

#include "common.h"
#include "object.h"
#include "queue.h"

#include <vector>

GCDPP_NS_BEGIN

struct DispatchData : public DispatchObject<dispatch_data_t> {
    using Base = DispatchObject<dispatch_data_t>;
public:
    using Base::Base;

    /// Creates empty data
    DispatchData();

    DispatchData(
        void const *buffer,
        size_t size,
        DispatchQueue const &destroyerQueue = DispatchQueue::global());

    /// Creates a DispatchData using a specified data destroyer.
    /// The destroyer is called when inner data object's reference count become zero.
    ///
    /// Thes destroyer class should be defined like this:
    ///
    /// ```
    /// struct Destroyer {
    ///     static void destroy(void *dataBuffer);
    /// }
    /// ```
    /// This class is never instantiated, only static method is called.
    template<typename Destroyer>
    static DispatchData create(
        void const *buffer,
        size_t size,
        DispatchQueue const &destroyerQueue) {
        return DispatchData(buffer, size, destroyerQueue, &Destroyer::destroy);
    }

    static DispatchData concat(DispatchData const &data1, DispatchData const &data2);

    size_t size() const;

    DispatchData subRange(size_t offset, size_t length) const;

    size_t copyBytes(void *buffer, size_t count) const;

    std::vector<unsigned char> copyToVector() const;

private:
    DispatchData(
        void const *buffer,
        size_t size,
        DispatchQueue const &destroyerQueue,
        dispatch_function_t destroyer);
};

namespace DispatchDataDestroyer {
    // These destroyer types make use of pre-defined data destructor from libdispatch.
    struct Copy {
        // static void destroy(void *dataBuffer);
    };

    struct Free {
        // static void destroy(void *dataBuffer);
    };

    struct Munmap {
        // static void destroy(void *dataBuffer);
    };
}

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Copy>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue);

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Free>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue);

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Munmap>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue);

GCDPP_NS_END

#endif // __DATA_H_
