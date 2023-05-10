#include "knight2.h"

//===============================Utility Functions==========================================
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
//==========================================================================================
/* * *  Implement class inherited from BaseItem   * * */
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

/* * *                               END implement                     * * */
/* * ***************************************************************************** * */
/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag(BaseKnight* k, int a, int b){
    BaseItem* PhoeI = nullptr; BaseItem* Anti = nullptr;
    if(a > 0) PhoeI = new PhoenixDownI();
    if(b > 0) Anti = new Antidote();


    // for(int i = 0; i < a; ++i){
        
    // }
}

BaseItem* BaseBag::get(ItemType itemType){
    if(this->ar_items[itemType] == 0) return nullptr;
    Node* curr = this->head;
    Node* prev_curr = nullptr;

    while(curr->item->getItemType() != itemType){
        prev_curr = curr;
        curr = curr->next;
    }

    if(prev_curr != nullptr){
        Node* temp = this->head;
        prev_curr -> next = temp;
        temp->next = curr->next;
        curr->next = nullptr;

        // this->head = 
    }
    else{
        this->head = this->head->next;
        curr->next = nullptr;
    }

    this->ar_items[itemType] -= 1;
    return curr->item;

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

bool BaseBag::useItem(BaseKnight* k){
    Node* curr = this->head;
   // while(curr != nullptr &&)
    

    return true;
}

bool BaseBag::insertFirst(BaseItem* item){
    if(this->size == this->max_capacity) return false;
    Node* new_head = new Node(item, this->head);
    this->head = new_head;

    ++this->size;
    return true;
}

void BaseBag::del_items(int n){
    if(this->size == 0) return;
    while(n > 0 && this->size > 0){
        Node* curr = this->head->next;
        this->head->next = nullptr;

        delete this->head->item;
        delete this->head;
        this->head = curr;
        --n; --this->size;       
    }

    return;
}

void BaseBag::drop(int n = 3){
    if(this->size < 3){
        this->del_items(this->size);
        return;       
    }
    this->del_items(n);
    return;
}



/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
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
        // + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
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
            bool isRevi = this->revival();
            return isRevi;
        }
        else{
            this->useItem(this);
            return true;
        }
    }

    this->useItem(this);
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
    if(_HP > this->maxhp) {this->hp = this->maxhp;}
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
    return true;
}

bool BaseKnight::addItemIntoBag(BaseItem* item){
    return true;
}

void BaseKnight::useItem(BaseKnight * k){
    return;
}

void BaseKnight::dropItem(const int& n){
    this->bag->drop(n);
    return;
}
/* * * END implementation of class BaseKnight * * */
/*=======================================================*/
/* * *BEGIN IMPLEMENT INHERITED CLASS FROM CLASS BASEKINGHT * * */

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::PALADIN;
    this->bag = new BaseBag(this, antidote, phoenixdownI);
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::LANCELOT;
    this->bag = new BaseBag(this, antidote, phoenixdownI);
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){
    this->knightType = KnightType::DRAGON;
    this->bag = new BaseBag(this, antidote, phoenixdownI);
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil, antidote,  phoenixdownI){ 
    this->knightType = KnightType::NORMAL;
    this->bag = new BaseBag(this, antidote, phoenixdownI);

}

/* * *END IMPLEMENT INHERITED CLASS FROM CLASS BASEKINGHT * * */
/*==================================================================================*/
/* * *BEGIN IMPLEMENT OPPONENT CLASS * * */
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
        if(k->getPhoeAndAnti().second > 0){
            k->useItem(k);
        }
        else{
            k->dropItem(3);
            k->setHP(k->getHPAndMHP().first - 10);
        }
    }
    return true;
}

bool QueenOfCards::fight(BaseKnight* k){
    int level_knight = k->getLevel();
    if(level_knight >= this->levelO){
        k->setGil(k->getGil() * 2);
    }
    else{
        if(k->getType() != KnightType::PALADIN)
            k->setGil(k->getGil() / 2);
    }
    return true;
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

/* * * BEGIN implementation of class ArmyKnights * * */

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

        int _id = 0, _maxhp, _level, _gil, _antidote, _phoenixdownI;
        while(getline(ifs, line)){
            stringstream ss(line);
            ss >> _maxhp >> _level >> _phoenixdownI >> _gil >> _antidote;
            this->ar_knight[_id] = BaseKnight::create(_id, _maxhp, _level, _gil, _antidote, _phoenixdownI);
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
   
    while(true){

        if(this->NumberOfKnights <= 0) return false;
        BaseKnight* k = this->lastKnight();
        bool result = k->knightFight(opponent);
        if(result){
            this->update_gil();
            return true;
        }
        else{
            delete k;
            this->NumberOfKnights -= 1;
        }
    }

    return true;
}

bool ArmyKnights::lastFight(){
    if(this->hasExcaliburSword()){
        return true;
    }
    else{
        if(this->hasAll()){
            int Ulti_HP = 5000;
            while(Ulti_HP > 0 && this->NumberOfKnights > 0){

            }

            if(Ulti_HP <= 0  && this->NumberOfKnights > 0){
                return true;
            }
            else{

            }
        }
        else{

            return false;
        }
    }

    return true;
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
            if(res) this->printInfo();
            return res;
        }
        else{
            if(event_id == 10 && this->hasFightOmega) continue;
            if(event_id == 11 && this->hasFightHades) continue;

            BaseOpponent* opponent = BaseOpponent::create(i, event_id);
            bool w = this->fight(opponent);
            if(!w){ return false;}
            else{
                if(event_id == 10 || event_id == 11){
                    if(event_id == 10) {this->hasFightOmega = true;}
                    else{
                        this->hasFightHades = true;
                        if(!this->hasPaladinShield())
                            this->isTake[treasures::PALADINSHIELD] = true;
                    }
                }
                else{

                }
            }
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

/* * * END implementation of class ArmyKnights * * */
/**************************************************************/

/* * *BEGIN IMPLEMENTATION OF CLASS EVENTS * * */

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


/* * *END IMPLEMENTATION OF CLASS EVENTS * * */
/**************************************************************/


/* * * BEGIN implementation of class KnightAdventure * * */
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
/* * * END implementation of class KnightAdventure * * */

/*==================================================================*/
/*=======================DEBUG======================================*/
void ArmyKnights::printOppo(Events* events) const{
    for(int i = 0; i < events->count(); ++i){
        if(events->getEvent(i) <= 11 && events->getEvent(i) >= 1)
        {
            BaseOpponent* o = BaseOpponent::create(i, events->getEvent(i));
            o->printOpponent();
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