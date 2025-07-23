#include <stdint.h>
#include <vector>

#include "OptiStruct.h"
#include "UsingDelerations.h"

int CkPtrstrLRep(char*& str, unsigned amtPartrep)
{
    // D:\Coding\Visual Studio\VisualStudioProjects\Training\Window006
    // if Text -> check every space-char.
    // if Path -> check every Slash symbol '\'. (NOW I AM MAKING THIS)

    int result = 0;
    int stringParts = 0;
    //int offsetedIndex = 0;
    constexpr int maxstringlen = 10;
    Bit IsFile(Bit::bfalse); Bit IsPath(Bit::btrue);
    char seperator = (IsPath.BitBool == Bit::btrue) ? '\\' : ' ';

    PArray stringparts((void*)(&maxstringlen));
    stringparts.m_1maxsize = amtPartrep; // maybe 3 is it too few
    stringparts.LinkPtr((void**)stringparts.m_2arr, (void*)&stringparts.m_1arr);

    //for (int i = 0; i < MAXPATHLEN; i++) {
    //    char currChar = str[i + offsetedIndex];
    //    if (currChar == '\0')
    //        break;
    //    if (i == 0)
    //    {
    //        stringparts.m_116arr = &str[i];
    //    }
    //    else if (stringparts.m_116arr == nullptr)
    //    {
    //        stringparts.m_116arr = &str[i + offsetedIndex];
    //    }
    //    else if (currChar != seperator)
    //    {
    //        stringparts.m_116arr[i] = currChar; // on index 4 it shows 'U' but it is for real 'r'
    //    }
    //    else {
    //        // switch it
    //        // copy the first word, convert it in a sorted array 
    //        //stringparts.m_1arr[stringParts] = 0;
    //        for (int j = 0; j < maxstringlen; j++)
    //        {
    //            if (stringparts.m_116arr[j] != '\0')
    //            {
    //                stringparts.m_1arr = &stringparts.m_116arr[j];
    //            }
    //        }
    //        std::string asdklj;
    //        for (int k = 0; k < maxstringlen*10; k++)
    //        {
    //            if (stringparts.m_1arr[k] != '\0')
    //            {
    //                if (k == 0)
    //                {
    //                    asdklj = stringparts.m_1arr;
    //                }
    //                else
    //                {
    //                    asdklj += stringparts.m_1arr[k];
    //                }
    //            }
    //        }
    //        stringparts.m_2arr[stringParts] = stringparts.m_1arr;
    //        ++stringParts;
    //        stringparts.m_116arr = nullptr;
    //    }
    //    offsetedIndex++;
    //    
    //}
    //

    //Introduction
    // 1. Scan/Mark
    // 2. Take seperately in a Buffer

    for (int i = 0; i < MAXPATHLEN; i++)
    {

    }

    return result;
}

char* SFileInPath(char* path, uint8_t szpath)
{
    char* result = {};
    char crrchpath; // currentcharpath
    Bit  myBoolBit(Bit::bfalse);

    char    fileTypeName[8];
    uint8_t pointPos = 0; // the value when you found the dot(so the file) in the path.
    uint8_t totalfileLen = 0;
    uint8_t fileTypeLen = 0;

    // 1. Get dot in Path | 2. get len of filetype.
    for (int i = 0; i < MAXPATHLEN; i++) {
        crrchpath = path[i];
        if (crrchpath == '.' && myBoolBit.BitBool == Bit::bfalse) {
            Bit* address = &myBoolBit;
            myBoolBit.BitBool = Bit::btrue;
            pointPos = (pointPos == 0) ? i : pointPos; // it can be changed ones 
        }
        if (crrchpath == '\0' && i % 2 == 0 || i >= szpath) { // xy for some reason every second char is '\0'
            fileTypeLen = i - pointPos;
            totalfileLen = i;
            break;
        }
    }


    // search back for the filename (after '\')
    const int szfilename = totalfileLen - fileTypeLen;
    std::vector<char> filenameTemp(szfilename); // i dont want to use Heap D:
    for (int i = pointPos; i > 0; i--) {
        crrchpath = path[i];
        if (crrchpath == '\\') {

            for (int i = 0; i < szfilename; i++) {
                crrchpath = path[i];
                filenameTemp.push_back(crrchpath);
            }
        }
    }

    // copy the data of the vector to result
    uint8_t i = 0;
    for (auto& o : filenameTemp) {
        result[i++] = o;
    }

    return result;
}