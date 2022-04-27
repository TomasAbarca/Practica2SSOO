/*  Aarón Peces García, Tomás Abarca Cerro, Fernando González García.

    LineResult.h: This header file that we have defined to create an objects when the program obteains a result 
*/

#include "lib.h"

#ifndef LineResult_h
#define LineResult_h

using namespace std;

class LineResult{
private:
    int id_thread;
    int first_line;
    int last_line;
    int n_line;
    int color;
    string prev_word;
    string word;
    string post_word;
public:
    LineResult(int,int,int,int,string,string,string);
    int get_n_line(){
        return n_line;
    }
    int get_id_thread(){
        return id_thread;
    }
    void showResult(int);
};

LineResult::LineResult(int _id_thread,int _first_line, int _last_line,int _n_line,string _prev_word, string _word, string _post_word){
    id_thread=_id_thread;
    first_line=_first_line;
    last_line=_last_line;
    n_line=_n_line;
    prev_word=_prev_word;
    word=_word;
    post_word=_post_word;
}

void LineResult::showResult(int _color){
    color=_color;
    switch (color)
    {
    case 1:
        cout<<COLOR_BLUE<<"[Hilo "<<id_thread<<" inicio: "<<first_line<<" - final: "<<last_line<<"]" <<COLOR_MAGENTA<<" :: linea "<<n_line<<" :: " <<COLOR_RESET<<"... "<<prev_word<<" "<<COLOR_CYAN<<word<<" "<<COLOR_RESET<<post_word<<" ..."<<endl;
        break;
    case 2:
        cout<<COLOR_RED<<"[Hilo "<<id_thread<<" inicio: "<<first_line<<" - final: "<<last_line<<"]" <<COLOR_MAGENTA<<" :: linea "<<n_line<<" :: " <<COLOR_RESET<<"... "<<prev_word<<" "<<COLOR_CYAN<<word<<" "<<COLOR_RESET<<post_word<<" ..."<<endl;
        break;
    case 3:
        cout<<COLOR_YELLOW<<"[Hilo "<<id_thread<<" inicio: "<<first_line<<" - final: "<<last_line<<"]" <<COLOR_MAGENTA<<" :: linea "<<n_line<<" :: " <<COLOR_RESET<<"... "<<prev_word<<" "<<COLOR_CYAN<<word<<" "<<COLOR_RESET<<post_word<<" ..."<<endl;
        break;
    case 4:
        cout<<COLOR_GREEN<<"[Hilo "<<id_thread<<" inicio: "<<first_line<<" - final: "<<last_line<<"]" <<COLOR_MAGENTA<<" :: linea "<<n_line<<" :: " <<COLOR_RESET<<"... "<<prev_word<<" "<<COLOR_CYAN<<word<<" "<<COLOR_RESET<<post_word<<" ..."<<endl;
        break;
    default:
        cout<<"[Hilo "<<id_thread<<" inicio: "<<first_line<<" - final: "<<last_line<<"]" <<COLOR_MAGENTA<<" :: linea "<<n_line<<" :: " <<COLOR_RESET<<"... "<<prev_word<<" "<<COLOR_CYAN<<word<<" "<<COLOR_RESET<<post_word<<" ..."<<endl;
        break;
    }
    
    /*FORMATO DE SALIDA: [Hilo 1 inicio:0 – final: 25] :: línea 12 :: ... el castillo antiguo ...*/
}

#endif /* LineResult_h */
