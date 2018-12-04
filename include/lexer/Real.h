//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_REAL_H
#define CENO_LANG_REAL_H

#include "Token.h"
#include "Tag.h"

namespace  CenoLang {
    class Real : public Token {
    public:
        float value;
        Real(float value) : Token(Tag::REAL){
            this->value = value;
        }
    };
};


#endif //CENO_LANG_REAL_H
