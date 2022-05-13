/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: ProtectedMediatoryVector.h
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: In this class, we are going to create a vector of mediatory search.
         It has the methods to manage the vector protected by a semaphore.
         
*/

#ifndef PROTECTEDMEDIATORYVECTOR_H
#define PROTECTEDMEDIATORYVECTOR_H

class ProtectedMediatoryVector{
    private:
        std::vector <MediatorySearch> m_search_vector;
        std::mutex sem;
    public:
        ProtectedMediatoryVector();

        std::vector <MediatorySearch> get_mandatory_search_vector();

        void insert(MediatorySearch); //Here, we insert a mediatory search in the protected vector

        bool find_mandatory_search(int id_client); //Here we check if the mandatory search exists

        MediatorySearch get_mandatory_search(int id_client); //Here, we return a mediatory search of some client
};

#endif