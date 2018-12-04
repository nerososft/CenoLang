//
// Created by neroyang on 2018/12/4.
//

#ifndef CENO_LANG_TYPEQUALIFIER_H
#define CENO_LANG_TYPEQUALIFIER_H


#include "../lexer/Keyword.h"

namespace CenoLang {
    class TypeQualifier : public Keyword {
    public:
        TypeQualifier(std::string lexeme, int tag) : Keyword(lexeme,tag){
        }
    };
    namespace TypeQualifiers {
        static TypeQualifier *CONST = new TypeQualifier("const", Tag::TYPE_QUALIFIER);
        static TypeQualifier *VOLATILE = new TypeQualifier("volatile", Tag::TYPE_QUALIFIER);
    };
};


#endif //CENO_LANG_TYPEQUALIFIER_H
