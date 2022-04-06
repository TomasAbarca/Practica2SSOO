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
#include "searchResult.h"

#define NUMBER_CHAR_TO_ERASE 1

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

void searchTheWord(int id_line, std::vector<std::string> v_words, std::string wordToSearch){
    unsigned i;

    for(i=0; i<v_words.size(); i++){
        if(v_words.at(i).compare(wordToSearch) == 0){
            std::cout << "Linea " << id_line << std::endl;
        }
    }
}

void obtainsLinesOfWords(std::string filename, std::string wordToSearch){
    int id_line = 1;
    std::ifstream fp(filename, std::ifstream::in);
    std::string line;
    std::vector<std::string> v_words;

    while(getline(fp, line)){
        line = toLowerCaseAndDeleteSimbols(line);
        v_words = divideLineInWords(line);
        searchTheWord(id_line, v_words, wordToSearch);
        ++id_line;
    }
}

int main(int argc, char *argv[]){
    std::string filename = argv[1];
    std::string wordToSearch = toLowerCaseAndDeleteSimbols(argv[2]);

    obtainsLinesOfWords(filename, wordToSearch);

}