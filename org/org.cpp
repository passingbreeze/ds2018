#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <string>

#include <algorithm>
#include <iterator>
#include <memory>

#define ALL(x) (x).begin(), (x).end()

using namespace std;

struct node {
    string name;
    int level = 1;
    int count = 0;
    shared_ptr<node> parent = nullptr;

    explicit node(string n) : name(move(n)) {}
};

using nodeptr = shared_ptr<node>;

class tree{
    nodeptr p,c;
    vector<nodeptr> treestr;
    string sub, boss, result;
    ostringstream oss;
    int nodenum = 0;
public:
    explicit tree(ifstream& ifs) {
        ifs >> nodenum;
        while(--nodenum > 0 && (ifs >> sub >> boss)) {
            auto bit = find_if(ALL(treestr), [&](const nodeptr &p) { return p->name == boss; });
            auto sit = find_if(ALL(treestr), [&](const nodeptr &p) { return p->name == sub; });
            if (bit == treestr.end() && sit == treestr.end()) {
                p = make_shared<node>(boss);
                c = make_shared<node>(sub);
                c->parent = p;
                treestr.push_back(p);
                treestr.push_back(c);
            } else if (bit == treestr.end() && sit != treestr.end()) {
                p = make_shared<node>(boss);
                (*sit)->parent = p;
                treestr.push_back(p);
            } else if (bit != treestr.end() && sit == treestr.end()) {
                c = make_shared<node>(sub);
                c->parent = *bit;
                treestr.push_back(c);
            } else if (bit != treestr.end() && sit != treestr.end()) {
                (*sit)->parent = (*bit);
            }
        }
    }

    void travel() {
        nodeptr ppl;
        for(auto &vit:treestr){
            int adv=0;
            ppl = vit;
            while(ppl->parent!=nullptr){
                ppl = ppl->parent;
                ppl->count++;
                adv++;
            }
            vit->level = adv;
        }
        sort(ALL(treestr), [](const nodeptr& a, const nodeptr& b){
           if(a->count > b->count) return true;
           else if(a->count == b->count) {
               if(a->level < b->level) return true;
               else if(a->level == b->level) return a->name < b->name;
               else return false;
           }
           else return false;
        });
    }

    void treeleaves(ofstream& ofs) {
        for(auto& it : treestr)
            oss << it->name << " ";
        result = oss.str();
        result.pop_back();
        ofs << result;
    }
};

int main()
{
    ifstream ifs("org.inp", ios::binary);
    ofstream ofs("org.out", ios::binary);
    if(!ifs.is_open()){
        ofs << "missing input file...";
        ofs.close();
        ifs.close();
        return EXIT_FAILURE;
    }

    tree t(ifs);
    t.travel();
    t.treeleaves(ofs);

    ofs.close();
    ifs.close();
    return EXIT_SUCCESS;
}
