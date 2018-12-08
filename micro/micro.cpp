#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <array>
#include <set>
#include <deque>

#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>

#define FOR(i,b,e) for((i)=(b); (i)<=(e); ++i)
#define ALL(x) (x).begin(), (x).end()
#define qfront(x) (x).front()

using namespace std;
using namespace chrono;

using pos = array<int ,2>;

class virus {
    enum {X, Y};
    vector<vector<bool>> vir;
    vector<bool> tempvec;
    multiset<pos> viruspos;
    multiset<int, greater<int>> countvir;
    deque<pos> visitQ;
    string result;
    ostringstream oss;
    char chr='a';
    int row=0, col=0, stdsize=0;
public:
    explicit virus (ifstream& ifs) {
        int i=1,j=1;
        ifs >> col >> row >> stdsize;
        tempvec = move(vector<bool>(col+1, false));
        vir = move(vector<vector<bool>>(row+1, tempvec));
        while(ifs >> chr){
            if(j == col+1){
                i++;
                j=1;
            }
            if(chr == '#')
                vir[i][j] = true;
            j++;
        }
    }

    void findVirus() {
        int i, j, size;

        FOR(i,1,row){
            FOR(j, 1, col) {
                if(vir[i][j])
                    viruspos.emplace(pos{i,j});
            }
        }

        multiset<pos> temp = viruspos;

        while(!temp.empty()){
            size = 1;
            visitQ.emplace_back(*temp.begin());
            temp.erase(temp.begin());
            while(!visitQ.empty()){
                if(temp.find({qfront(visitQ)[X]-1, qfront(visitQ)[Y]})!=temp.end()){
                    size++;
                    temp.erase({qfront(visitQ)[X]-1, qfront(visitQ)[Y]});
                    if(find(ALL(visitQ), pos{qfront(visitQ)[X]-1, qfront(visitQ)[Y]})==visitQ.end())
                     visitQ.emplace_back(pos{qfront(visitQ)[X]-1, qfront(visitQ)[Y]});
                }
                if(temp.find({qfront(visitQ)[X], qfront(visitQ)[Y]+1})!=temp.end()){
                    size++;
                    temp.erase({qfront(visitQ)[X], qfront(visitQ)[Y]+1});
                    if(find(ALL(visitQ), pos{qfront(visitQ)[X], qfront(visitQ)[Y]+1})==visitQ.end())
                        visitQ.emplace_back(pos{qfront(visitQ)[X], qfront(visitQ)[Y]+1});
                }
                if(temp.find({qfront(visitQ)[X]+1, qfront(visitQ)[Y]})!=temp.end()){
                    size++;
                    temp.erase({qfront(visitQ)[X]+1, qfront(visitQ)[Y]});
                    if(find(ALL(visitQ), pos{qfront(visitQ)[X]+1, qfront(visitQ)[Y]})==visitQ.end())
                        visitQ.emplace_back(pos{qfront(visitQ)[X]+1, qfront(visitQ)[Y]});
                }
                if(temp.find({qfront(visitQ)[X], qfront(visitQ)[Y]-1})!=temp.end()){
                    size++;
                    temp.erase({qfront(visitQ)[X], qfront(visitQ)[Y]-1});
                    if(find(ALL(visitQ), pos{qfront(visitQ)[X], qfront(visitQ)[Y]-1})==visitQ.end())
                        visitQ.emplace_back(pos{qfront(visitQ)[X], qfront(visitQ)[Y]-1});
                }
                visitQ.pop_front();
            }
            if(size >= stdsize)
                countvir.insert(size);
        }
    }

    void getResult(ofstream& ofs) {
        if(!countvir.empty()){
            oss << countvir.size() << " " << *(countvir.begin());
            result = oss.str();
        }
        else
            result = "there is no virus.";
        ofs << result;
    }
};

int main()
{
    system_clock time;
    duration<double> diff;
    auto sys_beg = time.now();

    auto begin = time.now();
    ifstream inp("micro.inp", ios::binary);
    ofstream out("micro.out", ios::binary);
    if(!inp.is_open()){
        out << "missing input file...";
        out.close();
        inp.close();
        return EXIT_FAILURE;
    }

    virus solv(inp);
    solv.findVirus();
    solv.getResult(out);

    out.close();
    inp.close();
    auto sys_end = time.now();
    diff = sys_end - sys_beg;
    cout << "total exec time : " << diff.count() << " sec(s)" << endl;
    return EXIT_SUCCESS;
}
