#include "decorateWrite.h"
#include "decorate_data.h"
#include "dehackedParser.h" //For helper functions
#include <algorithm>

//==========================================================================
//
//  decorateWrite
//
//==========================================================================
void decorate::decorateWrite(std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld)
{
    std::vector<int> changedThings;
    //Check if thing has changed
    for( size_t i=0; i<DoomNew.thingArray.size(); i++ )
    {
        //If thing values have changed (Whacked thing information)
        if( DoomNew.thingArray[i] != DoomOld.thingArray[i] )
        {
            changedThings.push_back(i);
        }
        else
        {
            //The states the thing uses are different
            if(!isLoopsEqual( DoomNew.thingArray[i].getStates( ), DoomOld.thingArray[i].getStates( ), DoomNew.stateArray, DoomOld.stateArray ) )
            {
                changedThings.push_back(i);
            }
        }
    }

    //Check if weapon has changed
    for( size_t i=0; i<DoomNew.weaponArray.size(); i++ )
    {
        //If weapon values have changed (Whacked weapon information)
        if( DoomNew.weaponArray[i] != DoomOld.weaponArray[i] )
        {
            changedThings.push_back( DoomNew.weaponArray[i].getProperties().thingNumber );
        }
        else
        {
            //The states the weapon uses are different
            if(!isLoopsEqual( DoomNew.weaponArray[i].getStates( ), DoomOld.weaponArray[i].getStates( ), DoomNew.stateArray, DoomOld.stateArray ) )
            {
                changedThings.push_back( DoomNew.weaponArray[i].getProperties().thingNumber );
            }
        }
    }

    //Sort and remove the non-unique elements
    std::sort( changedThings.begin(), changedThings.end() );
    changedThings.erase( std::unique( changedThings.begin(), changedThings.end() ), changedThings.end() );

    for( size_t i=0; i<changedThings.size(); i++ )
    {
        decorate::decorateActor( changedThings[i] , fileStream, DoomNew, DoomOld );
    }
}

