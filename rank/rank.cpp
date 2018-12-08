#include <bits/stdc++.h>
#define v std::vector<int>
std::ifstream i("rank.inp");
std::ofstream o("rank.out");
std::vector<v>r;
int k,n,m;
int main(){for(i>>m;k++<m;){r.emplace_back(v());
r[k-1].push_back(0);
while(i>>n&&n!=-1)r[k-1].push_back(n);
sort(r[k-1].begin()+1,r[k-1].end());
r[k-1][0]=r[k-1].size()-1;
r[k-1].push_back(m-k+1);}
sort(r.begin(),r.end(),std::greater<v>());
for(auto l:r){o<<(m-*(l.end()-1))+1;
if(l!=*(r.end()-1))o<<'\n';}
o.close();
i.close();}