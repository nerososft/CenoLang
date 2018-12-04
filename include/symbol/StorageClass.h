//
// Created by neroyang on 2018/12/4.
//

#ifndef CENO_LANG_STORAGECLASS_H
#define CENO_LANG_STORAGECLASS_H


#include "../lexer/Keyword.h"

namespace CenoLang {
    class StorageClass : public Keyword {
    public:
        StorageClass(std::string lexeme, int tag) : Keyword(lexeme,tag){
        }
    };
    namespace StorageClasses {
        static StorageClass *AUTO = new StorageClass("auto", Tag::STORAGE_TYPE);
        static StorageClass *REGISTER = new StorageClass("register", Tag::STORAGE_TYPE);
        static StorageClass *STATIC = new StorageClass("static", Tag::STORAGE_TYPE);
        static StorageClass *EXTERN = new StorageClass("extern", Tag::STORAGE_TYPE);
        static StorageClass *TYPEDEF = new StorageClass("typedef", Tag::STORAGE_TYPE);
    };
};


#endif //CENO_LANG_STORAGECLASS_H
