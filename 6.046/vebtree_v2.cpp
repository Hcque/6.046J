#include <cmath>
#include <iostream>

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

#define high(x) ( (x/(llu)sqrt(u)))
#define low(x) ( (x%(llu)sqrt(u)))
#define index(i, j) ( i*(llu)sqrt(u) + j)

class vEB{

    llu u;
    llu *m, *M;
    vEB *summary;
    vEB **cluster;

public:
    vEB(llu);

    bool member(llu);
    void insert(llu);
    void delet(llu);

    llu min();
    llu max();
    
    llu* pred(llu x);
    llu* suce(llu x);
};

vEB::vEB(llu u){
    this->u = u;
    m = nullptr;
    M = nullptr;

    // recursive constructor
    if (u == 2 ){
        summary = nullptr;
        cluster = nullptr;
    }
    else {
        llu sub_size = (llu)sqrt(u);
        // cout << u  << " " << sub_size << endl;

        summary = new vEB(sub_size);
        cluster = new vEB*[sub_size];
    }
}

bool vEB::member(llu x){
    if (u <= 2){
        if (m == nullptr) return false;
        if (x == 0 && *(m) == 0) return true;
        if (x == 1 && *(M) == 1) return true;
        return false;
    }
    else {
        if (m == nullptr) return false;
        else if ( x == *(m) || x == *(M)) return true;
        else if ( x < *(m) || x > *(M)) return false;
        else{
            llu hi = high(x), lo = low(x);
            if (cluster[hi] == nullptr ) return false;
            else return cluster[hi]->member( lo );
        }
    }
}

void vEB::insert(llu x){
    // base case
    if (u == 2){
        if (x == 0){
            if (m == nullptr) {
                m = new llu;
                M = new llu;
                *m = *M = x;
            }
            else *m = x;
        }
        if (x == 1){
            if (M == nullptr) {
                m = new llu;
                M = new llu;
                *m = *M = x;
            }
            else *M = x;
        }
    }
    else{
        if (m == nullptr){
            m = new llu;
            M = new llu;
            (*m) = (*M) = x;
            return;
        }
        if (x < *m) {
            llu cur_min = *m;
            *m = x;
            this->insert(cur_min);
        }
        if ( M != nullptr && x > *M) 
            *M = x;

        llu sub_size = (llu) sqrt(u);
        llu hi = high(x), lo = low(x);
        if (cluster[hi] == nullptr){
            cluster[hi] = new vEB(sub_size); // build tree
            this->summary->insert(hi);
        }
        cluster[hi]->insert(lo); // main insert
    }
}

void vEB::delet(llu x){
    if (u == 2){
        if (x == 0){
            if (*M == 0){
                m = nullptr;
                M = nullptr;
            }
            else *m = 1;
        }
        if (x == 1){
            if (*m = 1)
                m = M = nullptr;
            else *M = 0;
        }
    }
    else {
        // main dele
        llu hi = high(x), lo = low(x);
        if (x == *m){
            if (x == *M )
                m = M = nullptr;
            else {
                // next min update min
                llu next_mhi = summary->min();
                llu next_mlo = cluster[next_mhi]->min();
                llu next_m = index(next_mhi, next_mlo);
                delet(next_m);
                *m = next_m;
            }
        }
        else {
            cluster[hi]->delet(lo);
            if (cluster[hi]->m == nullptr){
                summary->delet(hi);
                delete cluster[hi];
                cluster[hi] = nullptr;
            }

            // adjust the max
            if (x == *M){
                if (summary->m == nullptr) *M = *m;
                else {
                    llu next_maxhi = summary->max();
                    llu next_maxlo = cluster[next_maxhi]->max();
                    *M = index(next_maxhi, next_maxlo);
                }
            }
        }

    }

}

llu* vEB::suce(llu x){
    if (u == 2){
        if (x == 0){
            if (M == nullptr) return nullptr;
            if (*M == 0) return nullptr;
            return M;
        }
        else return nullptr;
    }
    else {
        if (m == nullptr) return nullptr;
        if (x > *M) return nullptr;
        if (x < *m) return m;
        llu hi = high(x), lo;
        if (cluster[hi] == nullptr){
            hi = *(this->summary->suce(hi));
            lo = cluster[hi]->min();
        }
         if (low(x) < cluster[hi]->max() ){
            //  cout << low(x) << endl;
            //  cout << cluster[hi]->max() << endl;
            lo = *cluster[hi]->suce(low(x));
        }
        else {
            hi = *this->summary->suce(hi);
            lo = cluster[hi]->min();
        }
        llu *ans = new llu;
        *ans = index(hi, lo);
        return ans;
    }
}

llu vEB::min() { return *m; }
llu vEB::max() { return *M; }

int main()
{
    vEB *veb = new vEB(16);

    veb->insert(1);
    veb->insert(2);
    // veb->insert(3);
    veb->insert(4);
    veb->insert(5);
    veb->insert(7);
    veb->insert(14);
    veb->insert(15);

    // cout << veb->min() << " | " << veb->max() << endl;
    cout << *veb->suce(7) << endl;

    veb->delet(14);
    veb->delet(2);
    veb->delet(4);
    veb->delet(5);
    veb->delet(7);
    veb->delet(14);
    veb->delet(15);
    cout << *veb->suce(0) << endl;


    return 0;
}





