# gcdpp

gcdpp is a C++ wrapper of [libdispatch](https://github.com/apple/swift-corelibs-libdispatch), providing a friendly API.

# platform availability

On Apple platforms, system provided libdispatch is used.

On non-Apple platforms, you need to build libdispatch manually, and provide it to gcdpp.

gcdpp does not use blocks, using gcc/msvc is ok.
