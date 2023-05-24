#ifndef THING_H
#define THING_H
#include <cstdint>
#include <iostream>
/*
 * This file defines the Thing class
 *
 * This class contains the various properties that make a thing
 * i.e. if Whacked is opened and and a thing is viewed, the properties
 * are the information shown
 * It will be split into 4 described below
 */

class thing
{
    public:
    //This contains the 9 basic properties of a Thing
	struct thingProperties
	{
		int ID;
		int Health;
		int Speed;
		int Radius;
		int Height;
		int Damage;
		int ReactionTime;
		int PainChance;
		int Mass;
	};
    //This contains the 8 basic states of a Thing
    //Note: does not include weapon states (these have their own class)
    //      or the Archvile's 'Heal' state
	struct thingStates
	{
		int Spawn;
		int Walk;  //See in DECORATE
		int Pain;
		int Melee;
		int Attack; //Missile in DECORATE
		int Death;
		int Explode; //XDeath in DECORATE
		int Raise;
	};
    //This contains the 5 basic sound types of a Thing
	struct thingSounds
	{
		int Alert;  //SeeSound
		int Attack; //AttackSound
		int Pain;   //PainSound
		int Death;  //DeathSound
		int Active; //ActiveSound
	};

    private:
		thingProperties tProperties;
		thingStates tStates;
		thingSounds tSounds;
		uint32_t tFlags; //This is the 32 bits that define the DEHACKED Flags

    public:
        /*  CONSTRUCTORS */
		thing(int prop[9], int states[8], int sounds[5], uint32_t flags);

		/*  ACCESSORS   */
		//The accessors with ints will allow you to extract
		//the i-th element of that particular struct
		//This is useful when iterating
		thingProperties getProperties() const;
		int getProperties(int i) const;

		thingStates getStates() const;
		int getStates(int i) const;

		thingSounds getSounds() const;
		int getSounds(int i) const;

		uint32_t getFlags() const;

		/*  MUTATORS    */
        //The first 3 mutators will allow you to set
		//the i-th element of that particular struct
		//This is useful when iterating
        void setProperties  (int v, int i);
		void setStates      (int v, int i);
		void setSounds      (int v, int i);

		//Basic Mutators
		void setID(int a);
        void setHealth(int a);
		void setSpeed(int a);
		void setRadius(int a);
		void setHeight(int a);
		void setDamage(int a);
		void setReactionTime(int a);
		void setPainChance(int a);
		void setMass(int a);

        void setSpawnState(int a);
		void setWalkState(int a);
		void setPainState(int a);
		void setMeleeState(int a);
		void setAttackState(int a);
		void setDeathState(int a);
		void setExplodeState(int a);
		void setRaiseState(int a);

        void setAlertSound(int a);
		void setAttackSound(int a);
		void setPainSound(int a);
		void setDeathSound(int a);
		void setActiveSound(int a);

		void setFlags(uint32_t a);


        /*  OPERATORS  */
		bool operator== (const thing& t2) const;
		bool operator!= (const thing& t2) const;

		/*  METHODS  */
		void print(std::ostream &stream=std::cout);
};



#endif //THING_H
