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
    this -> limit = credit;
}

//Prime Limitless Account
Client::Client(int id_client, std::string category, std::string word_to_search){
    this -> id_client = id_client;
    this -> word_to_search = word_to_search;
    this -> category = category;
    this -> limit = -1;
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

        title = "***** RESULT OF SEARCHING " + get_word_to_search() + " IN THE BOOK *****\n";
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

    title = "THE CLIENT " + std::to_string(id_client) + " HAS SPEND " + std::to_string(time) + " SECONDS\n";
    file << title;
    file.close();
}

int Client::operator()(int n){
    unsigned tI, tF;
    double time;
    const int id = id_client;

    std::cout << COLOR_GREEN << "***** CLIENT " << id_client << " STARTS TO USE SSOOIIGLE *****" << std::endl;
    
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

    std::cout << COLOR_GREEN << "***** CLIENT " << id_client << " HAS THE RESULTS ON HIS DIRECTORY *****" << std::endl;

    return EXIT_SUCCESS;
}

void Client::toString(){
    if(category == "Free Account"){
        std::cout << COLOR_GREEN << "CLIENT " << id_client << " WITH A FREE ACCOUNT HAS BEEN CREATED" << std::endl; 
    }else if(category == "Premium Limit"){
        std::cout << COLOR_GREEN << "CLIENT " << id_client << " WITH A PREMIUM LIMIT ACCOUNT HAS BEEN CREATED. HE STARTS WITH " << credit << " CREDITS" << std::endl;
    }else{
        std::cout << COLOR_GREEN << "CLIENT " << id_client << " WITH A PREMIUM LIMITLESS ACCOUNT HAS BEEN CREATED" << std::endl;
    }
}