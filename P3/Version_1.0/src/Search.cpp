#include "../include/Search.h"
#include "../include/Client.h"
#include "../include/lib.h"
Search::Search(std::queue<Client> q_clients)
{
    this-> q_clients=q_clients;
}

int Search::operator()(int i)
{
    std::cout<<"Hemos entrado en el buscador"<<std::endl;
    while (! q_clients.empty() )
    {
        int cont=0;
        if(cont==i){
            std::cout<<"Hilo: "<<i<<std::endl;
            q_clients.front().toString();
            q_clients.pop();
        }else;
        cont++;
        
    }

    return EXIT_SUCCESS;
}

void toString()
{
    std::cout<<"Buscador"<<std::endl;
}

/*------------------------ Read Book Function ----------------------------

void readFile(int line_min, int line_max, int id_thread, char const *Gfilename)
{
    int id_line=0;
    std::string line;
    std::ifstream file(Gfilename);
    std::vector<std::string> v_words;

    if(existFile(Gfilename)){
        while(getline(file, line)){
            if(id_line>=line_min && id_line<=line_max){
                line = toLowerCaseDeleteSimbols(line);
                v_words = divideLineInWords(line);
                searchTheWord(id_line, id_thread, line_min, line_max, v_words);
                
            }else;
            id_line++;
        }
    }else{
        std::cout<<"Error opening the file..."<<std::endl;
        exit(EXIT_FAILURE);
    }
    
}*/


/*------------------------ Search Word Function ----------------------------

void searchTheWord(int id_line, int id_thread, int line_min, int line_max, std::vector<std::string> v_words){

    id_line++;
    for(unsigned i=0; i<v_words.size(); i++){
        if(v_words.at(i).compare(q_clients.get_word()) == 0){
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
}*/
