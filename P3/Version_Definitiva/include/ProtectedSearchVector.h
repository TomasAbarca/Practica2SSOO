/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: ProtectedSearchVector.h
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: In this class we are going to protect a vector of request with a mutex
         
*/

#ifndef PROTECTEDSEARCHVECTOR_H
#define PROTECTEDSEARCHVECTOR_H

class ProtectedSearchVector{
    private:
        std::vector<SearchRequest> v_request;
        std::mutex sem;
    public:
        ProtectedSearchVector();

        std::vector<SearchRequest> get_v_request();

        SearchRequest get_request(int id_client);

        SearchRequest get_request_by_pos(int pos);

        SearchRequest front();

        void pop();

        void insert(SearchRequest sr);

        void del_request_by_pos(int pos);

        int get_pos_free_request();

        int get_pos_premium_request();

        bool has_request(int id_client); // Here, return true if the client has a request

        bool same_priority(); // Here, return true if all the request are with the same priority
};

#endif