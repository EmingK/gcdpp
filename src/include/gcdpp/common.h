// -*- mode: c++; -*-

#ifndef __COMMON_H_
#define __COMMON_H_

#define GCDPP_NS_BEGIN namespace gcdpp {
#define GCDPP_NS_END }

#include <functional>

GCDPP_NS_BEGIN

using DispatchWork = std::function<void()>;

GCDPP_NS_END

#endif // __COMMON_H_
