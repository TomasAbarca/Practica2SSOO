// In this class we will store and show the results

#ifndef LINERESULT_H
#define LINERESULT_H

#include "ThreadResult.h"

class LineResult{
    private:
        int n_line;
        std::string word;
        int pos_in_line;
        ThreadResult tr;
    public:
        LineResult(int n_line, std::string word, int pos_in_line, ThreadResult tr) : n_line{n_line}, word{word}, pos_in_line{pos_in_line}, tr{tr}{}
        
        int get_n_line();
        
        int get_pos_in_line();

        std::string get_word();
        
        ThreadResult get_tr();

        std::string getString();
        
        void toString();
};

#endif