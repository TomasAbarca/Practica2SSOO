#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <thread>

#include "client.cpp"

#define NUM_CLIENTS 6

std::vector<Client> g_clients;
std::vector<std::string> g_dictionary = {"hola", "adios", "perro", "gato", "dia", "mes", "hora"};

void createClients();
void createClientThread();

int main(){ 
    std::thread clients(createClients);
    clients.join();
    std::thread clients_threads(createClientThread);
    clients_threads.join();
}

void createClients(){
    int i, account_type, word_to_search;
    std::string category;
    srand(time(NULL));

    for(i=0; i<NUM_CLIENTS; i++){
        account_type = rand() % 3;
        word_to_search = rand() % (g_dictionary.size() - 1);

        switch(account_type){
            case 0:{
                category = "Free account";
                Client c (i, g_dictionary[word_to_search], category);
                g_clients.push_back(c);
                break;
            }
            case 1:{
                category = "Premium limit account";
                Client c (i, g_dictionary[word_to_search], category);
                g_clients.push_back(c);
                break;
            }
            case 2:{
                category = "Premium limitless account";
                Client c (i, g_dictionary[word_to_search], category);
                g_clients.push_back(c);
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void createClientThread(){
    int i;
    std::thread client_thread[NUM_CLIENTS];

    for(i=0; i<g_clients.size(); i++){
        client_thread[i] = std::thread(g_clients[i], i);
        client_thread[i].join();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}