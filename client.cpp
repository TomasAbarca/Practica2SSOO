#include "client.h"

Client::Client(int id, std::string word_to_search, std::string category){
    this-> id = id;
    this-> word_to_search = word_to_search;
    this-> category = category;
}

int Client::operator()(int n){
    std::cout << "Thread of Client " << id  << " has been created"<< std::endl;
    toString();

    return EXIT_SUCCESS;
}

void Client::toString(){
    std::cout << "Client " << id << " with " << category << " searchs the word " << word_to_search << std::endl;
}