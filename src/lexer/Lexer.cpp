//
// Created by neroyang on 2018/12/3.
//

#include "../../include/lexer/Lexer.h"
#include "../../include/lexer/Num.h"
#include "../../include/lexer/Real.h"
#include "../../include/symbol/Type.h"
#include "../../include/symbol/StorageClass.h"
#include "../../include/symbol/TypeQualifier.h"
#include "../../include/symbol/StructUnion.h"

#include <vector>
#include <iostream>

namespace  CenoLang {

    void Lexer::reserve(Keyword* kword){
        this->words.insert(std::pair<std::string,Keyword*>(kword->lexeme, kword));
    }

    void Lexer::reserveKeywords(){
        reserve(Keywords::FALSE);
        reserve(Keywords::TRUE); // true


        reserve(Keywords::IF); // if
        reserve(Keywords::ELSE); // else
        reserve(Keywords::SWITCH); // switch
        reserve(Keywords::DO); // do
        reserve(Keywords::WHILE); // while
        reserve(Keywords::FOR); // for

        reserve(Keywords::GOTO); // goto
        reserve(Keywords::CONTINUE); // continue
        reserve(Keywords::BREAK); // break
        reserve(Keywords::RETURN); // return


        reserve(Types::BOOLEAN); // double
        reserve(Types::CHAR); // char
        reserve(Types::FLOAT); // float
        reserve(Types::VOID); // void
        reserve(Types::SHORT); //short
        reserve(Types::DOUBLE); // double
        reserve(Types::LONG); // long
        reserve(Types::UNSIGNED); // unsigned
        reserve(Types::SIGNED); // signed

        reserve(StorageClasses::AUTO); // auto
        reserve(StorageClasses::REGISTER); // register
        reserve(StorageClasses::STATIC); // static
        reserve(StorageClasses::EXTERN); // extern
        reserve(StorageClasses::TYPEDEF); // typedef

        reserve(TypeQualifiers::CONST); // consts
        reserve(TypeQualifiers::VOLATILE); // volatile

        reserve(StructUnions::STRUCT); // struct
        reserve(StructUnions::UNION); // union


    }

    Lexer::Lexer(){
        reserveKeywords();
    }

    void Lexer::read(){
        peek = (char)getchar();
    }

    bool  Lexer::read(char c){
        read();
        if(peek != c){
            return false;
        }
        peek = ' ';
        return true;
    }

    Token* Lexer::scan(){
        for(;;read()){
            if(peek== ' ' || peek == '\t'){
                //continue;
            } else if(peek == '\n'){
                line = line+1;
            } else {
                break;
            }
        }


        switch(peek){
            case '&':
                if(read('&')){
                    return Keywords::AND;
                } else {
                    return new Token('&');
                }
            case '|':
                if(read('|')){
                    return Keywords::OR;
                } else {
                    return new Token('|');
                }

            case '=':
                if(read('=')){
                    return Keywords::EQUAL;
                } else {
                    return new Token('=');
                }

            case '!':
                if(read('=')){
                    return Keywords::N_EQUAL;
                } else {
                    return new Token('!');
                }

            case '>':
                if(read('=')){
                    return Keywords::G_EQUAL;
                } else {
                    return new Token('>');
                }

            case '<':
                if(read('=')){
                    return Keywords::L_EQUAL;
                } else {
                    return new Token('<');
                }
            default:break;
        }

        if(isdigit(peek)){
            int v = 0;
            do {
                v = 10 * v +  (int)(peek - '0');
                read();
            } while(isdigit(peek));

            if(peek != '.'){
                return new Num(v);
            }

            float x = v, d =10;
            for(;;){
                read();
                if(!isdigit(peek)){
                    break;
                }
                x = x + (int)(peek - '0')/d;
                d = d * 10;
            }
            return new Real(x);
        }

        auto buffer = new std::vector<char>();
        if((peek>='a' && peek <='z')||(peek>='A' && peek <='Z')){ //字母
            do{
                buffer->push_back(peek);
                read();
            }while(isdigit(peek) || ((peek>='a' && peek <='z')||(peek>='A' && peek <='Z'))); // 数字或者小写字母

            auto *w = new char[buffer->size()]();
            std::vector<char>::iterator it;
            int index = 0;
            for(it=buffer->begin();it!=buffer->end();it++){
                w[index++] = *it;
            }
            std::string sw(w);

            Keyword* kw = findKeywordInTable(sw);
            if(kw != NULL){
                return kw;
            }
            return new Keyword(sw,Tag::ID);
        }

        auto *t = new Token(peek);
        peek = ' ';
        return t;
    }

    Keyword* Lexer::findKeywordInTable(std::string key){
        std::map<std::string,Keyword*>::iterator iter;
        for(iter=this->words.begin(); iter!=this->words.end(); iter++) {
            Keyword* keyword = iter->second;
            std::cout<<"FINF("<<key<<") BL("<<iter->first<<") TAG("<<keyword->tag<<")"<<std::endl;
            if(iter->first==key){
                return iter->second;
            }
        }
        return NULL;
    }
};