#include <cstring>
#include <gcdpp/data.h>

// form private header
extern "C"
dispatch_data_t
dispatch_data_create_f(const void *buffer,
                       size_t size,
                       dispatch_queue_t queue,
                       dispatch_function_t destructor);

typedef bool (*dispatch_data_applier_function_t)(void * context,
	dispatch_data_t region, size_t offset, const void *buffer, size_t size);

extern "C"
bool
dispatch_data_apply_f(dispatch_data_t data, void * context,
                      dispatch_data_applier_function_t applier);

GCDPP_NS_BEGIN

DispatchData::DispatchData()
    : Base(dispatch_data_empty) {}

DispatchData::DispatchData(void const *buffer, size_t size, DispatchQueue const &destroyerQueue, dispatch_function_t destroyer)
    : Base(dispatch_data_create_f(buffer, size, destroyerQueue.nativeHandle(), destroyer)) {}

DispatchData::DispatchData(void const *buffer, size_t size, DispatchQueue const &destroyerQueue)
    : DispatchData(buffer, size, destroyerQueue, DISPATCH_DATA_DESTRUCTOR_DEFAULT) {}

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Copy>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue) {
    return DispatchData(buffer, size, destroyerQueue, DISPATCH_DATA_DESTRUCTOR_DEFAULT);
}

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Free>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue) {
    return DispatchData(buffer, size, destroyerQueue, (dispatch_function_t)DISPATCH_DATA_DESTRUCTOR_FREE);
}

template<>
DispatchData DispatchData::create<DispatchDataDestroyer::Munmap>(
    void const *buffer,
    size_t size,
    DispatchQueue const &destroyerQueue) {
    return DispatchData(buffer, size, destroyerQueue, (dispatch_function_t)DISPATCH_DATA_DESTRUCTOR_MUNMAP);
}

DispatchData DispatchData::concat(DispatchData const &data1, DispatchData const &data2) {
    return DispatchData(dispatch_data_create_concat(data1.nativeHandle(), data2.nativeHandle()));
}

size_t DispatchData::size() const {
    return dispatch_data_get_size(_dobject);
}

DispatchData DispatchData::subRange(size_t offset, size_t length) const {
    return DispatchData(dispatch_data_create_subrange(_dobject, offset, length));
}

size_t DispatchData::copyBytes(void *buffer, size_t count) const {
    struct DispatchDataApplyContext {
        void *buffer;
        size_t remaining;
    };
    DispatchDataApplyContext ctx {
        buffer, count
    };
    dispatch_data_apply_f(_dobject, &ctx, [](void *_ctx, dispatch_data_t dd, size_t offset, const void *buffer, size_t size) {
        DispatchDataApplyContext *ctx = reinterpret_cast<DispatchDataApplyContext *>(_ctx);

        bool result = true;
        size_t copySize = size;
        if (size > ctx->remaining) {
            copySize = ctx->remaining;
            result = false;
        }
        memcpy(ctx->buffer, buffer, copySize);
        ctx->buffer = (void *)((size_t)ctx->buffer + copySize);
        ctx->remaining -= copySize;
        return result;;
    });
    return count - ctx.remaining;
}

std::vector<unsigned char> DispatchData::copyToVector() const {
    std::vector<unsigned char> result;
    size_t dataSize = size();
    result.resize(dataSize);
    copyBytes(result.data(), dataSize);

    return result;
}

GCDPP_NS_END
