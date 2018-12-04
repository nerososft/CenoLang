//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_KEYWORD_H
#define CENO_LANG_KEYWORD_H

#include <string>
#include "Token.h"
#include "Tag.h"

namespace CenoLang {
    class Keyword : public Token{
    public:
        std::string lexeme;
        Keyword(std::string lexeme, int tag) : Token(tag) {
            this->lexeme = lexeme;
        }
    };

    namespace Keywords {
        static Keyword *AND = new Keyword("&&", Tag::AND);
        static Keyword *OR = new Keyword("||", Tag::OR);

        static Keyword *EQUAL = new Keyword("==", Tag::EQUAL);
        static Keyword *N_EQUAL = new Keyword("!=", Tag::N_EQUAL);
        static Keyword *L_EQUAL = new Keyword("<=", Tag::L_EQUAL);
        static Keyword *G_EQUAL = new Keyword(">=", Tag::G_EQUAL);


        static Keyword *TRUE = new Keyword("true", Tag::TRUE);
        static Keyword *FALSE = new Keyword("false", Tag::FALSE);

        static Keyword *IF = new Keyword("if", Tag::IF);
        static Keyword *ELSE = new Keyword("else", Tag::ELSE);
        static Keyword *BREAK = new Keyword("break", Tag::BREAK);
        static Keyword *DO = new Keyword("do", Tag::DO);
        static Keyword *WHILE = new Keyword("while", Tag::WHILE);

        static Keyword *CONTINUE = new Keyword("continue", Tag::CONTINUE);
        static Keyword *RETURN = new Keyword("return", Tag::RETURN);

    };

};

#endif //CENO_LANG_KEYWORD_H
