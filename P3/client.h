#include <iostream>

class Client{
    private:
        int id;
        std::string word_to_search;
        std::string category;
    public:
        Client(int id, std::string word_to_search, std::string category);
        int operator()(int n);
        void toString();
};

