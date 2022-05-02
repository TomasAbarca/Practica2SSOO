#include "../include/Client.h"
#include "../include/lib.h"

Client::Client(int id, std::string word_to_search, int category){
    this-> id = id;
    this-> word_to_search = word_to_search;
    this-> category = category;
}int Client::get_id()
{
    return id;
}

std::string Client::get_word()
{
    return word_to_search;
}
int Client::get_category()
{
    return category;
}

void Client::toString(){

    switch (category)
    {
        case 1:
            std::cout << "Client " << id << " with a Free Account" << " searchs the word " << word_to_search << std::endl;
            break;
        case 2:
            std::cout << "Client " << id << " with a Premium with Limit Account" << " searchs the word " << word_to_search << std::endl;
            break;
        case 3:
            std::cout << "Client " << id << " with a Premium Account" << " searchs the word " << word_to_search << std::endl;
            break;
        default:
            break;
    }
}