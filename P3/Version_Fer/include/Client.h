/* In this class, we will store al the information about the three types
*  of clients. We implement a operator that every client execute. 
*  The clients make a request and then,they get blocked until we get the result
*  from the search system with a reply.
*  After all this, we create a file with the results */

#ifndef CLIENT_H
#define CLIENT_H

#include "MediatorySearch.h"

class Client{
    private:
        int id_client;
        std::string word_to_search;
        std::string category;
        int limit;
        int credit;
    public:
        //Free Account
        Client(int id_client, std::string category, std::string word_to_search, int limit);
        //Premium Limit Account
        Client(int id_client, std::string category, int credit, std::string word_to_search);
        //Premium Limitless Account
        Client(int id_client, std::string category, std::string word_to_search);

        int get_id_client();

        std::string get_category();

        std::string get_word_to_search();

        int get_limit();

        int get_credit();

        void set_limit(int limit);

        SearchRequest do_search();

        void file_for_results(MediatorySearch ms);

        bool existDirectory(std::string dir_name);

        void file_for_time_results(double t);

        int operator()(int num);

        void toString();
};

#endif