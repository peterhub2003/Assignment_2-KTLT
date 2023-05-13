#include "knight2.h"

/* * ***************************************************************************** * */
/* * ****************************UTILITY FUNCTIONS******************************** * */
/* * ***************************************************************************** * */

bool isPrime(const int& n){ 
    if(n <= 1) return false;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) return false;
    return true;
}

bool isPytago(int n){
    short int a = n%10;
    short int b = (n/10)%10;
    short int c = ((n/10)/10)%10;

    if(a*b*c == 0) return false;
    if(a*a + b*b == c*c || c*c + b*b == a*a || a*a + c*c == b*b) 
        return true;

    return false;   
}

int Max(const int a, const int b){
    return (a > b) ? a : b;
}

int Min(const int a, const int b){ 
    return (a < b) ? a : b;
}

string strip(string s){
    string res = s;
    while(res.length() > 0 && res.front() == ' ') res.erase(0, 1);
    while(res.length() > 0 && res.back() == ' ') res.pop_back();
    
    return res;
}

/* * ***************************************************************************** * */
/* * ****************************END UTILITY FUNCTIONS**************************** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * **************IMPLEMENT CLASS BASEITEM AND INHERITED OF BASEITEM************* * */
/* * ***************************************************************************** * */

ItemType BaseItem::getItemType() const{
    return this->type;
}

bool Antidote::canUse(BaseKnight * k){
    return k->isPoison();
}

void Antidote::use(BaseKnight * k){
    k->setAttrPoison(false);
    return;
}

//Phoenix I: Set HP = MaxHP
bool PhoenixDownI::canUse(BaseKnight * k){
    return k->getHPAndMHP().first <= 0;
}

void PhoenixDownI::use(BaseKnight * k){
    k->setHP(k->getHPAndMHP().second);
    return;
}

//Phoenix II: Set HP = MaxHP
bool PhoenixDownII::canUse(BaseKnight * k){
    return k->getHPAndMHP().first < (k->getHPAndMHP().second/4);
}

void PhoenixDownII::use(BaseKnight * k){
    k->setHP(k->getHPAndMHP().second);
    return;
}

//Phoenix III: 
bool PhoenixDownIII::canUse(BaseKnight * k){
    return k->getHPAndMHP().first < (k->getHPAndMHP().second/3);
}

void PhoenixDownIII::use(BaseKnight * k){
    if(k->getHPAndMHP().first <= 0) k->setHP(k->getHPAndMHP().second/3);
    else k->setHP(k->getHPAndMHP().second/4 + k->getHPAndMHP().first);
    return;
}

//Phoenix IV
bool PhoenixDownIV::canUse(BaseKnight * k){
    return k->getHPAndMHP().first < (k->getHPAndMHP().second/2);
}

void PhoenixDownIV::use(BaseKnight * k){
    if(k->getHPAndMHP().first <= 0) k->setHP(k->getHPAndMHP().second/2);
    else k->setHP(k->getHPAndMHP().second/5 + k->getHPAndMHP().first);
    return;   
}

/* * ***************************************************************************** * */
/* * ************ END IMPLEMENTATION BASEITEM AND INHERITED BASEITEM************** * */
/* * ***************************************************************************** * */



/* * ***************************************************************************** * */
/* * ***********************BEGIN IMPLEMENTATION OF CLASS BASEBAG***************** * */
/* * ***************************************************************************** * */
BaseBag::BaseBag(){
    this->size = 0;
    this->head = nullptr;
}

BaseBag::~BaseBag(){
    while(head){
        Node* next_head = head->next;
        head->next = nullptr;
        delete head;
        head = next_head;
    }
    this->size = 0; 
}

