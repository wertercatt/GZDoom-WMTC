#include <string>
#include <iostream>
#include "state.h"

const int LITFLAG = 32768;
//==========================================================================
//
//  CONSTRUCTORS
//
//==========================================================================
state::state(int spr, int sub, bool lit, int nstate, int dur, std::string act, int p1, int p2)
{
	Info.Sprite     = spr;
	Info.SpriteSub  = sub;
	Info.Lit        = lit;
	Info.NextState  = nstate;
	Info.Duration   = dur;
	Info.Action     = act;
	Info.Param1     = p1;
	Info.Param2     = p2;
};

//==========================================================================
//
//  ACCESSORS
//
//==========================================================================

//Returns the stateInfo of the class
state::stateInfo state::get() const
{
    return Info;
}

//==========================================================================
//
//  MUTATORS
//
//==========================================================================
void state::setSprite(int spr)
{
	Info.Sprite=spr;
}
void state::setLit(bool lit)
{
	Info.Lit = lit;
}
void state::setSpriteSub(int sub)
{
	Info.SpriteSub = sub%LITFLAG;
	if (sub<LITFLAG)
    {
        setLit(false);
    }
    else
    {
        setLit(true);
    };
}
void state::setNextState(int nstate)
{
	Info.NextState = nstate;
}
void state::setDuration(int dur)
{
	Info.Duration = dur;
}
void state::setAction(std::string act)
{
	Info.Action = act;
}
void state::setParam1(int p1)
{
	Info.Param1 = p1;
}
void state::setParam2(int p2)
{
	Info.Param2 = p2;
}
void state::setParams(int p1, int p2)
{
	Info.Param1 = p1;
	Info.Param2 = p2;
}

//==========================================================================
//
//  OPERATORS
//
//==========================================================================
bool state::operator== (const state& s2) const
{
    bool returnValue = 1;

        returnValue &= this->Info.Sprite     == s2.Info.Sprite;
		returnValue &= this->Info.SpriteSub  == s2.Info.SpriteSub;
		returnValue &= this->Info.Lit        == s2.Info.Lit;
		returnValue &= this->Info.NextState  == s2.Info.NextState;
		returnValue &= this->Info.Duration   == s2.Info.Duration;
		returnValue &= this->Info.Action     == s2.Info.Action;
		returnValue &= this->Info.Param1     == s2.Info.Param1;
		returnValue &= this->Info.Param2     == s2.Info.Param2;

    return returnValue;
}

bool state::operator!= (const state& s2) const
{
    return !( (*this) == s2 );
}

//==========================================================================
//
//  METHODS
//
//==========================================================================
void state::print(std::ostream &stream)
{
		stream <<
		"Sprite:\t\t" << Info.Sprite << "," << Info.SpriteSub << "\n"
		"Lit:\t\t" << (Info.Lit ? "X" : "") << "\n"
		"Next:\t\t" << Info.NextState << "\n"
		"Duration:\t" << Info.Duration << "\n"
		"Action:\t\t" << Info.Action << "\n"
		;
};
