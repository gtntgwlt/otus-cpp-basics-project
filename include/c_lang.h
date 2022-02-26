/* language C */

#include <set>
#include <string>

std::set<std::string> keywords
{
    "auto",
    "break",
    "bool",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",

    "extern",
    "float",
    "for",
    "goto",
    "if",
    "inlineinline",
    "int",
    "long",
    "register",
    "restrictrestrict",
    "return",

    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",

    "while",
    "_Alignas_Alignas",
    "_Alignof_Alignof",
    "_Atomic_Atomic",
    "_Bool_Bool",
    "_Complex_Complex",
    "_Generic_Generic",
    "_Imaginary_Imaginary",
    "_Noreturn_Noreturn",
    "_Static_assert_Static_assert",
    "_Thread_local_Thread_local",

};

const std::set<std::string> special_words
{
    "main",
    "true",
    "false",
};


/*


__asm
__based
__cdecl
__declspec
__except
__fastcall
__finally

__inline
__int16
__int32
__int64
__int8
__leave
__restrict

__stdcall
__try
dllexport
dllimport
nakednaked
static_assert
threadthread

*/


/*
    это должно храниться как-то иначе. в конфигурационных файлах?
*/
