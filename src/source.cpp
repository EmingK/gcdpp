#include <gcdpp/source.h>

GCDPP_NS_BEGIN

struct DispatchSourceContext {
    DispatchWork registrationHandler;
    DispatchWork eventHandler;
    DispatchWork cancelHandler;

    static void destroy(void *ctx) {
        DispatchSourceContext *self = reinterpret_cast<DispatchSourceContext *>(ctx);
        delete self;
    }

    static void invokeRegistrationHandler(void *ctx) {
        DispatchSourceContext *self = reinterpret_cast<DispatchSourceContext *>(ctx);
        if (self->registrationHandler) {
            self->registrationHandler();
        }
    }

    static void invokeEventHandler(void *ctx) {
        DispatchSourceContext *self = reinterpret_cast<DispatchSourceContext *>(ctx);
        if (self->eventHandler) {
            self->eventHandler();
        }
    }

    static void invokeCancelHandler(void *ctx) {
        DispatchSourceContext *self = reinterpret_cast<DispatchSourceContext *>(ctx);
        if (self->cancelHandler) {
            self->cancelHandler();
        }
    }
};

DispatchSource::DispatchSource(dispatch_source_type_t type, uintptr_t handle, uintptr_t mask, DispatchQueue const &dq)
    : Base(dispatch_source_create(type, handle, mask, dq.nativeHandle()))
{
    DispatchSourceContext *ctx = new DispatchSourceContext;
    dispatch_set_context(_dobject, ctx);
    dispatch_set_finalizer_f(_dobject, &DispatchSourceContext::destroy);
}

void DispatchSource::setRegistrationHandler(DispatchWork handler) {
    DispatchSourceContext *ctx = reinterpret_cast<DispatchSourceContext *>(dispatch_get_context(_dobject));
    ctx->registrationHandler = handler;
    dispatch_source_set_registration_handler_f(_dobject, &DispatchSourceContext::invokeRegistrationHandler);
}

void DispatchSource::setEventHandler(DispatchWork handler) {
    DispatchSourceContext *ctx = reinterpret_cast<DispatchSourceContext *>(dispatch_get_context(_dobject));
    ctx->eventHandler = handler;
    dispatch_source_set_event_handler_f(_dobject, &DispatchSourceContext::invokeEventHandler);
}

void DispatchSource::setCancelHandler(DispatchWork handler) {
    DispatchSourceContext *ctx = reinterpret_cast<DispatchSourceContext *>(dispatch_get_context(_dobject));
    ctx->cancelHandler = handler;
    dispatch_source_set_cancel_handler_f(_dobject, &DispatchSourceContext::invokeCancelHandler);
}

void DispatchSource::activate() const {
    dispatch_activate(_dobject);
}

void DispatchSource::cancel() const {
    dispatch_source_cancel(_dobject);
}

bool DispatchSource::isCancelled() const {
    return dispatch_source_testcancel(_dobject) != 0;
}

uintptr_t DispatchSource::data() const {
    return dispatch_source_get_data(_dobject);
}

uintptr_t DispatchSource::handle() const {
    return dispatch_source_get_handle(_dobject);
}

DispatchSourceTimer::DispatchSourceTimer(DispatchQueue const &targetQueue)
    : DispatchSource(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, targetQueue) {}

void DispatchSourceTimer::setTimer(DispatchTime start, uint64_t interval, uint64_t leeway) {
    dispatch_source_set_timer(_dobject, start._dt, interval, leeway);
}

GCDPP_NS_END
