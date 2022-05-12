#include <stdio.h>
#include <string>
#include <queue>
#include "OrderQueue.h"


std::vector <std::string> readFile (std::string file);

std::vector<std::string> divideLineInWords(std::string str);

std::string toUpperCase(std::string s);

std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> searchTheWord(std::vector<std::string> v_string, std::string word_to_search, int id_line, int id_thread, int LimitMin, int LimitMax, std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> pq);

bool compareWords(std::string word, std::string w_found);