#pragma once
//Optistruct -> "Optimized Struct"

//Initialization -> bitbool = bfalse;
struct Bit
{
    unsigned BitBool : 1; // i prefer to use bitfields, rather then bools
    enum BooleanKeyword
    {
        bfalse,
        btrue
    };
    Bit(BooleanKeyword em) : BitBool(em) { };
};

// I dont want to use Heap! >:| | P -> Pointer.
// In my case m_0arr is the array of chars -> string
// And m_1arr is the array of these ( (array of chars) -> string)
// and that array of strings i am calling "Parts"
struct PArray
{
    int   m_116maxsize = 0; char* m_116arr = 0; // 1D|2D    // 116 -> 't' -> temp buffer -> only 
    int   m_0maxsize = 0, m_1maxsize = 0; // 1D|2D
    char* m_1arr = 0;  char** m_2arr = 0; // 1D|2D    // m_0arr would be just an char, we dont want that.
    // void* because i use int and int8_t.
    PArray(void* maxsize);
    void LinkPtr(void** a, void* b) { a = &b; } //m_1arr = &m_0arr; 
};