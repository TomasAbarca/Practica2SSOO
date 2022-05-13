/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: SearchRequest.h
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: In this class we will manage the information about the search request that the client makes
         
*/


#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

class SearchRequest{
    private:
        int id_client;
        int id_search;
        std::string word_to_search;
        int priority;
    public:
        SearchRequest(int id_client, std::string word_to_search, int priority);

        int get_id_client();
        
        int get_id_search();
        
        std::string get_word_to_search();
        
        int get_priority();
        
        void set_id_request();
        
        void toString();
};

#endif