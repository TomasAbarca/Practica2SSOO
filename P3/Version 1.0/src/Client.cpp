#include "../include/Client.h"
#include "../include/lib.h"



Client::Client(int id, std::string word_to_search, int category, int priority){
    this-> id = id;
    this-> word_to_search = word_to_search;
    this-> category = category;
    this-> priority = priority;
}
int Client::get_priority()
{
    return priority;
}
/*
int Client::operator()(int n){
    std::cout << "Thread of Client " << id  << " has been created"<< std::endl;
    toString();
    return EXIT_SUCCESS;
}
*/
void Client::toString(){

    switch (category)
    {
    case 1:
        std::cout << "Client " << id << " with a Free Account" << " searchs the word " << word_to_search << " Priority: "<< priority << std::endl;
        break;
    case 2:
        std::cout << "Client " << id << " with a Premium with Limit Account" << " searchs the word " << word_to_search << " Priority: "<< priority << std::endl;
        break;
    case 3:
        std::cout << "Client " << id << " with a Premium Account" << " searchs the word " << word_to_search << " Priority: "<< priority << std::endl;
        break;
    default:
        break;
    }
   
}