//==========================================================================
//
//  decorateActor
//
//==========================================================================
void decorate::decorateActor( int thingN ,std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld )
{
    thing newThing = DoomNew.thingArray[thingN];
    thing oldThing = DoomOld.thingArray[thingN];

    std::string actorName = ZDOOMNAMES[thingN];
    uint32_t thingFlags = newThing.getFlags();

    //Start name and brackets
    fileStream << "Actor DH_" << actorName << " : " << actorName << " replaces " << actorName << " " << newThing.getProperties().ID << std::endl;
    fileStream << "{" << std::endl;

    //Consider the basic thing properties (health, etc.)
    //Note the i=1 is intentional (to skip ID)
    for( size_t i=1; i<=8; i++ )
    {
        if( newThing.getProperties(i) != oldThing.getProperties(i) )
        {
            fileStream << "\t" << ZDOOMTHINGPROPERTIES[i] << " " << newThing.getProperties(i) << std::endl;
        }
    }

    //Translation unit
    //This MUST be done; no base actor uses a translation (why would they?)
    int translationValue = -1;
    for( size_t i=0; i<ZDOOMTRANSLATION.size(); i++ )
    {
        if( thingFlags & ZDOOMTRANSLATION[i].flag )
        {
            translationValue += ZDOOMTRANSLATION[i].value;
        }
    }
    if (translationValue != -1)
    {
        fileStream << "\tTranslation " << translationValue << std::endl;
    }

    //Consider all the flags
    int flagChange;
    for( size_t i=0; i<ZDOOMFLAGS.size(); i++ )
    {
        flagChange = isBitChanged( newThing.getFlags(), oldThing.getFlags(), ZDOOMFLAGS[i].flag );
        if( flagChange == 1 )
        {
            fileStream << "\t" << ZDOOMFLAGS[i].added << std::endl;
        }
        else if( flagChange == 2 )
        {
            fileStream << "\t" << ZDOOMFLAGS[i].removed << std::endl;
        }
    }

    //Consider the thing sounds
    for( size_t i=0; i<=4; i++ )
    {
        if( newThing.getSounds(i) != oldThing.getSounds(i) )
        {
            fileStream << "\t" << ZDOOMTHINGSOUNDS[i] << " \"" << ZDOOMSOUNDNAMES[newThing.getSounds(i)] << "\"" << std::endl;
        }
    }

    //Consider Weapon stuff
    int weaponID = getWeaponID(thingN,DoomNew.weaponArray);
    if( weaponID != -1 )
    {
        weapon newWeapon = DoomNew.weaponArray[weaponID];
        weapon oldWeapon = DoomOld.weaponArray[weaponID];

        fileStream << "\tWeapon.SlotNumber "   << newWeapon.getProperties().weaponSlot     << std::endl;
        fileStream << "\tWeapon.SlotPriority " << newWeapon.getProperties().weaponPriority << std::endl;

        //If the ammo has changed
        if( newWeapon.getProperties().ammoType != oldWeapon.getProperties().ammoType )
        {
            fileStream << "\tWeapon.AmmoType \""   << ZDOOMAMMONAMES [newWeapon.getProperties().ammoType] << "\"" << std::endl;
            //Ammo became infinite
            if ( newWeapon.getProperties().ammoType == 4 )
                fileStream << "\t+WEAPON.AMMO_OPTIONAL" << std::endl;
            //Ammo was infinite
            else if ( oldWeapon.getProperties().ammoType == 4 )
                fileStream << "\t-WEAPON.AMMO_OPTIONAL" << std::endl;
        }
    }

    //Do the states
    decorate::decorateStates(thingN, fileStream, DoomNew, DoomOld);

    //Close brackets
    fileStream << "}" << std::endl << std::endl;
}
/*
void decorate::decorateStates( int thingN ,std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld )
{
    bool statesChanged=false;

    thing newThing = DoomNew.thingArray[thingN];
    thing oldThing = DoomOld.thingArray[thingN];
    int weaponID = getWeaponID(thingN,DoomNew.weaponArray);

    //Check if states have actually changed
    statesChanged |= !isLoopsEqual( newThing.getStates(), oldThing.getStates(), DoomNew.stateArray, DoomOld.stateArray );
    if( weaponID != -1 )
    {
        statesChanged |= !isLoopsEqual( DoomNew.weaponArray[weaponID].getStates(), DoomOld.weaponArray[weaponID].getStates(), DoomNew.stateArray, DoomOld.stateArray );
    }

    //If states have not changed, no need to do anything
    if(statesChanged)
    {
        std::vector<int> newStates
        {
            newThing.getStates().Spawn,
            newThing.getStates().Walk,
            newThing.getStates().Pain,
            newThing.getStates().Melee,
            newThing.getStates().Attack,
            newThing.getStates().Death,
            newThing.getStates().Explode,
            newThing.getStates().Raise,
        };

        std::vector<int> oldStates
        {
            oldThing.getStates().Spawn,
            oldThing.getStates().Walk,
            oldThing.getStates().Pain,
            oldThing.getStates().Melee,
            oldThing.getStates().Attack,
            oldThing.getStates().Death,
            oldThing.getStates().Explode,
            oldThing.getStates().Raise,
        };

        std::vector<int> specialStates = getSpecialStates(newStates,DoomNew.stateArray);
        //Start name and brackets
        fileStream << "\tStates" << std::endl;
        fileStream << "\t{"      << std::endl;

        for( size_t i=0; i<newStates.size(); i++)
        {
            //If the state loops differ, write that state
            if( stateLoop(newStates[i],DoomNew.stateArray) != stateLoop(oldStates[i],DoomOld.stateArray) )
            {
                std::vector<int> newStateLoops = stateLoop(newStates[i],DoomNew.stateArray);
                fileStream << "\t" << ZDOOMTHINGSTATES[i] << ":" << std::endl;

                //If current state is not a stop
                if( newStates[i] != 0 )
                {
                    for( j=0; j<newStateLoops.size(); j++ )
                    {
                        currentState = DoomNew.stateArray[newStateLoops[j]].get();
                        fileStream << "\t\t" << ZDOOMSPRITENAMES[currentState.Sprite] << " " << ZDOOMSPRITESUBNAMES[currentState.SpriteSub] << " " << currentState.Duration
                                   << (currentState.Lit?" Bright ":"");
                        if( !icompare(currentState.Action,"NULL") )
                        {
                            fileStream << "A_" << currentState.Action << std::endl;
                        }
                        if( currentState.NextState == 0 || isInSet(currentState.NextState,newStates) || isInSet(currentState.NextState,specialStates) )
                            break;
                    }
                }
                if( currentState.NextState == 0 )
                    fileStream << "stop" << std::endl;
                else if( currentState.NextState )

            }
        }
        //Close brackets
        fileStream << "\t}" << std::endl;
    }


}
*/
void decorate::decorateStates(int thingN, std::ostream &fileStream, base::baseArray DoomNew, base::baseArray DoomOld)
{
    thing::thingStates newStates = DoomNew.thingArray[thingN].getStates();
    thing::thingStates oldStates = DoomOld.thingArray[thingN].getStates();

    std::vector< std::vector<int> > newStateLoops =
    {
        stateLoop (newStates.Spawn,   DoomNew.stateArray),
        stateLoop (newStates.Walk,    DoomNew.stateArray),
        stateLoop (newStates.Pain,    DoomNew.stateArray),
        stateLoop (newStates.Melee,   DoomNew.stateArray),
        stateLoop (newStates.Attack,  DoomNew.stateArray),
        stateLoop (newStates.Death,   DoomNew.stateArray),
        stateLoop (newStates.Explode, DoomNew.stateArray),
        stateLoop (newStates.Raise,   DoomNew.stateArray),
    };

    std::vector< std::vector<int> > oldStateLoops =
    {
        stateLoop (oldStates.Spawn,   DoomOld.stateArray),
        stateLoop (oldStates.Walk,    DoomOld.stateArray),
        stateLoop (oldStates.Pain,    DoomOld.stateArray),
        stateLoop (oldStates.Melee,   DoomOld.stateArray),
        stateLoop (oldStates.Attack,  DoomOld.stateArray),
        stateLoop (oldStates.Death,   DoomOld.stateArray),
        stateLoop (oldStates.Explode, DoomOld.stateArray),
        stateLoop (oldStates.Raise,   DoomOld.stateArray),
    };

    std::vector<int> loopFrames
    {
        newStates.Spawn,
        newStates.Walk,
        newStates.Pain,
        newStates.Melee,
        newStates.Attack,
        newStates.Death,
        newStates.Explode,
        newStates.Raise,
    };

    //Add weapon stateloops
    int weaponID = getWeaponID(thingN,DoomNew.weaponArray);
    if( weaponID != -1 )
    {
        weapon::weaponStates newWeaponStates = DoomNew.weaponArray[weaponID].getStates();
        weapon::weaponStates oldWeaponStates = DoomOld.weaponArray[weaponID].getStates();

        std::vector< std::vector<int> > newWeaponStateLoops =
        {
            stateLoop (newWeaponStates.Lower,  DoomNew.stateArray),
            stateLoop (newWeaponStates.Raise,  DoomNew.stateArray),
            stateLoop (newWeaponStates.Bob,    DoomNew.stateArray),
            stateLoop (newWeaponStates.Fire,   DoomNew.stateArray),
            stateLoop (newWeaponStates.Flash,  DoomNew.stateArray),
        };

        std::vector< std::vector<int> > oldWeaponStateLoops =
        {
            stateLoop (oldWeaponStates.Lower,  DoomOld.stateArray),
            stateLoop (oldWeaponStates.Raise,  DoomOld.stateArray),
            stateLoop (oldWeaponStates.Bob,    DoomOld.stateArray),
            stateLoop (oldWeaponStates.Fire,   DoomOld.stateArray),
            stateLoop (oldWeaponStates.Flash,  DoomOld.stateArray),
        };

        std::vector<int> loopWeaponFrames
        {
            newWeaponStates.Lower,
            newWeaponStates.Raise,
            newWeaponStates.Bob,
            newWeaponStates.Fire,
            newWeaponStates.Flash,
        };

        //Add to original vectors
        newStateLoops.insert( newStateLoops.end(), newWeaponStateLoops.begin(), newWeaponStateLoops.end() );
        oldStateLoops.insert( oldStateLoops.end(), oldWeaponStateLoops.begin(), oldWeaponStateLoops.end() );
        loopFrames.insert   ( loopFrames.end(),    loopWeaponFrames.begin(),    loopWeaponFrames.end() );
    }

    std::vector<int> specialLoopFrames;
    for( size_t i=0; i<newStateLoops.size(); i++ )
    {
        //If the loop frame is not one of the main states
        int setLocation = isInSet( newStateLoops[i].back(), loopFrames );
        if( (setLocation == -1) && (newStateLoops[i].back() != 0) )
        {
            specialLoopFrames.push_back( newStateLoops[i].back() );
        }
    }
    //Sort and remove the non-unique elements
    std::sort( specialLoopFrames.begin(), specialLoopFrames.end() );
    specialLoopFrames.erase( std::unique( specialLoopFrames.begin(), specialLoopFrames.end() ), specialLoopFrames.end() );
    size_t i;
    size_t j;

    fileStream << "\tStates" << "\n";
    fileStream << "\t{" << "\n";
    for( i=0; i<newStateLoops.size(); i++)
    {
        //If particular state has changed
        if( !isLoopEqual(newStateLoops[i], oldStateLoops[i], DoomNew.stateArray, DoomOld.stateArray) )
        {
            fileStream << "\t" << ZDOOMTHINGSTATES[i] << ":" << "\n";

            size_t loopSize = newStateLoops[i].size()-1;
            for( j=0; j<loopSize; j++)
            {
                state::stateInfo stateValues = DoomNew.stateArray[ newStateLoops[i][j] ].get();
                if( isInSet( newStateLoops[i][j], specialLoopFrames ) != -1 )
                {
                    fileStream << "\t" << "State_" << newStateLoops[i][j] << ":" << "\n";
                }

                fileStream << "\t\t" << ZDOOMSPRITENAMES[stateValues.Sprite] << " " << ZDOOMSPRITESUBNAMES[stateValues.SpriteSub];
                //Next action is the same and this state is not a loop frame
                while(
                      isSameActions( DoomNew.stateArray[ newStateLoops[i][j] ] , DoomNew.stateArray[ newStateLoops[i][j+1] ]) &&
                      isInSet( newStateLoops[i][j+1], loopFrames ) == -1 &&
                      isInSet( newStateLoops[i][j+1], specialLoopFrames ) == -1
                      )
                {
                    int frameNumber = DoomNew.stateArray[ newStateLoops[i][j+1] ].get().SpriteSub;
                    fileStream << ZDOOMSPRITESUBNAMES[frameNumber];
                    j++;
                    if ( j > loopSize-1) break;
                }
                fileStream << " " << stateValues.Duration << (stateValues.Lit?" Bright ":" ");
                if( !icompare(stateValues.Action,"NULL") )
                {
                    fileStream << "A_" << stateValues.Action << "\n";
                }
                else
                {
                    fileStream  << "\n";
                }
            }

            int standardState = isInSet( newStateLoops[i][j], loopFrames );
            int specialState = isInSet( newStateLoops[i][j], specialLoopFrames );
            if ( newStateLoops[i][j] == 0 )
            {
                fileStream << "\t\t" << "stop" << "\n";
            }
            else if ( standardState != -1 )
            {
                fileStream << "\t\t" << "goto " << ZDOOMTHINGSTATES[standardState] << "\n";
            }
            else if ( specialState != -1 )
            {
                fileStream << "\t\t" << "goto " << "State_" << newStateLoops[i][j] << "\n";
            }
        }
    }
    fileStream << "\t}" << "\n";
}
