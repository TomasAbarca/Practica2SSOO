#include "../include/Client_PremiumLimit.h"

Client_PremiumLimit::Client_PremiumLimit(int id, std::string word_to_search, int category, int priority, int _credits) : Client(id, word_to_search, category, priority)
{
   this-> credits = _credits;
}

int Client_PremiumLimit::get_credits()
{
    return credits;
}
