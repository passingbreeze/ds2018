#include <iostream>
#include <fstream>
#include <ctime>

#include <vector>
#include <algorithm>

using namespace std;
using szt = size_t;

#define FOR(i, b, e) for((i)=(b); (i)<(e); ++(i))
enum {CMPT=1, ENLG = 1, MIN=3};

ifstream inp;
ofstream out;
vector<int> parkLot;
vector<int> temp;
int i,j;
int minLot, lotNum, lotLim, carNum, carN, emptyP, cnt;

struct parkingLot{
    explicit parkingLot() {
        cnt = 0;
        inp >> minLot >> carNum;
        lotNum = minLot;
        parkLot = vector<int>(lotNum,0);
        lotLim = lotNum/MIN;
        emptyP = -1;

        FOR(i, 0, carNum){
//            cout << "check lotLim : " << lotLim << endl;
            inp >> carN;

            if(carN > 0){
                if(emptyP < 0){
                    cout << "parking...slot number : " << i << endl;
                    parkLot[i] = carN;
                }
                else if(emptyP >= 0) {
                    cout << "reparking...slot number : " << emptyP << endl;
                    parkLot[emptyP] = carN;
                }
                cnt++;
            }

            else if (carN > 0 && cnt == lotNum){
                cout << "check slot full." << endl;
                lotNum <<= ENLG;
                parkLot.resize(lotNum);
                cout << "resize enlarge : " << parkLot.size() << endl;
                parkLot[i] = carN;
                cnt++;
            }

            else if(carN < 0){
                cout << "car is going out." << endl;
                auto it = find(parkLot.begin(), parkLot.end(), (-carN));
                emptyP = it!=parkLot.end() ? it - parkLot.begin() : -1;
                cout << "make pos empty : " << emptyP << endl;
                if(it!=parkLot.end()){
                    *it = 0;
                    cnt--;
                }
            }

            else if (cnt == lotLim){
                cout << "check car num == lotLim" << endl;
                temp.assign(parkLot.begin(), parkLot.end());
                for(auto it = temp.begin(); it != temp.end(); ++it){
                    if(*it <= 0)
                        it = temp.erase(it);
                }
                parkLot.assign(temp.begin(), temp.end());
                lotNum = lotNum > minLot ? lotNum >> CMPT : minLot;
                parkLot.resize(lotNum);
                lotLim = lotNum/MIN;
                cout << "resize narrow : " << parkLot.size() << endl;
            }


        }
    }

    friend ofstream& operator<< (ofstream& ofs, const parkingLot& p) {
        FOR(i, 0, parkLot.size()){
            if (i<parkLot.size()-1) ofs << i+1 << ' '<< parkLot[i] << '\n';
            else ofs << i+1 << ' ' << parkLot[i];
        }
        return ofs;
    }
};

parkingLot *ex = nullptr;

int main()
{
    clock_t start, begin, finish;
    clock_t end;
    time_t currentTime;
    time(&currentTime);
    start = clock();

    inp.open("parking.inp", ios::binary);
    out.open("parking.out", ios::binary);

    begin = clock();
    ex = new parkingLot();
    end = clock();
    cout << "set time -> "<< ((double)(end - begin))/((long)(CLOCKS_PER_SEC)) << " sec" << '\n';

    out << *ex;

    finish = clock();
    cout << "total exe time -> "<< ((double)(finish - start))/((long)(CLOCKS_PER_SEC)) << " sec" << '\n';

    out.close();
    inp.close();
    delete ex;
    return EXIT_SUCCESS;
}
