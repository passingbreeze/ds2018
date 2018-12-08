#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <list>
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
    list<shared_ptr<node>> children;
    
    explicit node(string n) : name(move(n)) {}
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

    shared_ptr<node> child;
    // vector<node> tree;
    string sub, boss;
    int nodenum;
    ifs >> nodenum;
    while(--nodenum > 0 && (ifs >> sub >> boss)){
        child = make_shared<node>(sub);

        if(child->parent == nullptr || child->parent->name!=boss)
            child->parent = make_shared<node>(boss);

        child->level += child->parent->level;
        child->parent->count += child->count+1;
        child->parent->children.push_back(child);
    }

    while(child->parent!=nullptr){
        cout << child->name << " : level : " << child->level << ", " << child->count << endl;
        child = child->parent;
    }

    ofs.close();
    ifs.close();
    return EXIT_SUCCESS;
}