#include <iostream>
#include<array>
#include<ctime>

enum class Mast
{
    TREF,BUBNY,CHERVI,PIKI,
    TOTALMAST
};


enum class Dostoinstvo
{
    DVA,TREE,CHETIRI,FIVE,SIXE,SEVEN,ETHE,NINE,TEN,
    VALET,DAMA,KING,TUZ,

    TOTALDOSTOINSTVO
};

struct Card
{
    Mast mast;
    Dostoinstvo dostoinstvo;
};

void printCard(const Card &card)
{
    switch(card.mast)
    {
        case(Mast::TREF): std::cout<<"TREF ";break;
        case(Mast::BUBNY): std::cout<<"BUBNY ";break;
        case(Mast::CHERVI): std::cout<<"CHERVI ";break;
        case(Mast::PIKI): std::cout<<"PIKI ";break;
    }

    if(card.dostoinstvo==Dostoinstvo::DVA)
        std::cout<<"DVA ";
    if(card.dostoinstvo==Dostoinstvo::TREE)
        std::cout<<"TREE ";
    if(card.dostoinstvo==Dostoinstvo::CHETIRI)
        std::cout<<"CHETIRI ";
    if(card.dostoinstvo==Dostoinstvo::FIVE)
        std::cout<<"FIVE ";
    if(card.dostoinstvo==Dostoinstvo::SIXE)
        std::cout<<"SIXE ";
    if(card.dostoinstvo==Dostoinstvo::SEVEN)
        std::cout<<"SEVEN ";
    if(card.dostoinstvo==Dostoinstvo::ETHE)
        std::cout<<"ETHE ";
    if(card.dostoinstvo==Dostoinstvo::NINE)
        std::cout<<"NINE ";
    if(card.dostoinstvo==Dostoinstvo::TEN)
        std::cout<<"TEN ";

    if(card.dostoinstvo==Dostoinstvo::VALET)
        std::cout<<"VALET ";
    if(card.dostoinstvo==Dostoinstvo::DAMA)
        std::cout<<"DAMA ";
    if(card.dostoinstvo==Dostoinstvo::KING)
        std::cout<<"KING ";
    if(card.dostoinstvo==Dostoinstvo::TUZ)
        std::cout<<"TUZ ";
}

 void printDeck(const std::array<Card,52> &desk)
 {
    for(int i=0;i<desk.size();++i)
    {
        printCard(desk.at(i));
        std::cout<<std::endl;
    }
 }

 void swapCard(Card *card1,Card *card2)
 {
    Card temp=*(card1);
    *card1=*card2;
    *card2=temp;
 }

 int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

 void shuffleDeck(std::array<Card,52> &desk)
 {
    for (int i=0;i<52;++i)
        swapCard(&desk[i],&desk[getRandomNumber(0,51)]);
 }

 int getCardValue(const Card &card)
 {
    switch(card.dostoinstvo)
    {

        case(Dostoinstvo::TUZ):
            return 11;

        case(Dostoinstvo::DAMA):
        case(Dostoinstvo::KING):
        case(Dostoinstvo::VALET):
        case(Dostoinstvo::TEN):
            return 10;

        case(Dostoinstvo::NINE):
            return 9;

        case(Dostoinstvo::ETHE):
            return 8;

        case(Dostoinstvo::SEVEN):
            return 7;

        case(Dostoinstvo::SIXE):
            return 6;

        case(Dostoinstvo::FIVE):
            return 5;

        case(Dostoinstvo::CHETIRI):
            return 4;

        case(Dostoinstvo::TREE):
            return 3;

        case(Dostoinstvo::DVA):
            return 2;
    }
    return 0;
 }

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::array<Card,52>desk{};

    int index{0};

    for(int i=0;i<(static_cast<int>(Dostoinstvo::TOTALDOSTOINSTVO));++i)
    {
        for(int j=0;j<(static_cast<int>(Mast::TOTALMAST));++j)
        {
            desk[index].mast=static_cast<Mast>(j);
            desk[index].dostoinstvo=static_cast<Dostoinstvo>(i);
            ++index;
        }
    }

   shuffleDeck(desk);
   printDeck(desk);

   std::cout<<std::endl;

    return 0;
}