//
// Created by neroyang on 2018/12/4.
//

#include <iostream>
#include "../../include/praser/CPraser.h"

namespace CenoLang {
    void CPraser::move() {
        this->look = this->lexer->scan();
    }

    void CPraser::match(int t) {
        std::cout << "MATCH(" << look->tag << ")(" << t << ")" << std::endl;
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
        program();
    }

    void CPraser::program() {
        translation_unit();
    }

    /**
         *  translation_unit    : external_decl
         * | translation_unit external_decl
         * ;
         */
    void CPraser::translation_unit(){
        external_decl();
        // todo
    }


    /**
     *  external_decl       : function_definition
     * | decl
     * ;
     */
    void CPraser::external_decl(){
        function_definition();
    }


    /**
     * function_definition : decl_specs declarator decl_list compound_stat
     * |       declarator decl_list compound_stat
     * | decl_specs declarator     compound_stat
     * |       declarator  compound_stat
     * ;
     */
    void CPraser::function_definition();

    /**
     * decl            : decl_specs init_declarator_list ';'
     * | decl_specs            ';'
     * ;
     */
    void CPraser::decl();

    /**
     * decl_list       : decl
     * | decl_list decl
     * ;
     */
    void CPraser::decl_list();


    /**
     * decl_specs      : storage_class_spec decl_specs
     * | storage_class_spec
     * | type_spec decl_specs
     * | type_spec
     * | type_qualifier decl_specs
     * | type_qualifier
     * ;
     */
    void CPraser::decl_specs();

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
        // todo
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
    void CPraser::struct_decl_list();


    /**
     * init_declarator_list    : init_declarator
     * | init_declarator_list ',' init_declarator
     * ;
     */
    void CPraser::init_declarator_list();

    /**
     * init_declarator     : declarator
     * | declarator '=' initializer
     * ;
     */
    void CPraser::init_declarator();

    /**
     * struct_decl     : spec_qualifier_list struct_declarator_list ';'
     * ;
     */
    void CPraser::struct_decl();

    /**
     * spec_qualifier_list : type_spec spec_qualifier_list
     * | type_spec
     * | type_qualifier spec_qualifier_list
     * | type_qualifier
     * ;
     */
    void CPraser::spec_qualifier_list();


    /**
     *  struct_declarator_list  : struct_declarator
     * | struct_declarator_list ',' struct_declarator
     * ;
     */
    void CPraser::struct_declarator_list();

    /**
     *  struct_declarator   : declarator
     * | declarator ':' const_exp
     * |       ':' const_exp
     * ;
     */
    void CPraser::struct_declarator();

    /**
     * enum_spec       : 'enum' id '{' enumerator_list '}'
     * | 'enum'    '{' enumerator_list '}'
     * | 'enum' id
     * ;
     */
    void CPraser::enum_spec();

    /**
     *  enumerator_list     : enumerator
     * | enumerator_list ',' enumerator
     * ;
     */
    void CPraser::enumerator_list();

    /**
     * enumerator      : id
     * | id '=' const_exp
     * ;
     */
    void CPraser::enumerator();

    /**
     *  declarator      : pointer direct_declarator
     * |   direct_declarator
     * ;
     */
    void CPraser::declarator();

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
    void CPraser::direct_declarator();

    /**
     *  pointer         : '*' type_qualifier_list
     * | '*'
     * | '*' type_qualifier_list pointer
     * | '*'           pointer
     * ;
     */
    void CPraser::pointer();

    /**
     *  type_qualifier_list : type_qualifier
     * | type_qualifier_list type_qualifier
     * ;
     */
    void CPraser::type_qualifier_list();

    /**
     * param_type_list     : param_list
     * | param_list ',' '...'
     * ;
     */
    void CPraser::param_type_list();

    /**
     *  param_list      : param_decl
     * | param_list ',' param_decl
     * ;
     */
    void CPraser::param_list();

    /**
     *  param_decl      : decl_specs declarator
     * | decl_specs abstract_declarator
     * | decl_specs
     * ;
     */
    void CPraser::param_decl();


    /**
     *  id_list         : id
     * | id_list ',' id
     * ;
     */
    void CPraser::id_list();

    /**
     * initializer     : assignment_exp
     * | '{' initializer_list '}'
     * | '{' initializer_list ',' '}'
     * ;
     */
    void CPraser::initializer();

