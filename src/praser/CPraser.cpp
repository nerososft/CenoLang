//
// Created by neroyang on 2018/12/4.
//

#include <iostream>
#include "../../include/clcompiler/Config.h"
#include "../../include/praser/CPraser.h"

namespace CenoLang {
    void CPraser::move() {
        this->look = this->lexer->scan();
    }

    void CPraser::match(int t) {

#if defined(_DEBUG_PRASER)
        std::cout << "MATCH(" << look->tag << ")(" << t << ")" << std::endl;
#endif

        if (look->tag == t) {
            move();
        } else {
            error("Syntax Error", t);
        }
    }

    void CPraser::error(std::string s, int t) {
        std::cout << s << ": near line " << lexer->line << ", next char need be '" << (char) t << "'" << std::endl;
    }

    void CPraser::start(){

#if defined(_DEBUG_PRASER)
        std::cout << "start (" << look->tag << ")"<< std::endl;
#endif

        program();
    }

    void CPraser::program() {

#if defined(_DEBUG_PRASER)
        std::cout << "program (" << look->tag << ")"<< std::endl;
#endif

        translation_unit();
    }

    /**
         *  translation_unit    : external_decl
         * | translation_unit external_decl
         * ;
         */
    void CPraser::translation_unit(){

#if defined(_DEBUG_PRASER)
        std::cout << "translation_unit (" << look->tag << ")"<< std::endl;
#endif

       // do {
            external_decl();
       // }while(look->tag!=Tag::TYPE_QUALIFIER
       //       && look->tag!=Tag::BASIC_TYPE
       //       && look->tag!=Tag::STORAGE_TYPE
       //       && look->tag!='*'
       //       && look->tag!='('
       //       && look->tag!=Tag::ID);
    }


    /**
     *  external_decl       : function_definition
     * | decl
     * ;
     */
    void CPraser::external_decl(){

#if defined(_DEBUG_PRASER)
        std::cout << "external_decl (" << look->tag << ")"<< std::endl;
#endif


        function_definition();
    }


    /**
     * function_definition : decl_specs declarator decl_list compound_stat
     * |       declarator decl_list compound_stat
     * |        decl_specs declarator     compound_stat
     * |       declarator  compound_stat
     * ;
     */
    void CPraser::function_definition(){

#if defined(_DEBUG_PRASER)
        std::cout << "function_definition (" << look->tag << ")"<< std::endl;
#endif
        if(look->tag==Tag::BASIC_TYPE||look->tag==Tag::TYPE_QUALIFIER||look->tag==Tag::STORAGE_TYPE){ // decl_specs
            decl_specs();
            if(look->tag==Tag::ID || look->tag=='(' || look->tag=='*') { // // declarator
                declarator();
            }

            if(look->tag==Tag::BASIC_TYPE||look->tag==Tag::TYPE_QUALIFIER||look->tag==Tag::STORAGE_TYPE) {
                decl_list();
            }
            compound_stat();
        }else if(look->tag==Tag::ID || look->tag=='(' || look->tag=='*'){ // // declarator
            if(look->tag==Tag::BASIC_TYPE||look->tag==Tag::TYPE_QUALIFIER||look->tag==Tag::STORAGE_TYPE) {
                decl_list();
            }
            compound_stat();
        }

    }

    /**
     * decl            : decl_specs init_declarator_list ';'
     * | decl_specs            ';'
     * ;
     */
    void CPraser::decl(){
        decl_specs();
        if(look->tag==';'){ // decl_specs ';'
            match(';');
        }else{ // decl_specs init_declarator_list ';'
            init_declarator_list();
            match(';');
        }
    }

    /**
     * decl_list       : decl
     * | decl_list decl
     * ;
     */
    void CPraser::decl_list(){
        do{
            decl();
        }while(look->tag!=';');
    }


