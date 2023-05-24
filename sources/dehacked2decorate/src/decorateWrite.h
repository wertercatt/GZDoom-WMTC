#ifndef DECORATEWRITE_H
#define DECORATEWRITE_H

#include "base_tables.h"
#include <algorithm>
#include <vector>

/*
 * This is the main library to write a DECORATE file
 * to some ostream
 */
namespace decorate
{
   /*
    * This is the main function to write a DECORATE file
    *
    *@fileStream: the filestream to output the DECORATE file to
    *@DoomNew: this is the modified Doom data (i.e. after calling dehackedParse)
    *@DoomOld: this is the Doom data to compare against
    *
    * On exit, the data has been written to the fileStream. Only outputs data that was
    * actually changed (i.e. will not write a definition for imp if not at all changed).
    * New actors are heavily dependent on inheretance, i.e. output has form of
    *
    * Actor DH_DoomImp : DoomImp replaces DoomImp 3001
    */
    void decorateWrite(std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld);

   /*
    * This file writes the actor with the thing number to the filestream
    *
    *@thingN: the thing number of the actor you wish to write
    *@fileStream: the filestream to output the DECORATE file to
    *@DoomNew: this is the modified Doom data (i.e. after calling dehackedParse)
    *@DoomOld: this is the Doom data to compare against
    *
    * On exit, the data has been written to the fileStream. Only outputs data that was
    * actually changed (i.e. will not write "+COUNTKILL" if the thing already had that flag)
    * New actors are heavily dependent on inheretance, i.e. output has form of
    *
    * Actor DH_DoomImp : DoomImp replaces DoomImp 3001
    */
    void decorateActor( int thingN ,std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld );

    /*
    * This file writes the actor states of the thing number to the filestream
    *
    *@thingN: the thing number of the actor you wish to write
    *@fileStream: the filestream to output the DECORATE file to
    *@DoomNew: this is the modified Doom data (i.e. after calling dehackedParse)
    *@DoomOld: this is the Doom data to compare against
    *
    * On exit, the data has been written to the fileStream. Only outputs data that was
    * actually changed (i.e. Spawn will not be writted if it hasn't been changed)
    * New actors are heavily dependent on inheretance, i.e. output has form of
    *
    * Actor DH_DoomImp : DoomImp replaces DoomImp 3001
    */
    void decorateStates( int thingN, std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld );
}

//==========================================================================
//
//  HELPER FUNCTIONS
//
//==========================================================================

//Returns a vector of the "state loop"
//i.e. (state 709)->(state 710)->711->709
inline std::vector<int> stateLoop(int stateValue, std::vector<state> stateArray)
{
    std::vector<int> stateLoop;
    bool complete=false;
    int currentState = stateValue;

    while(!complete)
    {
        stateLoop.push_back(currentState);
        currentState = stateArray[currentState].get().NextState;
        //check that the current state is not an endpoint (repeat or stop [state 0])
        for( size_t i=0; i<stateLoop.size(); i++ )
        {
            if (currentState == stateLoop[i] || currentState == 0 )
            {
                //add the final state and complete
                stateLoop.push_back(currentState);
                complete=true;
                break;
            }
        }
    }
    return stateLoop;
}

//Check that the states a thing uses are the same
//i.e. Spawn=700 for both things, but frame 700 itself is different
inline bool isLoopsEqual( thing::thingStates t1, thing::thingStates t2, std::vector<state> stateArray1, std::vector<state> stateArray2 )
{
    bool returnValue = 1;

    std::vector< std::vector<int> > stateLoopVector1 =
    {
        stateLoop (t1.Spawn,   stateArray1),
        stateLoop (t1.Walk,    stateArray1),
        stateLoop (t1.Pain,    stateArray1),
        stateLoop (t1.Melee,   stateArray1),
        stateLoop (t1.Attack,  stateArray1),
        stateLoop (t1.Death,   stateArray1),
        stateLoop (t1.Explode, stateArray1),
        stateLoop (t1.Raise,   stateArray1),
    };
    std::vector< std::vector<int> > stateLoopVector2 =
    {
        stateLoop (t2.Spawn,   stateArray1),
        stateLoop (t2.Walk,    stateArray1),
        stateLoop (t2.Pain,    stateArray1),
        stateLoop (t2.Melee,   stateArray1),
        stateLoop (t2.Attack,  stateArray1),
        stateLoop (t2.Death,   stateArray1),
        stateLoop (t2.Explode, stateArray1),
        stateLoop (t2.Raise,   stateArray1),
    };

    //For each type of state
    for( size_t i=0; i<stateLoopVector1.size(); i++)
    {
        //Check that state loops are equal
        if ( stateLoopVector1[i] == stateLoopVector2[i] )
        {
            //Check that the frames themselves are equal
            for( size_t j=0; j<stateLoopVector1[i].size(); j++)
            {
                //Frame is same for both vectors (since state loops are equal)
                int frameValue = stateLoopVector1[i][j];
                returnValue &= stateArray1[frameValue] == stateArray2[frameValue];
            }
        }
        else
        {
            returnValue = 0;
            break;
        }
    }
    return returnValue;
}

