project(Lang)

cmake_minimum_required(VERSION 3.5)


### Compiler options ###
# Enable C++14 standard
set(CMAKE_CXX_STANDARD 14)


### Variables ###
# Define Lang include directory
set(LANG_INCLUDE "src")

# Define main source directory
set(LANG_SRC "src")

# Define precompiled libraries
set(LANG_LIB "lib")
link_directories(${LANG_LIB})

# Define Catch include directory
set(CATCH_PATH "include/catch_1_5_6")

# Define Boost include directory
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.61.0 REQUIRED COMPONENTS program_options)
set(LANG_BOOST_INCLUDE "include/boost_1_61_0")

### Project source and headers ###
set(LANG_ROOT_PATH ${LANG_SRC})
set(LANG_ROOT_HEADERS "${LANG_ROOT_PATH}/LangFile.hpp"
                      "${LANG_ROOT_PATH}/FileFormatException.hpp"
                      "${LANG_ROOT_PATH}/FileNotFoundException.hpp"
)
set(LANG_ROOT_SOURCE "${LANG_ROOT_PATH}/LangFile.cpp")
source_group(Lang FILES ${LANG_ROOT_HEADERS} ${LANG_ROOT_SOURCE})

set(LANG_LANGUAGE_PATH "${LANG_SRC}/Language")
set(LANG_LANGUAGE_HEADERS "${LANG_LANGUAGE_PATH}/Language.hpp"
                          "${LANG_LANGUAGE_PATH}/AST.hpp"
                          "${LANG_LANGUAGE_PATH}/Grammar.hpp"
                          "${LANG_LANGUAGE_PATH}/Functions.hpp"
                          "${LANG_LANGUAGE_PATH}/Environment.hpp"
                          "${LANG_LANGUAGE_PATH}/Scope.hpp"
                          "${LANG_LANGUAGE_PATH}/ASTVisitor.hpp"
                          "${LANG_LANGUAGE_PATH}/CompileAST.hpp"
                          "${LANG_LANGUAGE_PATH}/PrintAST.hpp"
)
set(LANG_LANGUAGE_SOURCE "${LANG_LANGUAGE_PATH}/CompileAST.cpp"
                         "${LANG_LANGUAGE_PATH}/PrintAST.cpp"
)
source_group(Lang\\Language FILES ${LANG_LANGUAGE_HEADERS} ${LANG_LANGUAGE_SOURCE})

set(LANG_BYTECODE_PATH "${LANG_SRC}/Bytecode")
set(LANG_BYTECODE_HEADERS "${LANG_BYTECODE_PATH}/Bytecode.hpp"
                          "${LANG_BYTECODE_PATH}/AST.hpp"
                          "${LANG_BYTECODE_PATH}/Grammar.hpp"
                          "${LANG_BYTECODE_PATH}/InstructionSet.hpp"
                          "${LANG_BYTECODE_PATH}/Visitors.hpp"
                          "${LANG_BYTECODE_PATH}/Functions.hpp"
)
set(LANG_BYTECODE_SOURCE "${LANG_BYTECODE_PATH}/Visitors.cpp")
source_group(Lang\\Bytecode FILES ${LANG_BYTECODE_HEADERS} ${LANG_BYTECODE_SOURCE})

set(LANG_VM_PATH "${LANG_SRC}/VM")
set(LANG_VM_HEADERS "${LANG_VM_PATH}/VM.hpp"
                     "${LANG_VM_PATH}/DualKeys.hpp"
                     "${LANG_VM_PATH}/Stack.hpp"
)
set(LANG_VM_SOURCE "${LANG_VM_PATH}/VM.cpp")
source_group(Lang\\VM FILES ${LANG_VM_HEADERS} ${LANG_VM_SOURCE})

