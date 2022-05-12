// In this class, we will send the results from the search system to the clients

#ifndef MEDIATORYSEARCH_H
#define MEDIATORYSEARCH_H

class MediatorySearch{
    private:
        int id_client;
    public:
        std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector;

        MediatorySearch(int id_client, std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector);

        int get_id_client();
};

#endif