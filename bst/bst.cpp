#include <iostream>
#include <sstream>
#include <fstream>

#include <string>

#include <memory>

using namespace std;

struct bstnode {
    string word;
    int level;
    shared_ptr<bstnode> right = nullptr;
    shared_ptr<bstnode> left = nullptr;

    explicit bstnode(string w, int l) : word(move(w)), level(l){}
};

using nodeptr = shared_ptr<bstnode>;

bool chklevel;
ostringstream oss;

void insert(nodeptr* root, const string& word, int level)
{
    if(*root == nullptr){ // 트리가 비었을 때
        nodeptr newOne = make_shared<bstnode>(word, level);
        *root = newOne;
    }
    else if((*root)->word == word){ // 트리안의 문자열과 입력된 문자열이 같으면 덮어씀.
        (*root)->word = word;
    }
    else if((*root)->word > word){ // 트리안의 문자열보다 입력된 문자열이 작으면
        insert(&((*root)->left), word, ++level); // 왼쪽으로
    }

    else if((*root)->word < word){ // 트리안의 문자열보다 입력된 문자열이 크면
        insert(&((*root)->right), word, ++level); // 오른쪽으로
    }

}

nodeptr* findNode(const nodeptr& root, nodeptr* sub)
{
    nodeptr tNode;
    if(root->left!=nullptr){ // 왼쪽 부트리가 있으면
        tNode = root->left;
        sub = &(root->left);
        while(tNode->right != nullptr){ // 그 부트리 중에서 최댓값을 찾음
            sub = &(tNode->right);
            tNode = tNode->right;
        }
    }
    else if(root->right != nullptr){ // 오른쪽 부트리가 있으면
        tNode = root->right;
        sub = &(root->right);
        while(tNode->left != nullptr){  // 그 부트리 중에서 최솟값을 찾음
            sub = &(tNode->left);
            tNode = tNode->left;
        }
    }
    return sub;
}

void remove(nodeptr* root){
    if((*root)->left == nullptr && (*root)->right == nullptr)
        *root = nullptr; // 양쪽 부트리가 모두 없으면(leaf라면) 루트를 없앰
    else { // leaf까지 찾은 다음 없앰
        nodeptr* tNode = nullptr;
        tNode = findNode((*root), tNode);
        (*root)->word = (*tNode)->word;
        remove(tNode);
    }
}

void delNode(nodeptr* root, const string& word)
{
    if(*root != nullptr){
        if((*root)->word == word) // 입력된 문자열과 일치하면 없앰
            remove(root);
        else if((*root)->word < word) // 입력된 문자열보다 작으면
            delNode(&((*root)->right), word); // 왼쪽으로
        else if((*root)->word > word) // 입력된 문자열보다 크면
            delNode(&((*root)->left), word); // 오른쪽으로
    }
}

void leaf(nodeptr* root)
{
    if((*root)->left==nullptr && (*root)->right==nullptr)
        oss << (*root)->word << " ";
    if((*root)->left!=nullptr)
        leaf(&((*root)->left));
    if((*root)->right!=nullptr)
        leaf(&((*root)->right));
}

void findDepth(nodeptr* root, int lev)
{
    if((*root)->level == lev){
        oss << (*root)->word << " ";
        chklevel = true;
    }
    if((*root)->left!=nullptr)
        findDepth(&((*root)->left), lev);
    if((*root)->right!=nullptr)
        findDepth(&((*root)->right), lev);
}

int main()
{
    ifstream ifs("bst.inp", ios::binary);
    ofstream ofs("bst.out", ios::binary);
    if(!ifs.is_open()){
        ofs << "missing input file...";
        ofs.close();
        ifs.close();
        return EXIT_FAILURE;
    }
    nodeptr root = nullptr;
    int count=0, kdepth=0;
    int deflev=1; // default node level
    string cmd, word, result;
    ifs >> count;
    while(count > 0 && ifs >> cmd){
        if(cmd == "+"){
            ifs >> word;
            insert(&root, word, deflev);
        }
        else if(cmd == "-"){
            ifs >> word;
            delNode(&root, word);
        }
        else if(cmd == "depth"){
            ifs >> kdepth;
            chklevel = false;
            findDepth(&root, kdepth);
            if(!chklevel){
                result += "NO\n";
            }
            else{
                result += oss.str();
                result.pop_back();
                result+='\n';
            }
            oss.str("");
            oss.clear();
        }
        else if(cmd == "leaf"){
            leaf(&root);
            result += oss.str();
            result.pop_back();
            result+='\n';
            oss.str("");
            oss.clear();
        }
    }
    result.pop_back();
    ofs << result;
    ofs.close();
    ifs.close();
    return EXIT_SUCCESS;
}
