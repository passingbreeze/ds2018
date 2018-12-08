#include <iostream>
#include <fstream>
#include <sstream>

#include <queue>
#include <vector>

#include <iterator>
#include <algorithm>
#include <utility>

#define bckFOR(i,e,b) for((i)=((e)-1); (i)>=(b); --(i))
enum {BUYMIN=10, BUYMAX=20};
using namespace std;

using uint = unsigned int;
using cstm = pair<uint, uint>; // customer information
using recept = queue<cstm>; // receptionist queue

ifstream ifs("shopping.inp", ios::binary);
ofstream ofs("shopping.out", ios::binary);
ostringstream oss;

vector<recept> total;

int i;
uint ppl, recNum, id, buyNum,temp, cnt;
string result;

struct shop {
    shop() {
        ifs >> ppl >> recNum;
        total=vector<recept>(recNum, recept());
        for(i=0;i<recNum && (ifs >> id >> buyNum); ++i)
            total[i].emplace(cstm(buyNum,id));
    }
    void setQ() {
        while(ifs >> id >> buyNum){
            auto minPos = min_element(total.begin(), total.end(), [](const recept& a, const recept& b){
                return a.back().first < b.back().first;
            });
            buyNum += minPos->back().first;
            minPos->emplace(cstm(buyNum, id));
        }
    }
    void getOrd() {
        cnt = 0;
        while(cnt < ppl){
            temp = BUYMAX*(ppl+1);
            bckFOR(i,recNum,0){
                if(!total[i].empty()){
                    if(temp > total[i].front().first){
                        temp = total[i].front().first;
                    }
                }
            }
            bckFOR(i,recNum,0){
                if(!total[i].empty()){
                    if(temp == total[i].front().first){
                        oss << total[i].front().second << '\n';
                        total[i].pop();
                        break;
                    }
                }
            }
            cnt++;
        }
        result = oss.str();
        result.pop_back();
    }
};

int main(){
    shop solv;
    solv.setQ();
    solv.getOrd();
    ofs << result;
    return EXIT_SUCCESS;
}