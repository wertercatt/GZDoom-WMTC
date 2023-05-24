#include "weapon.h"
#include <iostream>

//==========================================================================
//
//  CONSTRUCTORS
//
//==========================================================================
weapon::weapon(int prop[4], int states[5])
{
    wProperties.thingNumber     = prop[0];
    wProperties.ammoType        = prop[1];
    wProperties.weaponSlot      = prop[2];
    wProperties.weaponPriority  = prop[3];

    wStates.Lower   = states[0];
    wStates.Raise   = states[1];
    wStates.Bob     = states[2];
    wStates.Fire    = states[3];
    wStates.Flash   = states[4];
}

//==========================================================================
//
//  ACCESSORS
//
//==========================================================================
//Access all properties
weapon::weaponProperties weapon::getProperties() const
{
    return wProperties;
}
//Access particular property
int weapon::getProperties(int i) const
{
    switch(i)
    {
        case 0: return wProperties.thingNumber;
        case 1: return wProperties.ammoType;
        case 2: return wProperties.weaponSlot;
        case 3: return wProperties.weaponPriority;
        default:
            std::cerr  << "Error in weapon::getProperties(int i): attempted to access beyond elements of weaponProperties" << std::endl;
            return EXIT_FAILURE;
    }
}

//Access all states
weapon::weaponStates weapon::getStates() const
{
    return wStates;
}
//Access particular state
int weapon::getStates(int i) const
{
    switch(i)
    {
        case 0: return wStates.Lower;
        case 1: return wStates.Raise;
        case 2: return wStates.Bob;
        case 3: return wStates.Fire;
        case 4: return wStates.Flash;
        default:
            std::cerr  << "Error in weapon::getStates(int i): attempted to access beyond elements of weaponStates" << std::endl;
            return EXIT_FAILURE;
    }
}

//==========================================================================
//
//  MUTATORS
//
//==========================================================================
void weapon::setProperties(int v, int i)
{
    switch(i)
    {
        case 0: wProperties.thingNumber     = v;
        case 1: wProperties.ammoType        = v;
        case 2: wProperties.weaponSlot      = v;
        case 3: wProperties.weaponPriority  = v;
        default:
            std::cerr  << "Error in weapon::setProperties(int i): attempted to access beyond elements of weaponProperties" << std::endl;
    }
}

void weapon::setStates(int v, int i)
{
    switch(i)
    {
        case 0: wStates.Lower   = v;
        case 1: wStates.Raise   = v;
        case 2: wStates.Bob     = v;
        case 3: wStates.Fire    = v;
        case 4: wStates.Flash   = v;
        default:
            std::cerr  << "Error in weapon::setStates(int i): attempted to access beyond elements of weaponStates" << std::endl;
    }
}

//Basic Mutators
void weapon::setLower(int a)    {wStates.Lower=a;};
void weapon::setRaise(int a)    {wStates.Raise=a;};
void weapon::setBob(int a)      {wStates.Bob=a;};
void weapon::setFire(int a)     {wStates.Fire=a;};
void weapon::setFlash(int a)    {wStates.Flash=a;};
void weapon::setAmmoType(int a) {wProperties.ammoType=a;};

//==========================================================================
//
//  OPERATORS
//
//==========================================================================

bool weapon::operator== (const weapon& w2) const
{
    bool returnValue = 1;

		returnValue &= this->wProperties.thingNumber        == w2.wProperties.thingNumber;
		returnValue &= this->wProperties.ammoType           == w2.wProperties.ammoType;
		returnValue &= this->wProperties.weaponSlot         == w2.wProperties.weaponSlot;
		returnValue &= this->wProperties.weaponPriority     == w2.wProperties.weaponPriority;

        returnValue &= this->wStates.Lower                  == w2.wStates.Lower;
		returnValue &= this->wStates.Raise                  == w2.wStates.Raise;
		returnValue &= this->wStates.Bob                    == w2.wStates.Bob;
		returnValue &= this->wStates.Fire                   == w2.wStates.Fire;
		returnValue &= this->wStates.Flash                  == w2.wStates.Flash;

    return returnValue;
};

bool weapon::operator!= (const weapon& w2) const
{
    return !( (*this) == w2 );
}

//==========================================================================
//
//  METHODS
//
//==========================================================================
void weapon::print(std::ostream &stream)
{
		stream <<
		"Lower:\t\t" << wStates.Lower << "\n"
		"Raise:\t\t" << wStates.Raise << "\n"
		"Bob:\t\t"   << wStates.Bob   << "\n"
		"Fire:\t\t"  << wStates.Fire  << "\n"
		"Flash:\t\t" << wStates.Flash << "\n"
		"Ammo Type:\t"  << wProperties.ammoType << "\n"
		;
};