    /**
     * decl_specs      : storage_class_spec decl_specs
     * | storage_class_spec
     * | type_spec decl_specs
     * | type_spec
     * | type_qualifier decl_specs
     * | type_qualifier
     * ;
     */
    // const int const int
    void CPraser::decl_specs(){
#if defined(_DEBUG_PRASER)
        std::cout << "decl_specs (" << look->tag << ")"<< std::endl;
#endif
        while(look->tag==Tag::STORAGE_TYPE || look->tag==Tag::BASIC_TYPE || look->tag==Tag::TYPE_QUALIFIER){
            switch (look->tag){
                case Tag::STORAGE_TYPE:
                    match(Tag::STORAGE_TYPE);
                case Tag::BASIC_TYPE:
                    match(Tag::BASIC_TYPE);
                case Tag::TYPE_QUALIFIER:
                    match(Tag::TYPE_QUALIFIER);
            }
        }

    }

    /**
     * storage_class_spec  : 'auto' | 'register' | 'static' | 'extern' | 'typedef'
     * ;
     */
    void CPraser::storage_class_spec(){
        if(look->tag==Tag::STORAGE_TYPE){
            match(Tag::STORAGE_TYPE); // auto' | 'register' | 'static' | 'extern' | 'typedef'
        }
    }

    /**
     *  type_spec       : 'void' | 'char' | 'short' | 'int' | 'long' | 'float'
     *                 | 'double' | 'signed' | 'unsigned'
     *                 | struct_or_union_spec
     *                 | enum_spec
     *                 | typedef_name
     * ;
     */
    void CPraser::type_spec(){
        if(look->tag==Tag::BASIC_TYPE){
            match(Tag::BASIC_TYPE);
        }
        // todo

    }

    /**
     * type_qualifier      : 'const' | 'volatile'
     * ;
     */
    void CPraser::type_qualifier(){
        if(look->tag==Tag::TYPE_QUALIFIER){
            match(Tag::TYPE_QUALIFIER);
        }
    }

    /**
     * struct_or_union_spec    : struct_or_union id '{' struct_decl_list '}'
     * | struct_or_union   '{' struct_decl_list '}'
     * | struct_or_union id
     * ;
     */
    void CPraser::struct_or_union_spec(){
        struct_or_union(); // struct_or_union
        if(look->tag==Tag::ID){
            match(Tag::ID); // id
            if(look->tag=='{'){ // '{' struct_decl_list '}'
                match('{');
                struct_decl_list();
                match('}');
            }
        }
        if(look->tag=='{'){ // '{' struct_decl_list '}'
            match('{');
            struct_decl_list();
            match('}');
        }
    }

    /**
     *  struct_or_union     : 'struct' | 'union'
     * ;
     */
    void CPraser::struct_or_union(){
        if(look->tag==Tag::STRUCT_UNION){
            match(Tag::STRUCT_UNION);
        }
    }

    /**
     * struct_decl_list    : struct_decl
     * | struct_decl_list struct_decl
     * ;
     */
    void CPraser::struct_decl_list(){
        do{
            struct_decl();
        }while(look->tag==Tag::BASIC_TYPE || look->tag==Tag::TYPE_QUALIFIER);
    }


    /**
     * init_declarator_list    : init_declarator
     * | init_declarator_list ',' init_declarator
     * ;
     */
    void CPraser::init_declarator_list(){
        init_declarator(); // init_declarator

        while(look->tag==','){ // init_declarator_list ',' init_declarator
            match(',');
            init_declarator();
        }

    }

    /**
     * init_declarator     : declarator
     * | declarator '=' initializer
     * ;
     */
    void CPraser::init_declarator(){
        declarator();
        if(look->tag=='='){ // declarator '=' initializer
            initializer();
        }
    }

    /**
     * struct_decl     : spec_qualifier_list struct_declarator_list ';'
     * ;
     */
    void CPraser::struct_decl(){
        spec_qualifier_list();
        struct_decl_list();
        match(';');
    }

    /**
     * spec_qualifier_list : type_spec spec_qualifier_list
     * | type_spec
     * | type_qualifier spec_qualifier_list
     * | type_qualifier
     * ;
     */
    void CPraser::spec_qualifier_list(){
        switch (look->tag){
            case Tag::BASIC_TYPE:
                do{
                    match(Tag::BASIC_TYPE);
                }while(look->tag==Tag::BASIC_TYPE);
            case Tag::TYPE_QUALIFIER:
                do{
                    match(Tag::TYPE_QUALIFIER);
                }while(look->tag==Tag::TYPE_QUALIFIER);
        }
    }


