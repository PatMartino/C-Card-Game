// Yıldırım Kaan Çuhadar, Berke Şiranur, Tolga Üredi
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include<time.h>
#include <chrono>
class card;
class creature;
class enchantment;
class landCard;
class effect;
class player {
protected:
    std::string name;
    int hitPoint;
    int blackMana;
    int whiteMana;
    int redMana;
    int greenMana;
    int blueMana;
    std::vector<std::shared_ptr<card>> Hand;
    std::vector<std::shared_ptr<card>> Library;
    std::vector<std::shared_ptr<card>> InPlay;
    std::vector<std::shared_ptr<card>> Graveyard;
    std::vector<std::shared_ptr<card>>::iterator ptr;


public:


    friend class creature;

    friend class enchantment;

    friend class card;

    friend class landCard;

    friend class sorcery;

    friend class effect;

    player() : hitPoint(0) {}

    player(std::string n, int hP, int bM, int wM, int rM, int gM, int blueM) : name(n), hitPoint(hP), blackMana(bM),
                                                                               whiteMana(wM), redMana(rM),
                                                                               greenMana(gM), blueMana(blueM) {}

    player(const player &a) {
        name = a.name;
        hitPoint = a.hitPoint;
        blackMana = a.blackMana;
        whiteMana = a.whiteMana;
        redMana = a.redMana;
        greenMana = a.greenMana;
        blueMana = a.blueMana;
        Hand = a.Hand;
        Library = a.Library;
        Graveyard = a.Graveyard;
        InPlay = a.InPlay;
    }

    void printInfo() {
        std::cout << "Hp: " << hitPoint << std::endl;
        std::cout << "Black Mana: " << blackMana << std::endl;
        std::cout << "white Mana: " << whiteMana << std::endl;
        std::cout << "red Mana: " << redMana << std::endl;
        std::cout << "green Mana: " << greenMana << std::endl;
        std::cout << "blue Mana: " << blueMana << std::endl;
    }
    int getHitByCreature(int number){
        hitPoint+=number;
    }

    void copyLibrary(std::vector<std::shared_ptr<card>> &a) {
        Library.reserve(26);
        for (ptr = a.begin(); ptr != a.end(); ptr++) {
            Library.emplace_back(*ptr);
        }
    }
    void giveFirstHand() {
        ptr = Library.begin();

        for (int i = 0; i < 5; i++) {
            Hand.push_back(*ptr);
            ptr= Library.erase(ptr);

        }
    }
    std::string getName(){
        return name;
    }


    void drawCard() {
        ptr = Library.begin();

        if (Hand.size() < 7) {
            Hand.push_back(*ptr);
            ptr= Library.erase(ptr);
        }
        else{
            std::cout<<"You have 7 cards. Cannot draw card!"<<std::endl;
        }
    }



    std::vector<std::shared_ptr<card>>&  getHand(){
        return Hand;
    }
    std::vector<std::shared_ptr<card>>&  getInplay(){
        return InPlay;
    }
    std::vector<std::shared_ptr<card>>&  getGraveyard(){
        return Graveyard;
    }
    std::vector<std::shared_ptr<card>>&  getLibrary(){
        return Library;
    }

    virtual void playCardToInPlay(player &e, int number){


        int num;
        num =number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.InPlay.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    int& getHitPoint(){
        return hitPoint;
    }
    void setHitPoint(int number){
        hitPoint-=number;
    }
    void turn0Mana(){
        blackMana=0;
        whiteMana=0;
        redMana=0;
        greenMana=0;
        blueMana=0;
    }


};



class card{
protected:
    std::string name;
    std::string manaType;
    bool isActive;
    std::string type;
public:
    friend class player;
    card():name("Null"),manaType("x"),type("Null"){}
    card(std::string t,std::string n,std::string mT):type(t),name(n),manaType(mT){
        isActive=false;
    }
    card(const card &a){
        name=a.name;
        manaType=a.manaType;
        isActive=a.isActive;
        type=a.type;
    }
    friend class player;
    virtual void playCardToGraveyard(player &e,int number)=0;
    virtual void descreaseHPbyOne()=0;
    virtual void gainMana(player &p)=0;
    virtual void play()=0;
    virtual void playCardToInPlay(player &e,int number)=0;
    virtual void cardInfo()=0;
    virtual void spendMana(player &p,int number)=0;
    virtual std::string getType(){
        return type;
    }
    virtual void setAbility2(std::string newAbility)=0;
    virtual std::string getAbility2()=0;
    virtual bool getRageEffectActive()=0;
    virtual bool getSlowEffectActive()=0;
    virtual void setRageEffectActive(bool trueOrFalse)=0;
    virtual void setSlowEffectActive(bool trueOrFalse)=0;
    virtual std::string getName()=0;
    virtual bool getUntapped()=0;
    virtual void tapCard()=0;
    virtual bool getTap()=0;
    virtual int getAP()=0;
    virtual int getHP()=0;
    virtual void setHPOf(int number)=0;
    virtual std::string getAbility()=0;
    virtual void giveAbility(std::string a)=0;
    virtual bool getisPlayed()=0;
    virtual void changeAttackAndHp(int effectAttack, int effectHp)=0;
    virtual void setAbility(std::string newAbility)=0;
    virtual std::string getCardColor()=0;
    virtual int getBaseHp()=0;
    virtual bool setIsAttackTrue()=0;
    virtual bool setIsAttackFalse()=0;
    virtual bool getIsAttack()=0;




};
class landCard: public card{
protected:
    bool untapped=true;
public:
    virtual int getAP(){return 0;}
    virtual bool getisPlayed(){}
    virtual int getHP(){return 0;}
    virtual void setHPOf(int number){}
    virtual std::string getAbility(){return 0;}
    landCard():card(){}
    landCard(std::string t,std::string n,std::string mT):card(t,n,mT){
        isActive=true;

    }
    virtual std::string getType(){
        return type;
    }
    virtual int getBaseHp(){
    }
    virtual bool getIsAttack(){}
    landCard(const landCard &a){
        name=a.name;
        manaType=a.manaType;
        isActive=a.isActive;
        type=a.type;

    }
    friend class player;
    virtual void descreaseHPbyOne(){}
    virtual std::string getName(){
        return name;
    }
    virtual bool getUntapped(){
        untapped =true;
    }
    virtual bool getTap(){
        return untapped;
    }
    virtual void setAbility2(std::string newAbility){
    }
    virtual std::string getAbility2(){
        return 0;
    }
    virtual bool setIsAttackTrue(){}
    virtual bool setIsAttackFalse(){}
    virtual void gainMana(player &p){

        if (name =="Island") {
            p.blueMana++;
            std::cout<<p.name<<" gain one "<< this->manaType<<std::endl;
        }
        else if (name =="Forest") {
            p.greenMana++;
            std::cout<<p.name<<" gain one "<< this->manaType<<std::endl;
        }
        else if (name =="Mountain") {
            p.redMana++;
            std::cout<<p.name<<" gain one "<< this->manaType<<std::endl;
        }
        else if (name =="Plain") {
            p.whiteMana++;
            std::cout<<p.name<<" gain one "<< this->manaType<<std::endl;
        }
        else{
            p.blackMana++;
            std::cout<<p.name<<" gain one "<< this->manaType<<std::endl;
        }


    }
    virtual void cardInfo(){
        if (isActive== true){
            std::cout<<"Name: "<<this->name<<std::endl;
            std::cout<<"Mana type: "<<this->manaType<<std::endl;
            std::cout<<"Effect: gain one"<<this->manaType<<std::endl;
        }

    }
    void playCardToInPlay(player &e,int number){
        int num;
        num =number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.InPlay.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    virtual void play(){
        isActive=true;
        std::cout<< this->name<<" is active"<<std::endl;
    }

    virtual void spendMana(player &p,int number){}

    virtual void tapCard(){
        untapped=false;
    }
    void giveAbility(std::string a){}
    virtual void playCardToGraveyard(player &e,int number) {
        int num;
        num = number;
        std::vector<std::shared_ptr<card>>::iterator ptr1 = e.Hand.begin();


        e.Graveyard.push_back(e.Hand[num - 1]);
        for (int i = 0; i < num - 1; i++) {
            ptr1++;
        }
    }
    virtual void setAbility(std::string newAbility){}
    virtual std::string getCardColor(){}
    virtual void changeAttackAndHp(int effectAttack, int effectHp){
    }
    virtual bool getRageEffectActive(){

    }
    virtual bool getSlowEffectActive(){

    }
    virtual void setRageEffectActive(bool trueOrFalse){

    }
    virtual void setSlowEffectActive(bool trueOrFalse){

    }


};
class creature:public card{
protected:
    std::string cardColor;
    int attackPower;
    int hitPoint;
    std::string ability;
    int untapped=true;
    int baseHp;
    bool rageEffectActive;
    bool slowEffectActive;
    std::string ability2;
    bool secondAbilityActive;
    bool isAttack;

public:
    creature():card(){}
    creature(std::string t,std::string n,std::string mT,std::string cC,int aP,int hP,std::string a):card(t,n,mT),cardColor(cC),attackPower(aP),hitPoint(hP),ability(a){
        isActive=true;
        baseHp=hP;
        rageEffectActive=0;
        slowEffectActive=0;
        ability2="None";
        if(a=="First Strike"||a=="Trample"){
            secondAbilityActive=1;
        }
        else{
            secondAbilityActive=0;
        }
        isAttack=false;
    }
    creature(const creature &a){
        name=a.name;
        manaType=a.manaType;
        cardColor=a.cardColor;
        attackPower=a.attackPower;
        hitPoint=a.hitPoint;
        ability=a.ability;
        isActive=a.isActive;
        type=a.type;
        baseHp=a.baseHp;
        rageEffectActive=a.rageEffectActive;
        slowEffectActive=a.slowEffectActive;
        secondAbilityActive=a.secondAbilityActive;
        ability2=a.ability2;
        isAttack=a.isAttack;
    }
    virtual void setAbility2(std::string newAbility){
        ability2=newAbility;
    }
    virtual bool setIsAttackTrue(){
        isAttack =true;
    }
    virtual bool setIsAttackFalse(){
    isAttack =false;
    }
    virtual bool getIsAttack(){
        return isAttack;
    }
    virtual std::string getAbility2(){
        return ability2;
    }
    virtual bool getRageEffectActive(){
        return rageEffectActive;
    }
    virtual bool getSlowEffectActive(){
        return slowEffectActive;
    }
    virtual void setRageEffectActive(bool trueOrFalse){
        rageEffectActive=trueOrFalse;
    }
    virtual void setSlowEffectActive(bool trueOrFalse){
        slowEffectActive=trueOrFalse;
    }
    virtual int getBaseHp(){
        return baseHp;
    }
    virtual void setAbility(std::string newAbility){
        ability=newAbility;
    }
    virtual std::string getCardColor(){
        return cardColor;
    }
    virtual void changeAttackAndHp(int effectAttack, int effectHp){
        attackPower+=effectAttack;
        hitPoint+=effectHp;
    }
    virtual bool getisPlayed(){}
    virtual void setHPOf(int number){
        hitPoint=number;
    }
    virtual std::string getAbility(){
        return ability;
    }
    virtual int getAP(){
        return attackPower;
    }
    virtual int getHP(){
        return hitPoint;
    }

    virtual std::string getType(){
        return type;
    }
    virtual std::string getName(){
        return name;
    }
    virtual bool getUntapped(){
        untapped =true;
    }
    virtual bool getTap(){
        return untapped;
    }
    friend class enchantment;
    friend class player;
    friend class effect;

