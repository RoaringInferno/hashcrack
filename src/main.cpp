#include "daemon.hpp"

#include <iostream>

int main(int arcg, char** argv) {
    daemon d(arcg, argv);
    d.run();
    return 0;
}