#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#define FOR(i,b,e) for((i)=(b);(i)<(e);++(i))

using namespace std;
using uint=unsigned;

ifstream inp("function.inp",ios::binary);
ofstream out("function.out",ios::binary);

vector<string> stmt, result(2,"NONE\n");
vector<uint> chkDlock;
vector<vector<string>> func;

stack<string> mainMem;
stack<string> fStmt;
stack<uint> curPos;
stack<string> retSig;

enum {MAIN=0, NAME=0, FPOS=0, SPOS=1};

string temp, unit;
istringstream iss;
uint i,j,numF, fPos, sPos, cnt;

void getFile(){
    getline(inp,temp);
    iss.str(temp);
    iss >> numF >> fPos >> sPos;
    iss.clear();
    chkDlock = vector<uint>(numF,0);
    func = vector<vector<string>>(numF, vector<string>());
    FOR(i,0,numF){
        getline(inp,temp);
        iss.str(temp);
        while(iss >> unit) stmt.push_back(unit);
        func[i]=stmt;
        stmt.clear();
        iss.clear();
    }
}

void funcCall(uint funcN){
    chkDlock[funcN]++;
    if(chkDlock[funcN]>2){
        out.seekp(0);
        out << "DEADLOCK";
        out.close();
        inp.close();
        exit(0);
    }

    if(!curPos.empty()&&!retSig.empty()){
        i=curPos.top()+1;
        curPos.pop();
        retSig.pop();
    }
    else i=1;

    for(;i<func[funcN].size();++i){
        if(func[funcN][i]!="$"){
            if(isupper(func[funcN][i][0])){
                curPos.push(i);
                mainMem.push(func[funcN][i]);
                FOR(j,0,numF)
                    if(func[j][0] == func[funcN][i]) funcCall(j);
            }
            fStmt.push(func[funcN][i]);
            cnt++;
            if(cnt==fPos) result[FPOS]=mainMem.top()+"-"+fStmt.top()+"\n";
            else if(cnt==sPos) result[SPOS]=mainMem.top()+"-"+fStmt.top()+"\n";
        }
        else{
            if(funcN == MAIN){
                result[SPOS].pop_back();
                out << result[FPOS] << result[SPOS];
                out.close();
                inp.close();
                exit(0);
            }
            chkDlock[funcN]--;
            mainMem.pop();
            retSig.push(func[funcN][i]);
            FOR(j, 0, numF) {
                if (func[j][0] == mainMem.top()){
                    chkDlock[j]--;
                    funcCall(j);
                }
            }
        }
    }
}

int main(){
    getFile();
    mainMem.push(func[MAIN][NAME]);
    funcCall(MAIN);
    return EXIT_SUCCESS;
}
