#include "Client.h"

//Free Account
Client::Client(int id_client, std::string category, std::string word_to_search, int limit){
    this -> id_client = id_client;
    this -> word_to_search = word_to_search;
    this -> category = category;
    this -> limit = limit;
}

//Prime Limit Account
Client::Client(int id_client, std::string category, int credit, std::string word_to_search){
    this -> id_client = id_client;
    this -> word_to_search = word_to_search;
    this -> category = category;
    this -> credit = credit;
}

//Prime Limitless Account
Client::Client(int id_client, std::string category, std::string word_to_search){
    this -> id_client = id_client;
    this -> word_to_search = word_to_search;
    this -> category = category;
}

int Client::get_id_client(){
    return id_client;
}

std::string Client::get_category(){
    return category;
}

std::string Client::get_word_to_search(){
    return word_to_search;
}

int Client::get_limit(){
    return limit;
}

int Client::get_credit(){
    return credit;
}

void Client::set_limit(int limit){
    this -> limit = limit;
}

SearchRequest Client::do_search(){
    SearchRequest sr(-1, "", -1);

    if(category == "Free Account"){
        SearchRequest s(id_client, get_word_to_search(), 0);
        sr = s;
    }else{
        SearchRequest s(id_client, get_word_to_search(), 1);
        sr = s;
    }

    sr.set_id_request();
    return sr;
}

void Client::file_for_results(MediatorySearch ms){
    std::string title;
    std::string address;
    char client_address[20];
    int i;

    std::sprintf(client_address, "cd Clients/%d", id_client);
    system(client_address);

    for(i=0; i<g_books_num; i++){
        address = "./Clients/" + std::to_string(id_client) + "/Results_" + g_books[i];
        
        std::ofstream file(address.c_str());

        title = "----- RESULTS IN THE TEXT SEARCHING THE WORD " + get_word_to_search() + " IN THE BOOK------------\n";
        file << title;

        while(ms.pq_vector[i].empty() == false){
            LineResult lr = ms.pq_vector[i].top();
            ms.pq_vector[i].pop();
            file << lr.getString() + "\n";
        }
        file.close();
    }
}

bool Client::existDirectory(std::string dir_name){
    DIR *dir;

    if(dir = opendir(dir_name.c_str())){
        closedir(dir);
        return true;
    }

    return false;

}

void Client::file_for_time_results(double time){
    std::string title;
    std::string address;
    char client_address[20];

    std::sprintf(client_address, "mkdir Clients/%d", id_client);
    system(client_address);

    address = "./Clients/" + std::to_string(id_client) + "/Client_time.txt";

    std::ofstream file(address.c_str());

    title = "The client " + std::to_string(id_client) + " has spend a time of " + std::to_string(time) + " seconds\n";
    file << title;
    file.close();
}

int Client::operator()(int n){
    unsigned tI, tF;
    double time;
    const int id = id_client;

    std::cout << "Client " << id_client << " created" << std::endl;
    
    toString();

    tI = clock();

    SearchRequest sr = do_search();
    
    g_searchRequest_vector.insert(sr);

    g_wait_searchSystem.notify_one();

    std::unique_lock<std::mutex> ul(g_sem_client);

    g_wait_client.wait(ul, [id]{return (g_mediatory_vector.get_mandatory_search_vector().empty() == false && g_mediatory_vector.find_mandatory_search(id) == true);});

    tF = clock();

    time = (double(tF - tI) / CLOCKS_PER_SEC);

    file_for_time_results(time);

    MediatorySearch ms = g_mediatory_vector.get_mandatory_search(id);

    file_for_results(ms);

    std::cout << "The client " << id_client << " has the results on his directory" << std::endl;

    return EXIT_SUCCESS;
}

void Client::toString(){
    if(category == "Free Account"){
        std::cout << "Client " << id_client << " with a Free Account created. It can search " << limit << " words" << std::endl; 
    }else if(category == "Premium Limit"){
        std::cout << "Client " << id_client << " with a Premium Limit Account created. It has " << credit << " credits" << std::endl;
    }else{
        std::cout << "Client " << id_client << " with a Premium Limitless Account created" << std::endl;
    }
}