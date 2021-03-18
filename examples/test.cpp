#include <gcdpp/gcdpp.h>

#include <iostream>

using namespace gcdpp;

int main() {
    DispatchGroup dg;

    dg.enter();
    DispatchQueue::global().asyncAfter(dispatch_time(DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC), [=]() {
        std::cout << "111\n";
        dg.leave();
    });
    dg.enter();
    DispatchQueue::global().asyncAfter(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), [=]() {
        std::cout << "222\n";
        dg.leave();
    });
    dg.enter();
    DispatchQueue::global().asyncAfter(dispatch_time(DISPATCH_TIME_NOW, 3 * NSEC_PER_SEC), [=]() {
        std::cout << "333\n";
        dg.leave();
    });

    dg.notify(DispatchQueue::main(), []() {
        std::cout << "done\n";
    });

    dispatch_main();

    return 0;
}
