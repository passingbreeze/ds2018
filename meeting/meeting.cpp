#include <fstream>

#include <map>
#include <list>
#include <deque>

#include <algorithm>
#include <utility>

#define ALL(x) (x).begin(), (x).end()
#define qfront(x) (x).front()
#define pname first
#define elapse second

using namespace std;
using nodeinfo = pair<char, int>;

map<char, list<char>> graphmap; // adjacent list
map<char, list<int>> proceeding; // count time check list from 3 starters..

class meetmap {
    /*
       WAY == 1 minute to go along with the road,
       IC == 2 minute to go through the interchange
    */
	enum {WAY=1, IC};
	list<char> temp;
	int nodeNum;
	char begA, begB, begC, paren, child;

	void fromBeg(char start) {
		int takentime = 1;
		deque<nodeinfo> ord;
		map<char,int> visited;

		visited.emplace(start, 0);
		for(const auto &r : graphmap[start])
			ord.emplace_back(r, takentime);
		while(!ord.empty()){
			if(!graphmap[qfront(ord).pname].empty()){
				for(const auto &r : graphmap[qfront(ord).pname]){
					auto fit = find_if(ALL(ord), [&](const nodeinfo& a){ return a.pname == r; });
					if(fit==ord.end() && visited.count(r)==0){
						ord.emplace_back(r, qfront(ord).elapse+IC+WAY);
					}
				}
			}
			visited.emplace(qfront(ord).pname, qfront(ord).elapse);
			ord.pop_front();
		}
		for(const auto& m:visited){
			if(proceeding.count(m.first)==0)
				proceeding.emplace(m.first, list<int>{m.second});
			else
				proceeding[m.first].push_back(m.second);
		}
		visited.clear();
	}

public:
	explicit meetmap(ifstream& ifs) {
		int i, j;
		ifs >> nodeNum;
		ifs >> begA >> begB >> begC;
		while(nodeNum > 0){
			ifs >> paren;
			while(ifs >> child){
				if(child == '$')
					break;
				temp.push_back(child);
			}
			graphmap.emplace(paren, move(temp));
			nodeNum--;
		}
	}

	void findPoint(ofstream& ofs) {
		fromBeg(begA);
		fromBeg(begB);
		fromBeg(begC);

		int sum=0;
		map<int, char> findless;

		for(const auto& m:proceeding)
			findless.emplace(*(max_element(ALL(m.second))), m.first);

		auto lessit = findless.begin();
		ofs << lessit->second << '\n' << lessit->first;
	}

};

int main()
{
	ifstream inp("meeting.inp", ios::binary);
	ofstream out("meeting.out", ios::binary);
	if(!inp.is_open()){
		out << "missing input files...";
		out.close();
		inp.close();
		return EXIT_FAILURE;
	}

	meetmap graph(inp);
	graph.findPoint(out);

	out.close();
	inp.close();
	return EXIT_SUCCESS;
}
