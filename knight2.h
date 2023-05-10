#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class Events;

enum ItemType {Anti = 0, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV};
class BaseItem {
protected:
    ItemType type;
public:
    // ~BaseItem();
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
private:
    class Node{
    public:
        BaseItem* item;
        Node* next;

        Node(BaseItem* _item, Node* _next = nullptr){
            this->item = _item;
            this->next = _next;
        }
    };

    Node* head;
    short int ar_items[5];
    int max_capacity;
    int size;

public:     

    ~BaseBag();
    BaseBag(BaseKnight* knight, int a, int b); //a is phoenix and b is antitode
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    void drop(int n);
    void del_items(int n); //Delete n items from head 
    bool useItem(BaseKnight* k);

};  

class DragonBag: public BaseBag{
public:
    bool insertFirst(BaseItem* item);
};

class LanceBag: public BaseBag{

};

class NormalBag: public BaseBag{

};

class PaladinBag: public BaseBag{
public:
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
    virtual void printOpponent() const = 0;
};

class MadBear: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    MadBear();
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "MadBear" << endl;
        cout << "Level        :  " << this->levelO << endl;
        cout << "BaseDamage   :  " << this->baseDamage << endl;
        cout << "Gil          :  " << this->gil << endl;
    }
};

class Bandit: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Bandit();
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "Bandit" << endl;
        cout << "Level        :  " << this->levelO << endl;
        cout << "BaseDamage   :  " << this->baseDamage << endl;
        cout << "Gil          :  " << this->gil << endl;
    }
};

class LordLupin: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    LordLupin();
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "LordLupin" << endl;
        cout << "Level        :  " << this->levelO << endl;
        cout << "BaseDamage   :  " << this->baseDamage << endl;
        cout << "Gil          :  " << this->gil << endl;
    }
};

class Elf: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Elf();
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "Elf" << endl;
        cout << "Level        :  " << this->levelO << endl;
        cout << "BaseDamage   :  " << this->baseDamage << endl;
        cout << "Gil          :  " << this->gil << endl;
    }
};

class Troll: public BaseOpponent{
private:
    int baseDamage;
    int gil;
public:
    Troll();
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "Troll" << endl;
        cout << "Level        :  " << this->levelO << endl;
        cout << "BaseDamage   :  " << this->baseDamage << endl;
        cout << "Gil          :  " << this->gil << endl;
    }
};

class Tornbery: public BaseOpponent{
public:
    Tornbery(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "Tornbery" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
};

class QueenOfCards: public BaseOpponent{
public:
    QueenOfCards(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "QueenOfCards" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
};

class NinaDeRings: public BaseOpponent{
public:
    NinaDeRings(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "NinaDeRings" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
};


class DurianGarden: public BaseOpponent{
public:
    DurianGarden(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "DurianGarden" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
};

class OmegaWeapon: public BaseOpponent{
public:
    OmegaWeapon(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "OmegaWeapon" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
};

class Hades: public BaseOpponent{
public:
    Hades(){;}
    bool fight(BaseKnight* k);
    void printOpponent() const{
        cout << "Opponent Name:  " << "Hades" << endl;
        cout << "Level        :  " << this->levelO << endl;
    }
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

public:
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    bool knightFight(BaseOpponent* opponent);
    bool revival();

    bool addItemIntoBag(BaseItem* item);
    void useItem(BaseKnight* k);
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
    float knightBaseDamage = 0.06;
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class LancelotKnight: public BaseKnight{
    float knightBaseDamage = 0.05;
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class DragonKnight: public BaseKnight{
    float knightBaseDamage = 0.075;
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


