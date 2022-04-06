#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream> 
#include <mutex>
#include <locale>   
#include <functional>
#include <sstream>  
#include <cctype>   
#include <clocale>

#include "lineResult.h" 

#define NUMBER_CHAR_TO_ERASE 1

std::vector<std::thread> g_vthreads;
std::vector<LineResult> g_vSearchingThreads;
std::mutex sem;

std::string toLowerCaseAndDeleteSimbols(std::string wordToSearch){

    unsigned i;

    std::for_each(wordToSearch.begin(), wordToSearch.end(), [](char & c){
        c = std::tolower(c); 
    });
    
    for(i=0; i<wordToSearch.size(); i++){
        if(ispunct(wordToSearch[i])){
            wordToSearch.erase(i, NUMBER_CHAR_TO_ERASE);
        }
    }

    return wordToSearch;
}

std::vector<std::string> divideLineInWords(std::string line){
    std::vector<std::string> v_words;
    std::istringstream stream (line, std::istringstream::in);
    std::string token;

    while(getline(stream, token, ' ')){
        v_words.push_back(token);
    }

    return v_words;
}

void searchTheWord(int id_line, std::vector<std::string> v_words, std::string wordToSearch, int index){
    ResultContent resCont;
    unsigned i;

    for(i=0; i<v_words.size(); i++){
        if(v_words.at(i).compare(wordToSearch) == 0){
            resCont.n_line = id_line;
            resCont.word = v_words.at(i);

            if(i == 0){
                resCont.pre_word = "Start of the line";
            }else{
                resCont.pre_word = v_words.at(i-1);
            }

            if(i == v_words.size() - 1){
                resCont.post_word = "End of the line";
            }else{
                resCont.post_word = v_words.at(i+1);
            }

            std::lock_guard<std::mutex> lg(sem);
            g_vSearchingThreads.at(index).addContent(resCont);
        }
    }
}

void obtainsLinesOfWords(std::string filename, std::string wordToSearch, int id_thread){
    int _line_start;
    int _line_end;
    int index = id_thread - 1;
    int id_line = 1;
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> v_words;
    
    std::unique_lock<std::mutex> ul(sem);
    _line_start = g_vSearchingThreads.at(index).getLineStart();
    _line_end = g_vSearchingThreads.at(index).getLineEnd();
    ul.unlock();

    std::cout << "Thread " << id_thread << " start to search..." << std::endl;

    while(id_line <= _line_end){
        getline(file, line);
        if(id_line >= _line_start){
            line = toLowerCaseAndDeleteSimbols(line);
            v_words = divideLineInWords(line);
            searchTheWord(id_line, v_words, wordToSearch, index); 
        }
        id_line++;
    }
}

int countLines(std::string filename){
    int cont = 0;
    std::ifstream file(filename);
    std::string line;

    while(getline(file, line)){
        cont++;
    }
    
    return cont;
}

void createThreadAndAssignLines(int n_threads, int n_lines, std::string filename, std::string wordToSearch){
    int line_start = 0;
    int line_end = 0;
    int id_thread = 0;
    int block_line_thread = n_lines / n_threads;
    unsigned i;

    for(i=0; i<n_threads; i++){
        line_start = (i * block_line_thread) + 1;
        line_end = (line_start + block_line_thread) - 1;
        id_thread++;

        LineResult lR(id_thread, line_start, line_end);
        std::unique_lock<std::mutex> ul(sem);
        g_vSearchingThreads.push_back(lR);
        ul.unlock();

        g_vthreads.push_back(std::thread(obtainsLinesOfWords, filename, wordToSearch, id_thread));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void waitCompletitionThreads(){
    unsigned i;

    std::for_each(g_vthreads.begin(), g_vthreads.end(), std::mem_fn(&std::thread::join));

    for(i=0; i<g_vthreads.size(); i++){
        std::lock_guard<std::mutex> lg(sem);
        g_vSearchingThreads.at(i).showContent();
    }
}

int main(int argc, char *argv[]){
    std::string filename = argv[1];
    std::string wordToSearch = toLowerCaseAndDeleteSimbols(argv[2]);
    int n_threads = atoi(argv[3]);
    int n_lines = countLines(filename);

    createThreadAndAssignLines(n_threads, n_lines, filename, wordToSearch);
    waitCompletitionThreads();

    return 0;
}