#include "SearchSystem.h"



std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector
{

}

int search(SearchRequest sr, Client client, std::string book, int limit, std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> &pq_pointer)
{

}

Client get_client(int id_client)
{
    bool find = false;
	Client c(0,"","");
	for(int i = 0; i < g_clients.size() && !find; i++){
		if(g_clients[i].get_id_client() == id_client){
			Client c = g_clients[i];
			find = true;
			return c;
		}
	}
	return u;
}

SearchRequest get_search_request()
{

}

void search_on_book(SearchRequest sr)
{

}

void fill_pq_vector()
{
    std::priority_queue<CSearch, vector<CSearch>,compareFunction> pq;
	for(int i = 0; i < global_books_number; i++){
			pq_vector.push_back(pq);
	}
}

void operator()()
{
    
}