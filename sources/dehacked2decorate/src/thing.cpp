#include "thing.h"
#include <cstdint>
#include <iostream>
#include <bitset>

//==========================================================================
//
//  CONSTRUCTORS
//
//==========================================================================
thing::thing(int prop[9], int states[8], int sounds[5], uint32_t flags)
{
	tProperties.ID			 = prop[0];
	tProperties.Health		 = prop[1];
	tProperties.Speed		 = prop[2];
	tProperties.Radius		 = prop[3];
	tProperties.Height		 = prop[4];
	tProperties.Damage		 = prop[5];
	tProperties.ReactionTime = prop[6];
	tProperties.PainChance	 = prop[7];
	tProperties.Mass		 = prop[8];

	tStates.Spawn 	= states[0];
	tStates.Walk 	= states[1];
	tStates.Pain 	= states[2];
	tStates.Melee 	= states[3];
	tStates.Attack	= states[4];
	tStates.Death 	= states[5];
	tStates.Explode = states[6];
	tStates.Raise 	= states[7];

	tSounds.Alert 	= sounds[0];
	tSounds.Attack 	= sounds[1];
	tSounds.Pain 	= sounds[2];
	tSounds.Death 	= sounds[3];
	tSounds.Active 	= sounds[4];

	tFlags = flags;
};

//==========================================================================
//
//  ACCESSORS
//
//==========================================================================

//Access all properties
thing::thingProperties thing::getProperties() const
{
    return tProperties;
}
//Access particular property
int thing::getProperties(int i) const
{
    switch(i)
    {
        case 0: return tProperties.ID;
        case 1: return tProperties.Health;
        case 2: return tProperties.Speed;
        case 3: return tProperties.Radius;
        case 4: return tProperties.Height;
        case 5: return tProperties.Damage;
        case 6: return tProperties.ReactionTime;
        case 7: return tProperties.PainChance;
        case 8: return tProperties.Mass;
        default:
            std::cerr  << "Error in thing::getProperties(int i): attempted to access beyond elements of thingProperties" << std::endl;
            return EXIT_FAILURE;
    }
}

//Access all states
thing::thingStates thing::getStates() const
{
    return tStates;
}
//Access particular state
int thing::getStates(int i) const
{
    switch(i)
    {
        case 0: return tStates.Spawn;
        case 1: return tStates.Walk;
        case 2: return tStates.Pain;
        case 3: return tStates.Melee;
        case 4: return tStates.Attack;
        case 5: return tStates.Death;
        case 6: return tStates.Explode;
        case 7: return tStates.Raise;
        default:
            std::cerr  << "Error in thing::getStates(int i): attempted to access beyond elements of thingStates" << std::endl;
            return EXIT_FAILURE;
    }
}

//Access all sounds
thing::thingSounds thing::getSounds() const
{
    return tSounds;
}
//Access particular sound
int thing::getSounds(int i) const
{
    switch(i)
    {
        case 0: return tSounds.Alert;
        case 1: return tSounds.Attack;
        case 2: return tSounds.Pain;
        case 3: return tSounds.Death;
        case 4: return tSounds.Active;
        default:
            std::cerr  << "Error in thing::getSounds(int i): attempted to access beyond elements of thingSounds" << std::endl;
            return EXIT_FAILURE;
    }
}

//Access the flag bits
uint32_t thing::getFlags() const
{
    return tFlags;
}

//==========================================================================
//
//  MUTATORS
//
//==========================================================================
void thing::setProperties  (int v, int i)
{
    switch(i)
    {
        case 0: tProperties.ID              = v;
        case 1: tProperties.Health          = v;
        case 2: tProperties.Speed           = v;
        case 3: tProperties.Radius          = v;
        case 4: tProperties.Height          = v;
        case 5: tProperties.Damage          = v;
        case 6: tProperties.ReactionTime    = v;
        case 7: tProperties.PainChance      = v;
        case 8: tProperties.Mass            = v;
        default:
            std::cerr  << "Error in thing::setProperties(int v, int i): attempted to access beyond elements of thingProperties" << std::endl;
    }
}

void thing::setStates      (int v, int i)
{
    switch(i)
    {
        case 0: tStates.Spawn   = v;
        case 1: tStates.Walk    = v;
        case 2: tStates.Pain    = v;
        case 3: tStates.Melee   = v;
        case 4: tStates.Attack  = v;
        case 5: tStates.Death   = v;
        case 6: tStates.Explode = v;
        case 7: tStates.Raise   = v;
        default:
            std::cerr  << "Error in thing::setStates(int v, int i): attempted to access beyond elements of thingStates" << std::endl;
    }
}

void thing::setSounds      (int v, int i)
{
    switch(i)
    {
        case 0: tSounds.Alert   = v;
        case 1: tSounds.Attack  = v;
        case 2: tSounds.Pain    = v;
        case 3: tSounds.Death   = v;
        case 4: tSounds.Active  = v;
        default:
            std::cerr  << "Error in thing::setSounds(int v, int i): attempted to access beyond elements of thingSounds" << std::endl;
    }
}

