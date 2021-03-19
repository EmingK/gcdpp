// -*- mode: c++; -*-

#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "common.h"
#include <dispatch/dispatch.h>
#include <cassert>

GCDPP_NS_BEGIN

template<typename Tdo>
struct DispatchObject {
    protected:
        /// The wrapped libdispatch object.
        Tdo _dobject;
    public:
        DispatchObject(Tdo dobject, bool transferOwnership = true) {
            assert(dobject != nullptr);

            _dobject = dobject;
            if (!transferOwnership) {
                dispatch_retain(_dobject);
            }
        }

        DispatchObject(DispatchObject const &other) {
            dispatch_retain(other._dobject);
            _dobject = other._dobject;
        }

        // Don't move `DispatchObject`, copy them.
        DispatchObject(DispatchObject&& other) = delete;

        ~DispatchObject() {
            dispatch_release(_dobject);
        }

        void suspend() const {
            dispatch_suspend(_dobject);
        }

        void resume() const {
            dispatch_resume(_dobject);
        }

        Tdo nativeHandle() const {
            return _dobject;
        }
};

GCDPP_NS_END

#endif // __OBJECT_H_