    /**
     *  struct_declarator_list  : struct_declarator
     * | struct_declarator_list ',' struct_declarator
     * ;
     */
    void CPraser::struct_declarator_list(){
        do{
            struct_declarator();
        }while(look->tag==',');
        struct_declarator();
    }

    /**
     *  struct_declarator   : declarator
     * | declarator ':' const_exp
     * |       ':' const_exp
     * ;
     */
    void CPraser::struct_declarator(){
        if(look->tag==':'){ // ':' const_exp
            match(':');
            cast_exp();
        }else{
            declarator();
            if(look->tag==':'){ // declarator ':' const_exp
                const_exp();
            }
        }
    }

    /**
     * enum_spec       : 'enum' id '{' enumerator_list '}'
     * | 'enum'    '{' enumerator_list '}'
     * | 'enum' id
     * ;
     */
    void CPraser::enum_spec(){
        match(Tag::ENUM);
        if(look->tag==Tag::ID){
            match(Tag::ID);
            if(look->tag=='{'){ // 'enum' id '{' enumerator_list '}'
                match('{');
                enumerator_list();
                match('}');
            }
        }else{ // 'enum'    '{' enumerator_list '}'
            match('{');
            enumerator_list();
            match('}');
        }
    }

    /**
     *  enumerator_list     : enumerator
     * | enumerator_list ',' enumerator
     * ;
     */
    void CPraser::enumerator_list(){
        do{
            enumerator();
        }while(look->tag==',');
        enumerator();
    }

    /**
     * enumerator      : id
     * | id '=' const_exp
     * ;
     */
    void CPraser::enumerator(){
        match(Tag::ID);
        if(look->tag=='='){ // id '=' const_exp
            match('=');
            const_exp();
        }
    }

    /**
     *  declarator      : pointer direct_declarator
     * |   direct_declarator
     * ;
     */
    void CPraser::declarator(){

#if defined(_DEBUG_PRASER)
        std::cout << "declarator (" << look->tag << ")"<< std::endl;
#endif

        if(look->tag=='*'){ // pointer direct_declarator
            pointer();
            direct_declarator();
        }else{
            direct_declarator();
        }
    }

    /**
     * direct_declarator   : id
     * | '(' declarator ')'
     * | direct_declarator '[' const_exp ']'
     * | direct_declarator '['     ']'
     * | direct_declarator '(' param_type_list ')'
     * | direct_declarator '(' id_list ')'
     * | direct_declarator '('     ')'
     * ;
     */
    void CPraser::direct_declarator(){

#if defined(_DEBUG_PRASER)
        std::cout << "direct_declarator (" << look->tag << ")"<< std::endl;
#endif

        if(look->tag==Tag::ID){
            match(Tag::ID);
        }

        if(look->tag=='('){
            match('(');
            declarator();
            match(')');
            while(look->tag=='('){
                if(look->tag==')'){
                    match(')'); // direct_declarator '('     ')'
                }
                if(look->tag==Tag::ID){ // direct_declarator '(' id_list ')'
                    id_list();
                    match(')');
                }
                if(look->tag==Tag::BASIC_TYPE ||  look->tag==Tag::TYPE_QUALIFIER || look->tag==Tag::STORAGE_TYPE){ // direct_declarator '(' param_type_list ')'
                    param_type_list();
                    match(')');
                }
            }
        }

        if(look->tag=='['){
            if(look->tag==']'){
                match(']'); // direct_declarator '['     ']'
            }
            if(look->tag==Tag::NUM || look->tag==Tag::REAL){ // direct_declarator '[' const_exp ']' // todo : CONSTANT
                const_exp();
                match(']');
            }

        }


    }

