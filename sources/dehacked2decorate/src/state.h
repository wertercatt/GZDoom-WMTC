#ifndef STATE_H
#define STATE_H

#include <string>
/*
 * This file defines the State class
 *
 * This class contains the various properties that make a state
 * i.e. if Whacked is opened and and a state is viewed, the properties
 * are the information shown
 */

class state
{
    public:
        //This struct contains the 8 things that define a State in DEHACKED
        //The definitions below show what their DECORATE Equivelents are
        struct stateInfo
        {
            int Sprite;             //TROO
            int SpriteSub;          //A
            bool Lit;               //Bright
            int NextState;          //(the next line)
            int Duration;           //10
            std::string Action;     //A_Fall
            int Param1;             //Function Parameter; depends on Action
            int Param2;             //Function Parameter; depends on Action
        };

    private:
        stateInfo Info;
    public:
        /*  CONSTRUCTORS */
        //Basic constructor for the state class
        state(int spr, int sub, bool lit, int nstate, int dur, std::string act="NULL", int p1=0, int p2=0);

        /*	ACCESSORS	*/
        // Returns the stateInfo
        stateInfo get() const;

        /*  MUTATORS    */
        void setSprite(int spr);
        void setSpriteSub(int sub); //Also modifies Lit state accordingly
        void setLit(bool lit);
		void setNextState(int nstate);
		void setDuration(int dur);
		void setAction(std::string act);
		void setParam1(int p1);
		void setParam2(int p2);
		void setParams(int p1, int p2);

        /*  OPERATORS  */
		bool operator== (const state& s2) const;
		bool operator!= (const state& s2) const;

        /*  METHODS  */
		void print(std::ostream &stream=std::cout);
};
#endif //STATE_H
