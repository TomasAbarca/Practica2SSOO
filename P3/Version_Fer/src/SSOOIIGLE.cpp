#include "Lib.h"

#include "Client.cpp"
#include "SearchSystem.cpp"
#include "PaySystem.cpp"
#include "PaymentReload.cpp"

std::vector<Client> g_clients;
std::queue<PaymentReload> g_pay_queue; //Queue where the petitions of reload are stored
std::vector<std::string> g_dictionary = {"uno", "dos", "tres", "cuatro", "cinco", "seis", "siete"};
std::mutex g_semPaySystem;
std::condition_variable g_waitPaySystem;
std::atomic<int> g_id_request (0);

void createClients();
void createDirectoryForInformationOfClient();
void createClientThreads();
void searchSystemThreads();

int main(){
    PaySystem pS;

    std::thread create_clients(createClients);
    create_clients.detach();

    createDirectoryForInformationOfClient();

    std::thread create_client_threads(createClientThreads);
    create_client_threads.detach();

    searchSystemThreads();

    std::thread pay_thread(pS);
    pay_thread.join();

    return 0;
}

void createClients(){
    std::string category;
    int i, random_category, random_word;
    srand(time(NULL));

    for(i=0; i < CLIENTS; i++){
        random_category = rand() % 3;
        random_word = rand() % (g_dictionary.size() - 1);

        switch (random_category){
            case 0:{
                category = "Free Account";
                Client c (i, category, g_dictionary[random_word], LIMIT_WORDS);
                g_clients.push_back(c);
                break;
            }
            case 1:{
                category = "Premium Limit";
                Client c (i, category, CREDITS, g_dictionary[random_word]);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
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