    virtual void playCardToGraveyard(player &e,int number){
        int num;
        num=number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.Graveyard.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    void playCardToInPlay(player &e,int number){
        int num;
        num=number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.InPlay.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    virtual void descreaseHPbyOne(){
        hitPoint=hitPoint-1;
    }
    virtual void gainMana(player &p){}

    virtual void play(){
        isActive=true;
        std::cout<< this->name<<" is active"<<std::endl;
    }
    virtual void cardInfo() {
        if (isActive== true) {
            std::cout << "Name: " << this->name << std::endl;
            std::cout << "Mana type: " << this->manaType << std::endl;
            std::cout << "Attack power: " << this->attackPower << std::endl;
            std::cout << "Hitpoint: " << this->hitPoint << std::endl;
            if (this->ability == "Trample") {
                std::cout << "Ability: " << this->ability << std::endl;
            } else if (this->ability == "FirstStrike") {
                std::cout << "Ability: " << this->ability << std::endl;
            } else {
                std::cout << "Ability: " << this->ability << std::endl;
            }

        }
    }
    virtual void spendMana(player &p,int number){
        std::string manatypee;
        if(this->name=="Soldier"){
            if(p.whiteMana>=1){
                p.whiteMana-=1;
                playCardToInPlay(p,number);
                play();
            }
            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Armored Pegasus"){
            if(p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.whiteMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            play();
                            playCardToInPlay(p,number);
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if (this->name=="White Knight"){
            if (p.whiteMana >= 2){
                p.whiteMana-=2;
                playCardToInPlay(p,number);
                play();
            }
            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if (this->name=="Skeleton") {
            if (p.blackMana >= 1) {
                p.blackMana -= 1;
                playCardToInPlay(p,number);
                play();
            } else {
                std::cout << "Not enough mana" << std::endl;
            }
        }
        if (this->name == "Black Knight") {
            if (p.blackMana >= 2) {
                p.blackMana -= 2;
                playCardToInPlay(p,number);
                play();
            } else {
                std::cout << "Not enough mana" << std::endl;
            }


        }
        if(this->name=="Ghost"){
            if(p.blackMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.blackMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Hobgoblin"){
            if(p.blackMana>=1 &p.redMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.blackMana-=1;
                p.redMana -=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            playCardToInPlay(p,number);
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Angry Bear"){
            if(p.greenMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.greenMana-=2;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Guard"){
            if(p.whiteMana>=2 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=4){
                p.whiteMana-=2;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        playCardToInPlay(p,number);
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Werewolf"){
            if(p.greenMana>=1 & p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=4){
                p.greenMana-=1;
                p.whiteMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="OrcManiac"){
            if(p.redMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.redMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        playCardToInPlay(p,number);
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Vampire"){
            if(p.blackMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=4){
                p.blackMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> manatypee;
                    if (manatypee == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p, number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p, number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p, number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p, number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p, number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }

                                    else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (manatypee == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (manatypee == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> manatypee;
                                if (manatypee == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (manatypee == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (manatypee == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        while (true) {
                                            std::cout << "You need to choose mana" << std::endl;
                                            std::cout << "1 -> Black Mana" << std::endl;
                                            std::cout << "2 -> White Mana" << std::endl;
                                            std::cout << "3 -> Red mana" << std::endl;
                                            std::cout << "4 -> Green Mana" << std::endl;
                                            std::cout << "5 -> Blue Mana" << std::endl;
                                            std::cin >> manatypee;
                                            if (manatypee == "1") {
                                                if (p.blackMana >= 1) {
                                                    p.blackMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "2") {
                                                if (p.whiteMana >= 1) {
                                                    p.whiteMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                } else {
                                                    std::cout << "Not enough mana" << std::endl;
                                                }
                                            }
                                            if (manatypee == "3") {
                                                if (p.redMana >= 1) {
                                                    p.redMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "4") {
                                                if (p.greenMana >= 1) {
                                                    p.greenMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                            if (manatypee == "5") {
                                                if (p.blueMana >= 1) {
                                                    p.blueMana -= 1;
                                                    playCardToInPlay(p,number);
                                                    play();
                                                    break;
                                                }
                                                else{
                                                    std::cout<<"Not enough mana"<<std::endl;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }





    }
    void giveAbility(std::string a){
        ability=a;
    }
    virtual void tapCard(){
        untapped=false;
    }
    int getHp(){
        return hitPoint;
    }



};
class sorcery: public card{
protected:
    bool isPlayed=false;
    std::string cardColor;
    std::shared_ptr<effect> cardEffectCarrier;
public:
    virtual bool getIsAttack(){}
    virtual int getAP(){return 0;}
    virtual int getHP(){return 0;}
    virtual void setHPOf(int number){}
    virtual std::string getAbility(){return 0;}
    void giveAbility(std::string a){}
    virtual int getBaseHp(){
    }
    virtual bool setIsAttackTrue(){}
    virtual bool setIsAttackFalse(){}

    virtual void descreaseHPbyOne(){}
    virtual bool getUntapped(){
    }
    virtual bool getTap(){
    }
    virtual std::string getName(){
        return name;
    }
    virtual bool getRageEffectActive(){

    }
    virtual bool getSlowEffectActive(){

    }
    virtual void setRageEffectActive(bool trueOrFalse){

    }
    virtual void setSlowEffectActive(bool trueOrFalse){

    }
    virtual void tapCard(){}
    friend class player;
    sorcery():card(){}
    sorcery(std::string t,std::string n,std::string mT,std::string cC,std::shared_ptr<effect> &cardEffect):card(t,n,mT),cardColor(cC){
        isActive=true;
        cardEffectCarrier=cardEffect;
    }
    sorcery(const sorcery &a){
        name=a.name;
        manaType=a.manaType;
        cardColor=a.cardColor;
        isActive=a.isActive;
        type=a.type;
    }

    virtual void play(){
        isPlayed=true;

    }
    virtual void playCardToGraveyard(player &e,int number) {
        int num;
        num = number;
        std::vector<std::shared_ptr<card>>::iterator ptr1 = e.Hand.begin();


        e.Graveyard.push_back(e.Hand[num - 1]);

        for (int i = 0; i < num - 1; i++) {
            ptr1++;
        }
        e.Hand.erase(ptr1);
    }
    void playCardToInPlay(player &e,int number){
        int num;
        num = number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.InPlay.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    virtual void cardInfo() {
        if (isActive== true) {
            std::cout << "Name: " << this->name << std::endl;
            std::cout << "Mana type: " << this->manaType << std::endl;
        }
    }
    virtual void gainMana(player &p){};

    virtual void spendMana(player &p,int number) {

        std::string sorceryManaType;
        if(this->name=="Disenchant"){
            if(p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.whiteMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> sorceryManaType;
                    if (sorceryManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;

                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (sorceryManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Lightning Bolt"){
            if(p.greenMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.greenMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> sorceryManaType;
                    if (sorceryManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;

                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (sorceryManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Terror"){
            if(p.blackMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.blackMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> sorceryManaType;
                    if (sorceryManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;

                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (sorceryManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;

                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Flood"){
            if(p.greenMana>=1 &p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.greenMana-=1;
                p.whiteMana -=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> sorceryManaType;
                    if (sorceryManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (sorceryManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Plague"){
            if(p.blackMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.blackMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> sorceryManaType;
                    if (sorceryManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> sorceryManaType;
                                if (sorceryManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (sorceryManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;

                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;

                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;

                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >>sorceryManaType;
                                if (sorceryManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;

                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (sorceryManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (sorceryManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> sorceryManaType;
                                if (sorceryManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (sorceryManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> sorceryManaType;
                                if (sorceryManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (sorceryManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (sorceryManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> sorceryManaType;
                                if (sorceryManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (sorceryManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (sorceryManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Reanimate"){
            if(p.blackMana>=1){
                p.blackMana-=1;
                play();
            }
            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
    }

    virtual std::string getType(){
        return type;
    }
    auto returnEffectItem(){
        return cardEffectCarrier;
    }
    virtual bool getisPlayed(){
        return isPlayed;
    }
    virtual void setAbility(std::string newAbility){}
    virtual std::string getCardColor(){}
    virtual void changeAttackAndHp(int effectAttack, int effectHp){
    }
    virtual void setAbility2(std::string newAbility){
    }
    virtual std::string getAbility2(){
        return 0;
    }
};
class enchantment: public card{
protected:
    bool isPlayed=false;
    std::string cardColor;
    std::shared_ptr<effect> cardEffectCarrier;
public:
    virtual bool getIsAttack(){}
    virtual int getAP(){return 0;}
    virtual void playCardToGraveyard(player &e,int number) {
        int num;
        num = number;
        std::vector<std::shared_ptr<card>>::iterator ptr1 = e.Hand.begin();


        e.Graveyard.push_back(e.Hand[num - 1]);
        for (int i = 0; i < num - 1; i++) {
            ptr1++;
        }
        e.InPlay.erase(ptr1);
    }
    virtual void setAbility2(std::string newAbility){
    }
    virtual std::string getAbility2(){
        return 0;
    }
    virtual bool getRageEffectActive(){

    }
    virtual bool setIsAttackTrue(){}
    virtual bool setIsAttackFalse(){}
    virtual bool getSlowEffectActive(){

    }
    virtual void setRageEffectActive(bool trueOrFalse){

    }
    virtual void setSlowEffectActive(bool trueOrFalse){

    }
    virtual int getHP(){return 0;}
    virtual void setHPOf(int number){}
    virtual std::string getAbility(){return 0;}
    virtual void descreaseHPbyOne(){}
    virtual std::string getName(){
        return name;
    }
    virtual int getBaseHp(){
    }
    void giveAbility(std::string a){}
    virtual bool getUntapped(){
    }
    virtual void tapCard(){}
    virtual bool getTap(){
    }
    friend class creature;
    friend class effect;
    enchantment():card(){}
    enchantment(std::string t,std::string n,std::string mT,std::string cC,std::shared_ptr<effect> &cardEffect):card(t,n,mT),cardColor(cC){
        isActive=true;
        cardEffectCarrier=cardEffect;

    }
    enchantment(const enchantment &a) {
        name = a.name;
        manaType = a.manaType;
        cardColor = a.cardColor;
        isActive=a.isActive;
        type=a.type;
        cardEffectCarrier=a.cardEffectCarrier;

    }
    virtual void play(){
        isActive=true;
        isPlayed=true;
        std::cout<< this->name<<" is active"<<std::endl;
    }

    virtual void cardInfo() {
        if(isActive== true){
            std::cout << "Name: " << this->name << std::endl;
            std::cout << "Mana type: " << this->manaType << std::endl;
        }
    }
    virtual void gainMana(player &p){}
    virtual void spendMana(player &p,int number){
        std::string enchantmentManaType;
        if(this->name=="Rage"){
            if(p.greenMana>=1){
                p.greenMana-=1;
                play();
            }
            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Holy War"){
            if(p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.whiteMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> enchantmentManaType;
                    if (enchantmentManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (enchantmentManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Holy Light"){
            if(p.whiteMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.whiteMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> enchantmentManaType;
                    if (enchantmentManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (enchantmentManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Unholy War"){
            if(p.blackMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=2){
                p.blackMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> enchantmentManaType;
                    if (enchantmentManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            play();
                            break;
                        } else {
                            std::cout << "Not enough mana" << std::endl;
                        }
                    }
                    if (enchantmentManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            play();
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Restrain"){
            if(p.redMana>=1 & p.whiteMana+p.blackMana+p.redMana+p.blueMana+p.greenMana >=3){
                p.redMana-=1;
                while (true) {
                    std::cout << "You need to choose mana" << std::endl;
                    std::cout << "1 -> Black Mana" << std::endl;
                    std::cout << "2 -> White Mana" << std::endl;
                    std::cout << "3 -> Red mana" << std::endl;
                    std::cout << "4 -> Green Mana" << std::endl;
                    std::cout << "5 -> Blue Mana" << std::endl;
                    std::cin >> enchantmentManaType;
                    if (enchantmentManaType == "1") {
                        if (p.blackMana >= 1) {
                            p.blackMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> enchantmentManaType;
                                if (enchantmentManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (enchantmentManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "2") {
                        if (p.whiteMana >= 1) {
                            p.whiteMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> enchantmentManaType;
                                if (enchantmentManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (enchantmentManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else {
                            std::cout << "Not enough mana" << std::endl;
                        }

                    }
                    if (enchantmentManaType == "3") {
                        if (p.redMana >= 1) {
                            p.redMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> enchantmentManaType;
                                if (enchantmentManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (enchantmentManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "4") {
                        if (p.greenMana >= 1) {
                            p.greenMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> enchantmentManaType;
                                if (enchantmentManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (enchantmentManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                    if (enchantmentManaType == "5") {
                        if (p.blueMana >= 1) {
                            p.blueMana -= 1;
                            while (true) {
                                std::cout << "You need to choose mana" << std::endl;
                                std::cout << "1 -> Black Mana" << std::endl;
                                std::cout << "2 -> White Mana" << std::endl;
                                std::cout << "3 -> Red mana" << std::endl;
                                std::cout << "4 -> Green Mana" << std::endl;
                                std::cout << "5 -> Blue Mana" << std::endl;
                                std::cin >> enchantmentManaType;
                                if (enchantmentManaType == "1") {
                                    if (p.blackMana >= 1) {
                                        p.blackMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "2") {
                                    if (p.whiteMana >= 1) {
                                        p.whiteMana -= 1;
                                        play();
                                        break;
                                    } else {
                                        std::cout << "Not enough mana" << std::endl;
                                    }
                                }
                                if (enchantmentManaType == "3") {
                                    if (p.redMana >= 1) {
                                        p.redMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "4") {
                                    if (p.greenMana >= 1) {
                                        p.greenMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                                if (enchantmentManaType == "5") {
                                    if (p.blueMana >= 1) {
                                        p.blueMana -= 1;
                                        play();
                                        break;
                                    }
                                    else{
                                        std::cout<<"Not enough mana"<<std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        else{
                            std::cout<<"Not enough mana"<<std::endl;
                        }
                    }
                }
            }

            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }
        if(this->name=="Slow"){
            if(p.blackMana>=1){
                p.blackMana-=1;
                play();
            }
            else{
                std::cout<<"Not enough mana"<<std::endl;
            }
        }


    }
    virtual std::string getType(){
        return type;
    }
    void playCardToInPlay(player &e,int number){
        int num;
        num = number;
        std::vector<std::shared_ptr<card>>::iterator ptr1=e.Hand.begin();


        e.InPlay.push_back(e.Hand[num-1]);
        for(int i=0;i<num-1;i++){
            ptr1++;
        }
        e.Hand.erase(ptr1);

    }
    std::shared_ptr<effect> returnEffectItem(){
        return cardEffectCarrier;
    }
    virtual bool getisPlayed(){
        return isPlayed;
    }
    virtual void setAbility(std::string newAbility){}
    virtual std::string getCardColor(){}
    virtual void changeAttackAndHp(int effectAttack, int effectHp){
    }
};

class effect
{
protected:
    std::string cardName;
public:
    effect(std::string CN):cardName(CN){}
    virtual std::string getName(){
        return cardName;
    }
    effect():cardName(""){}
    effect(const effect &l){
        cardName=l.cardName;
    }
    friend class card;
    friend class creature;
    friend class sorcery;
    friend class player;
    friend class enchantment;

    void rageEffect(player &first) {
        bool num= false;
        while (num!= true) {
            int num;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1 = first.InPlay.begin();

            for (int i = 0; i < first.InPlay.size(); i++) {
                if (first.getInplay()[i]->getType() == "Creature") {

                    temp1.push_back(first.getInplay()[i]);
                    i-=1;
                    ptr1 = first.InPlay.erase(ptr1);

                } else if(first.getInplay()[i]->getType() != "Creature") {
                    ptr1++; }

            }
            if (temp1.size() == 0) {
                std::cout << "No Creature Card To Use Rage Effect." << std::endl;
                break;
            }
            else {

                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }

                std::cout << "Enter Number Of Creature To Give Rage Effect" << std::endl;
                std::cin >> num;
                temp1[(num-1)]->giveAbility("Trample");
                temp1[(num-1)]->setRageEffectActive(true);
                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    first.InPlay.push_back(*ptr3);
                    ptr3++;
                }

                std::cout << "Card Gained Trample" << std::endl;
                std::cout << std::endl;

                std::cout << "========================================================================" << std::endl;
                break;
            }
        }
    }
    void lightingBoltEffect( player &second) {
        if (cardName == "Lightning Bolt") {
            std::cout << "========================================================================" << std::endl;

            std::string which;
            std::cout << "1 -> Creature" << std::endl;
            std::cout << "2 -> Player" << std::endl;
            std::cin>>which;
            if (which == "1") {
                bool num= false;
                while (num!= true) {
                    int num;
                    std::vector<std::shared_ptr<card>> temp1;
                    std::vector<std::shared_ptr<card>>::iterator ptr1 = second.InPlay.begin();

                    for (int i = 0; i < second.InPlay.size(); i++) {
                        if (second.getInplay()[i]->getType() == "Creature") {

                            temp1.push_back(second.getInplay()[i]);
                            i-=1;
                            ptr1 = second.InPlay.erase(ptr1);

                        } else { ptr1++; }

                    }
                    if (temp1.size() == 0) {
                        std::cout << "No Creature Card To Use Lightning Bolt Effect." << std::endl;
                        break;
                    }
                    else {

                        for (int i = 0; i < temp1.size(); i++) {
                            std::cout << i + 1 << "--> ";
                            temp1[i]->cardInfo();
                            std::cout << std::endl;
                        }
                        std::cout << "Enter Number Of Creature To Give Lightning Bolt Effect" << std::endl;
                        std::cin >> num;
                        temp1[(num-1)]->setHPOf(temp1[num-1]->getHP()-2);
                        std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                        for (int i = 0; i < temp1.size(); i++) {

                            second.InPlay.push_back(*ptr3);
                            ptr3++;
                        }

                        std::cout << "Card Got Hit By 2" << std::endl;
                        std::cout << std::endl;

                        std::cout << "========================================================================" << std::endl;
                        break;
                    }
                }
            } else if (which == "2") {
                second.setHitPoint(2);
                std::cout << "Enemy Got Hit By 2" << std::endl;
            }
            std::cout << "========================================================================" << std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void disenchantEffect(player &second,player &first){
        if (cardName == "Disenchant") {
            std::cout<<"========================================================================"<<std::endl;

            int num;
            int sayac=0;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1=second.InPlay.begin();

            for(int i=0;i<second.InPlay.size();i++){
                if(second.getInplay()[i]->getType()=="Enchantment"){
                    sayac++;
                    temp1.push_back(second.getInplay()[i]);
                    i-=1;
                    ptr1=second.InPlay.erase(ptr1);

                }
                else{ptr1++;}

            }
            if(sayac==0){
                std::cout << "No Enchantment To Destroy. Your Card Is Gone..." << std::endl;
                return;
            }
            else {
                std::vector<std::shared_ptr<card>>::iterator ptr2 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }
                std::cout << "Enter Number Of Enchantment To Destroy" << std::endl;
                std::cin >> num;

                if (temp1[num - 1]->getName() == "Rage") {
                    for (int i = 0; i < second.getInplay().size(); i++) {
                        if (second.getInplay()[i]->getRageEffectActive() == true) {
                            second.getInplay()[i]->setRageEffectActive(false);
                            second.getInplay()[i]->setAbility("None");
                        }
                    }
                } else if (temp1[num - 1]->getName() == "Slow") {
                    for (int i = 0; i < second.getInplay().size(); i++) {
                        if (second.getInplay()[i]->getSlowEffectActive() == true) {
                            second.getInplay()[i]->setSlowEffectActive(false);
                            second.getInplay()[i]->setAbility("First Strike");
                        }
                    }
                } else if (temp1[num - 1]->getName() == "Holy War") {
                    std::vector<std::shared_ptr<card>>::iterator ptr1 = first.InPlay.begin();

                    std::string targetColor = "White";
                    for (int i = 0; i < first.InPlay.size(); i++) {
                        if ((first.getInplay()[i]->getType() == "Creature") &&
                            (first.getInplay()[i]->getCardColor() == targetColor)) {
                            first.getInplay()[i]->changeAttackAndHp(-1, -1);
                            ptr1++;
                        } else { ptr1++; }

                    }
                    std::vector<std::shared_ptr<card>>::iterator ptr2 = second.InPlay.begin();


                    for (int i = 0; i < second.InPlay.size(); i++) {
                        if ((second.getInplay()[i]->getType() == "Creature") &&
                            (second.getInplay()[i]->getCardColor() == targetColor)) {
                            second.getInplay()[i]->changeAttackAndHp(-1, -1);
                            ptr2++;
                        } else { ptr2++; }

                    }
                } else if (temp1[num - 1]->getName() == "Holy Light") {
                    std::vector<std::shared_ptr<card>>::iterator ptr1 = first.InPlay.begin();

                    std::string targetColor = "Black";
                    for (int i = 0; i < first.InPlay.size(); i++) {
                        if ((first.getInplay()[i]->getType() == "Creature") &&
                            (first.getInplay()[i]->getCardColor() == targetColor)) {
                            first.getInplay()[i]->changeAttackAndHp(+1, +1);
                            ptr1++;
                        } else { ptr1++; }

                    }
                    std::vector<std::shared_ptr<card>>::iterator ptr2 = second.InPlay.begin();


                    for (int i = 0; i < second.InPlay.size(); i++) {
                        if ((second.getInplay()[i]->getType() == "Creature") &&
                            (second.getInplay()[i]->getCardColor() == targetColor)) {
                            second.getInplay()[i]->changeAttackAndHp(+1, +1);
                            ptr2++;
                        } else { ptr2++; }

                    }
                } else if (temp1[num - 1]->getName() == "Unholy War") {
                    std::vector<std::shared_ptr<card>>::iterator ptr1 = first.InPlay.begin();

                    std::string targetColor = "Black";
                    for (int i = 0; i < first.InPlay.size(); i++) {
                        if ((first.getInplay()[i]->getType() == "Creature") &&
                            (first.getInplay()[i]->getCardColor() == targetColor)) {
                            first.getInplay()[i]->changeAttackAndHp(-2, 0);
                            ptr1++;
                        } else { ptr1++; }

                    }
                    std::vector<std::shared_ptr<card>>::iterator ptr2 = second.InPlay.begin();

                    for (int i = 0; i < second.InPlay.size(); i++) {
                        if ((second.getInplay()[i]->getType() == "Creature") &&
                            (second.getInplay()[i]->getCardColor() == targetColor)) {
                            second.getInplay()[i]->changeAttackAndHp(-2, 0);
                            ptr2++;
                        } else { ptr2++; }

                    }
                }


                ptr2 + num - 1 = temp1.erase(ptr2 + num - 1);

                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    second.InPlay.push_back(*ptr3);
                    ptr3++;
                }

                std::cout << "Card Is Destroyed" << std::endl;
                std::cout << std::endl;

                std::cout << "========================================================================" << std::endl;

            }
        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void floodEffect(player &second){
        if (cardName == "Flood") {
            std::cout << "========================================================================" << std::endl;
            int num;
            int sayac = 0;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1 = second.InPlay.begin();

            for (int i = 0; i < second.InPlay.size(); i++) {
                if (second.getInplay()[i]->getType() == "Land Card") {
                    sayac++;
                    temp1.push_back(second.getInplay()[i]);
                    i -= 1;
                    ptr1 = second.InPlay.erase(ptr1);

                } else { ptr1++; }

            }
            if (sayac == 0) {
                std::cout << "No Land Card To Destroy. Your Card Is Gone..." << std::endl;
                return;
            } else {
                std::vector<std::shared_ptr<card>>::iterator ptr2 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }
                std::cout << "Enter Number Of Land Card To Destroy" << std::endl;
                std::cin >> num;
                ptr2 + num - 1 = temp1.erase(ptr2 + num - 1);
                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    second.InPlay.push_back(*ptr3);
                    ptr3++;
                }

                std::cout << "Card Is Destroyed" << std::endl;
                std::cout << std::endl;

                std::cout << "========================================================================" << std::endl;

            }
        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void reanimateEffect(player &first) {
        if (cardName == "Reanimate") {
            std::cout << "========================================================================" << std::endl;
            int num;
            int sayac = 0;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1 = first.Graveyard.begin();

            for (int i = 0; i < first.Graveyard.size(); i++) {
                if (first.getGraveyard()[i]->getType() == "Creature") {
                    sayac++;
                    temp1.push_back(first.getGraveyard()[i]);
                    i -= 1;
                    ptr1 = first.Graveyard.erase(ptr1);

                } else { ptr1++; }
            }
            if (sayac == 0) {
                std::cout << "No Creature To Reanimate. Your Card Is Gone..." << std::endl;
                return;
            }
            else {
                std::vector<std::shared_ptr<card>>::iterator ptr2 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }
                std::cout << "Enter Number Creature To Reanimate" << std::endl;
                std::cin >> num;
                first.Hand.push_back(temp1[num - 1]);
                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    first.Graveyard.push_back(*ptr3);
                    ptr3++;
                }
                std::cout << "Card Is Reanimated" << std::endl;
                std::cout << std::endl;

                std::cout << "========================================================================" << std::endl;
            }
        }
        else{
            std::cout << "Wrong Effect!" << std::endl;
        }
    }
    void plagueEffect(player &first,player &second){
        if (cardName == "Plague") {
            std::cout<<"========================================================================"<<std::endl;
            std::vector<std::shared_ptr<card>>::iterator ptr1=first.InPlay.begin();


            for(int i=0;i<first.InPlay.size();i++){
                if(first.InPlay[i]->getType()=="Creature"){
                    first.InPlay[i]->descreaseHPbyOne();

                    ptr1++;
                }
                else{ptr1++;}

            }
            std::vector<std::shared_ptr<card>>::iterator ptr2=second.InPlay.begin();


            for(int i=0;i<second.InPlay.size();i++){
                if(second.InPlay[i]->getType()=="Creature"){
                    second.InPlay[i]->descreaseHPbyOne();

                    ptr2++;
                }
                else{ptr2++;}

            }
            std::cout<<"All Creatures Hp Is Reduced By One"<<std::endl;

            std::cout<<std::endl;

            std::cout<<"========================================================================"<<std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void terrorEffect(player &second){
        if (cardName == "Terror") {
            std::cout<<"========================================================================"<<std::endl;
            int num;
            int sayac1=0;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1=second.InPlay.begin();

            for(int i=0;i<second.InPlay.size();i++) {
                if (second.getInplay()[i]->getType() == "Creature") {
                    sayac1++;
                    temp1.push_back(second.getInplay()[i]);
                    i -= 1;
                    ptr1 = second.InPlay.erase(ptr1);

                } else { ptr1++; }
            }
            if (sayac1 == 0) {
                std::cout << "No Creature To Destroy. Your Card Is Gone..." << std::endl;
                return;

            } else {
                std::vector<std::shared_ptr<card>>::iterator ptr2 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }
                std::cout << "Enter Number Of Creature To Destroy" << std::endl;
                std::cin >> num;
                ptr2 + num - 1 = temp1.erase(ptr2 + num - 1);
                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    second.InPlay.push_back(*ptr3);
                    ptr3++;
                }
                std::cout << "Card Is Destroyed" << std::endl;
                std::cout << "========================================================================" << std::endl;
                return;
            }
        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void holyWarEffect(player &first,player &second){
        if (cardName == "Holy War") {
            std::cout << "========================================================================" << std::endl;
            std::vector<std::shared_ptr<card>>::iterator ptr1=first.InPlay.begin();

            std::string targetColor="White";
            for(int i=0;i<first.InPlay.size();i++){
                if((first.getInplay()[i]->getType()=="Creature")&&(first.getInplay()[i]->getCardColor()==targetColor)){
                    first.getInplay()[i]->changeAttackAndHp(1,1);
                    ptr1++;
                }
                else{ptr1++;}

            }
            std::vector<std::shared_ptr<card>>::iterator ptr2=second.InPlay.begin();


            for(int i=0;i<second.InPlay.size();i++){
                if((second.getInplay()[i]->getType()=="Creature")&&(second.getInplay()[i]->getCardColor()==targetColor)){
                    second.getInplay()[i]->changeAttackAndHp(1,1);
                    ptr2++;
                }
                else{ptr2++;}

            }
            std::cout<<"All White Creatures Gained +1/+1"<<std::endl;

            std::cout<<std::endl;

            std::cout<<"========================================================================"<<std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void holyLightEffect(player &p,player &second){
        if (cardName == "Holy Light") {
            std::cout << "========================================================================" << std::endl;
            std::vector<std::shared_ptr<card>>::iterator ptr1=p.InPlay.begin();

            std::string targetColor="Black";
            for(int i=0;i<p.InPlay.size();i++){
                if((p.getInplay()[i]->getType()=="Creature")&&(p.getInplay()[i]->getCardColor()==targetColor)){
                    p.getInplay()[i]->changeAttackAndHp(-1,-1);
                    ptr1++;
                }
                else{ptr1++;}

            }
            std::vector<std::shared_ptr<card>>::iterator ptr2=second.InPlay.begin();


            for(int i=0;i<second.InPlay.size();i++){
                if((second.getInplay()[i]->getType()=="Creature")&&(second.getInplay()[i]->getCardColor()==targetColor)){
                    second.getInplay()[i]->changeAttackAndHp(-1,-1);
                    ptr2++;
                }
                else{ptr2++;}

            }
            std::cout<<"All Black Creatures Gained -1/-1"<<std::endl;

            std::cout<<std::endl;

            std::cout<<"========================================================================"<<std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void unholyWarEffect(player &p,player &second){
        if (cardName == "Unholy War") {
            std::cout << "========================================================================" << std::endl;
            std::vector<std::shared_ptr<card>>::iterator ptr1=p.InPlay.begin();

            std::string targetColor="Black";
            for(int i=0;i<p.InPlay.size();i++){
                if((p.getInplay()[i]->getType()=="Creature")&&(p.getInplay()[i]->getCardColor()==targetColor)){
                    p.getInplay()[i]->changeAttackAndHp(2,0);
                    ptr1++;
                }
                else{ptr1++;}

            }
            std::vector<std::shared_ptr<card>>::iterator ptr2=second.InPlay.begin();

            for(int i=0;i<second.InPlay.size();i++){
                if((second.getInplay()[i]->getType()=="Creature")&&(second.getInplay()[i]->getCardColor()==targetColor)){
                    second.getInplay()[i]->changeAttackAndHp(2,0);
                    ptr2++;
                }
                else{ptr2++;}

            }
            std::cout<<"All Black Creatures Gained +2/0"<<std::endl;

            std::cout<<std::endl;

            std::cout<<"========================================================================"<<std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void restrainEffect(player &p,player &second){

        if (cardName == "Restrain") {
            std::cout << "========================================================================" << std::endl;
            std::vector<std::shared_ptr<card>>::iterator ptr1=p.InPlay.begin();

            std::string targetColor="Green";
            for(int i=0;i<p.InPlay.size();i++){
                if((p.getInplay()[i]->getType()=="Creature")&&(p.getInplay()[i]->getCardColor()==targetColor)){
                    p.getInplay()[i]->setAbility("None");
                    ptr1++;
                }
                else{ptr1++;}

            }
            std::vector<std::shared_ptr<card>>::iterator ptr2=second.InPlay.begin();


            for(int i=0;i<second.InPlay.size();i++){
                if((second.getInplay()[i]->getType()=="Creature")&&(second.getInplay()[i]->getCardColor()==targetColor)){
                    second.getInplay()[i]->setAbility("None");
                    ptr2++;
                }
                else{ptr2++;}

            }
            std::cout<<"All Green Creatures Lost Trample"<<std::endl;

            std::cout<<std::endl;

            std::cout<<"========================================================================"<<std::endl;

        }
        else{
            std::cout<<"Wrong Effect!"<<std::endl;
        }
    }
    void slowEffect(player &first){

        bool num= false;
        while (num!= true) {
            int num;
            std::vector<std::shared_ptr<card>> temp1;
            std::vector<std::shared_ptr<card>>::iterator ptr1 = first.InPlay.begin();

            for (int i = 0; i < first.InPlay.size(); i++) {
                if (first.getInplay()[i]->getType() == "Creature" && first.getInplay()[i]->getAbility()=="First Strike") {

                    temp1.push_back(first.getInplay()[i]);
                    i-=1;
                    ptr1 = first.InPlay.erase(ptr1);

                } else { ptr1++; }

            }
            if (temp1.size() == 0) {
                std::cout << "No Creature Card To Use Slow Effect." << std::endl;
                break;
            }
            else {

                for (int i = 0; i < temp1.size(); i++) {
                    std::cout << i + 1 << "--> ";
                    temp1[i]->cardInfo();
                    std::cout << std::endl;
                }
                std::cout << "Enter Number Of Creature To Erase It's Effect" << std::endl;
                std::cin >> num;
                temp1[(num-1)]->giveAbility("None");
                temp1[(num-1)]->setSlowEffectActive(true);
                std::vector<std::shared_ptr<card>>::iterator ptr3 = temp1.begin();
                for (int i = 0; i < temp1.size(); i++) {

                    first.InPlay.push_back(*ptr3);
                    ptr3++;
                }

                std::cout << "Card Lost Ability" << std::endl;
                std::cout << std::endl;

                std::cout << "========================================================================" << std::endl;
                break;
            }
        }
    }
};



void showHand(player &a){

    for(int i=0;i<a.getHand().size();i++){
        a.getHand()[i]->cardInfo();
        std::cout<<std::endl;
    }
}
void showInPlay(player &a){

    for(int i=0;i<a.getInplay().size();i++){
        a.getInplay()[i]->cardInfo();
        std::cout<<std::endl;
    }
}
void attackCreatureOrOtherPlayer(player &first, player &second) {


    int num;
std::vector<std::shared_ptr<card>> birinciTasiyici;
std::vector<std::shared_ptr<card>> ikinciTasiyici;

std::vector<std::shared_ptr<card>>::iterator birinciOyuncununInplayIteratoru = first.getInplay().begin();
std::vector<std::shared_ptr<card>>::iterator birinciTasiyicininIteratoru = birinciTasiyici.begin();
for (int i = 0; i < first.getInplay().size(); i++) {
if (first.getInplay()[i]->getType() == "Creature" && first.getInplay()[i]->getTap() == false && first.getInplay()[i]->getIsAttack()==false) {

birinciTasiyici.push_back(first.getInplay()[i]);
birinciOyuncununInplayIteratoru=first.getInplay().erase(birinciOyuncununInplayIteratoru);
i-=1;
} else { birinciOyuncununInplayIteratoru++; }

}
std::vector<std::shared_ptr<card>>::iterator birinciTasiyiciIteratoru2 = birinciTasiyici.begin();
for (int i = 0; i < birinciTasiyici.size(); i++) {
std::cout << i + 1 << "--> ";
birinciTasiyici[i]->cardInfo();
std::cout << std::endl;
}
    int a;
    a = 0;
    for(int i=0;i<birinciTasiyici.size();i++){

        if(birinciTasiyici[i]->getIsAttack()==false){
            a++;
        }
    }
    if(a ==0){
        std::cout<<"No creature to attack with press a to leave"<<std::endl;
        return;
    }
    else {

        std::cout << "Enter Number Of Creature To Attack With" << std::endl;
        std::cin >> num;
        for (int i = 0; i < num - 1; i++) {
            birinciTasiyiciIteratoru2++;
        }
        ikinciTasiyici.push_back(*birinciTasiyiciIteratoru2);
        birinciTasiyiciIteratoru2 = birinciTasiyici.erase(birinciTasiyiciIteratoru2);
        std::vector<std::shared_ptr<card>>::iterator birinciTasiyiciIteratoru3 = birinciTasiyici.begin();
        for (int i = 0; i < birinciTasiyici.size(); i++) {

            first.getInplay().push_back(*birinciTasiyiciIteratoru3);
            birinciTasiyiciIteratoru3++;
        }
        int sayac = 0;


        std::cout << "Second Player, Do You Want To Defend?" << std::endl;
        if (second.getInplay().size() >= 0) {
            for (int i = 0; i < second.getInplay().size(); i++) {
                if (second.getInplay()[i]->getType() == "Creature" && second.getInplay()[i]->getTap() == true) {
                    sayac++;
                }
            }
            if (sayac > 0) {
                std::cout << "1 -> Yes, Pick A Card To Defend" << std::endl;
                std::cout << "2 -> No, Get Hit Directly" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            } else {
                std::cout << "2 -> No Defenders In Play, Get Hit Directly" << std::endl;
            }

        }
        int number2;
        std::cin >> number2;
        if (number2 == 1) {

            int number3;
            std::vector<std::shared_ptr<card>> ikinciOyuncuTasiyici;
            std::vector<std::shared_ptr<card>> ikinciOyuncuIkinciTasiyici;

            std::vector<std::shared_ptr<card>>::iterator ikinciOyuncuInplayIterator = second.getInplay().begin();
            std::vector<std::shared_ptr<card>>::iterator ikincioyuncuTasiyiciIteratoru = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < second.getInplay().size(); i++) {
                if (second.getInplay()[i]->getType() == "Creature" && second.getInplay()[i]->getTap() == true) {

                    ikinciOyuncuTasiyici.push_back(second.getInplay()[i]);
                    ikinciOyuncuInplayIterator = second.getInplay().erase(ikinciOyuncuInplayIterator);
                    i -= 1;

                } else { ikinciOyuncuInplayIterator++; }

            }
            std::vector<std::shared_ptr<card>>::iterator ikinciOyuncuTasiyiciIteratoru2 = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < ikinciOyuncuTasiyici.size(); i++) {
                std::cout << i + 1 << "--> ";
                ikinciOyuncuTasiyici[i]->cardInfo();
                std::cout << std::endl;
            }
            std::cout << "Enter Number Of Creature To Defend With" << std::endl;
            std::cin >> number3;
            for (int i = 0; i < number3 - 1; i++) {
                ikinciOyuncuTasiyiciIteratoru2++;
            }
            ikinciOyuncuIkinciTasiyici.push_back(*ikinciOyuncuTasiyiciIteratoru2);
            ikinciOyuncuTasiyiciIteratoru2 = ikinciOyuncuTasiyici.erase(ikinciOyuncuTasiyiciIteratoru2);
            std::vector<std::shared_ptr<card>>::iterator secondptr3 = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < ikinciOyuncuTasiyici.size(); i++) {

                second.getInplay().push_back(*secondptr3);

                secondptr3++;
            }
            std::vector<std::shared_ptr<card>>::iterator firstCreature;
            std::vector<std::shared_ptr<card>>::iterator secondCreature;
            firstCreature = ikinciTasiyici.begin();
            secondCreature = ikinciOyuncuIkinciTasiyici.begin();

            if (firstCreature[0]->getAbility() == "None" && firstCreature[0]->getAbility2() == "None" &&
                secondCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility2() == "None") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {
                    firstCreature[0]->setIsAttackTrue();
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);

                    std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setIsAttackTrue();
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setIsAttackTrue();
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << "Nobody Is Dead" << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }

                }

            } else if (firstCreature[0]->getAbility() == "First Strike" &&
                       secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample" && secondCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }
                } else if (firstCreature[0]->getAbility2() == "Trample" && secondCreature[0]->getAbility2() == "None") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {

                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                } else if (firstCreature[0]->getAbility2() == "None" && secondCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }
                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                }
            } else if (firstCreature[0]->getAbility() == "First Strike" && secondCreature[0]->getAbility() == "None") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {

                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }


                }
            } else if (firstCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample") {

                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                } else {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());

                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                        if (secondCreature[0]->getHP() <= 0) {
                            secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                            second.getGraveyard().push_back(secondCreature[0]);
                            first.getInplay().push_back(firstCreature[0]);

                            std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                }
            } else if (firstCreature[0]->getAbility() == "Trample" && secondCreature[0]->getAbility() == "None") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {

                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);
                    second.getHitByCreature(secondCreature[0]->getHP());
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is " << second.getHitPoint()
                              << std::endl;

                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << "Nobody Is Dead" << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }

                }

            } else if (firstCreature[0]->getAbility() == "Trample" && secondCreature[0]->getAbility() == "Trample") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {
                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);

                    second.getHitByCreature(secondCreature[0]->getHP());
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is " << second.getHitPoint()
                              << std::endl;
                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        first.getHitByCreature(firstCreature[0]->getHP());
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << first.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << "Nobody Is Dead" << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }

                }

            } else if (firstCreature[0]->getAbility() == "Trample" &&
                       secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (secondCreature[0]->getAbility2() == "None") {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());

                    if (firstCreature[0]->getHP() <= 0) {
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        std::cout << firstCreature[0]->getName() << " Is Dead " << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                        if (secondCreature[0]->getHP() <= 0) {
                            second.getGraveyard().push_back(secondCreature[0]);
                            first.getInplay().push_back(firstCreature[0]);

                            second.getHitByCreature(secondCreature[0]->getHP());
                            secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                            std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << second.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }
                }
            } else if (firstCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility() == "Trample") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "None") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead " << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead " << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }
                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                }


            }


        } else if (number2 = 2) {
            second.getHitByCreature(-ikinciTasiyici[0]->getAP());
            std::cout << "Enemy Player got hit by " << ikinciTasiyici[0]->getName() << " with "
                      << ikinciTasiyici[0]->getAP() << std::endl;
            ikinciTasiyici[0]->setIsAttackTrue();
            first.getInplay().push_back(ikinciTasiyici[0]);
            ikinciTasiyici.clear();
        }
    }
}


void setBaseHp(player &p){
    for(int i=0;i<p.getInplay().size();i++){
        if(p.getInplay()[i]->getType()=="Creature"){
            p.getInplay()[i]->setHPOf(p.getInplay()[i]->getBaseHp());
        }
        else{}
    }
}

void checkIfThereIsDead(player &first,player &second){

    std::vector<std::shared_ptr<card>>::iterator ptr1=first.getInplay().begin();
    for(int i=0;i<first.getInplay().size();i++){
        if(first.getInplay()[i]->getHP()<=0 && first.getInplay()[i]->getType() =="Creature")  {
            std::cout<<first.getInplay()[i]->getName()<<"' Is Dead"<<std::endl;
            first.getGraveyard().push_back(*ptr1);
            ptr1=first.getInplay().erase(ptr1);
            i-=1;
        }
        else{ptr1++;
        }
    }
    std::vector<std::shared_ptr<card>>::iterator ptr2=second.getInplay().begin();
    for(int i=0;i<second.getInplay().size();i++){
        if(second.getInplay()[i]->getHP()<=0 && second.getInplay()[i]->getType() =="Creature"){
            std::cout<<second.getInplay()[i]->getName()<<"' Is Dead"<<std::endl;
            second.getGraveyard().push_back(*ptr2);
            ptr2=second.getInplay().erase(ptr2);
            i-=1;
        }
        else{ptr2++;
        }
    }
}
int main() {

    std::srand(std::time(0));

    player Player1("Leo", 15, 0, 0, 0, 0, 0);
    player Player2("Sezar", 15, 0, 0, 0, 0, 0);

    std::vector<std::shared_ptr<card>> Library1;
    std::vector<std::shared_ptr<card>> Library2;


    std::shared_ptr<landCard> Plain1 = std::make_shared<landCard>("Land Card","Plain", "whiteMana");
    std::shared_ptr<landCard> Plain2 = std::make_shared<landCard>("Land Card","Plain", "whiteMana");
    std::shared_ptr<landCard> Plain3 = std::make_shared<landCard>("Land Card","Plain", "whiteMana");
    std::shared_ptr<landCard> Plain4 = std::make_shared<landCard>("Land Card","Plain", "whiteMana");
    std::shared_ptr<landCard> Plain5 = std::make_shared<landCard>("Land Card","Plain", "whiteMana");

    Library1.push_back(std::shared_ptr<landCard>(Plain1));
    Library1.push_back(std::shared_ptr<landCard>(Plain2));
    Library1.push_back(std::shared_ptr<landCard>(Plain3));
    Library1.push_back(std::shared_ptr<landCard>(Plain4));
    Library1.push_back(std::shared_ptr<landCard>(Plain5));

    std::shared_ptr<landCard> Forest1 = std::make_shared<landCard>("Land Card","Forest", "greenMana");
    std::shared_ptr<landCard> Forest2 = std::make_shared<landCard>("Land Card","Forest", "greenMana");
    std::shared_ptr<landCard> Forest3 = std::make_shared<landCard>("Land Card","Forest", "greenMana");
    Library1.push_back(std::shared_ptr<landCard>(Forest1));
    Library1.push_back(std::shared_ptr<landCard>(Forest2));
    Library1.push_back(std::shared_ptr<landCard>(Forest3));

    std::shared_ptr<landCard> Island11 = std::make_shared<landCard>("Land Card","Island", "blueMana");//1. oyuncunun 1. kartı
    Library1.push_back(std::shared_ptr<landCard>(Island11));


    std::shared_ptr<creature> Soldier1 = std::make_shared<creature>("Creature","Soldier", "whiteMana", "White", 1, 1, "None");
    std::shared_ptr<creature> Soldier2 = std::make_shared<creature>("Creature","Soldier", "whiteMana", "White", 1, 1, "None");
    std::shared_ptr<creature> Soldier3 = std::make_shared<creature>("Creature","Soldier", "whiteMana", "White", 1, 1, "None");
    Library1.push_back(std::shared_ptr<creature>(Soldier1));
    Library1.push_back(std::shared_ptr<creature>(Soldier2));
    Library1.push_back(std::shared_ptr<creature>(Soldier3));

    std::shared_ptr<creature> ArmoredPegasus1 = std::make_shared<creature>("Creature","Armored Pegasus", "whiteMana", "White", 1,
                                                                           2, "None");
    std::shared_ptr<creature> ArmoredPegasus2 = std::make_shared<creature>("Creature","Armored Pegasus", "whiteMana", "White", 1,
                                                                           2, "None");
    Library1.push_back(std::shared_ptr<creature>(ArmoredPegasus1));
    Library1.push_back(std::shared_ptr<creature>(ArmoredPegasus2));


    std::shared_ptr<creature> WhiteKnight1 = std::make_shared<creature>("Creature","White Knight", "whiteMana", "White", 2, 2,
                                                                        "FirstStrike");
    std::shared_ptr<creature> WhiteKnight2 = std::make_shared<creature>("Creature","White Knight", "whiteMana", "White", 2, 2,
                                                                        "FirstStrike");
    Library1.push_back(std::shared_ptr<creature>(WhiteKnight1));
    Library1.push_back(std::shared_ptr<creature>(WhiteKnight2));


    std::shared_ptr<creature> AngryBear1 = std::make_shared<creature>("Creature","Angry Bear", "greenMana", "Green", 3, 2,
                                                                      "Trample");
    Library1.push_back(std::shared_ptr<creature>(AngryBear1));

    std::shared_ptr<creature> Guard1 = std::make_shared<creature>("Creature","Guard", "whiteMana", "White", 2, 5, "None");
    Library1.push_back(std::shared_ptr<creature>(Guard1));

    std::shared_ptr<creature> Werewolf1 = std::make_shared<creature>("Creature","Werewolf", "greenMana", "Green", 4, 6, "Trample");
    Library1.push_back(std::shared_ptr<creature>(Werewolf1));
    auto disenchant1Effect=std::make_shared<effect>("Disenchant");
    std::shared_ptr<sorcery> Disenchant1 = std::make_shared<sorcery>("Sorcery","Disenchant", "whiteMana", "White",disenchant1Effect);
    Library1.push_back(std::shared_ptr<sorcery>(Disenchant1));
    auto lightningBolt1Effect=std::make_shared<effect>("Lightning Bolt");
    std::shared_ptr<sorcery> LigthningBolt1 = std::make_shared<sorcery>("Sorcery","Lightning Bolt", "greenMana", "Green",lightningBolt1Effect);
    Library1.push_back(std::shared_ptr<sorcery>(LigthningBolt1));
    auto floodEffect=std::make_shared<effect>("Flood");
    std::shared_ptr<sorcery> Flood1 = std::make_shared<sorcery>("Sorcery","Flood", "greenMana", "Green",floodEffect);
    std::shared_ptr<sorcery> Flood2 = std::make_shared<sorcery>("Sorcery","Flood", "greenMana", "Green",floodEffect);
    Library1.push_back(std::shared_ptr<sorcery>(Flood1));
    Library1.push_back(std::shared_ptr<sorcery>(Flood2));

    auto rage1Effect=std::make_shared<effect>("Rage");
    auto holyWar1Effect=std::make_shared<effect>("Holy War");
    auto holyLight1Effect=std::make_shared<effect>("Holy Light");
    std::shared_ptr<enchantment> Rage1 = std::make_shared<enchantment>("Enchantment","Rage", "blackMana", "Black", rage1Effect);
    std::shared_ptr<enchantment> HolyWar1 = std::make_shared<enchantment>("Enchantment","Holy War", "whiteMana", "White",holyWar1Effect);
    std::shared_ptr<enchantment> HolyLight1 = std::make_shared<enchantment>("Enchantment","Holy Light", "whiteMana", "White",holyLight1Effect);
    Library1.push_back(std::shared_ptr<enchantment>(Rage1));
    Library1.push_back(std::shared_ptr<enchantment>(HolyWar1));
    Library1.push_back(std::shared_ptr<enchantment>(HolyLight1));

    unsigned seed1 = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

    std::shuffle(std::begin(Library1), std::end(Library1),std::default_random_engine(seed1));



//player 1 destesi

    std::shared_ptr<landCard> Swamp1 = std::make_shared<landCard>("Land Card","Swamp", "blackMana");
    std::shared_ptr<landCard> Swamp2 = std::make_shared<landCard>("Land Card","Swamp", "blackMana");
    std::shared_ptr<landCard> Swamp3 = std::make_shared<landCard>("Land Card","Swamp", "blackMana");
    std::shared_ptr<landCard> Swamp4 = std::make_shared<landCard>("Land Card","Swamp", "blackMana");
    std::shared_ptr<landCard> Swamp5 = std::make_shared<landCard>("Land Card","Swamp", "blackMana");
    Library2.push_back(std::shared_ptr<landCard>(Swamp1));
    Library2.push_back(std::shared_ptr<landCard>(Swamp2));
    Library2.push_back(std::shared_ptr<landCard>(Swamp3));
    Library2.push_back(std::shared_ptr<landCard>(Swamp4));
    Library2.push_back(std::shared_ptr<landCard>(Swamp5));

    std::shared_ptr<landCard> Mountain1 = std::make_shared<landCard>("Land Card","Mountain", "redMana");
    std::shared_ptr<landCard> Mountain2 = std::make_shared<landCard>("Land Card","Mountain", "redMana");
    std::shared_ptr<landCard> Mountain3 = std::make_shared<landCard>("Land Card","Mountain", "redMana");
    Library2.push_back(std::shared_ptr<landCard>(Mountain1));
    Library2.push_back(std::shared_ptr<landCard>(Mountain2));
    Library2.push_back(std::shared_ptr<landCard>(Mountain3));

    std::shared_ptr<landCard> Island21 = std::make_shared<landCard>("Land Card","Island", "blueMana");//2. oyuncunun 1. kartı
    Library2.push_back(std::shared_ptr<landCard>(Island21));

    std::shared_ptr<creature> Skeleton1 = std::make_shared<creature>("Creature","Skeleton", "blackMana", "Black", 1, 1, "None");
    std::shared_ptr<creature> Skeleton2 = std::make_shared<creature>("Creature","Skeleton", "blackMana", "Black", 1, 1, "None");
    std::shared_ptr<creature> Skeleton3 = std::make_shared<creature>("Creature","Skeleton", "blackMana", "Black", 1, 1, "None");
    Library2.push_back(std::shared_ptr<creature>(Skeleton1));
    Library2.push_back(std::shared_ptr<creature>(Skeleton2));
    Library2.push_back(std::shared_ptr<creature>(Skeleton3));

    std::shared_ptr<creature> Ghost1 = std::make_shared<creature>("Creature","Ghost", "blackMana", "Black", 2, 1, "None");
    std::shared_ptr<creature> Ghost2 = std::make_shared<creature>("Creature","Ghost", "blackMana", "Black", 2, 1, "None");
    Library2.push_back(std::shared_ptr<creature>(Ghost1));
    Library2.push_back(std::shared_ptr<creature>(Ghost2));

    std::shared_ptr<creature> BlackKnight1 = std::make_shared<creature>("Creature","Black Knight", "blackMana", "Black", 2, 2,
                                                                        "FirstStrike");
    std::shared_ptr<creature> BlackKnight2 = std::make_shared<creature>("Creature","Black Knight", "blackMana", "Black", 2, 2,
                                                                        "FirstStrike");
    Library2.push_back(std::shared_ptr<creature>(BlackKnight1));
    Library2.push_back(std::shared_ptr<creature>(BlackKnight2));

    std::shared_ptr<creature> OrcManiac1 = std::make_shared<creature>("Creature","OrcManiac", "redMana", "Red", 4, 1, "None");
    Library2.push_back(std::shared_ptr<creature>(OrcManiac1));

    std::shared_ptr<creature> Hobgoblin1 = std::make_shared<creature>("Creature","Hobgoblin", "redMana", "Red", 3, 3, "None");
    Library2.push_back(std::shared_ptr<creature>(Hobgoblin1));

    std::shared_ptr<creature> Vampire1 = std::make_shared<creature>("Creature","Vampire", "blackMana", "Black", 6, 3, "None");
    Library2.push_back(std::shared_ptr<creature>(Vampire1));
    auto reanimateEffect=std::make_shared<effect>("Reanimate");
    std::shared_ptr<sorcery> Reanimate1 = std::make_shared<sorcery>("Sorcery","Reanimate", "blackMana", "Black",reanimateEffect);
    Library2.push_back(std::shared_ptr<sorcery>(Reanimate1));
    auto plagueEffect=std::make_shared<effect>("Plague");
    std::shared_ptr<sorcery> Plague1 = std::make_shared<sorcery>("Sorcery","Plague", "blackMana", "Black",plagueEffect);
    Library2.push_back(std::shared_ptr<sorcery>(Plague1));
    auto terrorEffect=std::make_shared<effect>("Terror");
    std::shared_ptr<sorcery> Terror1 = std::make_shared<sorcery>("Sorcery","Terror", "blackMana", "Black",terrorEffect);
    std::shared_ptr<sorcery> Terror2 = std::make_shared<sorcery>("Sorcery","Terror", "blackMana", "Black",terrorEffect);
    Library2.push_back(std::shared_ptr<sorcery>(Terror1));
    Library2.push_back(std::shared_ptr<sorcery>(Terror2));

    auto slow1Effect=std::make_shared<effect>("Slow");
    auto unholyWar1Effect=std::make_shared<effect>("Unholy War");
    auto restrain1Effect=std::make_shared<effect>("Restrain");
    std::shared_ptr<enchantment> UnholyWar1 = std::make_shared<enchantment>("Enchantment","Unholy War", "blackMana", "Black",unholyWar1Effect);
    Library2.push_back(std::shared_ptr<enchantment>(UnholyWar1));

    std::shared_ptr<enchantment> Restrain1 = std::make_shared<enchantment>("Enchantment","Restrain", "redMana", "Red",restrain1Effect);
    Library2.push_back(std::shared_ptr<enchantment>(Restrain1));

    std::shared_ptr<enchantment> Slow1 = std::make_shared<enchantment>("Enchantment","Slow", "blackMana", "Black",slow1Effect);
    Library2.push_back(std::shared_ptr<enchantment>(Slow1));

    unsigned seed2 = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();
    std::shuffle(std::begin(Library2), std::end(Library2),std::default_random_engine(seed2));


    //game starts
    Player1.copyLibrary(Library1);
    Player2.copyLibrary(Library2);

    Player1.giveFirstHand();
    Player2.giveFirstHand();
    std::vector<std::shared_ptr<card>>::iterator Hand;
    int turnNumber =1;

    std::string playCarda1;
    std::string playCardb1;
    std::string playCarda2;
    std::string playCardb2;
    std::string tapCard1;
    std::string tapCard2;
    std::string attack1;
    std::string attack2;
    bool landCardd1;
    bool landCardd2;


    while(true) {
        if(Player1.getLibrary().size() == 0){
            std::cout<<Player2.getName()<<" won the match!!!"<<std::endl;
            break;
        }

        Player1.drawCard();
        landCardd1 = false;
        std::cout << "Turn number " << turnNumber << std::endl;
        std::cout <<Player1.getName()<< "'s turn " << std::endl;
        std::cout<<"/==========================================/"<<std::endl;
        Player1.printInfo();
        std::cout<<"/==========================================/"<<std::endl;
        std::cout << "YOUR HAND: " << std::endl;
        for (int i = 0; i < Player1.getHand().size(); i++) {
            Player1.getHand()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        std::cout << "IN PLAY: " << std::endl;
        for (int i = 0; i < Player1.getInplay().size(); i++) {
            Player1.getInplay()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        std::cout << "All your cards untapped " << std::endl;
        std::cout<<"/==========================================/"<<std::endl;
        for (int i = 0; i < Player1.getInplay().size(); i++){
            Player1.getInplay()[i]->getUntapped();
        }
        while (playCarda1 != "a") {
            std::cout << "Play your cards" << std::endl;
            for (int i = 0; i < Player1.getHand().size(); i++) {
                std::cout << i + 1 << " -> " << Player1.getHand()[i]->getName() << std::endl;
            }
            std::cout << "a -> stop playing" << std::endl;
            std::cout << "t -> tap cards" << std::endl;
            std::cin >> playCarda1;

            if (playCarda1 == "1") {
                if (Player1.getHand()[0]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[0]->playCardToInPlay(Player1,1);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Rage"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Plague"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Disenchant"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Lightning Bolt"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Flood"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Reanimate"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Terror"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Holy War"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Holy Light"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Unholy War"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Restrain"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Slow"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }

                else {
                    Player1.getHand()[0]->spendMana(Player1,1);


                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "t"){
                while(tapCard1 != "b"){
                    std::cout<<"Tap your cards "<<std::endl;
                    for (int i = 0; i < Player1.getInplay().size(); i++) {
                        if (Player1.getInplay()[i]->getType()=="Land Card" || Player1.getInplay()[i]->getType()== "Creature") {
                            std::cout << i + 1 << " -> " << Player1.getInplay()[i]->getName() << std::endl;
                        }
                    }
                    std::cout << "b -> stop playing" << std::endl;
                    std::cin >> tapCard1;
                    if (tapCard1 == "1"){
                        if (Player1.getInplay()[0]->getTap()==true) {
                            Player1.getInplay()[0]->tapCard();
                            if(Player1.getInplay()[0]->getType()=="Land Card") {
                                Player1.getInplay()[0]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "2"){
                        if (Player1.getInplay()[1]->getTap()==true) {
                            Player1.getInplay()[1]->tapCard();
                            if(Player1.getInplay()[1]->getType()=="Land Card") {
                                Player1.getInplay()[1]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "3"){
                        if (Player1.getInplay()[2]->getTap()==true) {
                            Player1.getInplay()[2]->tapCard();
                            if(Player1.getInplay()[2]->getType()=="Land Card") {
                                Player1.getInplay()[2]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "4"){
                        if (Player1.getInplay()[3]->getTap()==true) {
                            Player1.getInplay()[3]->tapCard();
                            if(Player1.getInplay()[3]->getType()=="Land Card") {
                                Player1.getInplay()[3]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "5"){
                        if (Player1.getInplay()[4]->getTap()==true) {
                            Player1.getInplay()[4]->tapCard();
                            if(Player1.getInplay()[4]->getType()=="Land Card") {
                                Player1.getInplay()[4]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "6"){
                        if (Player1.getInplay()[5]->getTap()==true) {
                            Player1.getInplay()[5]->tapCard();
                            if(Player1.getInplay()[5]->getType()=="Land Card") {
                                Player1.getInplay()[5]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "7"){
                        if (Player1.getInplay()[6]->getTap()==true) {
                            Player1.getInplay()[6]->tapCard();
                            if(Player1.getInplay()[6]->getType()=="Land Card") {
                                Player1.getInplay()[6]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "8"){
                        if (Player1.getInplay()[7]->getTap()==true) {
                            Player1.getInplay()[7]->tapCard();
                            if(Player1.getInplay()[7]->getType()=="Land Card") {
                                Player1.getInplay()[7]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "9"){
                        if (Player1.getInplay()[8]->getTap()==true) {
                            Player1.getInplay()[8]->tapCard();
                            if(Player1.getInplay()[8]->getType()=="Land Card") {
                                Player1.getInplay()[8]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "10"){
                        if (Player1.getInplay()[9]->getTap()==true) {
                            Player1.getInplay()[9]->tapCard();
                            if(Player1.getInplay()[9]->getType()=="Land Card") {
                                Player1.getInplay()[9]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "11"){
                        if (Player1.getInplay()[10]->getTap()==true) {
                            Player1.getInplay()[10]->tapCard();
                            if(Player1.getInplay()[10]->getType()=="Land Card") {
                                Player1.getInplay()[10]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "12"){
                        if (Player1.getInplay()[11]->getTap()==true) {
                            Player1.getInplay()[11]->tapCard();
                            if(Player1.getInplay()[11]->getType()=="Land Card") {
                                Player1.getInplay()[11]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "13"){
                        if (Player1.getInplay()[12]->getTap()==true) {
                            Player1.getInplay()[12]->tapCard();
                            if(Player1.getInplay()[12]->getType()=="Land Card") {
                                Player1.getInplay()[12]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "14"){
                        if (Player1.getInplay()[13]->getTap()==true) {
                            Player1.getInplay()[13]->tapCard();
                            if(Player1.getInplay()[13]->getType()=="Land Card") {
                                Player1.getInplay()[13]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "15"){
                        if (Player1.getInplay()[14]->getTap()==true) {
                            Player1.getInplay()[14]->tapCard();
                            if(Player1.getInplay()[14]->getType()=="Land Card") {
                                Player1.getInplay()[14]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "16"){
                        if (Player1.getInplay()[15]->getTap()==true) {
                            Player1.getInplay()[15]->tapCard();
                            if(Player1.getInplay()[15]->getType()=="Land Card") {
                                Player1.getInplay()[15]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "17"){
                        if (Player1.getInplay()[16]->getTap()==true) {
                            Player1.getInplay()[16]->tapCard();
                            if(Player1.getInplay()[16]->getType()=="Land Card") {
                                Player1.getInplay()[16]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "18"){
                        if (Player1.getInplay()[17]->getTap()==true) {
                            Player1.getInplay()[17]->tapCard();
                            if(Player1.getInplay()[17]->getType()=="Land Card") {
                                Player1.getInplay()[17]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "19"){
                        if (Player1.getInplay()[18]->getTap()==true) {
                            Player1.getInplay()[18]->tapCard();
                            if(Player1.getInplay()[18]->getType()=="Land Card") {
                                Player1.getInplay()[18]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "20"){
                        if (Player1.getInplay()[19]->getTap()==true) {
                            Player1.getInplay()[19]->tapCard();
                            if(Player1.getInplay()[19]->getType()=="Land Card") {
                                Player1.getInplay()[19]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }

                }
                tapCard1="NULL";

            }

            else if (playCarda1 == "2") {


                //Player1.getHand()[1]->effect();
                if (Player1.getHand()[1]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[1]->playCardToInPlay(Player1,2);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Rage"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Plague"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Disenchant"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Lightning Bolt"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Flood"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Reanimate"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Terror"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Holy War"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Holy Light"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Unholy War"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Restrain"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Slow"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else {
                    Player1.getHand()[1]->spendMana(Player1,2);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "3") {
                //Player1.getHand()[2]->effect();
                if (Player1.getHand()[2]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[2]->playCardToInPlay(Player1,3);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Rage"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Plague"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Disenchant"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Lightning Bolt"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Flood"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Reanimate"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Terror"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Holy War"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Holy Light"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Unholy War"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Restrain"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Slow"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else {
                    Player1.getHand()[2]->spendMana(Player1,3);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "4") {
                //Player1.getHand()[3]->effect();
                if (Player1.getHand()[3]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[3]->playCardToInPlay(Player1,4);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Rage"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Plague"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Disenchant"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Lightning Bolt"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Flood"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Reanimate"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Terror"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Holy War"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Holy Light"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Unholy War"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Restrain"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Slow"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else {
                    Player1.getHand()[3]->spendMana(Player1,4);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "5") {
                //Player1.getHand()[4]->effect();
                if (Player1.getHand()[4]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[4]->playCardToInPlay(Player1,5);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Rage"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Plague"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Disenchant"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Lightning Bolt"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Flood"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Reanimate"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Terror"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Holy War"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Holy Light"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Unholy War"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Restrain"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Slow"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else {
                    Player1.getHand()[4]->spendMana(Player1,5);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "6") {

                //Player1.getHand()[5]->effect();
                if (Player1.getHand()[5]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[5]->playCardToInPlay(Player1,6);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Rage"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Plague"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Disenchant"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Lightning Bolt"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Flood"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Reanimate"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Terror"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Holy War"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Holy Light"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Unholy War"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Restrain"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Slow"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else {
                    Player1.getHand()[5]->spendMana(Player1,6);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCarda1 == "7") {
                //Player1.getHand()[6]->effect();
                if (Player1.getHand()[6]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[6]->playCardToInPlay(Player1,7);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Rage"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Plague"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Disenchant"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Lightning Bolt"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Flood"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Reanimate"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Terror"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Holy War"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Holy Light"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Unholy War"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Restrain"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Slow"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else {
                    Player1.getHand()[6]->spendMana(Player1,7);

                }
                checkIfThereIsDead(Player1,Player2);
            }
        }
        setBaseHp(Player1);
        setBaseHp(Player2);
        tapCard1="NULL";


        std::cout<<"Attack Phase!"<<std::endl;
        while (attack1 !="a") {
            std::cout << "Do you want attack" << std::endl;
            std::cout << "Yes -> b" << std::endl;
            std::cout << "No -> a" << std::endl;
            std::cin >> attack1;
            if (attack1 != "a") {
                attackCreatureOrOtherPlayer(Player1, Player2);
            }
            if(Player2.getHitPoint() <=0){
                std::cout<<Player1.getName()<<"' won the match"<<std::endl;
                return 0;
            }

            }


        setBaseHp(Player1);
        setBaseHp(Player2);
        std::cout<<"/==========================================/"<<std::endl;
        std::cout<<"Second Play Phase"<<std::endl;
        Player1.printInfo();
        std::cout<<"/==========================================/"<<std::endl;

        std::cout << "YOUR HAND: " << std::endl;
        for (int i = 0; i < Player1.getHand().size(); i++) {
            Player1.getHand()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        while (playCardb1 != "a") {
            std::cout << "Play your cards" << std::endl;
            for (int i = 0; i < Player1.getHand().size(); i++) {
                std::cout << i + 1 << " -> " << Player1.getHand()[i]->getName() << std::endl;
            }
            std::cout << "a -> stop playing" << std::endl;
            std::cout << "t -> tap cards" << std::endl;
            std::cin >> playCardb1;
            if (playCardb1 == "1") {
                if (Player1.getHand()[0]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[0]->playCardToInPlay(Player1,1);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Rage"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Plague"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Disenchant"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Lightning Bolt"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Flood"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Reanimate"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Terror"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Holy War"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Holy Light"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Unholy War"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Restrain"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }
                else if (Player1.getHand()[0]->getName()=="Slow"){
                    Player1.getHand()[0]->spendMana(Player1,1);
                    if (Player1.getHand()[0]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[0]);
                        Player1.getHand().erase(Player1.getHand().begin());
                    }
                }

                else {
                    Player1.getHand()[0]->spendMana(Player1,1);


                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "t"){
                while(tapCard1 != "b"){
                    std::cout<<"Tap your cards "<<std::endl;
                    for (int i = 0; i < Player1.getInplay().size(); i++) {
                        if (Player1.getInplay()[i]->getType()=="Land Card" || Player1.getInplay()[i]->getType()== "Creature") {
                            std::cout << i + 1 << " -> " << Player1.getInplay()[i]->getName() << std::endl;
                        }
                    }
                    std::cout << "b -> stop playing" << std::endl;
                    std::cin >> tapCard1;
                    if (tapCard1 == "1"){
                        if (Player1.getInplay()[0]->getTap()==true) {
                            Player1.getInplay()[0]->tapCard();
                            if(Player1.getInplay()[0]->getType()=="Land Card") {
                                Player1.getInplay()[0]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "2"){
                        if (Player1.getInplay()[1]->getTap()==true) {
                            Player1.getInplay()[1]->tapCard();
                            if(Player1.getInplay()[1]->getType()=="Land Card") {
                                Player1.getInplay()[1]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "3"){
                        if (Player1.getInplay()[2]->getTap()==true) {
                            Player1.getInplay()[2]->tapCard();
                            if(Player1.getInplay()[2]->getType()=="Land Card") {
                                Player1.getInplay()[2]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "4"){
                        if (Player1.getInplay()[3]->getTap()==true) {
                            Player1.getInplay()[3]->tapCard();
                            if(Player1.getInplay()[3]->getType()=="Land Card") {
                                Player1.getInplay()[3]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "5"){
                        if (Player1.getInplay()[4]->getTap()==true) {
                            Player1.getInplay()[4]->tapCard();
                            if(Player1.getInplay()[4]->getType()=="Land Card") {
                                Player1.getInplay()[4]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "6"){
                        if (Player1.getInplay()[5]->getTap()==true) {
                            Player1.getInplay()[5]->tapCard();
                            if(Player1.getInplay()[5]->getType()=="Land Card") {
                                Player1.getInplay()[5]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "7"){
                        if (Player1.getInplay()[6]->getTap()==true) {
                            Player1.getInplay()[6]->tapCard();
                            if(Player1.getInplay()[6]->getType()=="Land Card") {
                                Player1.getInplay()[6]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "8"){
                        if (Player1.getInplay()[7]->getTap()==true) {
                            Player1.getInplay()[7]->tapCard();
                            if(Player1.getInplay()[7]->getType()=="Land Card") {
                                Player1.getInplay()[7]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "9"){
                        if (Player1.getInplay()[8]->getTap()==true) {
                            Player1.getInplay()[8]->tapCard();
                            if(Player1.getInplay()[8]->getType()=="Land Card") {
                                Player1.getInplay()[8]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "10"){
                        if (Player1.getInplay()[9]->getTap()==true) {
                            Player1.getInplay()[9]->tapCard();
                            if(Player1.getInplay()[9]->getType()=="Land Card") {
                                Player1.getInplay()[9]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "11"){
                        if (Player1.getInplay()[10]->getTap()==true) {
                            Player1.getInplay()[10]->tapCard();
                            if(Player1.getInplay()[10]->getType()=="Land Card") {
                                Player1.getInplay()[10]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "12"){
                        if (Player1.getInplay()[11]->getTap()==true) {
                            Player1.getInplay()[11]->tapCard();
                            if(Player1.getInplay()[11]->getType()=="Land Card") {
                                Player1.getInplay()[11]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "13"){
                        if (Player1.getInplay()[12]->getTap()==true) {
                            Player1.getInplay()[12]->tapCard();
                            if(Player1.getInplay()[12]->getType()=="Land Card") {
                                Player1.getInplay()[12]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "14"){
                        if (Player1.getInplay()[13]->getTap()==true) {
                            Player1.getInplay()[13]->tapCard();
                            if(Player1.getInplay()[13]->getType()=="Land Card") {
                                Player1.getInplay()[13]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "15"){
                        if (Player1.getInplay()[14]->getTap()==true) {
                            Player1.getInplay()[14]->tapCard();
                            if(Player1.getInplay()[14]->getType()=="Land Card") {
                                Player1.getInplay()[14]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "16"){
                        if (Player1.getInplay()[15]->getTap()==true) {
                            Player1.getInplay()[15]->tapCard();
                            if(Player1.getInplay()[15]->getType()=="Land Card") {
                                Player1.getInplay()[15]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "17"){
                        if (Player1.getInplay()[16]->getTap()==true) {
                            Player1.getInplay()[16]->tapCard();
                            if(Player1.getInplay()[16]->getType()=="Land Card") {
                                Player1.getInplay()[16]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "18"){
                        if (Player1.getInplay()[17]->getTap()==true) {
                            Player1.getInplay()[17]->tapCard();
                            if(Player1.getInplay()[17]->getType()=="Land Card") {
                                Player1.getInplay()[17]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "19"){
                        if (Player1.getInplay()[18]->getTap()==true) {
                            Player1.getInplay()[18]->tapCard();
                            if(Player1.getInplay()[18]->getType()=="Land Card") {
                                Player1.getInplay()[18]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard1 == "20"){
                        if (Player1.getInplay()[19]->getTap()==true) {
                            Player1.getInplay()[19]->tapCard();
                            if(Player1.getInplay()[19]->getType()=="Land Card") {
                                Player1.getInplay()[19]->gainMana(Player1);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }

                }
                tapCard1="NULL";

            }

            else if (playCardb1 == "2") {


                //Player1.getHand()[1]->effect();
                if (Player1.getHand()[1]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[1]->playCardToInPlay(Player1,2);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Rage"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Plague"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Disenchant"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Lightning Bolt"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Flood"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Reanimate"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Terror"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Holy War"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Holy Light"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Unholy War"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Restrain"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else if (Player1.getHand()[1]->getName()=="Slow"){
                    Player1.getHand()[1]->spendMana(Player1,2);
                    if (Player1.getHand()[1]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[1]);
                        Player1.getHand().erase(Player1.getHand().begin()+1);
                    }
                }
                else {
                    Player1.getHand()[1]->spendMana(Player1,2);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "3") {
                //Player1.getHand()[2]->effect();
                if (Player1.getHand()[2]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[2]->playCardToInPlay(Player1,3);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Rage"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Plague"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Disenchant"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Lightning Bolt"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Flood"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Reanimate"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Terror"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Holy War"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Holy Light"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Unholy War"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Restrain"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else if (Player1.getHand()[2]->getName()=="Slow"){
                    Player1.getHand()[2]->spendMana(Player1,3);
                    if (Player1.getHand()[2]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[2]);
                        Player1.getHand().erase(Player1.getHand().begin()+2);
                    }
                }
                else {
                    Player1.getHand()[2]->spendMana(Player1,3);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "4") {
                //Player1.getHand()[3]->effect();
                if (Player1.getHand()[3]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[3]->playCardToInPlay(Player1,4);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Rage"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Plague"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Disenchant"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Lightning Bolt"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Flood"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Reanimate"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Terror"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Holy War"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Holy Light"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Unholy War"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Restrain"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else if (Player1.getHand()[3]->getName()=="Slow"){
                    Player1.getHand()[3]->spendMana(Player1,4);
                    if (Player1.getHand()[3]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[3]);
                        Player1.getHand().erase(Player1.getHand().begin()+3);
                    }
                }
                else {
                    Player1.getHand()[3]->spendMana(Player1,4);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "5") {
                //Player1.getHand()[4]->effect();
                if (Player1.getHand()[4]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[4]->playCardToInPlay(Player1,5);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Rage"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Plague"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Disenchant"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Lightning Bolt"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Flood"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Reanimate"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Terror"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Holy War"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Holy Light"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Unholy War"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Restrain"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else if (Player1.getHand()[4]->getName()=="Slow"){
                    Player1.getHand()[4]->spendMana(Player1,5);
                    if (Player1.getHand()[4]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[4]);
                        Player1.getHand().erase(Player1.getHand().begin()+4);
                    }
                }
                else {
                    Player1.getHand()[4]->spendMana(Player1,5);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "6") {

                //Player1.getHand()[5]->effect();
                if (Player1.getHand()[5]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[5]->playCardToInPlay(Player1,6);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Rage"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Plague"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Disenchant"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Lightning Bolt"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Flood"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Reanimate"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Terror"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Holy War"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Holy Light"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Unholy War"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Restrain"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else if (Player1.getHand()[5]->getName()=="Slow"){
                    Player1.getHand()[5]->spendMana(Player1,6);
                    if (Player1.getHand()[5]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[5]);
                        Player1.getHand().erase(Player1.getHand().begin()+5);
                    }
                }
                else {
                    Player1.getHand()[5]->spendMana(Player1,6);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else if (playCardb1 == "7") {
                //Player1.getHand()[6]->effect();
                if (Player1.getHand()[6]->getType() == "Land Card") {
                    if (landCardd1 == false) {

                        Player1.getHand()[6]->playCardToInPlay(Player1,7);
                        landCardd1 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Rage"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player1);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Plague"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player1,Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Disenchant"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Lightning Bolt"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Flood"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Reanimate"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player1);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Terror"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player2);
                        Player1.getGraveyard().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Holy War"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Holy Light"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Unholy War"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Restrain"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player1,Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else if (Player1.getHand()[6]->getName()=="Slow"){
                    Player1.getHand()[6]->spendMana(Player1,7);
                    if (Player1.getHand()[6]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player2);
                        Player1.getInplay().push_back(Player1.getHand()[6]);
                        Player1.getHand().erase(Player1.getHand().begin()+6);
                    }
                }
                else {
                    Player1.getHand()[6]->spendMana(Player1,7);

                }
                checkIfThereIsDead(Player1,Player2);
            }
            else{
                std::cout<<"Wrong input is given"<<std::endl;
            }
        }
        setBaseHp(Player1);
        setBaseHp(Player2);
        std::cout<<Player1.getName()<<"'s turn over"<<std::endl;
        Player1.turn0Mana();
        std::cout<<"/==========================================/"<<std::endl;
        landCardd2 = false;
        std::cout << "Turn number " << turnNumber << std::endl;
        std::cout <<Player2.getName()<< "'s turn " << std::endl;
        if(Player2.getLibrary().size() == 0){
            std::cout<<Player1.getName()<<" won the match!!!"<<std::endl;
            break;
        }
        Player2.drawCard();
        std::cout<<"/==========================================/"<<std::endl;
        Player2.printInfo();
        std::cout<<"/==========================================/"<<std::endl;
        std::cout << "YOUR HAND: " << std::endl;
        for (int i = 0; i < Player2.getHand().size(); i++) {
            Player2.getHand()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        std::cout << "IN PLAY: " << std::endl;
        for (int i = 0; i < Player2.getInplay().size(); i++) {
            Player2.getInplay()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        std::cout << "All your cards untapped " << std::endl;
        std::cout<<"/==========================================/"<<std::endl;
        for (int i = 0; i < Player2.getInplay().size(); i++){
            Player2.getInplay()[i]->getUntapped();
        }
        while (playCarda2 != "a") {
            std::cout << "Play your cards" << std::endl;
            for (int i = 0; i < Player2.getHand().size(); i++) {
                std::cout << i + 1 << " -> " << Player2.getHand()[i]->getName() << std::endl;
            }
            std::cout << "a -> stop playing" << std::endl;
            std::cout << "t -> tap cards" << std::endl;
            std::cin >> playCarda2;
            if (playCarda2 == "1") {
                //Player1.getHand()[0]->effect();
                if (Player2.getHand()[0]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[0]->playCardToInPlay(Player2,1);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Rage"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Plague"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Disenchant"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Lightning Bolt"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Flood"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Reanimate"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Terror"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Holy War"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Holy Light"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Unholy War"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Restrain"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Slow"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else {
                    Player2.getHand()[0]->spendMana(Player2,1);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "t"){
                while(tapCard2 != "b"){
                    std::cout<<"Tap your cards "<<std::endl;
                    for (int i = 0; i < Player2.getInplay().size(); i++) {
                        if (Player2.getInplay()[i]->getType()=="Land Card" || Player2.getInplay()[i]->getType()== "Creature") {
                            std::cout << i + 1 << " -> " << Player2.getInplay()[i]->getName() << std::endl;
                        }
                    }
                    std::cout << "b -> stop playing" << std::endl;
                    std::cin >> tapCard2;
                    if (tapCard2 == "1"){
                        if (Player2.getInplay()[0]->getTap()==true) {
                            Player2.getInplay()[0]->tapCard();
                            if(Player2.getInplay()[0]->getType()=="Land Card") {
                                Player2.getInplay()[0]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "2"){
                        if (Player2.getInplay()[1]->getTap()==true) {
                            Player2.getInplay()[1]->tapCard();
                            if(Player2.getInplay()[1]->getType()=="Land Card") {
                                Player2.getInplay()[1]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "3"){
                        if (Player2.getInplay()[2]->getTap()==true) {
                            Player2.getInplay()[2]->tapCard();
                            if(Player2.getInplay()[2]->getType()=="Land Card") {
                                Player2.getInplay()[2]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "4"){
                        if (Player2.getInplay()[3]->getTap()==true) {
                            Player2.getInplay()[3]->tapCard();
                            if(Player2.getInplay()[3]->getType()=="Land Card") {
                                Player2.getInplay()[3]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "5"){
                        if (Player2.getInplay()[4]->getTap()==true) {
                            Player2.getInplay()[4]->tapCard();
                            if(Player2.getInplay()[4]->getType()=="Land Card") {
                                Player2.getInplay()[4]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "6"){
                        if (Player2.getInplay()[5]->getTap()==true) {
                            Player2.getInplay()[5]->tapCard();
                            if(Player2.getInplay()[5]->getType()=="Land Card") {
                                Player2.getInplay()[5]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "7"){
                        if (Player2.getInplay()[6]->getTap()==true) {
                            Player2.getInplay()[6]->tapCard();
                            if(Player2.getInplay()[6]->getType()=="Land Card") {
                                Player2.getInplay()[6]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "8"){
                        if (Player2.getInplay()[7]->getTap()==true) {
                            Player2.getInplay()[7]->tapCard();
                            if(Player2.getInplay()[7]->getType()=="Land Card") {
                                Player2.getInplay()[7]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "9"){
                        if (Player2.getInplay()[8]->getTap()==true) {
                            Player2.getInplay()[8]->tapCard();
                            if(Player2.getInplay()[8]->getType()=="Land Card") {
                                Player2.getInplay()[8]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "10"){
                        if (Player2.getInplay()[9]->getTap()==true) {
                            Player2.getInplay()[9]->tapCard();
                            if(Player2.getInplay()[9]->getType()=="Land Card") {
                                Player2.getInplay()[9]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "11"){
                        if (Player2.getInplay()[10]->getTap()==true) {
                            Player2.getInplay()[10]->tapCard();
                            if(Player2.getInplay()[10]->getType()=="Land Card") {
                                Player2.getInplay()[10]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "12"){
                        if (Player2.getInplay()[11]->getTap()==true) {
                            Player2.getInplay()[11]->tapCard();
                            if(Player2.getInplay()[11]->getType()=="Land Card") {
                                Player2.getInplay()[11]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "13"){
                        if (Player2.getInplay()[12]->getTap()==true) {
                            Player2.getInplay()[12]->tapCard();
                            if(Player2.getInplay()[12]->getType()=="Land Card") {
                                Player2.getInplay()[12]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "14"){
                        if (Player2.getInplay()[13]->getTap()==true) {
                            Player2.getInplay()[13]->tapCard();
                            if(Player2.getInplay()[13]->getType()=="Land Card") {
                                Player2.getInplay()[13]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "15"){
                        if (Player2.getInplay()[14]->getTap()==true) {
                            Player2.getInplay()[14]->tapCard();
                            if(Player2.getInplay()[14]->getType()=="Land Card") {
                                Player2.getInplay()[14]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "16"){
                        if (Player2.getInplay()[15]->getTap()==true) {
                            Player2.getInplay()[15]->tapCard();
                            if(Player2.getInplay()[15]->getType()=="Land Card") {
                                Player2.getInplay()[15]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "17"){
                        if (Player2.getInplay()[16]->getTap()==true) {
                            Player2.getInplay()[16]->tapCard();
                            if(Player2.getInplay()[16]->getType()=="Land Card") {
                                Player2.getInplay()[16]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "18"){
                        if (Player2.getInplay()[17]->getTap()==true) {
                            Player2.getInplay()[17]->tapCard();
                            if(Player2.getInplay()[17]->getType()=="Land Card") {
                                Player2.getInplay()[17]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "19"){
                        if (Player2.getInplay()[18]->getTap()==true) {
                            Player2.getInplay()[18]->tapCard();
                            if(Player2.getInplay()[18]->getType()=="Land Card") {
                                Player2.getInplay()[18]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "20"){
                        if (Player2.getInplay()[19]->getTap()==true) {
                            Player2.getInplay()[19]->tapCard();
                            if(Player2.getInplay()[19]->getType()=="Land Card") {
                                Player2.getInplay()[19]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }

                }
                tapCard2="NULL";

            }

            else if (playCarda2 == "2") {


                //Player1.getHand()[1]->effect();
                if (Player2.getHand()[1]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[1]->playCardToInPlay(Player2,2);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Rage"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Plague"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Disenchant"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Lightning Bolt"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Flood"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Reanimate"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Terror"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Holy War"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Holy Light"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Unholy War"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Restrain"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Slow"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else {
                    Player2.getHand()[1]->spendMana(Player2,2);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "3") {
                //Player1.getHand()[2]->effect();
                if (Player2.getHand()[2]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[2]->playCardToInPlay(Player2,3);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Rage"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Plague"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Disenchant"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Lightning Bolt"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Flood"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Reanimate"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Terror"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Holy War"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Holy Light"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Unholy War"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Restrain"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Slow"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else {
                    Player2.getHand()[2]->spendMana(Player2,3);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "4") {
                //Player1.getHand()[3]->effect();
                if (Player2.getHand()[3]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[3]->playCardToInPlay(Player2,4);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Rage"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Plague"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Disenchant"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Lightning Bolt"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Flood"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Reanimate"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Terror"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Holy War"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Holy Light"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Unholy War"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Restrain"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Slow"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else {
                    Player2.getHand()[3]->spendMana(Player2,4);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "5") {
                //Player1.getHand()[4]->effect();
                if (Player2.getHand()[4]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[4]->playCardToInPlay(Player2,5);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Rage"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Plague"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Disenchant"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Lightning Bolt"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Flood"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Reanimate"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Terror"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Holy War"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Holy Light"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Unholy War"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Restrain"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Slow"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else {
                    Player2.getHand()[4]->spendMana(Player2,5);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "6") {

                //Player1.getHand()[5]->effect();
                if (Player2.getHand()[5]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[5]->playCardToInPlay(Player2,6);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Rage"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Plague"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Disenchant"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Lightning Bolt"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Flood"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Reanimate"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Terror"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Holy War"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Holy Light"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Unholy War"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Restrain"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);

                    }
                }
                else if (Player2.getHand()[5]->getName()=="Slow"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else {
                    Player2.getHand()[5]->spendMana(Player2,6);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCarda2 == "7") {
                //Player1.getHand()[6]->effect();
                if (Player2.getHand()[6]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[6]->playCardToInPlay(Player2,7);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Rage"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Plague"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Disenchant"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Lightning Bolt"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Flood"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Reanimate"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Terror"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Holy War"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Holy Light"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Unholy War"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Restrain"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Slow") {
                    Player2.getHand()[6]->spendMana(Player2, 7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else {
                    Player2.getHand()[6]->spendMana(Player2,7);

                }
                checkIfThereIsDead(Player2,Player1);
            }
        }
        setBaseHp(Player1);
        setBaseHp(Player2);
        tapCard2="NULL";



        std::cout<<"Attack Phase!"<<std::endl;
        while (attack2 !="a") {
            std::cout << "Do you want attack" << std::endl;
            std::cout << "Yes -> b" << std::endl;
            std::cout << "No -> a" << std::endl;
            std::cin >> attack2;
            if (attack2 != "a") {
                attackCreatureOrOtherPlayer(Player2, Player1);
            }
            if(Player1.getHitPoint() <=0){
                std::cout<<Player2.getName()<<"' won the match"<<std::endl;
                return 0;
            }

        }
        setBaseHp(Player1);
        setBaseHp(Player2);
        std::cout<<"/==========================================/"<<std::endl;
        std::cout<<"Second Play Phase"<<std::endl;

        std::cout << "YOUR HAND: " << std::endl;
        for (int i = 0; i < Player2.getHand().size(); i++) {
            Player2.getHand()[i]->cardInfo();
            std::cout<<"/==========================================/"<<std::endl;
        }
        while (playCardb2 != "a") {
            std::cout << "Play your cards" << std::endl;
            for (int i = 0; i < Player2.getHand().size(); i++) {
                std::cout << i + 1 << " -> " << Player2.getHand()[i]->getName() << std::endl;
            }
            std::cout << "a -> stop playing" << std::endl;
            std::cout << "t -> tap cards" << std::endl;
            std::cin >> playCardb2;
            if (playCardb2 == "1") {
                //Player1.getHand()[0]->effect();
                if (Player2.getHand()[0]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[0]->playCardToInPlay(Player2,1);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Rage"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Plague"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Disenchant"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Lightning Bolt"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Flood"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Reanimate"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Terror"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Holy War"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Holy Light"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Unholy War"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Restrain"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else if (Player2.getHand()[0]->getName()=="Slow"){
                    Player2.getHand()[0]->spendMana(Player2,1);
                    if (Player2.getHand()[0]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[0]);
                        Player2.getHand().erase(Player2.getHand().begin());
                    }
                }
                else {
                    Player2.getHand()[0]->spendMana(Player2,1);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "t"){
                while(tapCard2 != "b"){
                    std::cout<<"Tap your cards "<<std::endl;
                    for (int i = 0; i < Player2.getInplay().size(); i++) {
                        if (Player2.getInplay()[i]->getType()=="Land Card" || Player2.getInplay()[i]->getType()== "Creature") {
                            std::cout << i + 1 << " -> " << Player2.getInplay()[i]->getName() << std::endl;
                        }
                    }
                    std::cout << "b -> stop playing" << std::endl;
                    std::cin >> tapCard2;
                    if (tapCard2 == "1"){
                        if (Player2.getInplay()[0]->getTap()==true) {
                            Player2.getInplay()[0]->tapCard();
                            if(Player2.getInplay()[0]->getType()=="Land Card") {
                                Player2.getInplay()[0]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "2"){
                        if (Player2.getInplay()[1]->getTap()==true) {
                            Player2.getInplay()[1]->tapCard();
                            if(Player2.getInplay()[1]->getType()=="Land Card") {
                                Player2.getInplay()[1]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "3"){
                        if (Player2.getInplay()[2]->getTap()==true) {
                            Player2.getInplay()[2]->tapCard();
                            if(Player2.getInplay()[2]->getType()=="Land Card") {
                                Player2.getInplay()[2]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "4"){
                        if (Player2.getInplay()[3]->getTap()==true) {
                            Player2.getInplay()[3]->tapCard();
                            if(Player2.getInplay()[3]->getType()=="Land Card") {
                                Player2.getInplay()[3]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "5"){
                        if (Player2.getInplay()[4]->getTap()==true) {
                            Player2.getInplay()[4]->tapCard();
                            if(Player2.getInplay()[4]->getType()=="Land Card") {
                                Player2.getInplay()[4]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "6"){
                        if (Player2.getInplay()[5]->getTap()==true) {
                            Player2.getInplay()[5]->tapCard();
                            if(Player2.getInplay()[5]->getType()=="Land Card") {
                                Player2.getInplay()[5]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "7"){
                        if (Player2.getInplay()[6]->getTap()==true) {
                            Player2.getInplay()[6]->tapCard();
                            if(Player2.getInplay()[6]->getType()=="Land Card") {
                                Player2.getInplay()[6]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "8"){
                        if (Player2.getInplay()[7]->getTap()==true) {
                            Player2.getInplay()[7]->tapCard();
                            if(Player2.getInplay()[7]->getType()=="Land Card") {
                                Player2.getInplay()[7]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "9"){
                        if (Player2.getInplay()[8]->getTap()==true) {
                            Player2.getInplay()[8]->tapCard();
                            if(Player2.getInplay()[8]->getType()=="Land Card") {
                                Player2.getInplay()[8]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "10"){
                        if (Player2.getInplay()[9]->getTap()==true) {
                            Player2.getInplay()[9]->tapCard();
                            if(Player2.getInplay()[9]->getType()=="Land Card") {
                                Player2.getInplay()[9]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "11"){
                        if (Player2.getInplay()[10]->getTap()==true) {
                            Player2.getInplay()[10]->tapCard();
                            if(Player2.getInplay()[10]->getType()=="Land Card") {
                                Player2.getInplay()[10]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "12"){
                        if (Player2.getInplay()[11]->getTap()==true) {
                            Player2.getInplay()[11]->tapCard();
                            if(Player2.getInplay()[11]->getType()=="Land Card") {
                                Player2.getInplay()[11]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "13"){
                        if (Player2.getInplay()[12]->getTap()==true) {
                            Player2.getInplay()[12]->tapCard();
                            if(Player2.getInplay()[12]->getType()=="Land Card") {
                                Player2.getInplay()[12]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "14"){
                        if (Player2.getInplay()[13]->getTap()==true) {
                            Player2.getInplay()[13]->tapCard();
                            if(Player2.getInplay()[13]->getType()=="Land Card") {
                                Player2.getInplay()[13]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "15"){
                        if (Player2.getInplay()[14]->getTap()==true) {
                            Player2.getInplay()[14]->tapCard();
                            if(Player2.getInplay()[14]->getType()=="Land Card") {
                                Player2.getInplay()[14]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "16"){
                        if (Player2.getInplay()[15]->getTap()==true) {
                            Player2.getInplay()[15]->tapCard();
                            if(Player2.getInplay()[15]->getType()=="Land Card") {
                                Player2.getInplay()[15]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "17"){
                        if (Player2.getInplay()[16]->getTap()==true) {
                            Player2.getInplay()[16]->tapCard();
                            if(Player2.getInplay()[16]->getType()=="Land Card") {
                                Player2.getInplay()[16]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "18"){
                        if (Player2.getInplay()[17]->getTap()==true) {
                            Player2.getInplay()[17]->tapCard();
                            if(Player2.getInplay()[17]->getType()=="Land Card") {
                                Player2.getInplay()[17]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "19"){
                        if (Player2.getInplay()[18]->getTap()==true) {
                            Player2.getInplay()[18]->tapCard();
                            if(Player2.getInplay()[18]->getType()=="Land Card") {
                                Player2.getInplay()[18]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }
                    else if (tapCard2 == "20"){
                        if (Player2.getInplay()[19]->getTap()==true) {
                            Player2.getInplay()[19]->tapCard();
                            if(Player2.getInplay()[19]->getType()=="Land Card") {
                                Player2.getInplay()[19]->gainMana(Player2);
                            }
                        }
                        else{
                            std::cout<<"You have already tapped this card"<<std::endl;
                        }
                    }

                }
                tapCard2="NULL";

            }

            else if (playCardb2 == "2") {


                //Player1.getHand()[1]->effect();
                if (Player2.getHand()[1]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[1]->playCardToInPlay(Player2,2);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Rage"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Plague"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Disenchant"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Lightning Bolt"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Flood"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Reanimate"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Terror"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Holy War"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Holy Light"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Unholy War"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Restrain"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else if (Player2.getHand()[1]->getName()=="Slow"){
                    Player2.getHand()[1]->spendMana(Player2,2);
                    if (Player2.getHand()[1]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[1]);
                        Player2.getHand().erase(Player2.getHand().begin()+1);
                    }
                }
                else {
                    Player2.getHand()[1]->spendMana(Player2,2);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "3") {
                //Player1.getHand()[2]->effect();
                if (Player2.getHand()[2]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[2]->playCardToInPlay(Player2,3);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Rage"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Plague"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Disenchant"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Lightning Bolt"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Flood"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Reanimate"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Terror"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Holy War"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Holy Light"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Unholy War"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Restrain"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else if (Player2.getHand()[2]->getName()=="Slow"){
                    Player2.getHand()[2]->spendMana(Player2,3);
                    if (Player2.getHand()[2]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[2]);
                        Player2.getHand().erase(Player2.getHand().begin()+2);
                    }
                }
                else {
                    Player2.getHand()[2]->spendMana(Player2,3);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "4") {
                //Player1.getHand()[3]->effect();
                if (Player2.getHand()[3]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[3]->playCardToInPlay(Player2,4);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Rage"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Plague"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Disenchant"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Lightning Bolt"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Flood"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Reanimate"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Terror"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Holy War"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Holy Light"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Unholy War"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Restrain"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else if (Player2.getHand()[3]->getName()=="Slow"){
                    Player2.getHand()[3]->spendMana(Player2,4);
                    if (Player2.getHand()[3]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[3]);
                        Player2.getHand().erase(Player2.getHand().begin()+3);
                    }
                }
                else {
                    Player2.getHand()[3]->spendMana(Player2,4);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "5") {
                //Player1.getHand()[4]->effect();
                if (Player2.getHand()[4]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[4]->playCardToInPlay(Player2,5);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Rage"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Plague"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Disenchant"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Lightning Bolt"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Flood"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Reanimate"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Terror"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Holy War"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Holy Light"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Unholy War"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Restrain"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else if (Player2.getHand()[4]->getName()=="Slow"){
                    Player2.getHand()[4]->spendMana(Player2,5);
                    if (Player2.getHand()[4]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[4]);
                        Player2.getHand().erase(Player2.getHand().begin()+4);
                    }
                }
                else {
                    Player2.getHand()[4]->spendMana(Player2,5);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "6") {

                //Player1.getHand()[5]->effect();
                if (Player2.getHand()[5]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[5]->playCardToInPlay(Player2,6);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Rage"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Plague"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Disenchant"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Lightning Bolt"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Flood"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Reanimate"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Terror"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Holy War"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Holy Light"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Unholy War"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else if (Player2.getHand()[5]->getName()=="Restrain"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);

                    }
                }
                else if (Player2.getHand()[5]->getName()=="Slow"){
                    Player2.getHand()[5]->spendMana(Player2,6);
                    if (Player2.getHand()[5]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[5]);
                        Player2.getHand().erase(Player2.getHand().begin()+5);
                    }
                }
                else {
                    Player2.getHand()[5]->spendMana(Player2,6);

                }
                checkIfThereIsDead(Player2,Player1);
            }
            else if (playCardb2 == "7") {
                //Player1.getHand()[6]->effect();
                if (Player2.getHand()[6]->getType() == "Land Card") {
                    if (landCardd2 == false) {

                        Player2.getHand()[6]->playCardToInPlay(Player2,7);
                        landCardd2 = true;
                    }
                    else {
                        std::cout << "You can't play more than one land card in one turn" << std::endl;
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Rage"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        rage1Effect->rageEffect(Player2);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Plague"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        plagueEffect->plagueEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Disenchant"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        disenchant1Effect->disenchantEffect(Player2,Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Lightning Bolt"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        lightningBolt1Effect->lightingBoltEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Flood"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        floodEffect->floodEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Reanimate"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        reanimateEffect->reanimateEffect(Player2);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Terror"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        terrorEffect->terrorEffect(Player1);
                        Player2.getGraveyard().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Holy War"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        holyWar1Effect->holyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Holy Light"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        holyLight1Effect->holyLightEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Unholy War"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        unholyWar1Effect->unholyWarEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Restrain"){
                    Player2.getHand()[6]->spendMana(Player2,7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        restrain1Effect->restrainEffect(Player2,Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else if (Player2.getHand()[6]->getName()=="Slow") {
                    Player2.getHand()[6]->spendMana(Player2, 7);
                    if (Player2.getHand()[6]->getisPlayed() == true) {
                        slow1Effect->slowEffect(Player1);
                        Player2.getInplay().push_back(Player2.getHand()[6]);
                        Player2.getHand().erase(Player2.getHand().begin()+6);
                    }
                }
                else {
                    Player2.getHand()[6]->spendMana(Player2,7);

                }
                checkIfThereIsDead(Player2,Player1);
            }
        }
        for (int i = 0; i < Player2.getInplay().size(); i++) {
            Player2.getInplay()[i]->setIsAttackFalse();

        }
        for (int i = 0; i < Player1.getInplay().size(); i++) {
            Player1.getInplay()[i]->setIsAttackFalse();
        }
        setBaseHp(Player1);
        setBaseHp(Player2);
        std::cout<<Player2.getName()<<"'s turn is over"<<std::endl;
        Player2.turn0Mana();
        playCarda1="NULL";
        playCardb1="NULL";
        playCarda2="NULL";
        playCardb2="NULL";
        tapCard1="NULL";
        tapCard2="NULL";
        attack1="NULL";
        attack2="NULL";
        turnNumber++;



    }








    return 0;
}