//Basic Mutators
void thing::setID(int a)               {tProperties.ID=a;};
void thing::setHealth(int a)           {tProperties.Health=a;};
void thing::setSpeed(int a)            {tProperties.Speed=a;};
void thing::setRadius(int a)           {tProperties.Radius=a;};
void thing::setHeight(int a)           {tProperties.Height=a;};
void thing::setDamage(int a)           {tProperties.Damage=a;};
void thing::setReactionTime(int a)     {tProperties.ReactionTime=a;};
void thing::setPainChance(int a)       {tProperties.PainChance=a;};
void thing::setMass(int a)             {tProperties.Mass=a;};

void thing::setSpawnState(int a)       {tStates.Spawn=a;};
void thing::setWalkState(int a)        {tStates.Walk =a;};
void thing::setPainState(int a)        {tStates.Pain=a;};
void thing::setMeleeState(int a)       {tStates.Melee=a;};
void thing::setAttackState(int a)      {tStates.Attack=a;};
void thing::setDeathState(int a)       {tStates.Death=a;};
void thing::setExplodeState(int a)     {tStates.Explode=a;};
void thing::setRaiseState(int a)       {tStates.Raise=a;};

void thing::setAlertSound(int a)       {tSounds.Alert=a;};
void thing::setAttackSound(int a)      {tSounds.Attack=a;};
void thing::setPainSound(int a)        {tSounds.Pain=a;};
void thing::setDeathSound(int a)       {tSounds.Death=a;};
void thing::setActiveSound(int a)      {tSounds.Active=a;};

void thing::setFlags(uint32_t a)       {tFlags=a;};
//==========================================================================
//
//  OPERATORS
//
//==========================================================================

bool thing::operator== (const thing& t2) const
{
    bool returnValue = 1;

		returnValue &= this->tProperties.ID             == t2.tProperties.ID;
		returnValue &= this->tProperties.Health         == t2.tProperties.Health;
		returnValue &= this->tProperties.Speed          == t2.tProperties.Speed;
		returnValue &= this->tProperties.Radius         == t2.tProperties.Radius;
		returnValue &= this->tProperties.Height         == t2.tProperties.Height;
		returnValue &= this->tProperties.Damage         == t2.tProperties.Damage;
		returnValue &= this->tProperties.ReactionTime   == t2.tProperties.ReactionTime;
		returnValue &= this->tProperties.PainChance     == t2.tProperties.PainChance;
		returnValue &= this->tProperties.Mass           == t2.tProperties.Mass;

        returnValue &= this->tStates.Spawn              == t2.tStates.Spawn;
		returnValue &= this->tStates.Walk               == t2.tStates.Walk;
		returnValue &= this->tStates.Pain               == t2.tStates.Pain;
		returnValue &= this->tStates.Melee              == t2.tStates.Melee;
		returnValue &= this->tStates.Attack             == t2.tStates.Attack;
		returnValue &= this->tStates.Death              == t2.tStates.Death;
		returnValue &= this->tStates.Explode            == t2.tStates.Explode;
		returnValue &= this->tStates.Raise              == t2.tStates.Raise;

        returnValue &= this->tSounds.Alert              == t2.tSounds.Alert;
		returnValue &= this->tSounds.Attack             == t2.tSounds.Attack;
		returnValue &= this->tSounds.Pain               == t2.tSounds.Pain;
		returnValue &= this->tSounds.Death              == t2.tSounds.Death;
		returnValue &= this->tSounds.Active             == t2.tSounds.Active;

		returnValue &= this->tFlags                     == t2.tFlags;

    return returnValue;
};

bool thing::operator!= (const thing& t2) const
{
    return !( (*this) == t2 );
};

//==========================================================================
//
//  METHODS
//
//==========================================================================
void thing::print(std::ostream &stream)
{
	stream <<

	"ID:\t\t" 			<<  tProperties.ID << "\n"
	"Health:\t\t" 		<<  tProperties.Health << "\n"
	"Speed:\t\t" 		<<  tProperties.Speed << "\n"
	"Radius:\t\t" 		<<  tProperties.Radius << "\n"
	"Height:\t\t"	 	<<  tProperties.Height << "\n"
	"Damage:\t\t" 		<<  tProperties.Damage << "\n"
	"ReactionTime:\t" <<  tProperties.ReactionTime << "\n"
	"PainChance:\t"	<<  tProperties.PainChance << "\n"
	"Mass:\t\t" 		<<  tProperties.Mass << "\n"
	<< "\n"

	"Spawn:\t\t" 	<<  tStates.Spawn << "\n"
	"Walk:\t\t" 	<<  tStates.Walk << "\n"
	"Pain:\t\t" 	<<  tStates.Pain << "\n"
	"Melee:\t\t" 	<<  tStates.Melee << "\n"
	"Attack:\t\t"	<<  tStates.Attack << "\n"
	"Death:\t\t" 	<<  tStates.Death << "\n"
	"Explode:\t" 	<<  tStates.Explode << "\n"
	"Raise:\t\t"	<<  tStates.Raise << "\n"
	<< "\n"

	"Alert:\t\t"	<< tSounds.Alert << "\n"
	"Attack:\t\t"	<< tSounds.Attack << "\n"
	"Pain:\t\t"		<< tSounds.Pain << "\n"
	"Death:\t\t"	<< tSounds.Death << "\n"
	"Active:\t\t"	<< tSounds.Active << "\n"
	<< "\n"

	"Flags:\t\t0x"	<< std::bitset<32>(tFlags) << "\n";
};
