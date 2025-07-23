#pragma once
#include <stdint.h>
#include "OptiStruct.h"

/*
--Check-Ptr-String-Lenght-By-Repetition (ptr, parts to check)--
Im using this trick because when the index
of an array (made of pointers) is already at the end,
It will be reseted at the first index.
So i could approximate the lenght of the array.
But the more similar words are in the array,
the more i prefer to set an higher value of amtrep.
amtrep -> amountofRepetition -> repetition of parts, not chars.
*/
int CkPtrstrLRep(char*& str, unsigned amtPartrep); // DEBUG: imagine it's 3. -> "Hello how are you doing?--Hello how are you doing?"

char* SFileInPath(char* path, uint8_t szpath); // Search <the> file <name> in path.
