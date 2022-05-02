#include <iostream>
#include "Client.h"
#include "lib.h"
#pragma once

class Search {
    private:
        std::queue <Client> q_clients;
    public:
        Search(std::queue<Client> q_clients);
        int operator()(int i);
        void toString();

};