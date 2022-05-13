/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: PaySystem.h
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: In this class we present the pay system. It will be blocked until 
         we get a payment request. The objective is to set a new credit when the 
         client need it
         
*/

#ifndef PAYSYSTEM_H
#define PAYSYSTEM_H

class PaySystem{
    public:
        Client get_client(int id_client);
        void operator()();
};

#endif