    /**
     *  pointer         : '*' type_qualifier_list
     * | '*'
     * | '*' type_qualifier_list pointer
     * | '*'           pointer
     * ;
     */
    void CPraser::pointer(){
        do{
            match('*');
            if(look->tag==Tag::TYPE_QUALIFIER){
                match(Tag::TYPE_QUALIFIER);
                if(look->tag=='*'){
                    pointer();  // todo ; may be bug
                }
            }
        }while(look->tag!='*');
    }

    /**
     *  type_qualifier_list : type_qualifier
     * | type_qualifier_list type_qualifier
     * ;
     */
    void CPraser::type_qualifier_list(){
        do{
            type_qualifier();
        }while(look->tag!=Tag::TYPE_QUALIFIER);
    }

    /**
     * param_type_list     : param_list
     * | param_list ',' '...'
     * ;
     */
    void CPraser::param_type_list(){
        param_list();
        if(look->tag==','){ // param_list ',' '...'
            match(',');
            //match('...') // todo
        }
    }

    /**
     *  param_list      : param_decl
     * | param_list ',' param_decl
     * ;
     */
    void CPraser::param_list(){
        param_decl();
        while(look->tag==','){
            match(',');
            param_decl();
        }
    }

    /**
     *  param_decl      : decl_specs declarator
     * | decl_specs abstract_declarator
     * | decl_specs
     * ;
     */
    void CPraser::param_decl(){
        decl_specs();
        // todo
    }


    /**
     *  id_list         : id
     * | id_list ',' id
     * ;
     */
    void CPraser::id_list(){
        match(Tag::ID);
        while(look->tag==','){
            match(',');
            match(Tag::ID);
        }
    }

    /**
     * initializer     : assignment_exp
     * | '{' initializer_list '}'
     * | '{' initializer_list ',' '}'
     * ;
     */
    void CPraser::initializer(){
        if(look->tag=='{'){
            match('{');
            initializer_list();
            if(look->tag==','){
                match(',');
            }
            match('}');
        }else{ // todo may be need a if condition
            assignment_exp();
        }
    }

    /**
     *  initializer_list    : initializer
     * | initializer_list ',' initializer
     * ;
     */
    void CPraser::initializer_list(){
        initializer();
        while(look->tag==','){
            match(',');
            initializer();
        }
    }


    /**
     *  type_name       : spec_qualifier_list abstract_declarator
     * | spec_qualifier_list
     * ;
     */
    void CPraser::type_name(){
        spec_qualifier_list();
        if(look->tag=='*'||look->tag=='('||look->tag=='['){
            abstract_declarator();
        }
    }

    /**
     * abstract_declarator : pointer
     * | pointer direct_abstract_declarator
     * |   direct_abstract_declarator
     * ;
     */
    void CPraser::abstract_declarator(){
        if(look->tag=='*'){
            pointer();
            if(look->tag=='('||look->tag=='['){ // pointer direct_abstract_declarator
                direct_abstract_declarator();
            }
        }else if(look->tag=='('||look->tag=='['){ // direct_abstract_declarator
            direct_abstract_declarator();
        }
    }

    /**
     *  direct_abstract_declarator: '(' abstract_declarator ')'
     * | direct_abstract_declarator '[' const_exp ']'
     * |               '[' const_exp ']'
     * | direct_abstract_declarator '['    ']'
     * |               '[' ']'
     * | direct_abstract_declarator '(' param_type_list ')'
     * |               '(' param_type_list ')'
     * | direct_abstract_declarator '('        ')'
     * |               '('     ')'
     * ;
     */
    void CPraser::direct_abstract_declarator(){
        // todo complex
    }


    /**
     *  typedef_name        : id
     * ;
     */
    void CPraser::typedef_name() {
        match(Tag::ID);
    }

    /**
     * stat            : labeled_stat
     * | exp_stat
     * | compound_stat
     * | selection_stat
     * | iteration_stat
     * | jump_stat
     * ;
     */
    void CPraser::stat(){
        if(look->tag==Tag::CASE||look->tag==Tag::DEFAULT){
            labeled_stat();
        }
        if(look->tag==';'){
            exp_stat();
        }
        if(look->tag==Tag::ID){
            // complex
        }
        if(look->tag=='{'){
            compound_stat();
        }
        if(look->tag==Tag::IF||look->tag==Tag::SWITCH){
            selection_stat();
        }
        if(look->tag==Tag::WHILE||look->tag==Tag::DO||look->tag==Tag::FOR){
            iteration_stat();
        }
        if(look->tag==Tag::GOTO||look->tag==Tag::BREAK||look->tag==Tag::CONTINUE||look->tag==Tag::RETURN){
            jump_stat();
        }

    }

