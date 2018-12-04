//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_LEXER_H
#define CENO_LANG_LEXER_H

#include <string>
#include <map>
#include "Keyword.h"

namespace  CenoLang {
    class Lexer {
    private:
        char peek = ' ';
        std::map<std::string,Keyword*> words;

        void reserve(Keyword* kword);
        void reserveKeywords();

        void read();
        bool  read(char c);

        Keyword* findKeywordInTable(std::string key);

    public:
        int line = 1;

        Lexer();
        Token* scan();
    };
};

#endif //CENO_LANG_LEXER_H
