#include<bits/stdc++.h>
using namespace std;
vector<string> solve(string s,char x) {
    vector<string> temp;
    char t = s[0];
    if (s.size() > 1) {
        s.erase(0,1);
        temp = solve(s,t);
    }
    string res = "";
    res += t;
     if (temp.empty()) temp.push_back(res);

    int f = temp.size();
    for(int i=0;i<f;i++) {

        int z = temp[i].size();
        for(int j=0;j<=z;j++) {

            string temp1 = temp[i];
            temp1.insert(j,1,x);
            temp.push_back(temp1);
            temp1 = "";

        }
    }
    temp.erase(temp.begin(),temp.begin()+f);
    return temp;
}
int main(){
    string s1;
    cin>>s1;
    char z = s1[0];
    s1.erase(0,1);
    vector<string> res = solve(s1,z);
    for(int i = 0; i < res.size(); i ++) {
        cout<<res[i]<<endl;
    }
}