set(LANG_TEST_PATH "${LANG_SRC}/Test")
set(LANG_TEST_SOURCE "${LANG_TEST_PATH}/Bytecode.cpp"
                     "${LANG_TEST_PATH}/Language.cpp"
                     "${LANG_TEST_PATH}/LangFile.cpp"
                     "${LANG_TEST_PATH}/VM.cpp"
)
source_group(Lang\\Test FILES ${LANG_TEST_SOURCE})

set(LANG_COMPILER_MAIN "${LANG_SRC}/Compiler/main.cpp")
source_group(Compiler FILES ${LANG_COMPILER_MAIN})
set(LANG_ASSEMBLER_MAIN "${LANG_SRC}/Assembler/main.cpp")
source_group(Assembler FILES ${LANG_ASSEMBLER_MAIN})
set(LANG_RUNTIME_MAIN "${LANG_SRC}/Runtime/main.cpp")
source_group(Runtime FILES ${LANG_RUNTIME_MAIN})
set(LANG_TEST_MAIN "${LANG_SRC}/Test/main.cpp")
source_group(Test FILES ${LANG_TEST_MAIN})

set(LANG_HEADERS ${LANG_ROOT_HEADERS} ${LANG_LANGUAGE_HEADERS} ${LANG_BYTECODE_HEADERS} ${LANG_VM_HEADERS})
set(LANG_SOURCE ${LANG_ROOT_SOURCE} ${LANG_LANGUAGE_SOURCE} ${LANG_BYTECODE_SOURCE} ${LANG_VM_SOURCE} ${LANG_TEST_SROUCE})


### Targets ###
# Test
add_executable(Test ${LANG_ROOT_HEADERS} ${LANG_ROOT_SOURCE} ${LANG_TEST_SOURCE} ${LANG_TEST_MAIN})
target_include_directories(Test BEFORE PUBLIC
                               #${Boost_INCLUDE_DIRS}   # bug in boost release for Windows
                               ${LANG_BOOST_INCLUDE}
                               ${CATCH_PATH}
                               ${LANG_INCLUDE}
)

# langc (compiler)
add_executable(langc ${LANG_ROOT_HEADERS} ${LANG_ROOT_SOURCE}
                     ${LANG_LANGUAGE_HEADERS} ${LANG_LANGUAGE_SOURCE}
                     ${LANG_BYTECODE_HEADERS} ${LANG_BYTECODE_SOURCE}
                     ${LANG_COMPILER_MAIN}
)
target_include_directories(langc BEFORE PUBLIC
                           #${Boost_INCLUDE_DIRS}
                           ${LANG_BOOST_INCLUDE}
                           ${LANG_INCLUDE}
)
target_link_libraries(langc ${Boost_PROGRAM_OPTIONS_LIBRARY})

# lang (runtime)
add_executable(lang ${LANG_ROOT_HEADERS} ${LANG_ROOT_SOURCE}
                    ${LANG_BYTECODE_HEADERS}
                    ${LANG_VM_HEADERS} ${LANG_VM_SOURCE}
                    ${LANG_RUNTIME_MAIN}
)
target_include_directories(lang BEFORE PUBLIC
                           #${Boost_INCLUDE_DIRS}
                           ${LANG_BOOST_INCLUDE}
                           ${LANG_INCLUDE}
)
target_link_libraries(lang ${Boost_PROGRAM_OPTIONS_LIBRARY})

# langasm (assembler)
add_executable(langasm ${LANG_ROOT_HEADERS} ${LANG_ROOT_SOURCE}
                       ${LANG_BYTECODE_HEADERS} ${LANG_BYTECODE_SOURCE}
                       ${LANG_ASSEMBLER_MAIN}
)
target_include_directories(langasm BEFORE PUBLIC
                           #${Boost_INCLUDE_DIRS}
                           ${LANG_BOOST_INCLUDE}
                           ${LANG_INCLUDE}
)
target_link_libraries(langasm ${Boost_PROGRAM_OPTIONS_LIBRARY})
