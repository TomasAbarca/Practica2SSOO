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
        void readFile(int id_thread, char const *filename, Client c);
        void searchTheWord(int id_line, int id_thread, int line_min, int line_max, std::vector<std::string> v_words, Client c);
        void showLinesResults();

};