BaseBag* BaseBag::create(BaseKnight* k, int a, int b){
    BaseBag* bag = nullptr;
    if(k->getType() == KnightType::PALADIN){
        bag = new PaladinBag();
    }
    else if(k->getType() == KnightType::LANCELOT){
        bag = new LanceBag();
    }
    else if(k->getType() == KnightType::DRAGON){
        bag = new DragonBag();
    }
    else{
        bag = new NormalBag();       
    } 

    int du_a = 0, du_b = 0;
    bool success;
    BaseItem* item = nullptr;
    for(int i = 1; i <= a; ++i){
        item = new PhoenixDownI();
        success = bag->insertFirst(item);
        if(!success){
            du_a = a - i + 1;
            break;
        }
    }

    if(du_a > 0 || k->getType() == KnightType::DRAGON) du_b = b;
    else{
        for(int i = 1; i <= b; ++i){
            item = new Antidote();
            success = bag->insertFirst(item);
            if(!success){
                du_b = b - i + 1;
                break;
            }
        }
    }

    return bag;

}

BaseItem* BaseBag::getFollowType(ItemType itemType){
    Node* prev = nullptr;
    Node* curr = head;

    while(curr){
        if(curr->item->getItemType() == itemType){
            BaseItem* temp = this->head->item;
            int temp_id = this->head->id;
            this->head->item = curr->item;
            this->head->id = curr->id;
            curr->item = temp;
            curr->id = temp_id;

            return this->head->item;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    return nullptr;

}

BaseItem* BaseBag::getFollowKnight(BaseKnight* k){
    Node* prev = nullptr;
    Node* curr = head;

    while(curr){
        if(curr->item->canUse(k)){
            BaseItem* temp = this->head->item;
            int temp_id = this->head->id;
            this->head->item = curr->item;
            this->head->id = curr->id;
            curr->item = temp;
            curr->id = temp_id;

            return this->head->item;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    return nullptr;   
}

BaseItem* BaseBag::retriveAndGet(BaseKnight* k){
    if(this->size == 0) return nullptr;
    BaseItem* item = nullptr;
    if(k->isPoison()){
        item = this->getFollowType(ItemType::Anti);
    }
    else{
        item = this->getFollowKnight(k);
    }

    return item;
}

string BaseBag::toString() const{

    string res = "";
    res += "Bag[count=" + to_string(this->size) + ';';
    if(this->size == 0) return res + ']';

    Node* curr = this->head;
    for(int i = 1; i <= this->size - 1; ++i){
        res += curr->item->getName() + ',';
        curr = curr->next;
    }

    res += curr->item->getName() + ']';
    return res;
}


bool BaseBag::insertFirst(BaseItem* item){
    if(this->size == this->max_capacity) return false;
    Node* new_head = new Node(this->size + 1, item, this->head);
    this->head = new_head;

    ++this->size;
    return true;
}

//Delete n items from head
void BaseBag::del_items(int n){
    if(this->size <= 0) return;
    while(n > 0 && this->size > 0){
        Node* curr = this->head->next;
        this->head->next = nullptr;
        delete this->head;

        this->head = curr;
        --n; --this->size;       
    }

    return;
}

void BaseBag::drop(int n = 3){
    if(this->size < 3){
        this->del_items(this->size);
        this->head = nullptr;
        return;       
    }
    else {
        int count = 0;
        Node* prev = nullptr;
        Node* curr = this->head;
        while(count < 3 && curr){
            if(curr->id <= this->size && curr->id >= this->size - 2){
                if(prev == nullptr){

                }
                else{
                    
                }
                ++count;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }

        this->size -= 3;
    }
    
    return;
}



/* * ***************************************************************************** * */
/* * ***********************END IMPLEMENTATION OF CLASS BASEBAG******************* * */
/* * ***************************************************************************** * */


DragonBag::DragonBag(){
    this->max_capacity = 14;
}
bool DragonBag::insertFirst(BaseItem* item){
    if(this->size == this->max_capacity) return false;
    if(item->getItemType() == ItemType::Anti) return false;

    Node* new_head = new Node(this->size + 1, item, this->head);
    this->head = new_head;
    ++this->size;
    return true;  
}

LanceBag::LanceBag(){
    this->max_capacity = 16;
}
NormalBag::NormalBag(){
    this->max_capacity = 19;
}

PaladinBag::PaladinBag(){
    this->max_capacity = -1;
}
bool PaladinBag::insertFirst(BaseItem* item){
    Node* new_head = new Node(this->size + 1, item, this->head);
    this->head = new_head;
    ++this->size;
    return true;    
}


/* * ***************************************************************************** * */
/* * ***********************BEGIN IMPLEMENTATION OF CLASS BASEKNIGHT************** * */
/* * ***************************************************************************** * */

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        // + ",max_capacity:" + to_string(this->bag->getMaxCapacity());
        + "]";
    return s;
}
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->isPoisonous = false;
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight* k = nullptr;
    if(maxhp == 888){
        k = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if(isPrime(maxhp)){
        k = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if(maxhp >= 100 && isPytago(maxhp)){
        k = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);        
    }
    else{
        k = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    return k;
}

bool BaseKnight::knightFight(BaseOpponent* opponent){
    bool res = opponent->fight(this);
    if(!res){
        if(this->hp <= 0){
            this->revival();
        }
        else if(this->isPoison()){
            bool use = this->useItem(this);
            if(!use){
                this->dropItem(3);
                this->setHP(this->getHPAndMHP().first - 10);
                this->setAttrPoison(false);  

                if(this->hp <= 0) this->revival();             
            }
        }
        else {
            this->useItem(this);
        }
        
    }
    else{ this->useItem(this);}
    return res;
}

KnightType BaseKnight::getType() const{
    return this->knightType;
}

pair<int, int> BaseKnight::getPhoeAndAnti() const{
    return {this->phoenixdownI, this->antidote};
}

bool BaseKnight::isPoison() const{
    return this->isPoisonous;
}
void BaseKnight::setAttrPoison(bool b){
    this->isPoisonous = b;
}

pair<int, int> BaseKnight::getHPAndMHP() const{
    return {this->hp, this->maxhp};
}
void BaseKnight::setHP(int _HP){
    if(_HP < 0) this->hp = 0; 
    else if(_HP > this->maxhp) {this->hp = this->maxhp;}
    else this->hp = _HP;
}

int BaseKnight::getGil() const {return this->gil;}
void BaseKnight::setGil(int _gil) {this->gil = _gil;}

int BaseKnight::getLevel() const {return this->level;}
void BaseKnight::setLevel(int _level) {
    if(_level <= 10)
        this->level = _level;
    else this->level = 10;
}

bool BaseKnight::revival(){
    bool res = this->useItem(this);
    if(!res){
        if(this->getGil() >= 100){
            this->setGil(this->getGil() - 100);
            this->setHP(this->getHPAndMHP().second / 2);
            return true;
        }
        else return false;
    }
    else return true;
}

bool BaseKnight::addItemIntoBag(BaseItem* item){
    bool res = this->bag->insertFirst(item);
    return res;
}

bool BaseKnight::useItem(BaseKnight * k){
    BaseItem* item = this->bag->retriveAndGet(k);
    if(item == nullptr) return false;
    else{
        if(item->getItemType() == ItemType::Anti) this->antidote -= 1;
        if(item->getItemType() == ItemType::PhoenixI) this->phoenixdownI -= 1;
        item->use(this);
        this->bag->del_items(1);
        return true;
    }
}

void BaseKnight::dropItem(const int& n){
    this->bag->drop(n);
    return;
}

/* * ***************************************************************************** * */
/* * *************************END IMPLEMENTATION OF CLASS BASEKNIGHT************** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * ****************BEGIN IMPLEMENTATION INHERITED OF CLASS BASEKNIGHT*********** * */
/* * ***************************************************************************** * */

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::PALADIN;
    this->bag = BaseBag::create(this, phoenixdownI, antidote);
    this->knightBaseDamage = 0.06;
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::LANCELOT;
    this->bag = BaseBag::create(this, phoenixdownI, antidote);
    this->knightBaseDamage = 0.05;
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::DRAGON;
    this->bag = BaseBag::create(this, phoenixdownI, antidote);
    this->knightBaseDamage = 0.075;
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){ 
    this->knightType = KnightType::NORMAL;
    this->bag = BaseBag::create(this, phoenixdownI, antidote);

}

/* * ***************************************************************************** * */
/* * ******************END IMPLEMENTATION INHERITED OF CLASS BASEKNIGHT*********** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * ***********************BEGIN IMPLEMENTATION OF CLASS BASEOPPONENT************ * */
/* * ***************************************************************************** * */

BaseOpponent* BaseOpponent::create(int i, int event_id){
    BaseOpponent* opponent = nullptr;
    if(event_id == 1){
        opponent = new MadBear();
    }
    else if(event_id == 2){
        opponent = new Bandit();
    }
    else if(event_id == 3){
        opponent = new LordLupin();
    }
    else if(event_id == 4){
        opponent = new Elf();   
    }
    else if(event_id == 5){
        opponent = new Troll();
    }
    else if(event_id == 6){
        opponent = new Tornbery();
    }
    else if(event_id == 7){
        opponent = new QueenOfCards();
    }
    else if(event_id == 8){
        opponent = new NinaDeRings();
    }
    else if(event_id == 9){
        opponent = new DurianGarden();
    }
    else if(event_id == 10){
        opponent = new OmegaWeapon();
    }
    else {opponent = new Hades();}

    opponent->levelO = (i + event_id) % 10 + 1;
    return opponent;
}

/* * ***************************************************************************** * */
/* * **********************END IMPLEMENTATION OF CLASS OPPONENT******************* * */
/* * ***************************************************************************** * */



/* * ***************************************************************************** * */
/* * *******************BEGIN IMPLEMENTATION INHERITED OF CLASS OPPONENT********** * */
/* * ***************************************************************************** * */

MadBear::MadBear(){baseDamage = 10; gil = 100;}
Bandit::Bandit(){baseDamage = 15; gil = 150;}
LordLupin::LordLupin(){baseDamage = 45; gil = 450;}
Elf::Elf(){baseDamage = 75; gil = 750;}
Troll::Troll(){baseDamage = 95; gil = 800;}

bool MadBear::fight(BaseKnight* k){
    if(k->getType() == KnightType::LANCELOT || k->getType() == KnightType::PALADIN){
        k->setGil(k->getGil() + this->gil);
        return true;
    }

    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    else{
        int new_hp = k->getHPAndMHP().first - this->baseDamage*(this->levelO - level_knight);
        k->setHP(new_hp);
        return false;
    }
}
bool Bandit::fight(BaseKnight* k){
    if(k->getType() == KnightType::LANCELOT ||k->getType() == KnightType::PALADIN){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    else{
        int new_hp = k->getHPAndMHP().first - this->baseDamage*(this->levelO - level_knight);
        k->setHP(new_hp);
        return false;
    }
}
bool LordLupin::fight(BaseKnight* k){
    if(k->getType() == KnightType::LANCELOT || k->getType() == KnightType::PALADIN){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    else{
        int new_hp = k->getHPAndMHP().first - this->baseDamage*(this->levelO - level_knight);
        k->setHP(new_hp);
        return false;
    }
}
bool Elf::fight(BaseKnight* k){
    if(k->getType() == KnightType::LANCELOT ||k->getType() == KnightType::PALADIN){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    else{
        int new_hp = k->getHPAndMHP().first - this->baseDamage*(this->levelO - level_knight);
        k->setHP(new_hp);
        return false;
    }
}
bool Troll::fight(BaseKnight* k){
    if(k->getType() == KnightType::LANCELOT ||k->getType() == KnightType::PALADIN){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() + this->gil);
        return true;
    }
    else{
        int new_hp = k->getHPAndMHP().first - this->baseDamage*(this->levelO - level_knight);
        k->setHP(new_hp);
        return false;
    }
}
bool Tornbery::fight(BaseKnight* k){
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setLevel(k->getLevel() + 1);
        return true;
    }    
    else{
        if(k->getType() == KnightType::DRAGON) return true;
        k->setAttrPoison(true);
        return false;
    }
}

bool QueenOfCards::fight(BaseKnight* k){
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() * 2);
        return true;
    }
    else{
        if(k->getType() != KnightType::PALADIN)
            k->setGil(k->getGil() / 2);
        return false;
    }

}

bool NinaDeRings::fight(BaseKnight* k){
    if(k->getGil() >= 50 || k->getType() == KnightType::PALADIN){
        if(k->getHPAndMHP().first < k->getHPAndMHP().second / 3)
        {
            if(k->getType() != KnightType::PALADIN)
                k->setGil(k->getGil() - 50);
            k->setHP(k->getHPAndMHP().first + k->getHPAndMHP().second / 5);
        }
    }
    return true;
}
    
bool DurianGarden::fight(BaseKnight* k){
    k->setHP(k->getHPAndMHP().second);
    return true;
}

bool OmegaWeapon::fight(BaseKnight* k){
    if(k->getType() == KnightType::DRAGON || (k->getLevel() == 10 && k->getHPAndMHP().first ==k->getHPAndMHP().second))
    {
        k->setLevel(10);
        k->setGil(999);
        return true;
    }
    else{
        k->setHP(0);
        return false;  
    }
}   

bool Hades::fight(BaseKnight* k){
    if(k->getLevel() == 10 || (k->getType() == KnightType::PALADIN && k->getLevel() >= 8))
        return true;
    else{
        k->setHP(0);
        return false;
    }
}


/* * ***************************************************************************** * */
/* * *********************END IMPLEMENTATION INHERITED OF CLASS OPPONENT********** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * ****************BEGIN IMPLEMENTATION CLASS ARMYKNGIHTS*********************** * */
/* * ***************************************************************************** * */

ArmyKnights::ArmyKnights(const string& file_armyknights){
    for(int i = 0; i < 3; this->isTake[i]=false, ++i);
    this->ExcaliburSword = false;
    this->hasFightHades = false;
    this->hasFightOmega = false;
    
    ifstream ifs;
    ifs.open(file_armyknights);

    if(ifs.is_open()){
        string line; getline(ifs, line);
        line = strip(line);
        this->NumberOfKnights = stoi(line);
        this->ar_knight = new BaseKnight*[this->NumberOfKnights];

        int _id = 1, _maxhp, _level, _gil, _antidote, _phoenixdownI;
        while(getline(ifs, line)){
            stringstream ss(line);
            ss >> _maxhp >> _level >> _phoenixdownI >> _gil >> _antidote;
            this->ar_knight[_id - 1] = BaseKnight::create(_id, _maxhp, _level, _gil, _antidote, _phoenixdownI);
            ++_id;
        }

        ifs.close();
    }
}

ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < this->NumberOfKnights; ++i){
        delete this->ar_knight[i];
    }
    delete[] this->ar_knight;
}

bool ArmyKnights::fight(BaseOpponent * opponent){
   
    if(this->NumberOfKnights <= 0) return false;
    BaseKnight* k = this->lastKnight();
    bool result = k->knightFight(opponent);
    if(result){
        this->update_gil();
        return true;
    }
    else{
        if(k->getHPAndMHP().first <= 0){
            delete k;
            this->NumberOfKnights -= 1;
        }
        return false;
    }

}

void ArmyKnights::sort_knights(int idx_begin, int idx_end){
    for(int i = idx_begin; i < idx_end; ++i){
        this->ar_knight[i] = this->ar_knight[i + 1];
    }

    return;
}

bool ArmyKnights::lastFight(){
    if(this->hasExcaliburSword()){
        return true;
    }
    else{
        if(this->hasAll()){
            int Ulti_HP = 5000;
            int idx = this->NumberOfKnights - 1;
            while(Ulti_HP > 0 && idx >= 0){
                BaseKnight* k = this->ar_knight[idx];
                if(k->getType() !=  KnightType::NORMAL){
                    this->sort_knights(idx, this->NumberOfKnights - 1);
                    this->ar_knight[this->NumberOfKnights - 1] = k;

                    int damage = (int)(k->getHPAndMHP().first * k->getLevel() * k->getBaseDamage());
                    Ulti_HP -= damage;
                    if(Ulti_HP <= 0) return true;
                    else{
                        delete k;
                        this->NumberOfKnights -= 1;
                    }
                }
                --idx;
            }

            if(Ulti_HP <= 0  && this->NumberOfKnights > 0){
                return true;
            }

            if(Ulti_HP > 0) {
                for(int i = 0; i <this->NumberOfKnights; i++){
                    delete this->ar_knight[i];
                }
                this->NumberOfKnights = 0;
                return false;
            }
        }
        else {
            for(int i = 0; i <this->NumberOfKnights; i++){
                delete this->ar_knight[i];
            }
            this->NumberOfKnights = 0;
            return false;           
        }

    }

    return false;
}

bool ArmyKnights::adventure(Events* events){
    if(this->NumberOfKnights == 0) return false;

    int n = events->count();
    for(int i = 0; i < n; ++i){
        int event_id = events->getEvent(i);
        if(112 <= event_id && event_id <= 114){
            BaseItem* item = nullptr;
            if(event_id == 112) item = new PhoenixDownII();
            else if(event_id == 113) item = new PhoenixDownIII();
            else item = new PhoenixDownIV();

            this->updateItem(item);
        }
        else if(event_id >= 95 && event_id <= 97){
            if(!this->isTake[event_id%95])
                this->isTake[event_id%95] = true;
        }
        else if(event_id == 98){
            if(!this->hasExcaliburSword() && this->hasAll()) 
                this->ExcaliburSword = true;
        }
        else if(event_id == 99){
            bool res = this->lastFight();
            this->printInfo();
            return res;
        }
        else{
            if(event_id == 10 && this->hasFightOmega) {
                this->printInfo();
                continue;
            }
            if(event_id == 11 && this->hasFightHades) {
                this->printInfo();
                continue;
            }

            BaseOpponent* opponent = BaseOpponent::create(i, event_id);
            bool w = this->fight(opponent);
            if(!w){ 
                if(this->NumberOfKnights <= 0) {
                    this->printInfo();
                    delete opponent;
                    return false;
                }
            }
            else{
                if(event_id == 10 || event_id == 11){
                    if(event_id == 10) {this->hasFightOmega = true;}
                    else{
                        this->hasFightHades = true;
                        if(!this->hasPaladinShield())
                            this->isTake[treasures::PALADINSHIELD] = true;
                    }
                }

            }
            delete opponent;
        }

        this->printInfo();
    }

    return true;
}

void ArmyKnights::update_gil(){
    if(this->NumberOfKnights <= 0) return;

    int residual_gil = Max(this->ar_knight[this->NumberOfKnights - 1]->getGil() - 999, 0);
    if(residual_gil > 0){
        this->ar_knight[this->NumberOfKnights -1]->setGil(999);
    }

    int idx = this->NumberOfKnights - 2;
    while(residual_gil > 0 && idx >=0){
        BaseKnight* k = this->ar_knight[idx];
        if(k->getGil() < 999){
            int g = 999 - k->getGil();
            if(residual_gil <= g){
                k->setGil(residual_gil + k->getGil());
                residual_gil = 0;
            }
            else{
                k->setGil(999);
                residual_gil -= g;
            }
        } 
        --idx; 
    }

    return;
}

void ArmyKnights::updateItem(BaseItem* item){
    if(this->NumberOfKnights <= 0) return;

    int idx = this->NumberOfKnights - 1;
    while(idx >= 0){
        bool success = this->ar_knight[idx]->addItemIntoBag(item);
        if(success) return;
        --idx;
    }

    return;
}

int ArmyKnights::count() const{
    return this->NumberOfKnights;
}

BaseKnight* ArmyKnights::lastKnight() const{
    if(this->count() <= 0) return nullptr;
    return this->ar_knight[this->count() - 1];
}

bool ArmyKnights::hasPaladinShield() const{
    return this->isTake[treasures::PALADINSHIELD];
}
bool ArmyKnights::hasLancelotSpear() const{
    return this->isTake[treasures::LANCELOTSPEAR];
}
bool ArmyKnights::hasGuinevereHair() const{
    return this->isTake[treasures::GUINEVEREHAIR];
}
bool ArmyKnights::hasExcaliburSword() const{
    return this->ExcaliburSword;
}
bool ArmyKnights::hasAll() const{
    return this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair();
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * ***************************************************************************** * */
/* * *******************END IMPLEMENTATION CLASS ARMYKNIGHTS********************** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * *******************BEGIN IMPLEMENTATION CLASS EVENTS************************* * */
/* * ***************************************************************************** * */

Events::Events(const string& file_events){

    ifstream ifs;
    ifs.open(file_events);

    if(ifs.is_open()){
        string s; getline(ifs, s);
        s = strip(s);
        this->n = stoi(s);
        this->eve = new int[this->n];

        getline(ifs, s);
        s = strip(s);
        stringstream ss(s);
        for(int i = 0; i < n; ++i){
            string inp; ss >> inp;
            this->eve[i] = stoi(inp);
        }

        ifs.close();
    }
}

Events::~Events(){
    if(this->eve)
        delete[] this->eve; 
}

int Events::count() const {return this->n;}

int Events::getEvent(int i) const {
    if(i < this->n && i >= 0) return this->eve[i];
    else return -1;
}


/* * ***************************************************************************** * */
/* * *******************END IMPLEMENTATION CLASS EVENTS*************************** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * *******************BEGIN IMPLEMENTATION CLASS KNIGHTADVENTURE**************** * */
/* * ***************************************************************************** * */

KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure() {
    delete this->armyKnights;
    delete this->events;
}

void KnightAdventure::loadArmyKnights(const string& s){
    armyKnights = new ArmyKnights(s);
}

void KnightAdventure::loadEvents(const string& s){
    events = new Events(s);
}

void KnightAdventure::run(){
    bool w = this->armyKnights->adventure(this->events);
    armyKnights->printResult(w);

    return;
}

/* * ***************************************************************************** * */
/* * *********************END IMPLEMENTATION CLASS KNIGHTADVENTURE**************** * */
/* * ***************************************************************************** * */


/* * ***************************************************************************** * */
/* * *************************************DEBUG*********************************** * */
/* * ***************************************************************************** * */

void BaseOpponent::printOpponent(int event_id) const{
    string Type[11] = {"MadBear", "Bandit", "LordLupin", "Elf", "Troll", "Tornbery", 
                      "QueenOfCards","NinaDeRings", "DurianGarden", "OmegaWeapon", "Hades"};
    string res = "";
    res += "[Name: " + Type[event_id - 1]
        +  ", Level: " + to_string(this->levelO)
        +  ']'; 
    cout << res << endl;
}

void ArmyKnights::printOppo(Events* events) const{
    for(int i = 0; i < events->count(); ++i){
        if(events->getEvent(i) <= 11 && events->getEvent(i) >= 1)
        {
            BaseOpponent* o = BaseOpponent::create(i, events->getEvent(i));
            o->printOpponent(events->getEvent(i));
            delete o;
        }
    }
    return;
}

void ArmyKnights::printArmy() const{
    cout << "The number of Knights:   " << this->NumberOfKnights << endl;
    for(int i = 0; i < this->NumberOfKnights ;++i){
        string s = this->ar_knight[i]->toString();
        cout << s << endl;
    }
    return;
}
void Events::printEvents() const {
    cout << "The number of Events:   " << this->n << endl;
    cout << '[';
    for(int i = 0; i < this->n - 1; ++i){
        cout << this->eve[i] << " ==> "; 
    }

    cout << this->eve[this->n - 1] << ']' << endl;
    return;
}

void KnightAdventure::print() const{
    this->events->printEvents();
    this->armyKnights->printArmy();
    this->armyKnights->printOppo(this->events);
    return;  
}