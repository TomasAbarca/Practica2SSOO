#include <iostream>
#include <queue>
#include "lineResult.h"

LineResult::LineResult(int id_thread, int line_start, int line_end){
    this -> id_thread = id_thread;
    this -> line_start = line_start;
    this -> line_end = line_end;
}

int LineResult::getThread(){
    return id_thread;
}

int LineResult::getLineStart(){
    return line_start;
}

int LineResult::getLineEnd(){
    return line_end;
}

int LineResult::getContent(){
    return resultContent_queue.size();
}

void LineResult::addContent(ResultContent resCont){
    resultContent_queue.push(resCont);
}

void LineResult::showContent(){
    while(!resultContent_queue.empty()){
        showResults(resultContent_queue.front());
        resultContent_queue.pop();
    }
}

void LineResult::showResults(ResultContent resCont){
    std::cout << "[Hilo " << id_thread;
    std::cout << " Inicio: " << line_start;
    std::cout << " - Final: " << line_end; 
    std::cout << "] :: linea " << resCont.n_line; 
    std::cout << " :: ... " << resCont.pre_word;
    std::cout << " " << resCont.word << " " << resCont.post_word << " ..." << std::endl;
}