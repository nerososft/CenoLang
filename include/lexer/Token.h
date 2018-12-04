//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_TOKEN_H
#define CENO_LANG_TOKEN_H

namespace CenoLang {
    class Token {
    public:
        int tag;

        Token(int tag){
            this->tag = tag;
        }
    };
};


#endif //CENO_LANG_TOKEN_H
