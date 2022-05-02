#include "Client.cpp"
#include "Search.cpp"
#include "Client_PremiumLimit.cpp"
#include "utils.cpp"

std::vector<Client> g_clients;
std::queue<Client> Gq_clients;
std::queue<Client> Gq_clients_premium;//CAMBIO DE VECTOR A COLA YA QUE ASI PODEMOS REORDENAR LOS CLIENTES A LA HORA DE HACER EL 80-20%
std::vector<std::string> g_dictionary;

void createClients();
void createClientThread();

int main(){ 
    g_dictionary=readDiccionary();
    std::thread clients(createClients);
    std::thread clients_threads(createClientThread);
    clients.detach();
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
                category = 1;
                Client c (i, g_dictionary[word_to_search], category);
                Gq_clients.push(c);
                break;
            }
            case 1:{
                category = 2;
                Client_PremiumLimit cpl(i, g_dictionary[word_to_search], category, credits);
                Gq_clients_premium.push(cpl);
                break;
            }
            case 2:{
                category = 3;
                Client c (i, g_dictionary[word_to_search], category);
                Gq_clients_premium.push(c);
                break;
            }
        }
        
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void createClientThread(){
    int i, cont=0;
    std::thread client_thread[NUM_CLIENTS];
    std::queue <Client> start_searching;
    while(! Gq_clients.empty() && ! Gq_clients_premium.empty()){
        if(cont<N_THREADS_SEARCHING){
            int random = std::rand() % 10+1;
            if(random<=2){//20% de probabilidad de empezar la busqueda siendo Free account
                start_searching.push(Gq_clients.front());
                Gq_clients.pop();
            }else{
                start_searching.push(Gq_clients_premium.front());
                Gq_clients_premium.pop();
            }
            cont++;
        }else{
            cont=0;
            std::vector<std::thread> v_threads;
            Search s(start_searching);
            for(int i=0; i<N_THREADS_SEARCHING;i++){
                v_threads.push_back(std::thread(s, i));
            }
            std::for_each(v_threads.begin(), v_threads.end(), std::mem_fn(&std::thread::join)); 
            while(! start_searching.empty()){
                start_searching.pop();
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}