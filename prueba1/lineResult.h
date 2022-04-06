#include <iostream>
#include <queue>

struct ResultContent{
    int n_line;
    std::string pre_word;
    std::string post_word;
    std::string word;
};

class LineResult{
    private:
        int id_thread;
        int line_start;
        int line_end;
        std::queue<ResultContent> resultContent_queue;
    
    public:
        LineResult(int id_thread, int line_start, int line_end);
        int getThread();
        int getLineStart();
        int getLineEnd();
        int getContent();
        void showContent();
        void addContent(ResultContent resCont);
        void showResults(ResultContent resCont);
};