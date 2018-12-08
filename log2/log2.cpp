#include <fstream>
#include <sstream>

#include <string>
#include <set>
#include <array>
#include <list>

#include <algorithm>
#include <utility>
#include <iterator>

#define FOR(i, b, e) for((i)=(b); (i)<(e); ++(i))
#define ALL(x) (x).begin(), (x).end()

#define psb push_back
#define epb emplace_back
#define pb pop_back
#define uid first // user id
#define utlog second // user time log
enum {B, E}; // begin, end

using namespace std;

using lli = long long;

using ids = set<lli>;
using range = array<lli, 2>;
using logs = pair<lli,range>;

ids idlist;
range logtime;
list<logs> loglist;
list<lli> questlist;

int main()
{
    lli idNum = 0, questNum = 0, id = 0, quest = 0;
    ostringstream oss;
    string id_result;

    ifstream ifs("log.inp", ios::binary);
    ofstream ofs("log.out", ios::binary);
    if(!ifs.is_open()){
        ofs << "missing input file...";
        ofs.close();
        return EXIT_FAILURE;
    }

    ifs >> idNum >> questNum;
    while(idNum > 0 && (ifs >> id >> logtime[B] >> logtime[E])){
        loglist.epb(id, logtime);
        idNum--;
    
    while(questNum > 0 && ifs >> quest){
        questlist.psb(quest);
        questNum--;
    }

    auto lit = loglist.begin();
    auto fit = loglist.end();
    for(auto qit : questlist){
        for(auto lit : loglist){
            if(lit.utlog[B] <= qit && qit <= lit.utlog[E])
                idlist.insert(lit.uid);
        }
        if(idlist.empty())
            idlist.insert(0);
        copy(idlist.begin(),idlist.end(),ostream_iterator<lli>(oss, " "));
        id_result += oss.str();
        id_result += '\n';
        oss.str("");
        oss.clear();
        idlist.clear();
    }
    id_result.pb();
    ofs << id_result;

    ifs.close();
    ofs.close();
    return EXIT_SUCCESS;
}
