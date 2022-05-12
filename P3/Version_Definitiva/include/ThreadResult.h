// In this class we will stored the information about the thread of the solution 

#ifndef THREADRESULT_H
#define THREADRESULT_H

class ThreadResult{
    private:
        int id_thread;
        int first_line;
        int last_line;
    public:
        ThreadResult(int id_thread, int first_line, int last_line);

        int get_id_thread();
        
        int get_first_line();
        
        int get_last_line();
        
        void toString();
};

#endif 