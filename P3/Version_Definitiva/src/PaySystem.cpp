/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: PaySystem.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: Class that implements her .h
         
*/

#include "PaySystem.h"

Client PaySystem::get_client(int id_client){
    bool correct_client = false;
    int i;
    Client c(0, "", "");

    for(i=0; i<g_clients.size() && !correct_client; i++){
        if(g_clients[i].get_id_client() == id_client){
            Client c = g_clients[i];
            correct_client = true;
            return c;
        }
    }
    return c;
}

void PaySystem::operator()(){
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::unique_lock<std::mutex> ul(g_sem_paySystem);
        
        g_wait_paySystem.wait(ul, [] {return (g_paymentReload_queue.empty() == false);});
        
        Client c = get_client(g_paymentReload_queue.front().id_client);

        try{
            g_paymentReload_queue.front().client_promise.set_value(c.get_credit());   
        }catch(std::exception e){
            std::cerr << COLOR_RED << "Error reloading the pay..." << std::endl;
        }

        std::cout << COLOR_CYAN << "***** PAY SYSTEM ACTIVATED *****" << std::endl;
        std::cout << COLOR_CYAN << "THE PAYMENT RELOAD FOR CLIENT " << c.get_id_client() << " HAS BEEN DONE" << std::endl;
    }
}