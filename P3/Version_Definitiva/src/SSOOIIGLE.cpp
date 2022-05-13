#include <iostream>
#include <time.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <condition_variable>
#include <atomic>
#include <string>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <algorithm>
#include <signal.h>

#include "Lib.h"
#include "SearchRequest.cpp"
#include "ProtectedSearchVector.cpp"
ProtectedSearchVector g_searchRequest_vector;
#include "PaymentReload.cpp"
std::queue<PaymentReload> g_paymentReload_queue; //Queue where the requests of reloads are store
#include "SearchLibrary.cpp"
#include "MediatorySearch.cpp"
#include "ProtectedMediatoryVector.cpp"
ProtectedMediatoryVector g_mediatory_vector;
#include "Client.cpp"
std::vector<Client> g_clients;
#include "SearchSystem.cpp"
#include "PaySystem.cpp"

void createClients();

void createDirectoryForInformationOfClient();

void createClientThreads();

void searchSystemThreads();

void control_of_errors();

void install_signal_handler();

void signal_handler(int sig);

bool complete_dictionary();

bool does_file_exists();

int main(){
    PaySystem pS;

    install_signal_handler();

    control_of_errors();
    

    std::thread create_clients(createClients);
    create_clients.detach();

    createDirectoryForInformationOfClient();
    g_books_num = g_books.size();

    std::thread create_client_threads(createClientThreads);
    create_client_threads.detach();

    searchSystemThreads();

    std::thread pay_thread(pS);
    pay_thread.join();

    return 0;
}

void createClients(){
    std::string category;
    int i, random_category, random_word, random_limit;
    srand(time(NULL));

    for(i=0; i < CLIENTS; i++){
        random_category = rand() % 3;
        random_word = rand() % (g_dictionary.size() - 1);
        random_limit = rand() % (LIMIT - 1);

        switch (random_category){
            case 0:{
                category = "Free Account";
                Client c (i, category, g_dictionary[random_word], random_limit);
                g_clients.push_back(c);
                break;
            }
            case 1:{
                category = "Premium Limit";
                Client c (i, category, random_limit, g_dictionary[random_word]);
                g_clients.push_back(c);
                break;
            }
            case 2:{
                category = "Premium Limitless";
                Client c(i, category, g_dictionary[random_word]);
                g_clients.push_back(c);
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void createDirectoryForInformationOfClient(){
    if(g_clients[0].existDirectory("Clients") == false){
        system("mkdir Clients");
    }else{
        system("rm -r Clients");
        system("mkdir Clients");
    }
}

void createClientThreads(){
    std::thread thread_client[CLIENTS];
    int i;

    for(i=0; i<g_clients.size(); i++){
        thread_client[i] = std::thread(g_clients[i], i);
        thread_client[i].detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void searchSystemThreads(){
    SearchSystem ss;
    std::thread system_threads[CONCURRENT_CLIENTS];
    int i;

    for(i=0; i<CONCURRENT_CLIENTS; i++){
        system_threads[i] = std::thread(ss);
        system_threads[i].detach();
    }
}

bool complete_dictionary(){
    std::vector<std::string> w_vector = readFile(FILE_WORD);
    std::vector<std::string> split_vector;
    int i, j;

    if(w_vector[0].size() == 0){
        return true;
    }

    for(i=0; i<w_vector.size(); i++){
        split_vector = divideLineInWords(w_vector[i]);
        for(j=0; j<split_vector.size(); j++){
            g_dictionary.push_back(split_vector[j]);
        }
    }
    return false;
}

bool does_file_exists(){
    bool exist = false;
    FILE *file;

    if((file = fopen(FILE_WORD, "r")) == NULL){
        return exist;
    }
    else{
        return !exist;
    }
}

void control_of_errors(){
    bool is_empty;

    if(!does_file_exists()){
        std::cerr << "The file " << FILE_WORD << " does not exist" << std::endl;
        exit(-1);
    }

    is_empty = complete_dictionary();

    if(is_empty == true && g_books.size() == 0){
        std::cerr << "The file " << FILE_WORD << " is empty" << std::endl;
        exit(-1);
    }
    if(is_empty == true){
        std::cerr << "The file " << FILE_WORD << " is empty" << std::endl;
        exit(-1);
    }
    else if(g_books.size() == 0){
        std::cerr << "The books array is empty" << std::endl;
        exit(-1);
    }
}

void install_signal_handler(){
    if(signal(SIGINT, signal_handler) == SIG_ERR){
        std::cerr << "Error at the instalation of the signal handler" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void signal_handler(int sig){
    std::cout << "INTERRUPTION: SIGNAL (CTRL + C) RECEIVED" << std::endl;
    std::terminate();
    std::exit(EXIT_FAILURE);
}