inline bool isLoopsEqual( weapon::weaponStates t1, weapon::weaponStates t2, std::vector<state> stateArray1, std::vector<state> stateArray2 )
{
    bool returnValue = 1;

    std::vector< std::vector<int> > stateLoopVector1 =
    {
        stateLoop (t1.Lower,  stateArray1),
        stateLoop (t1.Raise,  stateArray1),
        stateLoop (t1.Bob,    stateArray1),
        stateLoop (t1.Fire,   stateArray1),
        stateLoop (t1.Flash,  stateArray1),
    };
    std::vector< std::vector<int> > stateLoopVector2 =
    {
        stateLoop (t2.Lower,  stateArray2),
        stateLoop (t2.Raise,  stateArray2),
        stateLoop (t2.Bob,    stateArray2),
        stateLoop (t2.Fire,   stateArray2),
        stateLoop (t2.Flash,  stateArray2),
    };

    //For each type of state
    for( size_t i=0; i<stateLoopVector1.size(); i++)
    {
        //Check that state loops are equal
        if ( stateLoopVector1[i] == stateLoopVector2[i] )
        {
            //Check that the frames themselves are equal
            for( size_t j=0; j<stateLoopVector1[i].size(); j++)
            {
                //Frame is same for both vectors (since state loops are equal)
                int frameValue = stateLoopVector1[i][j];
                returnValue &= stateArray1[frameValue] == stateArray2[frameValue];
            }
        }
        else
        {
            returnValue = 0;
            break;
        }
    }
    return returnValue;
}

//Compare the bit pos between a and b
//If same,        return 0
//If a_bit>b_bit, return 1
//If a_bit<b_bit, return 2
inline int isBitChanged(uint32_t a, uint32_t b, uint32_t pos)
{
    uint32_t v1 = a & pos;
    uint32_t v2 = b & pos;

    if( v1 == v2 ) return 0;
    if( v1 >  v2 ) return 1;
    if( v1 <  v2 ) return 2;

    return 0;
}

//Check if thing is a weapon
//If so, return which weapon it is
//If not, return -1
inline int getWeaponID(int thingN, std::vector<weapon> weaponArray)
{
    for( size_t i=0; i<weaponArray.size(); i++ )
    {
        if( thingN == weaponArray[i].getProperties().thingNumber )
            return i;
    }
    return -1;
}

//Boolean that states if value is an element of the Set
inline int isInSet( int a, std::vector<int> Tset )
{
    for( size_t i=0; i<Tset.size(); i++)
    {
        if( a == Tset[i] ) return i;
    }
    return -1;
};

inline bool isSameActions( state s1, state s2 )
{
    bool returnValue = 1;

        returnValue &= s1.get().Sprite     == s2.get().Sprite;
		returnValue &= s1.get().Lit        == s2.get().Lit;
		returnValue &= s1.get().Duration   == s2.get().Duration;
		returnValue &= s1.get().Action     == s2.get().Action;
		returnValue &= s1.get().Param1     == s2.get().Param1;
		returnValue &= s1.get().Param2     == s2.get().Param2;

    return returnValue;
};

inline bool isLoopEqual( std::vector<int> v1, std::vector<int> v2, std::vector<state> stateArray1, std::vector<state> stateArray2 )
{
    bool returnValue = 1;

    //Check that state loops are equal
    if ( v1 == v2 )
    {
        //Check that the frames themselves are equal
        for( size_t j=0; j<v1.size(); j++)
        {
            //Frame is same for both vectors (since state loops are equal)
            int frameValue = v1[j];
            returnValue &= stateArray1[frameValue] == stateArray2[frameValue];
        }
    }
    else
    {
        returnValue = 0;
    }
    return returnValue;
}

#endif // DECORATEWRITE_H
