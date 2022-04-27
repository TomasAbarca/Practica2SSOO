/*  Aarón Peces García, Tomás Abarca Cerro, Fernando González García.

    utils.cpp: This .cpp store some functions that we use in the main program
*/


#include "../include/lib.h"
#include "../include/LineResult.h"

int countLines(char const *filename);
bool existFile(char const *path);
std::string toLowerCaseDeleteSimbols(std::string wordToSearch);
std::vector<std::string> divideLineInWords(std::string line);


/*------------------------ Count Lines Function ----------------------------*/

int countLines(char const *filename)
{
    int counter=0;
    std::string line;
    std::ifstream file(filename);
    if (existFile(filename)){
        while(getline(file,line)){
        counter++;
    }
    }
    file.close();
    return counter;
}


/*------------------------ Check the Existence of the file Function ----------------------------*/

bool existFile(char const *path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        return false;
    }
    return true;
}

std::string toLowerCaseDeleteSimbols(std::string wordToSearch){

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

/*------------------------ Divide One Line In Words Function ----------------------------*/

std::vector<std::string> divideLineInWords(std::string line){
    std::vector<std::string> v_words;
    std::istringstream stream (line, std::istringstream::in);
    std::string token;

    while(getline(stream, token, ' ')){
        v_words.push_back(token);
    }

    return v_words;
}

std::vector<std::string> readDiccionary()
{
    int counter=0;
    char const *filename="diccionario.txt";
    std::vector<std::string> words;
    std::string word;
    std::ifstream file(filename);
    if (existFile(filename)){
        while(file>>word){
            word=toLowerCaseDeleteSimbols(word);
            words.push_back(word);
        }
    }else{
        std::cerr<<"ERROR AL LEER EL DICCIONARIO DE PALABRAS"<<std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();
    return words;
}

