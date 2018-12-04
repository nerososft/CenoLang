//
// Created by neroyang on 2018/12/4.
//

#ifndef CENO_LANG_STRUCTUNION_H
#define CENO_LANG_STRUCTUNION_H


#include "../lexer/Keyword.h"

namespace CenoLang {
    class StructUnion : public Keyword {
    public:
        StructUnion(std::string lexeme, int tag) : Keyword(lexeme,tag){
        }
    };
    namespace StructUnions {
        static StructUnion *STRUCT = new StructUnion("struct", Tag::STRUCT_UNION);
        static StructUnion *UNION = new StructUnion("union", Tag::STRUCT_UNION);
    };
};


#endif //CENO_LANG_STRUCTUNION_H
