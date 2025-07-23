#include "OptiStruct.h"

PArray::PArray(void* maxsize) : m_1maxsize(0), m_2arr(0)
{
    m_0maxsize = *(int*)maxsize;
    m_1arr = {}; m_2arr = {};
}