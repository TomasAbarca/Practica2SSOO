#include "../include/Search.h"
#include "../include/Client.h"
#include "../include/lib.h"
Search::Search(std::queue<Client> q_clients)
{
    this-> q_clients=q_clients;
}

int Search::operator()()
{
    std::cout<<"Hemos entrado en el buscador"<<std::endl;
    while (! q_clients.empty() )
    {
        q_clients.front().toString();
        q_clients.pop();
    }

    return EXIT_SUCCESS;
}

void toString()
{
    std::cout<<"Buscador"<<std::endl;
}


