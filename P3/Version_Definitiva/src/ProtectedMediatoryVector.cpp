#include "ProtectedMediatoryVector.h"

ProtectedMediatoryVector::ProtectedMediatoryVector(){}

std::vector<MediatorySearch> ProtectedMediatoryVector::get_mandatory_search_vector(){
    return m_search_vector;
}

void ProtectedMediatoryVector::insert(MediatorySearch ms){
    std::lock_guard<std::mutex> lg(sem);
    m_search_vector.push_back(ms);
}

bool ProtectedMediatoryVector::find_mandatory_search(int id_client){
    int i;
    bool find = false;

    for(i=0; i < m_search_vector.size(); i++){
        if(m_search_vector[i].get_id_client() == id_client){
            find = true;
            break;
        }
    }

    return find;
}

MediatorySearch ProtectedMediatoryVector::get_mandatory_search(int id_client){
    int i;
    std::vector<std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector;
    MediatorySearch ms(-1, pq_vector);

    std::lock_guard<std::mutex> lg(sem);

    for(i=0; i<m_search_vector.size(); i++){
        if(m_search_vector[i].get_id_client() == id_client){
            ms = m_search_vector[i];
            auto erase_token = m_search_vector.begin() + i;
            if(erase_token != m_search_vector.end()){
                m_search_vector.erase(erase_token);
            }
            break;
        }
    }
    return ms;
}

