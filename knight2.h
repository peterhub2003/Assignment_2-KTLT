#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class Events;

enum ItemType {Anti = 0, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV, Nor};
class BaseItem {
protected:
    ItemType type;
public:
    //~BaseItem();
    ItemType getItemType() const;
    virtual string getName() const = 0;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};  


class Antidote: public BaseItem{
public:
    Antidote(){this->type = ItemType::Anti;}
    bool canUse(BaseKnight* k);
    void use(BaseKnight* k);
    string getName() const {return "Antidote";}
};
class PhoenixDownI: public BaseItem{
public:
    PhoenixDownI(){this->type = ItemType::PhoenixI;}
    bool canUse(BaseKnight* k);
    void use(BaseKnight* k);
    string getName() const {return "PhoenixI";}
};
class PhoenixDownII: public BaseItem{
public:
    PhoenixDownII(){this->type = ItemType::PhoenixII;}
    bool canUse(BaseKnight* k);
    void use(BaseKnight* k);
    string getName() const {return "PhoenixII";}
};
class PhoenixDownIII: public BaseItem{
public:
    PhoenixDownIII(){this->type = ItemType::PhoenixIII;}
    bool canUse(BaseKnight* k);
    void use(BaseKnight* k);
    string getName() const {return "PhoenixIII";}
};
class PhoenixDownIV:public BaseItem{
public:
    PhoenixDownIV(){this->type = ItemType::PhoenixIV;}
    bool canUse(BaseKnight* k);
    void use(BaseKnight* k);
    string getName() const {return "PhoenixIV";}
};

    
class BaseBag {
protected:
    class Node{
    public:
        BaseItem* item;
        Node* next;

        Node(BaseItem* _item, Node* _next = nullptr){
            this->item = _item;
            this->next = _next;
        }
        ~Node(){
            delete item;
            next = nullptr;
        }
    };

    Node* head;
    int max_capacity; //If max_capacity = -1 that mean unlimited
    int size;

public:     

    BaseBag();
    ~BaseBag();
    //BaseBag(BaseKnight* knight, int a, int b); //a is phoenix and b is antitode
    static BaseBag* create(BaseKnight* k, int a, int b);
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual BaseItem* retriveAndGet(BaseKnight* k);
    virtual string toString() const;

    BaseItem* getFollowKnight(BaseKnight* k);
    int getMaxCapacity() const{return this->max_capacity;}
    void drop(int n);
    void del_items(int n); //Delete n items from head 
    //bool useItem(BaseKnight* k);

};  

class DragonBag: public BaseBag{
public:
    DragonBag();
    bool insertFirst(BaseItem* item);
};

class LanceBag: public BaseBag{
public:
    LanceBag();
};

class NormalBag: public BaseBag{
public:
    NormalBag();
};

class PaladinBag: public BaseBag{
public:
    PaladinBag();
    bool insertFirst(BaseItem* item);
};

/*===========================CLASS OPPONENT========================================*/
class BaseOpponent{
protected:
    int levelO;
public:
    //virtual void cal_levelO(const int& i, const int& event_id);
    static BaseOpponent* create(int i, int event_id);
    virtual bool fight(BaseKnight* k) = 0;
    void printOpponent(int event_id) const;
};

class MadBear: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    MadBear();
    bool fight(BaseKnight* k);

};

class Bandit: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Bandit();
    bool fight(BaseKnight* k);
};

class LordLupin: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    LordLupin();
    bool fight(BaseKnight* k);
};

class Elf: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Elf();
    bool fight(BaseKnight* k);
};

class Troll: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Troll();
    bool fight(BaseKnight* k);

};

class Tornbery: public BaseOpponent{
public:
    Tornbery(){;}
    bool fight(BaseKnight* k);
};

class QueenOfCards: public BaseOpponent{
public:
    QueenOfCards(){;}
    bool fight(BaseKnight* k);
};

class NinaDeRings: public BaseOpponent{
public:
    NinaDeRings(){;}
    bool fight(BaseKnight* k);
};


class DurianGarden: public BaseOpponent{
public:
    DurianGarden(){;}
    bool fight(BaseKnight* k);
};

class OmegaWeapon: public BaseOpponent{
public:
    OmegaWeapon(){;}
    bool fight(BaseKnight* k);
};

class Hades: public BaseOpponent{
public:
    Hades(){;}
    bool fight(BaseKnight* k);
};



/* ================================================================================*/
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;
    bool isPoisonous;
    float knightBaseDamage;

public:
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    float getBaseDamage() const{ return this->knightBaseDamage;}
    bool knightFight(BaseOpponent* opponent);
    bool revival();

    bool addItemIntoBag(BaseItem* item);
    bool useItem(BaseKnight* k);
    void dropItem(const int& n);
    
    int getLevel() const;
    void setLevel(int _level);

    KnightType getType() const;
    pair<int, int> getPhoeAndAnti() const;
    
    bool isPoison() const; 
    void setAttrPoison(bool b);

    pair<int, int> getHPAndMHP() const;
    void setHP(int _HP);

    int getGil() const;
    void setGil(int gil);
};

class PaladinKnight: public BaseKnight{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class LancelotKnight: public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class DragonKnight: public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class NormalKnight: public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};


/*==============================================================================*/

class Events {
    int n;
    int* eve;

public:
    Events ( const string & file_events );
    ~Events();
    int count() const;
    int getEvent(int i) const;

    //Using debug
    void printEvents() const;
};  

/*================================================================================================*/
enum treasures { PALADINSHIELD = 0, LANCELOTSPEAR, GUINEVEREHAIR };
class ArmyKnights {
    
    BaseKnight** ar_knight;
    bool isTake[3];
    bool ExcaliburSword;
    bool hasFightOmega, hasFightHades;
    int NumberOfKnights;

public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();

    bool fight(BaseOpponent * opponent);
    bool lastFight();
    bool adventure (Events * events);
    
    int count() const;
    BaseKnight * lastKnight() const;

    void update_gil();
    void updateItem(BaseItem* item);

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasAll() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    //Using debug
    void printArmy() const;
    void printOppo(Events* events) const;
};




class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();

    void print() const;
};

#endif // __KNIGHT2_H__


