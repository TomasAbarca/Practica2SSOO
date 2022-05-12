#include "MediatorySearch.h"

MediatorySearch::MediatorySearch(int id_client, std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector){
    this -> id_client = id_client;
    this -> pq_vector = pq_vector;
}

int MediatorySearch::get_id_client(){
    return id_client;
}