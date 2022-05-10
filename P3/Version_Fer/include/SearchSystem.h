/* This class represents the search system of the program. The instances of this class
*  will be blocked until we have a search request */

#include <iostream>
#include <vector>
#include <queue>

#include "LineResult.h"
#include "OrderQueue.h"
#include "Client.h"
#include "SearchRequest.h"

class SearchSystem{
    public:
        std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector;
        
        int search(SearchRequest sr, Client client, std::string book, int limit, std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> &pq_pointer);

        Client get_client(int id_client);

        SearchRequest get_search_request();

        void search_on_book(SearchRequest sr);

        void fill_pq_vector();

        void operator()();
};