#include "lib.h"
#include "LineResult.h"

int count_lines(char const *filename);
bool existFile(char const *path);
std::string toLowerCase_Delete_Simbols(std::string wordToSearch);
std::vector<std::string> divideLine_InWords(std::string line);


int count_lines(char const *filename)
{
    int counter=0;
    std::string line;
    std::ifstream file(filename);
    if (existFile(filename)){
        while(getline(file,line)){
        counter++;
    }
    }
    return counter;
}


//Método para comprobar si existe el archivo

bool existFile(char const *path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        return false;
    }
    return true;
}

std::string toLowerCase_Delete_Simbols(std::string wordToSearch){

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

std::vector<std::string> divideLine_InWords(std::string line){
    std::vector<std::string> v_words;
    std::istringstream stream (line, std::istringstream::in);
    std::string token;

    while(getline(stream, token, ' ')){
        v_words.push_back(token);
    }

    return v_words;
}

