/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: PatmentReload.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: this class has information about a reload of the clients that
         will need credits.
         
*/

class PaymentReload{
    public:
        int id_client;
        std::promise<int> client_promise;
        std::future<int> client_future;

        PaymentReload(int id_client): id_client(id_client){
            client_future = client_promise.get_future();
        };
};