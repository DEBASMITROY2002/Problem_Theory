//
//  main.cpp
//  Solution
//
//  Created by DEBASMIT ROY on 02/03/23.
//
#include <iostream>
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/state_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/solution_common.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/problem_spec_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/dfs_solution_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/dls_solution_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/ids_solution_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/bls_solution_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/ibs_solution_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/bfs_solution_header.h"

#define MAX_LEFT 3
#define MAX_RIGHT 4

int main(int argc, const char * argv[]) {
    // insert code here...
    STATE::State init_state({
        {0,0}}
                   ,0,0,0,1);

    STATE::State goal_state({
        {2,4}}
                   ,0,0,0,1);
    
    bfs_solution s(init_state,goal_state);
    
    s.setConstraintsToAll([](STATE::State *st,int row,int col){
        return (st->stateSpace[0][0]>=0 && st->stateSpace[0][0]<=MAX_LEFT) && (st->stateSpace[0][1]>=0 && st->stateSpace[0][1]<=MAX_RIGHT);
    });
    
    s.set_operation_to_all_state({
        {"EMPTY LEFT",[](STATE::State *st,int row,int col){
            st->stateSpace[0][0] = 0;
            return true;
        }},
        {"EMPTY RIGHT",[](STATE::State *st,int row,int col){
            st->stateSpace[0][1] = 0;
            return true;
        }},
        {"FILL LEFT",[](STATE::State *st,int row,int col){
            st->stateSpace[0][0] = MAX_LEFT;
            return true;
        }},
        {"FILL RIGHT",[](STATE::State *st,int row,int col){
            st->stateSpace[0][1] = MAX_RIGHT;
            return true;
        }},
        {"FILL LEFT FROM RIGHT",[](STATE::State *st,int row,int col){
            int transfer_ammount = MAX_LEFT - st->stateSpace[0][0];
            if(st->stateSpace[0][1]>=transfer_ammount){
                st->stateSpace[0][1] = st->stateSpace[0][1]-transfer_ammount;
                st->stateSpace[0][0] = MAX_LEFT;
                return true;
            }
            return false;
        }},
        {"FILL RIGHT FROM LEFT",[](STATE::State *st,int row,int col){
            int transfer_ammount = MAX_RIGHT - st->stateSpace[0][1];
            if(st->stateSpace[0][0]>=transfer_ammount){
                st->stateSpace[0][0] = st->stateSpace[0][0]-transfer_ammount;
                st->stateSpace[0][1] = MAX_LEFT;
                return true;
            }
            return false;

        }}
    });

    s.search();
    return 0;
}
