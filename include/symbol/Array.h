//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_ARRAY_H
#define CENO_LANG_ARRAY_H

#include "Type.h"

namespace CenoLang {
    class Array : public Type{
    public:
        Type* of;
        int size;

        Array(int size,Type* of) : Type("[]",Tag::ARRAY_TYPE,size*of->width) {
            this->of = of;
            this->size = size;
        }
    };
};


#endif //CENO_LANG_ARRAY_H
