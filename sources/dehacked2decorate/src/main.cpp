#include <fstream>
#include <iostream>
#include "base_tables.h"
#include "dehackedParser.h"
#include "decorateWrite.h"

int main(int argc, char** argv)
{
    base::baseArray DoomData = DOOMBASEARRAYS;
    std::string argument = argv[1];
    size_t middle = argument.find('.');
    std::string name = argument.substr(0,middle);

    std::ifstream fs(argument, std::ios::binary);
    std::ofstream outputFile(name+".dec", std::ios::binary);
    std::ofstream log("log.txt", std::ios_base::app);
    auto orig = std::cerr.rdbuf(log.rdbuf());

    std::cerr << argument << std::endl;

    dehacked::dehackedParse( fs, DoomData );

    decorate::decorateWrite( outputFile, DoomData, DOOMBASEARRAYS );

    std::cerr << std::endl;

    std::cerr.rdbuf(orig);
    fs.close();
    outputFile.close();
    log.close();

    return 0;
}