    /**
     * labeled_stat        : id ':' stat
     * | 'case' const_exp ':' stat
     * | 'default' ':' stat
     * ;
     */
    void CPraser::labeled_stat(){
        switch (look->tag){
            case Tag::ID: // id ':' stat
                match(Tag::ID);
                match(':');
                stat();
            case Tag::CASE: // 'case' const_exp ':' stat
                match(Tag::CASE);
                const_exp();
                match(':');
                stat();
            case Tag::DEFAULT: // 'default' ':' stat
                match(Tag::DEFAULT);
                match(':');
                stat();
        }
    }

    /**
     * exp_stat        : exp ';'
     * |   ';'
     * ;
     */
    void CPraser::exp_stat(){
        if(look->tag==';'){ // ';'
            match(';');
        }else{ // exp ';'
            exp();
            match(';');
        }
    }

    /**
     * compound_stat       : '{' decl_list stat_list '}'
     * | '{'       stat_list '}'
     * | '{' decl_list     '}'
     * | '{'           '}'
     * ;
     */
    void CPraser::compound_stat(){

#if defined(_DEBUG_PRASER)
        std::cout << "compound_stat (" << look->tag << ")"<< std::endl;
#endif

        match('{');
        if(look->tag==Tag::BASIC_TYPE||look->tag==Tag::STORAGE_TYPE||look->tag==Tag::TYPE_QUALIFIER){
            decl_list();
            if(look->tag==Tag::WHILE
               ||look->tag==Tag::DO
               ||look->tag==Tag::FOR
               ||look->tag==Tag::GOTO
               ||look->tag==Tag::BREAK
               ||look->tag==Tag::CONTINUE
               ||look->tag==Tag::RETURN
               ||look->tag==Tag::CASE
               ||look->tag==Tag::DEFAULT
               ||look->tag==';'
               ||look->tag==Tag::ID) { // '{' decl_list stat_list '}'
                stat_list();
            }else if(look->tag=='}'){ // '{' decl_list     '}'
                match('}');
            }
        }else if(look->tag==Tag::WHILE
                 ||look->tag==Tag::DO
                 ||look->tag==Tag::FOR
                 ||look->tag==Tag::GOTO
                 ||look->tag==Tag::BREAK
                 ||look->tag==Tag::CONTINUE
                 ||look->tag==Tag::RETURN
                 ||look->tag==Tag::CASE
                 ||look->tag==Tag::DEFAULT
                 ||look->tag==';'
                 ||look->tag==Tag::ID){ //'{'       stat_list '}'
            stat_list();
        }else if(look->tag=='}'){ // '{'           '}'
            match('}');
        }

    }

    /**
     *  stat_list       : stat
     * | stat_list stat
     * ;
     */
    void CPraser::stat_list(){
        do{
            stat();
        }while(look->tag!=Tag::WHILE
               && look->tag!=Tag::DO
               && look->tag!=Tag::FOR
               && look->tag!=Tag::GOTO
               && look->tag!=Tag::BREAK
               && look->tag!=Tag::CONTINUE
               && look->tag!=Tag::RETURN
               && look->tag!=Tag::CASE
               && look->tag!=Tag::DEFAULT
               && look->tag!=';'
               && look->tag!=Tag::ID);
    }

