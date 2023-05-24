#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
/*
 * This file defines the Weapon class
 *
 * This class contains the various properties that define a weapon
 * i.e. if Whacked is opened and and a weapon is viewed, the properties
 * are the information shown
 * This information is in addition to their properties as things, so
 * parsing should be done after generic thing parsing
 */

class weapon
{
    public:
    //This defines the non-state properties of a weapon
    struct weaponProperties
    {
        int thingNumber;
        int ammoType;
        //These two matter for DECORATE, but cannot be changed
        //in DEHACKED
        int weaponSlot;
        int weaponPriority;
    };

    //This struct contains the 5 main states that define a weapon
    //This is in addition to the thing states of a weapon
    struct weaponStates
    {
        int Lower;  //Deselect
        int Raise;  //Select
        int Bob;    //Ready
        int Fire;   //Fire
        int Flash;  //Flash
    };

    private:
        weaponProperties wProperties;
        weaponStates wStates;

    public:
    /*  CONSTRUCTORS    */
    weapon(int prop[4], int states[5]);

    /*  ACCESSORS   */
    //The accessors with ints will allow you to extract
    //the i-th element of that particular struct
    //This is useful when iterating
    weaponProperties getProperties() const;
    int getProperties(int i) const;

    weaponStates getStates() const;
    int getStates(int i) const;

    /*  MUTATORS    */
    //The first 2 mutators will allow you to set
    //the i-th element of that particular struct
    //This is useful when iterating
    void setProperties  (int v, int i);
    void setStates      (int v, int i);

    void setLower       (int i);
    void setRaise       (int i);
    void setBob         (int i);
    void setFire        (int i);
    void setFlash       (int i);
    void setAmmoType    (int i);

    /*  OPERATORS   */
    bool operator== (const weapon& w2) const;
    bool operator!= (const weapon& w2) const;

    /*  METHODS */
    void print(std::ostream &stream=std::cout);
};

#endif //WEAPON_H
