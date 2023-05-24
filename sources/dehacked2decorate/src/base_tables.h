#ifndef BASE_H
#define BASE_H

#include "thing.h"
#include "state.h"
#include "weapon.h"
#include <vector>
#include <fstream>
#include <sstream>
/*
 * This file contains a function to read the files that create the
 * default Doom (actually MBF) data for states, weapons, and things
 */

namespace base
{
    struct baseArray
    {
        std::vector<thing>  thingArray;
        std::vector<state>  stateArray;
        std::vector<weapon> weaponArray;
    };

    inline baseArray baseInit()
    {
        std::ifstream thingStream ("BaseTables/base_things.dat",  std::ios::binary);
        std::ifstream stateStream ("BaseTables/base_states.dat",  std::ios::binary);
        std::ifstream weaponStream("BaseTables/base_weapons.dat", std::ios::binary);

        std::vector<thing>  thingVector;
        std::vector<state>  stateVector;
        std::vector<weapon> weaponVector;

        std::string currentLine;

        //thingVector
        while( !thingStream.eof() )
        {
            int prop[9];
            int states[8];
            int sounds[5];
            uint32_t flags;

            std::stringstream dataStream;

            std::getline (thingStream,currentLine);
            dataStream.str(currentLine);
            dataStream >> prop[0]   >> prop[1]   >> prop[2]   >> prop[3]   >> prop[4]   >> prop[5]   >> prop[6]   >> prop[7]   >> prop[8];
            dataStream >> states[0] >> states[1] >> states[2] >> states[3] >> states[4] >> states[5] >> states[6] >> states[7];
            dataStream >> sounds[0] >> sounds[1] >> sounds[2] >> sounds[3] >> sounds[4];
            dataStream >> flags;
            thingVector.push_back( thing(prop, states, sounds, flags) );
        }
        thingStream.close();

        //stateVector
        while( !stateStream.eof() )
        {
            int spr, sub, nstate, dur, p1, p2;
            bool lit;
            std::string act;

            std::stringstream dataStream;

            std::getline (stateStream,currentLine);
            dataStream.str(currentLine);
            dataStream >> spr  >> sub >> lit >> nstate  >> dur >> p1  >> p2 >> act;
            stateVector.push_back( state(spr,sub,lit,nstate,dur,act,p1,p2) );
        }
        stateStream.close();

        //weaponVector
        while( !weaponStream.eof() )
        {
            int states[5];
            int prop[4];

            std::stringstream dataStream;

            std::getline (weaponStream,currentLine);
            dataStream.str(currentLine);
            dataStream >> states[0] >> states[1] >> states[2] >> states[3] >> states[4];
            dataStream >> prop[0]   >> prop[1]   >> prop[2]   >> prop[3];
            weaponVector.push_back( weapon(prop,states) );
        }
        weaponStream.close();

        baseArray DoomBaseArrays { thingVector, stateVector, weaponVector };
        return DoomBaseArrays;
    }
}

const base::baseArray DOOMBASEARRAYS = base::baseInit();

#endif // BASE_H
