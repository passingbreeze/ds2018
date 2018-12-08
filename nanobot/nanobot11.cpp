#include <iostream>
#include <fstream>

#include <utility>
#include <memory>

#include <forward_list>
#include <array>

using namespace std;

enum {X, Y};
using value = int;
using point = array<value ,2>;

#define FOR(i, b, e) for((i)=(b); (i)<(e); ++i)
#define bckFOR(i, e, b) for((i)=(e); (i)>=(b); --i)

class nanobot {
    forward_list<pair<point, value>> table; // (좌표, 값) 단방향 list
    point leftUp, leftBottom, rightUp, rightBottom;
public:
    explicit nanobot(value c, value r) : leftUp{{1, r}}, leftBottom{{1,1}}, rightUp{{c, r}}, rightBottom{{c, 1}} {
        value i, j=1;

        while (j<=c*r){
            FOR(i, leftBottom[Y], leftUp[Y]+1){
                table.push_front(make_pair(point{{leftBottom[X], i}}, j++));
            }
            leftBottom[X]++;
            leftUp[X]++;

            FOR(i, leftUp[X], rightUp[X]+1){
                table.push_front(make_pair(point{{i, leftUp[Y]}}, j++));
            }
            rightUp[Y]--;
            leftUp[Y]--;

            bckFOR(i, rightUp[Y], rightBottom[Y]){
                table.push_front(make_pair(point{{rightUp[X],i}},j++));
            }
            rightBottom[X]--;
            rightUp[X]--;

            bckFOR(i, rightBottom[X], leftBottom[X]){
                table.push_front(make_pair(point{{i, rightBottom[Y]}},j++));
            }
            rightBottom[Y]++;
            leftBottom[Y]++;
        }
    }

    point findPoint(value v) {
        for(auto it: table){
            if(it.second == v)
                return it.first;
        }
        return point{{-1,-1}}; // (-1,-1) means the input value does not find its point in table.
    }

    value findValue(value c, value r){
        point getValue{{r, c}};
        for(auto it:table){
            if(it.first == getValue)
                return it.second;
        }
        return -1; // -1 means the input point does not find its value in table.
    }
};

int main()
{
    ifstream ifs("nanobot.inp", ios::binary);
    ofstream ofs("nanobot.out", ios::binary);
    if(!ifs.is_open())
        return EXIT_FAILURE;

    value x, y, find_vx, find_vy, find_v;
    ifs >> x >> y >> find_vx >> find_vy >> find_v;

    unique_ptr<nanobot> ex{new nanobot(x,y)};
    ofs << (ex->findValue(find_vy, find_vx)) << '\n';
    ofs << (ex->findPoint(find_v))[X] << " " << (ex->findPoint(find_v))[Y];

    ofs.close();
    ifs.close();
    return EXIT_SUCCESS;
}