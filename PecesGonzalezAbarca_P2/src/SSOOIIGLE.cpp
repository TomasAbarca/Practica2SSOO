/*  Aarón Peces García, Tomás Abarca Cerro, Fernando González García.

    SSOOIIGLE.cpp: This .cpp is the main program 
*/


#include "utils.cpp"

/*------------------------ Global Variables ----------------------------*/

int Gtotal_lines, Gthreads, *Gn_threads;
char const *Gfilename;
std::string GwordToSearch;
std::vector <std::thread> Gv_threads;
std::vector<LineResult> Gresults;
std::mutex sem;

/*------------------------ Process Management ----------------------------*/

void readFile(int line_min, int line_max, int id_thread);
void createThreads();
void searchTheWord(int id_line, int id_thread, int line_min, int line_max, std::vector<std::string> v_words);
void showLinesResults();

/*------------------------ Main Function ----------------------------*/

int main(int argc, char const *argv[])
{
    std::cout<<"\n"<<"Bienvenido al buscador "<<COLOR_BLUE<<"SS"<<COLOR_RED<<"O"<<COLOR_YELLOW<<"O"<<COLOR_BLUE<<"II"<<COLOR_GREEN<<"GL"<<COLOR_RED<<"E"<<COLOR_RESET<<"\n"<<std::endl;
    Gfilename=argv[1];
    GwordToSearch=toLowerCaseDeleteSimbols(argv[2]);
    Gn_threads=&Gthreads;
    *Gn_threads=std::atoi(argv[3]);
    Gtotal_lines=countLines(Gfilename);
    
    createThreads();
    showLinesResults();
}

/*------------------------ Create Threads Function ----------------------------*/

void createThreads()
{
    int block_size = Gtotal_lines/Gthreads;

    for (unsigned i=0;i<Gthreads;i++){
        int line_min = i * block_size;
        int line_max = (line_min + block_size)-1;
        if(i==(Gthreads-1)){
            line_max=(Gtotal_lines-1);
        }else;

        Gv_threads.push_back(std::thread(readFile, line_min, line_max, i));
    }

    std::for_each(Gv_threads.begin(), Gv_threads.end(), std::mem_fn(&std::thread::join)); 
}

/*------------------------ Read Book Function ----------------------------*/

void readFile(int line_min, int line_max, int id_thread)
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
    
}

/*------------------------ Search Word Function ----------------------------*/

void searchTheWord(int id_line, int id_thread, int line_min, int line_max, std::vector<std::string> v_words){

    id_line++;
    for(unsigned i=0; i<v_words.size(); i++){
        if(v_words.at(i).compare(GwordToSearch) == 0){
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

/*------------------------ Show Results Function ----------------------------*/

void showLinesResults()
{
    int id_thread=0, color=0, cont=0;
    
    for(int i=0;i<Gthreads;i++){
        color=(i+1)-(4*cont);
        for(int j=0;j<Gresults.size();j++){
            if(id_thread==Gresults[j].get_id_thread()){
                Gresults[j].showResult(color);
            }else;
        }
        if((i+1)%4==0){
            cont++;
        }
        id_thread++; 
    }
}