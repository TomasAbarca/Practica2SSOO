#include <iostream>
#pragma once

class Client{
    private:
        int id;
        std::string word_to_search;
        int category;
    public:
        Client(int id, std::string word_to_search, int category);
        int get_id();
        int get_category();
        std::string get_word();

        void toString();
        

};

