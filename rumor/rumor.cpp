#include <iostream>
#include <fstream>
#include <sstream>

#include <queue>
#include <vector>
#include <unordered_map>

#include <utility>
#include <algorithm>

using namespace std;
using friendmap = unordered_map<int, vector<int>>;

ifstream inp("rumor.inp", ios::binary);
ofstream out("rumor.out", ios::binary);
istringstream iss;
ostringstream oss;

friendmap graph;
queue<int> curQ, tempQ;
vector<int> chkRumor;

class rumor {
    vector<int> friends;
    string temp;
    int name=0, f=0, numF=0, begNum=0, endDay=0;
public:
    rumor() {
        getline(inp, temp);
        iss.str(temp);
        iss >> numF >> begNum >> endDay;
        iss.clear();
        chkRumor = vector<int>(numF+1, 0);
    }

    void setFrdmap() {
        while(getline(inp,temp)){
            iss.str(temp);
            iss >> name;
            while(iss >> f){
                if(f==0) break;
                friends.push_back(f);
            }
            sort(friends.begin(), friends.end());
            graph.emplace(name,friends);
            friends.clear();
            iss.clear();
        }
    }

    void setOrd(){
        int cntDay=0;

        curQ.push(begNum);
        oss << begNum << '\n';
        if(begNum<1 || begNum>numF)
            return;
        chkRumor[begNum] = 1;
        while(cntDay < endDay){
            while(!curQ.empty()){
                for(auto ppl:graph[curQ.front()]){
                    if(!chkRumor[ppl]){
                        chkRumor[ppl]=1;
                        tempQ.push(ppl);
                        oss << ppl << '\n';
                    }
                }
                curQ.pop();
            }
            curQ = tempQ;
            cntDay++;
        }
    }

    void getOrd(){
        temp = oss.str();
        temp.pop_back();
        out << temp;
    }
};

int main()
{
    rumor solv;
    solv.setFrdmap();
    solv.setOrd();
    solv.getOrd();
    inp.close();
    out.close();
    return EXIT_SUCCESS;
}