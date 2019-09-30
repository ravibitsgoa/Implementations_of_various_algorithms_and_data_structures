//https://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/
//story: you and another person are playing a game to take a card from either end
//of a card pile. Usual game rules apply. Try to maximize your sum of cards.

#include <iostream>
using namespace std;

int maxSum(int array[], int n, int l, int r, vector<vector<int> > &dp)
{
    if(l>=r)
        return 0;
    if(l == r-1)
        dp[l][r]= array[l];
    else if(dp[l][r] != -1) //cached value.
        return dp[l][r];
    else
    {
        dp[l][r] = max( array[l] + min(maxSum(array, n, l+2, r, dp), maxSum(array, n, l+1, r-1, dp)),
                        array[r-1] + min(maxSum(array, n, l, r-2, dp), maxSum(array, n, l+1, r-1, dp)));
    }               //if the opponent plays optimally.
    //if the opponent is dumb, replace both min with max, to get the max score that this player can get.

    return dp[l][r];
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int n=7;
    vector<vector<int> >dp(n+1, vector<int>(n+1, -1));
    cout << maxSum(array, n, 0, n, dp);
}
