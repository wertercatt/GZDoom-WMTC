#include "dehackedParser.h"
#include "dehacked_data.h"
//Would use regex but it is broken in C++11


int lineNumber;
using namespace std;
//==========================================================================
//
//  DehackedParse
//
//==========================================================================
void dehacked::dehackedParse( ifstream &fileStream, base::baseArray &DoomBase )
{
    lineNumber=0;
    string currentLine;

    while( !fileStream.eof() )
    {
        //These variable should all be intentionally cleared every loop
        string firstWord;
        string secondWord;
        stringstream dataStream;
        bool parseMatch=false;

        getline(fileStream, currentLine);
        lineNumber++;
        //get first two words
        dataStream << currentLine;
        dataStream >> firstWord >> secondWord;

        //Skip comments, patch formats, doom versions, whacked configs, and blank lines
        if( firstWord[0] == '#' || icompare(firstWord,"Patch") || icompare(firstWord,"Doom") || icompare(firstWord,"Engine") || icompare(firstWord,"Data") || icompare(firstWord,"IWAD") || icompare(firstWord,"") )
        {
            continue;
        }

        //If there is an equal sign without context
        if( currentLine.find_first_of("=") != string::npos )
        {
            std::cerr << "Error on line " << lineNumber << ": \"" << removeBreaks(currentLine) << "\" does not make sense without a header" << std::endl;
            continue;
        }

        //This is where the parsing happens
        for_each( parseActions.begin(), parseActions.end(), [&](stringAction Action)
        {
            if( icompare(firstWord,Action.str) && !parseMatch )
            {
                Action.foo(fileStream, secondWord, DoomBase);
                parseMatch=true;
            }
        });
        if(!parseMatch)
        {
            std::cerr << "Error on line " << lineNumber << ": cannot interpret meaning of \"" << removeBreaks(currentLine) << "\" in this context" << std::endl;
        }
    }
}

