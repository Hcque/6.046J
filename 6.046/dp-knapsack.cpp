#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_ = 7;

int n, m;
int V[MAX_], W[MAX_];
void init(){
    ifstream input("dpinput.txt");
    input >> n >> m;
    for (int i = 0; i < n; i++){
       input >> V[i] >> W[i];
    }
}
void knapsack(){
    init();
    // define dp[i][j]: afetr i item, using j weight, the max value
    // dp[i][j] = max(
    //     dp[i+1][j],
    //     dp[i+1][j-wi]
    // )

    int dp[MAX_][MAX_];
    for (int i = n; i >= 0; i--){
        for (int j = 0; j <= m; j++){
            // init
            if (i == n) dp[i][j] = 0;
            else {
                if (j-W[i] >= 0)
                    dp[i][j] = max(dp[i+1][j], dp[i+1][j-W[i]]+V[i]);
                else dp[i][j] = dp[i+1][j];
            }
        }
    }
    cout << dp[0][m] << endl;
}

void subset(){
    init();
    // dp[i][j] = dp[i+1][j], dp[i+1][j-wi]
    int dp[MAX_][MAX_];
    for (int i = n; i >= 0; i--){
        for (int j = 0; j <= m; j++){
            // init
            if (i == n) {
                if (j == 0) dp[i][j] = 1;
                else dp[i][j] = 0;
            }
            else {
                if (j-W[i] >= 0)
                    dp[i][j] = max(dp[i+1][j], dp[i+1][j-W[i]]);
                else dp[i][j] = dp[i+1][j];
            }
        }
    }
    cout << dp[0][m] << endl;
}

void ksubset(int K){
    init();
    // define i, i+1,... subset left j weight choose k items
    // dp[i][j][k] = dp[i+1][j][k], dp[i+1][j-wi]
    int dp[MAX_][MAX_][MAX_];
    for (int i = n; i >= 0; i--){
        for (int j = 0; j <= m; j++){
            for (int k = 0; k <= K; k++){
                // init
                if (i == n) {
                    if (j == 0 && k == 0) dp[i][j][k] = 1;
                    else dp[i][j][k] = 0;
                }
                else {
                    if (j-W[i] >= 0 && k-1 >= 0)
                        dp[i][j][k] = max(dp[i+1][j][k], dp[i+1][j-W[i]][k-1]);
                    else dp[i][j][k] = dp[i+1][j][k];
                }
            }

        }
    }
    cout << dp[0][m][K] << endl;
}


int main()
{
    // knapsack();
    // subset();
    ksubset(1);

    return 0;
}