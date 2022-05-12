#include "ProtectedSearchVector.h"

std::vector<SearchRequest> ProtectedSearchVector::get_v_request(){
    return v_request;
}

SearchRequest ProtectedSearchVector::get_request(int id_client){
    SearchRequest sr(-1, "", 0);
    int i;

    std::lock_guard<std::mutex> lg(sem);

    for(i=0; i<v_request.size(); i++){
        if(v_request[i].get_id_client() == id_client){
            sr = v_request[i];
            auto token_erase = v_request.begin() + i;
            if(token_erase != v_request.end()){
                v_request.erase(token_erase);
                g_wait_searchSystem.notify_all();
            }
            break;
        }
    }
    return sr;
}

SearchRequest ProtectedSearchVector::get_request_by_pos(int pos){
    SearchRequest sr = v_request[pos];

    return sr;
}

SearchRequest ProtectedSearchVector::front(){
    std::lock_guard<std::mutex> lg(sem);

    SearchRequest sr = v_request[0];

    return sr;
}

void ProtectedSearchVector::pop(){
    int i;

    std::lock_guard<std::mutex> lg(sem);

    for(i=0; i<v_request.size(); i++){
        if(i==0){
            while(i<v_request.size() - 1){
                v_request[i] = v_request[i+1];
                i++;
            }
            g_wait_searchSystem.notify_all();
            break;
        }
    }
    v_request.erase(v_request.end());
}

void ProtectedSearchVector::insert(SearchRequest sr){
    std::lock_guard<std::mutex> lg(sem);

    v_request.push_back(sr);
}

void ProtectedSearchVector::del_request_by_pos(int pos){
    int i;
    SearchRequest sr(-1, "", 0);

    std::lock_guard<std::mutex> lg(sem);

    for(i=0; i<v_request.size(); i++){
        if(i==pos){
            sr = v_request[i];
            auto token_erase = v_request.begin() + i;
            if(token_erase != v_request.end()){
                v_request.erase(token_erase);
                g_wait_searchSystem.notify_all();
            }
            break;
        }
    }
}

int ProtectedSearchVector::get_pos_free_request(){
    int i;
    int pos = 0;

    for(i=0; i<v_request.size(); i++){
        if(v_request[i].get_priority() == 0){
            pos = i;
            break;
        }
    }

    return pos;
}

int ProtectedSearchVector::get_pos_premium_request(){
    int i;
    int pos = 0;

    for(i=0; i<v_request.size(); i++){
        if(v_request[i].get_priority() == 1){
            pos = i;
            break;
        }
    }

    return pos;
}

bool ProtectedSearchVector::has_request(int id_client){
    int i;
    bool itHas = false;

    for(i=0; i<v_request.size(); i++){
        if(v_request[i].get_id_client() == id_client){
            itHas = true;
            break;
        }
    }
    return itHas;
}

bool ProtectedSearchVector::same_priority(){
    int i;
    int cont;
    bool same = false;

    std::lock_guard<std::mutex> lg(sem);

    for(i=0; i<v_request.size(); i++){
        cont = cont + v_request[i].get_priority();
    }
    if(cont == 0 || cont == v_request.size()){
        same = true;
    }

    return same;
}