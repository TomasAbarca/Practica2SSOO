#include <iostream>
#include "Client.h"
#pragma once

class Client_PremiumLimit : public Client{
    private:
        int credits;
    public:
        Client_PremiumLimit(int id, std::string word_to_search, int category, int _credits);
        int get_credits();

};