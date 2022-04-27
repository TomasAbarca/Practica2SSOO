#include "Client.cpp"
#include "Search.cpp"
#include "Client_PremiumLimit.cpp"
#include "utils.cpp"

std::vector<Client> g_clients;
std::queue<Client> Gq_clients;//CAMBIO DE VECTOR A COLA YA QUE ASI PODEMOS REORDENAR LOS CLIENTES A LA HORA DE HACER EL 80-20%
std::vector<std::string> g_dictionary;

void createClients();
void createClientThread2();

int main(){ 
    g_dictionary=readDiccionary();
    std::thread clients(createClients);
    clients.detach();
    std::thread clients_threads(createClientThread2);
    clients_threads.detach();
    std::this_thread::sleep_for(std::chrono::seconds(30));
}

void createClients(){
    int i, account_type, word_to_search;
    int category, credits=100;
    srand(time(NULL));

    for(i=0; i<NUM_CLIENTS; i++){
        account_type = std::rand() % 3;
        word_to_search = rand() % (g_dictionary.size() - 1);
        switch(account_type){

            case 0:{
                int priority = std::rand() % 2+1;
                category = 1;
                Client c (i, g_dictionary[word_to_search], category, priority);
                Gq_clients.push(c);
                break;
            }
            case 1:{
                int priority = (std::rand() % 4)+3;
                category = 2;
                Client_PremiumLimit cpl(i, g_dictionary[word_to_search], category, priority, credits);
                Gq_clients.push(cpl);
                break;
            }
            case 2:{
                int priority = (std::rand() % 4)+7;
                category = 3;
                Client c (i, g_dictionary[word_to_search], category, priority);
                Gq_clients.push(c);
                break;
            }
        }
        
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
/*
void createClientThread(){
    int i, cont=0;
    std::thread client_thread[NUM_CLIENTS];
    std::queue <Client> start_searching;

    for(i=0; i<g_clients.size(); i++){
        if(cont<N_THREADS_SEARCHING){
            int random = std::rand() % 10+1;
            if(random<=2 && g_clients[i].get_priority()<=2){
                start_searching.push(g_clients[i]);
            }else if(g_clients[i].get_priority()>2){
                start_searching.push(g_clients[i]);
            }else;
            cont++;
        }else{
            cont=0;
            Search s(start_searching);
            std::thread thread_to_search(s);
            thread_to_search.join();
            while(! start_searching.empty()){
                start_searching.pop();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

}
*/
void createClientThread2(){
    int i, cont=0;
    std::thread client_thread[NUM_CLIENTS];
    std::queue <Client> start_searching;
/***************************+ REVISAR EL ALGORITMO DE PREFERENCIA SOBRE LOS CLIENTES PREMIUM ***************************************************/
    while(! Gq_clients.empty()){
        if(cont<N_THREADS_SEARCHING){
            int random = std::rand() % 10+1;
            if(random<=2 && Gq_clients.front().get_priority()<=2){//20% de probabilidad de empezar la busqueda siendo Free account
                start_searching.push(Gq_clients.front());
                Gq_clients.pop();
            }else if(Gq_clients.front().get_priority()>2){//80% de probabilidad de empezar la busqueda siendo Premium
                start_searching.push(Gq_clients.front());
                Gq_clients.pop();
            }else;//
            Gq_clients.push(Gq_clients.front());
            Gq_clients.pop();
            cont++;
        }else{//
            cont=0;
            Search s(start_searching);
            std::thread thread_to_search(s);
            thread_to_search.join();
            while(! start_searching.empty()){
                start_searching.pop();
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}