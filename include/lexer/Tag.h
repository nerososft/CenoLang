//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_TAG_H
#define CENO_LANG_TAG_H

#include "Token.h"

namespace CenoLang {
    class Tag {
    public:
        static const int AND       = 0;
        static const int OR        = 1;

        static const int EQUAL     = 2;
        static const int N_EQUAL   = 3;
        static const int L_EQUAL   = 4;
        static const int G_EQUAL   = 5;

        static const int TRUE      = 6;
        static const int FALSE     = 7;

        static const int IF        = 8;
        static const int ELSE      = 9;
        static const int BREAK     = 10;
        static const int DO        = 11;
        static const int WHILE     = 12;

        static const int NUM       = 13;
        static const int REAL      = 14;

        static const int ID      = 15;

        static const int BASIC_TYPE      = 16;
        static const int ARRAY_TYPE      = 17;

        static const int CONTINUE = 18;
        static const int RETURN = 19;



    };
}


#endif //CENO_LANG_TAG_H
