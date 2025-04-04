#include <bits/stdc++.h>
using namespace std;
#define __GodLikeNeel__ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

bool isValidSudoku(vector<vector<char>>& board) {
    int n = 9;
    for(int i=0;i<n;i++){
        vector<int> arr(10,0);
        vector<int> arr1(10,0);
        for(int j=0;j<n;j++){
            if(board[i][j]!='.'){
                int num = board[i][j]-'0';
                if(arr[num]++) return false;
            }
            if(board[j][i]!='.'){
                int num = board[j][i]-'0';
                if(arr1[num]++) return false;
            }  
        }

        vector<int> arr2(10,0);
        if(i%3==0){
            for(int j=0;j<n;j++){
                for(int k=i;k<i+3;k++){
                    if(board[k][j]!='.') {
                        int num = board[k][j]-'0';
                        arr2[num]++;
                    }
                }
                if(j%3==2){
                    for(int x=0;x<10;x++){
                        if(arr2[x]>1) return false;
                        else arr2[x]=0;
                    }
                    
                }
            }
        }
    
    }
    return true;
}


int main() {
    __GodLikeNeel__
    vector<vector<char>> board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]];
    bool result = isValidSudoku(board);
    cout << (result ? "Valid Sudoku" : "Invalid Sudoku") << endl;
    return 0;
}