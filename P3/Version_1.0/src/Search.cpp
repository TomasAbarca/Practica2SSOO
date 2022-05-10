#include "../include/Search.h"
#include "../include/Client.h"
#include "../include/lib.h"
#include "../include/LineResult.h"

#include "utils.cpp"

std::vector<LineResult> Gresults;
std::mutex sem;

Search::Search(std::queue<Client> q_clients)
{
    this-> q_clients=q_clients;
}

int Search::operator()(int i)
{
    int cont=0;
    std::cout<<"Hemos entrado en el buscador"<<std::endl;
    while (! q_clients.empty() )
    {
        if(cont==i){
            std::cout<<"Hilo: "<<i<<std::endl;
            //q_clients.front().toString();
            readFile(i, "21-LEYES-DEL-LIDERAZGO.txt", q_clients.front());
            q_clients.pop();
        }else{
            q_clients.pop();
        }
        cont++;
    }
    showLinesResults();
    return EXIT_SUCCESS;
}

void toString()
{
    std::cout<<"Buscador"<<std::endl;
}

/*------------------------ Search Word Function ----------------------------*/

void searchTheWord(int id_line, int id_thread, int line_min, int line_max, std::vector<std::string> v_words, Client c)
{
    id_line++;
    for(unsigned i=0; i<v_words.size(); i++){
        if(v_words.at(i).compare(c.get_word()) == 0){
            std::string w_prev;
            std::string w_post;
            if(i==0){
                w_prev=" ";
            }else{
                w_prev=v_words.at(i-1);
            }

            if(i==(v_words.size()-1)){
                w_post=" ";
            }else{
                w_post=v_words.at(i+1);
            }
            std::unique_lock<std::mutex> UL(sem);
            Gresults.push_back(LineResult(id_thread, line_min, line_max, id_line, w_prev, v_words.at(i), w_post));
            UL.unlock();

        }
    }
}

/*------------------------ Read Book Function ----------------------------*/

void readFile(int id_thread, char const *filename, Client c)
{
    int id_line=0, line_min=0;
    std::string line;
    std::ifstream file(filename);
    std::vector<std::string> v_words;
    int line_max=countLines(filename);

    if(existFile(filename)){
        while(getline(file, line)){
            line = toLowerCaseDeleteSimbols(line);
            v_words = divideLineInWords(line);
            searchTheWord(id_line, id_thread, line_min, line_max, v_words, c);
            id_line++;
        }
    }else{
        std::cout<<"Error opening the file..."<<std::endl;
        exit(EXIT_FAILURE);
    }
    
}



/*------------------------ Show Results Function ----------------------------*/

void showLinesResults()
{
    for(int j=0;j<Gresults.size();j++){
        Gresults[j].showResult(0);
    }
}