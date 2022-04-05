
#include "utils.cpp"

int total_lines;

void read_file(char const *filename, int line_min, int line_max, int id_thread)
{
    int id_line=0;
    std::string linea;
    std::ifstream file(filename);
    /*std::cout<<"linea minima,"<<line_min<< " hilo: "<<id_thread<<std::endl;
    std::cout<<"linea maximo, "<<line_max<< " hilo: "<<id_thread<<std::endl;*/
    if(existFile(filename)){
        while(getline(file, linea)){
            if(id_line>=line_min && id_line<=line_max){
                if(id_thread==0){
                    std::cout<<COLOR_RED<<linea<<COLOR_RESET<<std::endl;
                }else if(id_thread>0){
                    std::cout<<COLOR_GREEN<<linea<<COLOR_RESET<<std::endl;
                }else;
            }else;
            id_line++;
        }
    }
    
}


int main(int argc, char const *argv[])
{
    std::cout<<"Bienvenido al buscardor "<<COLOR_BLUE<<"SS"<<COLOR_RED<<"O"<<COLOR_YELLOW<<"O"<<COLOR_BLUE<<"II"<<COLOR_GREEN<<"GL"<<COLOR_RED<<"E"<<COLOR_RESET<<std::endl;
    std::vector <std::thread> v_threads;
    char const *filename=argv[1];
    int threads, *n_threads;
    n_threads=&threads;
    *n_threads=std::atoi(argv[2]);
    total_lines=count_lines(filename);
    int block_size = total_lines/threads;

    std::cout<<total_lines<<std::endl;
    std::cout<< COLOR_MAGENTA <<"Numero de threads:"<<threads<< COLOR_RESET <<std::endl;

    for (unsigned i=0;i<threads;i++){
        int line_min = i * block_size;
        int line_max = (line_min + block_size)-1;

        v_threads.push_back(std::thread(read_file, filename, line_min, line_max, i));
    }

    std::for_each(v_threads.begin(), v_threads.end(), std::mem_fn(&std::thread::join)); 
 


}