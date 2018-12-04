//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_TYPE_H
#define CENO_LANG_TYPE_H

#include "../lexer/Keyword.h"

namespace CenoLang {
    class Type : public Keyword {
    public:
        int width;
        Type(std::string lexeme, int tag, int width) : Keyword(lexeme,tag){
            this->width = width;
        }


        static bool isNumeric(Type* p);

        static Type* maxNubericType(Type* t1, Type* t2);

    };
    namespace Types {
        static Type *INT = new Type("int", Tag::BASIC_TYPE, 4);
        static Type *FLOAT = new Type("float", Tag::BASIC_TYPE, 8);
        static Type *CHAR = new Type("char", Tag::BASIC_TYPE, 1);
        static Type *BOOLEAN = new Type("boolean", Tag::BASIC_TYPE, 1);
    };
};


#endif //CENO_LANG_TYPE_H