    /**
     * selection_stat      : 'if' '(' exp ')' stat
     * | 'if' '(' exp ')' stat 'else' stat
     * | 'switch' '(' exp ')' stat
     * ;
     */
    void CPraser::selection_stat(){
        switch (look->tag){
            case Tag::IF: // 'if' '(' exp ')' stat
                match(Tag::IF);
                match('(');
                exp();
                match(')');
                stat();
                if(look->tag==Tag::ELSE){ // 'if' '(' exp ')' stat 'else' stat
                    match(Tag::ELSE);
                    stat();
                }
            case Tag::SWITCH: // 'switch' '(' exp ')' stat
                match(Tag::SWITCH);
                match('(');
                exp();
                match(')');
                stat();
        }
    }

    /**
     * iteration_stat      : 'while' '(' exp ')' stat
     * | 'do' stat 'while' '(' exp ')' ';'
     * | 'for' '(' exp ';' exp ';' exp ')' stat
     * | 'for' '(' exp ';' exp ';' ')' stat
     * | 'for' '(' exp ';' ';' exp ')' stat
     * | 'for' '(' exp ';' ';' ')' stat
     * | 'for' '(' ';' exp ';' exp ')' stat
     * | 'for' '(' ';' exp ';' ')' stat
     * | 'for' '(' ';' ';' exp ')' stat
     * | 'for' '(' ';' ';' ')' stat
     * ;
     */
    void CPraser::iteration_stat(){
        switch (look->tag){
            case Tag::WHILE: // 'while' '(' exp ')' stat
                match(Tag::WHILE);
                match('(');
                exp();
                match(')');
                stat();
            case Tag::DO: // 'do' stat 'while' '(' exp ')' ';'
                match(Tag::DO);
                stat();
                match(Tag::WHILE);
                match('(');
                exp();
                match(')');
                match(';');
            case Tag::FOR:
                match(Tag::FOR);
                match('(');
                if(look->tag==';'){
                    match(';');
                    if(look->tag==';'){
                        match(';');
                        if(look->tag==')'){ // 'for' '(' ';' ';' ')' stat
                            match(')');
                            stat();
                        }else{ // 'for' '(' ';' ';' exp ')' stat
                            exp();
                            match(')');
                            stat();
                        }
                    }else{
                        exp();
                        match(';');
                        if(look->tag==')'){ // 'for' '(' ';' exp ';' ')' stat
                            match(')');
                            stat();
                        }else{ // 'for' '(' ';' exp ';' exp ')' stat
                            exp();
                            match(';');
                            exp();
                            match(')');
                            stat();
                        }
                    }
                }else{
                    exp();
                    match(';');
                    if(look->tag==';'){
                        match(';');
                        if(look->tag==')'){ // 'for' '(' exp ';' ';' ')' stat
                            match(')');
                            stat();
                        }else{ // 'for' '(' exp ';' ';' exp ')' stat
                            exp();
                            match(')');
                            stat();
                        }
                    }else{
                        exp();
                        match(';');
                        if(look->tag==')'){ // 'for' '(' exp ';' exp ';' ')' stat
                            match(')');
                            stat();
                        }else{ // 'for' '(' exp ';' exp ';' exp ')' stat
                            exp();
                            match(')');
                            stat();
                        }
                    }
                }
        }
    }

    /**
     *  jump_stat       : 'goto' id ';'
     * | 'continue' ';'
     * | 'break' ';'
     * | 'return' exp ';'
     * | 'return'  ';'
     * ;
     */
    void CPraser::jump_stat(){
        switch (look->tag){
            case Tag::GOTO: // 'goto' id ';'
                match(Tag::GOTO);
                match(Tag::ID);
                match(';');
            case Tag::CONTINUE: //'continue' ';'
                match(Tag::CONTINUE);
                match(';');
            case Tag::BREAK: // 'break' ';'
                match(Tag::BREAK);
                match(';');
            case Tag::RETURN:
                match(Tag::RETURN);
                if(look->tag==';'){
                    match(';');
                }else{
                    exp();
                    match(';');
                }
        }
    }

    /**
     *  exp         : assignment_exp
     * | exp ',' assignment_exp
     * ;
     */
    void CPraser::exp(){
        assignment_exp();
        while(look->tag==','){
            match(',');
            assignment_exp();
        }
    }

    /**
     *  assignment_exp      : conditional_exp
     * | unary_exp assignment_operator assignment_exp
     * ;
     */
    void CPraser::assignment_exp(){

    }


