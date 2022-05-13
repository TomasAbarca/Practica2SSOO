/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: OrderQueue.h
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: In this class we will order the priority queue
         
*/

#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include "LineResult.h"

class OrderQueue{
    public:
        int operator()(LineResult &a, LineResult &b);
};

#endif