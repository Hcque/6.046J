#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class RollingHash {
    string s;
    int curH;
    int strLen;
    const int HASH_BASE = 7;

public:
    RollingHash(string& str){
        strLen = str.size();
        int h = 0;
        int n = strLen - 1;
        for (char c: str){
            h += c * (pow(HASH_BASE, n));
            n--;
        }
        curH = h;
    }

    int hash(){ return curH; }
    
    int slide(char prev, char next){
        curH = curH * HASH_BASE + next;
        curH -= prev * pow(HASH_BASE, strLen);
        // cout << curH << endl;
        return curH;
    }

};

int krMatch(string& s1, string& s2){

    string stmp = s1.substr(0, s2.size());
    RollingHash *rh1 = new RollingHash(stmp);
    RollingHash *rh2 = new RollingHash(s2);
    for (int i = s2.size(); i < s1.size(); i++){
        if (rh1->hash() == rh2->hash())
            return i - s2.size();
        rh1->slide(s1[i-s2.size()], s1[i]);
    }

}


int main()
{
    string s1 = "daytime";
    string s2 = "im";
    cout << krMatch(s1, s2);
    return 0;
}
