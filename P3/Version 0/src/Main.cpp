#include "Client.cpp"
#include "Client_PremiumLimit.cpp"
#include "utils.cpp"

#define NUM_CLIENTS 6

std::vector<Client> g_clients;
std::vector<std::string> g_dictionary;

void createClients();
void createClientThread();

int main(){ 
    g_dictionary=readDiccionary();
    std::thread clients(createClients);
    clients.join();
    std::thread clients_threads(createClientThread);
    clients_threads.join();
}

void createClients(){
    int i, account_type, word_to_search;
    int category, credits=100;
    srand(time(NULL));

    for(i=0; i<NUM_CLIENTS; i++){
        account_type = rand() % 3; //Cambiar a 10 numeros para incluir la probabilidad del 80-20%
        word_to_search = rand() % (g_dictionary.size() - 1);

        switch(account_type){
            case 0:{
                category = 1;
                Client c (i, g_dictionary[word_to_search], category);
                g_clients.push_back(c);
                break;
            }
            case 1:{
                category = 2;
                Client_PremiumLimit cpl(i, g_dictionary[word_to_search], category, credits);
                g_clients.push_back(cpl);
                break;
            }
            case 2:{
                category = 3;
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