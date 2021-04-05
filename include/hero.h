#ifndef HERO_H
#define HERO_H

#include "entity.h"
#include "projectile.h"

class Hero: public Entity
{
private:
    int aiID;
    int type;
    int party;
    int range;
    int defence;
    int rateOfAttack;       //TODO change to 'delayBetweenAttacks'
    int rateOfSpecialAttack;
    time_t timeAttacked;
    time_t timeSpecialAttacked;
    bool specialAttacked;
    int specialAttackDuration;

public:

    int getAiID() { return aiID; }
    void setAiID(int newID) { aiID = newID; }
    int getType() { return this->type; }
    void setType(int newType) { this->type = newType; }
    int getParty() { return this->party; }
    void setParty(int newParty) { party = newParty; }
    int getRange() { return range; }
    void setRange(int newRange) { range = newRange; }
    int getDefence() { return defence; }
    void setDefence(int newDefence) { range = newDefence; }
    int getRateOfAttack() { return rateOfAttack; }
    void setRateOfAttack(int newRateOfAttack) { rateOfAttack = newRateOfAttack; }
    int getRateOfSpecialAttack() { return rateOfSpecialAttack; }
    void setRateOfSpecialAttack(int newRateOfSpecialAttack) { rateOfSpecialAttack = newRateOfSpecialAttack; }
    time_t getTimeAttacked() { return timeAttacked; }
    void setTimeAttacked(time_t newTimeAttacked) { timeAttacked = newTimeAttacked; }
    time_t getTimeSpecialAttacked() { return timeSpecialAttacked; }
    void setTimeSpecialAttacked(time_t newTimeSpecialAttacked) { timeSpecialAttacked = newTimeSpecialAttacked; }
    bool getSpecialAttacked() { return specialAttacked; }
    bool setSpecialAttacked(bool newSpecialAttacked) { specialAttacked = newSpecialAttacked; }
    int getSpecialAttackDuration() { return specialAttackDuration; }
    void setSpecialAttackDuration(int newSpecialAttackDuration) { specialAttackDuration = newSpecialAttackDuration; }

    virtual bool update() = 0;
    virtual void attack(Hero* target, std::vector<Projectile*> *projectiles) = 0;
    virtual void specialAttack(Hero* target) = 0;
    virtual Hero* copy() = 0;

    void moveToTarget() { setDestination(getTarget()->getSprite()->getPosition()); }
    Hero* nearestAlly(std::vector<Hero*> *heroes);
    Hero* nearestEnemy(std::vector<Hero*> *heroes);
    Hero* allyWithLowestHP(std::vector<Hero*> *heroes);
    Hero* enemyWithLowestHP(std::vector<Hero*> *heroes);
    bool allyInRange(std::vector<Hero*> *heroes);
    bool enemyInRange(std::vector<Hero*> *heroes);

    Hero(std::string pathToSprite, sf::Vector2f pos, int party);
    Hero(std::string pathToSprite, sf::Vector2f pos, int party, int AiID);
    ~Hero() {};
};

#endif