    /**
     *  initializer_list    : initializer
     * | initializer_list ',' initializer
     * ;
     */
    void CPraser::initializer_list();


    /**
     *  type_name       : spec_qualifier_list abstract_declarator
     * | spec_qualifier_list
     * ;
     */
    void CPraser::type_name();

    /**
     * abstract_declarator : pointer
     * | pointer direct_abstract_declarator
     * |   direct_abstract_declarator
     * ;
     */
    void CPraser::abstract_declarator();

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
    void CPraser::direct_abstract_declarator();


    /**
     *  typedef_name        : id
     * ;
     */
    void CPraser::typedef_name();

    /**
     * stat            : labeled_stat
     * | exp_stat
     * | compound_stat
     * | selection_stat
     * | iteration_stat
     * | jump_stat
     * ;
     */
    void CPraser::stat();

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
        match('{');
        // todo
    }

    /**
     *  stat_list       : stat
     * | stat_list stat
     * ;
     */
    void CPraser::stat_list();

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
    void CPraser::exp();

    /**
     *  assignment_exp      : conditional_exp
     * | unary_exp assignment_operator assignment_exp
     * ;
     */
    void CPraser::assignment_exp();


    /**
     * assignment_operator : '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<='
                          | '>>=' | '&=' | '^=' | '|='
     * ;
     */
    void CPraser::assignment_operator();

    /**
     * conditional_exp     : logical_or_exp
     * | logical_or_exp '?' exp ':' conditional_exp
     * ;
     */
    void CPraser::conditional_exp();

    /**
     *  const_exp       : conditional_exp
     * ;
     */
    void CPraser::const_exp();

    /**
     *  logical_or_exp      : logical_and_exp
     * | logical_or_exp '||' logical_and_exp
     * ;
     */
    void CPraser::logical_or_exp();

    /**
     * logical_and_exp     : inclusive_or_exp
     * | logical_and_exp '&&' inclusive_or_exp
     * ;
     */
    void CPraser::logical_and_exp();

    /**
     * inclusive_or_exp    : exclusive_or_exp
     * | inclusive_or_exp '|' exclusive_or_exp
     * ;
     */
    void CPraser::inclusive_or_exp();

    /**
     * exclusive_or_exp    : and_exp
     * | exclusive_or_exp '^' and_exp
     * ;
     */
    void CPraser::exclusive_or_exp();

    /**
     * and_exp         : equality_exp
     * | and_exp '&' equality_exp
     * ;
     */
    void CPraser::and_exp();

    /**
     *  equality_exp        : relational_exp
     * | equality_exp '==' relational_exp
     * | equality_exp '!=' relational_exp
     * ;
     */
    void CPraser::equality_exp();

    /**
     *  relational_exp      : shift_expression
     * | relational_exp '<' shift_expression
     * | relational_exp '>' shift_expression
     * | relational_exp '<=' shift_expression
     * | relational_exp '>=' shift_expression
     * ;
     */
    void CPraser::relational_exp();

    /**
     * shift_expression    : additive_exp
     * | shift_expression '<<' additive_exp
     * | shift_expression '>>' additive_exp
     * ;
     */
    void CPraser::shift_expression();

    /**
     *  additive_exp        : mult_exp
     * | additive_exp '+' mult_exp
     * | additive_exp '-' mult_exp
     * ;
     */
    void CPraser::additive_exp();

    /**
     *  mult_exp        : cast_exp
     * | mult_exp '*' cast_exp
     * | mult_exp '/' cast_exp
     * | mult_exp '%' cast_exp
    ;
     */
    void CPraser::mult_exp();

    /**
     * cast_exp        : unary_exp
     * | '(' type_name ')' cast_exp
     * ;
     */
    void CPraser::cast_exp();

    /**
     * unary_exp       : postfix_exp
     * | '++' unary_exp
     * | '--' unary_exp
     * | unary_operator cast_exp
     * | 'sizeof' unary_exp
     * | 'sizeof' '(' type_name ')'
     * ;
     */
    void CPraser::unary_exp();

    /**
     *  unary_operator      : '&' | '*' | '+' | '-' | '~' | '!'
     * ;
     */
    void CPraser::unary_operator();

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
    void CPraser::postfix_exp();

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