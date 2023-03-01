//
//  main.cpp
//  Problem
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#include <iostream>
#include "state_header.h"
#include "problem_spec_header.h"
using namespace std;
using STATE_ADT = vector<vector<int>>;

class Problem{
public:
    STATE::State init_state;
    STATE::State goal_state;
    vector<STATE::State>path;
    vector<STATE::State>order;
    
    Problem(STATE::State _init_state, STATE::State _goal_state){
        path = vector<STATE::State>();
        order = vector<STATE::State>();
        init_state = _init_state;
        goal_state = _goal_state;
    }
    
    void printOrder(){
        cout<<"--------------------- Path ---------------------\n";
        for(STATE::State x:order){
            cout<<x;
        }
        cout<<"--------------------- **** ---------------------\n";
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    STATE::State s({
        {1,2,3},
        {4,5,6},
        {7,8,0}}
                   ,0,2,0,2);
    
    s.setQuery({
        {"Where is the blank space?",[](STATE::State *st,int row,int col){
            for(int i=st->min_row;i<=st->max_row;i++){
                for(int j=st->min_col;j<=st->max_col;j++){
                    if(st->stateSpace[i][j]==0)
                        return string(to_string(i)+"$"+to_string(j));
                }
            }
            return string("$");
        }}
    });
    
    s.setOperationRule({
        {"NORTH",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank, col_blank-1);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank-1][col_blank]);
                return true;
            }else
                return false;
        }},
        {"SOUTH",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank, col_blank+1);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank+1][col_blank]);
                return true;
            }else
                return false;
        }},
        {"EAST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank-1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank-1]);
                return true;
            }else
                return false;
        }},
        {"WEST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank+1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank+1]);
                return true;
            }else
                return false;
        }}
    });
    
    
    cout<<s;
    auto [row,col] = decode_0(s.performQuery("Where is the blank space?",-1,-1));
    cout<<row<<" "<<col<<endl;
    s.performOperation("NORTH", -1, -1);
    cout<<s;
    auto [row_,col_] = decode_0(s.performQuery("Where is the blank space?",-1,-1));
    cout<<row_<<" "<<col_<<endl;


    return 0;
}
