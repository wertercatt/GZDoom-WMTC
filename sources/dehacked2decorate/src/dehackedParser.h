#ifndef DEHACKEDPARSE_H
#define DEHACKEDPARSE_H

#include <algorithm>
#include <functional>
#include "base_tables.h" //Contains BASEARRAYS
/*
 * This is a library of all the main functions necessary for
 * parsing a DEHACKED file.
 * What is meant by this is taking a filestream and a baseArray
 * (see base_tables header), reading the filestream as a DEHACKED
 * file, and returning a modified version of the baseArray.
 */

extern int lineNumber;

namespace dehacked
{
//==========================================================================
//
//  DehackedParse
//
//==========================================================================
    /*
     * This is the main file of this library
     *
     * @fileStream: the filestream to the DEHACKED file
     * @DoomBase: The base properties the DEHACKED file is changing
     *
     * On exit, the DoomBase array will be modified based on the DEHACKED file
     */
    void dehackedParse( std::ifstream &fileStream, base::baseArray &DoomBase );
}


//==========================================================================
//
//  Helper Functions
//
//==========================================================================

//Remove all whitespace
inline std::string removeSpace(const std::string str)
{
    std::string a = str;
    a.erase(remove_if(a.begin(), a.end(), isspace), a.end());
    return a;
}

//Remove all whitespace except space
inline std::string removeBreaks(const std::string str)
{
    std::string a = str;
    a.erase(remove_if(a.begin(), a.end(), [](char a){ return( isspace(a) && a!=' ' ); } ), a.end());
    return a;
}

//Tells if a string appears to be a number or not
//Empty string returns false
inline bool isNumber(std::string line)
{
    if(line == "")
        return 0;

    std::string str = removeSpace(line);

    char* p;
    strtol(str.c_str(), &p, 10);
    return *p == 0;
}

//Case and whitespace insensitive compare
inline bool icompare(const std::string str1, const std::string str2)
{
    std::string a = removeSpace(str1);
    std::string b = removeSpace(str2);

    if (a.size() != b.size())
        return false;

    for (unsigned int i = 0; i < a.size(); ++i)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}



#endif //DEHACKEDPARSE_H
