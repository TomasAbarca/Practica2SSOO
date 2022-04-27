#include <iostream>
#pragma once

class Client{
    private:
        int id;
        std::string word_to_search;
        int category;
        int priority;
    public:
        Client(int id, std::string word_to_search, int category, int priority);
        int get_priority();
        //int operator()(int n);
        void toString();

};

