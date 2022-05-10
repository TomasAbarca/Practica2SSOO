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

bool Client::existDirectory(std::string dir_name){
    DIR *dir;

    if(dir = opendir(dir_name.c_str())){
        closedir(dir);
        return true;
    }

    return false;

}

int Client::operator()(int n){
    std::cout << "Client " << id_client << " created" << std::endl;
    toString();
    return 0;
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