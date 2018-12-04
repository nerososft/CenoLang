cmake_minimum_required(VERSION 3.8)
project(Ceno_Lang)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/clcompiler/CenoLangCompiler.cpp include/clcompiler/CenoLangCompiler.h src/lexer/Lexer.cpp include/lexer/Lexer.h include/lexer/Token.h include/lexer/Keyword.h include/lexer/Tag.h include/lexer/Num.h include/lexer/Real.h src/symbol/Type.cpp include/symbol/Type.h src/symbol/Array.cpp include/symbol/Array.h src/praser/Praser.cpp include/praser/Praser.h src/praser/CPraser.cpp include/praser/CPraser.h include/symbol/StorageClass.h include/symbol/TypeQualifier.h include/symbol/StructUnion.h)
add_executable(Ceno_Lang ${SOURCE_FILES})