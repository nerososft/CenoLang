//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_NUM_H
#define CENO_LANG_NUM_H

#include "Token.h"
#include "Tag.h"

namespace  CenoLang {
    class Num : public Token {
    public:
        int value;
        Num(int v) : Token(Tag::NUM){
            this->value = v;
        }
    };
};


#endif //CENO_LANG_NUM_H
