#include "LineResult.h"
#include "Lib.h"

int LineResult::get_n_line(){
    return n_line;
}

std::string LineResult::get_word(){
    return word;
}

int LineResult::get_pos_in_line(){
    return pos_in_line;
}

ThreadResult LineResult::get_tr(){
    return tr;
}

/* Here, we show the information of the results. 
*  Depending of the thread, we print different colors */
void LineResult::toString(){
    int color;

    srand(time(NULL));
    color = rand() % (4 - 1);

    switch(color){
        case 0:
            std::cout << COLOR_BLUE;
        case 1:
            std::cout << COLOR_CYAN;
        case 2:
            std::cout << COLOR_GREEN;
        case 3:
            std::cout << COLOR_MAGENTA;
    }
    std::cout << "[Hilo " << tr.get_id_thread() << " inicio: " << tr.get_first_line();
    std::cout << " - final: " << tr.get_last_line() << "] :: línea " << n_line << " :: ... ";
    std::cout << word << std::endl;
    /*[Hilo 1 inicio:0 – final: 25] :: línea 12 :: ... el castillo antiguo ...*/
}