    /**
     * assignment_operator : '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<='
                          | '>>=' | '&=' | '^=' | '|='
     * ;
     */
    void CPraser::assignment_operator(){}

    /**
     * conditional_exp     : logical_or_exp
     * | logical_or_exp '?' exp ':' conditional_exp
     * ;
     */
    void CPraser::conditional_exp(){}

    /**
     *  const_exp       : conditional_exp
     * ;
     */
    void CPraser::const_exp(){}

    /**
     *  logical_or_exp      : logical_and_exp
     * | logical_or_exp '||' logical_and_exp
     * ;
     */
    void CPraser::logical_or_exp(){}

    /**
     * logical_and_exp     : inclusive_or_exp
     * | logical_and_exp '&&' inclusive_or_exp
     * ;
     */
    void CPraser::logical_and_exp(){}

    /**
     * inclusive_or_exp    : exclusive_or_exp
     * | inclusive_or_exp '|' exclusive_or_exp
     * ;
     */
    void CPraser::inclusive_or_exp(){}

    /**
     * exclusive_or_exp    : and_exp
     * | exclusive_or_exp '^' and_exp
     * ;
     */
    void CPraser::exclusive_or_exp(){}

    /**
     * and_exp         : equality_exp
     * | and_exp '&' equality_exp
     * ;
     */
    void CPraser::and_exp(){}

    /**
     *  equality_exp        : relational_exp
     * | equality_exp '==' relational_exp
     * | equality_exp '!=' relational_exp
     * ;
     */
    void CPraser::equality_exp(){}

    /**
     *  relational_exp      : shift_expression
     * | relational_exp '<' shift_expression
     * | relational_exp '>' shift_expression
     * | relational_exp '<=' shift_expression
     * | relational_exp '>=' shift_expression
     * ;
     */
    void CPraser::relational_exp(){}

    /**
     * shift_expression    : additive_exp
     * | shift_expression '<<' additive_exp
     * | shift_expression '>>' additive_exp
     * ;
     */
    void CPraser::shift_expression(){}

    /**
     *  additive_exp        : mult_exp
     * | additive_exp '+' mult_exp
     * | additive_exp '-' mult_exp
     * ;
     */
    void CPraser::additive_exp(){}

    /**
     *  mult_exp        : cast_exp
     * | mult_exp '*' cast_exp
     * | mult_exp '/' cast_exp
     * | mult_exp '%' cast_exp
    ;
     */
    void CPraser::mult_exp(){}

    /**
     * cast_exp        : unary_exp
     * | '(' type_name ')' cast_exp
     * ;
     */
    void CPraser::cast_exp(){}

    /**
     * unary_exp       : postfix_exp
     * | '++' unary_exp
     * | '--' unary_exp
     * | unary_operator cast_exp
     * | 'sizeof' unary_exp
     * | 'sizeof' '(' type_name ')'
     * ;
     */
    void CPraser::unary_exp(){}

    /**
     *  unary_operator      : '&' | '*' | '+' | '-' | '~' | '!'
     * ;
     */
    void CPraser::unary_operator(){}

    /**
     * postfix_exp     : primary_exp
     * | postfix_exp '[' exp ']'
     * | postfix_exp '(' argument_exp_list ')'
     * | postfix_exp '('           ')'
     * | postfix_exp '.' id
     * | postfix_exp '->' id
     * | postfix_exp '++'
     * | postfix_exp '--'
     * ;
     */
    void CPraser::postfix_exp(){}

    /**
     * primary_exp     : id
     * | const
     * | string
     * | '(' exp ')'
     * ;
     */
    void CPraser::primary_exp(){
        if(look->tag==Tag::ID){
            match(Tag::ID);
        }
        // todo
    }

    /**
     *  argument_exp_list   : assignment_exp
     * | argument_exp_list ',' assignment_exp
     * ;
     */
    void CPraser::argument_exp_list(){

    }

    /**
     * const           : int_const
     * | char_const
     * | float_const
     * | enumeration_const
     * ;
     */
    void CPraser::_const(){

    }

}