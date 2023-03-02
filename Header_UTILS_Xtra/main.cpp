//
//  main.cpp
//  Solution
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#include <iostream>
#include "state_header.h"
#include "solution_common.h"
#include "problem_spec_header.h"
#include "dfs_solution_header.h"
#include "dls_solution_header.h"
#include "ids_solution_header.h"
#include "bls_solution_header.h"
#include "ibs_solution_header.h"
#include "bfs_solution_header.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    STATE::State init_state({
        {1,2},
        {0,3}}
                   ,0,1,0,1);

    STATE::State goal_state({
        {1,2},
        {3,0}}
                   ,0,1,0,1);
    
    ids_solution s(init_state,goal_state,100);
    
    s.set_query_to_all_state({
        {"Where is the blank space?",[](STATE::State *st,int row,int col){
        for(int i=st->min_row;i<=st->max_row;i++){
            for(int j=st->min_col;j<=st->max_col;j++){
                if(st->stateSpace[i][j]==0)
                    return string(to_string(i)+" "+to_string(j));
            }
        }
        return string("$");}
        }});
    
    s.set_operation_to_all_state({
        {"NORTH",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank-1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank-1][col_blank]);
                return true;
            }else
                return false;
        }},
        {"SOUTH",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank+1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank+1][col_blank]);
                return true;
            }else
                return false;
        }},
        {"EAST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank, col_blank-1);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank-1]);
                return true;
            }else
                return false;
        }},
        {"WEST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank, col_blank+1);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank+1]);
                return true;
            }else
                return false;
        }}
    });

    s.search();
    
    return 0;
}
