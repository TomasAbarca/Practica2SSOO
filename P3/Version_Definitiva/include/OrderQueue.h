// In this class we will order the priority queue

#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include "LineResult.h"

class OrderQueue{
    public:
        int operator()(LineResult &a, LineResult &b);
};

#endif