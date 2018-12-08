#include <fstream>

#include <list>
#include <string>

#include <algorithm>
#include <iterator>

#define FOR(i,b,e) for((i)=(b); (i)<=(e); ++(i))

using namespace std;

using deck = list<int>; // 'deck' comes from deck of cards.

deck operator+(const deck& a, const deck& b)
{
    deck result(a.cbegin(), a.cend());
    result.insert(result.cend(), b.cbegin(), b.cend());
    return result;
}

class cardPack{
    deck card, toHalf, fromHalf;
    int cardNum=0, topCard=0, midCard=0, bottomCard=0, midPoint=0;
public:
    explicit cardPack(int n){
        cardNum = n;
        midPoint = (cardNum%2==0) ? cardNum/2 : cardNum/2+1;

        int i;
        FOR(i,1,cardNum/2)
            toHalf.push_back(i); // 1 2 3 4 5 6 7 8 ... cardNum/2
        FOR(i,cardNum/2+1,cardNum)
            fromHalf.push_back(i); // cardNum/2+1, cardNum/2+2, ..., cardNum
        card = toHalf+fromHalf;
    }
    void shuffle() {
        int cnt=0; // counting cards...

        if(!card.empty()) card.clear();

        card = move(toHalf); // move() function make "toHalf" list clear.
        auto shufflePos = card.begin();
        while(shufflePos!=card.end()) // cards in fromHalf deck goes to cards' intervals.
            card.splice(++shufflePos, fromHalf, fromHalf.begin());

        while(!fromHalf.empty()) // if "fromHalf" deck has more cards than "toHalf"deck
            card.splice(shufflePos, fromHalf, fromHalf.begin());
            // shufflePos == card.end()

        // ...Setting halves...
        for(auto it:card){
            if(cnt<midPoint)
                toHalf.push_back(it);
            else
                fromHalf.push_back(it);
            cnt++;
        }
        topCard = toHalf.front();
        midCard = *(next(card.begin(), cardNum/2-1));
        bottomCard = fromHalf.back();
    }

    void cut(int b, int e){
        toHalf.clear();
        fromHalf.clear();
        // clear previous decks to reset halves...

        int cnt = 0; // counting cards...

        auto cardPos = card.begin();
        auto begPos = next(cardPos, b-1);
        auto endPos = next(cardPos, e);
        // next(iter, int) function returns iterator come from advance(iter, int).

        card.splice(card.end(),card, begPos, endPos);

        // ...Setting halves...
        for(auto it:card){
            if(cnt<midPoint)
                toHalf.push_back(it);
            else
                fromHalf.push_back(it);
            cnt++;
        }
        topCard = toHalf.front();
        midCard = *(next(card.begin(), cardNum/2-1));
        bottomCard = fromHalf.back();
    }

    friend ofstream& operator<<(ofstream& ofs, const cardPack& c) {
        ofs << c.topCard << ' ' << c.midCard << ' ' << c.bottomCard;
        return ofs;
    }
};

int main()
{
    ifstream ifs("card.inp", ios::binary);
    ofstream ofs("card.out", ios::binary);
    int getNum, operNum, cutBeg, cutEnd;
    string cmd; // command

    ifs >> getNum >> operNum;

    cardPack pack(getNum);
    while(ifs >> cmd){
        if(cmd == "Shuffle"){
            pack.shuffle();
        }
        else if(cmd == "Cut"){
            ifs >> cutBeg >> cutEnd;
            pack.cut(cutBeg,cutEnd);
        }
    }
    ofs << pack;
    return 0;
}
