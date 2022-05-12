#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include "LineResult.h"
#include "ThreadResult.h"
#include "OrderQueue.h"
#include "SearchLibrary.h"

std::vector <std::string> readFile (std::string file)
{
    std::vector<std::string> v_line;
    std::ifstream m_file;
    std::string line;

	m_file.open(file, std::ios::in);
    
    if(m_file.fail()){
        std::cout << "Error opening the file ...." <<std::endl;
    }else{
        while(!m_file.eof()){
            getline(m_file, line);
            v_line.insert(v_line.end(), line);
        }
    }
    return v_line;
}

std::vector<std::string> divideLineInWords(std::string str)
{
    std::vector<std::string> v_string;
	std::istringstream isstream(str);
	std::string word;

	while(isstream >> word){
		v_string.push_back(word);
	}
	return v_string;
}

std::string toUpperCase(std::string s)
{
	int i;

    for(i = 0;i<s.length();i++){
		s[i]=toupper(s[i]);
	}
	return s;
}

std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> searchTheWord(std::vector<std::string> v_string, std::string word_to_search, int id_line, int id_thread, int LimitMin, int LimitMax, std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> pq)
{
	int i;
    std::string text;

	word_to_search = toUpperCase(word_to_search);

	for(i = 0; i < v_string.size();i++){
		if(compareWords(word_to_search, v_string[i]) == true) {	
			if(i == 0 && v_string.size()>1){		/* If the found word is the first word of the line and the line has more than one word... */
				text = v_string[i] + " " + v_string[i+1] + " ...";
			}
			else if(v_string.size() ==1)		/* If there is only a word in the line... */
				text = v_string[i] + " ...";
			else if(i+1==v_string.size())		/* If the found word is the last word of the line... */
				text = v_string[i-1] + " " + v_string[i] + " ...";
			else 						
				text = v_string[i-1] + " " + v_string[i] + " " + v_string[i+1] + " ...";

			ThreadResult tr(1, 0, LimitMax);	
			LineResult search(id_line+1, text, i, tr);
			pq.push(search);
		}
	}
	return pq;
}

bool compareWords(std::string word, std::string w_found)
{
	int i;
    bool coincidence = false;
	/* Vector with all the simbols that the searched word could have at the begining or at the end */	
	std::vector<std::string> symbols = {"!","¡","·","$","%","&","/","(",")","=","?","¿",",","^","]","[","-","_","@","*","|",">","<","#","+","{","}","¬",".", ";",":"};
	
	w_found = toUpperCase(w_found);
	
	for(i = 0; i < symbols.size() && coincidence == false;i++){
		if(w_found == word || w_found == word + symbols[i] || w_found == symbols[i] + word)
			coincidence = true;
	}
	return coincidence;
}