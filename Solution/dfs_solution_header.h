//
//  dfs_solution_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef dfs_solution_header_h
#define dfs_solution_header_h
#include "state_header.h"
#include "solution_common.h"
#include "problem_spec_header.h"

class dfs_solution:public solution{
public:
    dfs_solution(STATE::State _init_state,
                 STATE::State _goal_state,
                 int _verbose=2):solution(_init_state, _goal_state,_verbose){}
    
    STATE::State cur_state;
    map<STATE_ADT,bool>visited;
    
    
    bool util(){
        visited[cur_state.stateSpace]=true;
        cout<<".";
        order.push_back(cur_state.stateSpace);
        
        if(cur_state.equal(goal_state)){
            cout<<"\n                                     [Accepted(DFS)]\n"<<endl;
            return true;
        }
        
        for(auto op:cur_state.named_operationIndex_opp){
            STATE::State temp_state = cur_state;
            bool flag = cur_state.performOperation(op, -1, -1);
        
            if(flag){
                path.push_back(cur_state.stateSpace);
                
                if(visited.find(cur_state.stateSpace)==visited.end()){
                    if(util())
                        return true;
                }
                
                path.pop_back();
                cur_state = temp_state;
            }
        }
        return false;
    }
    
    bool search(){
        cur_state = init_state;
        bool isFound = util();
        if(isFound){
            cout<<"Accept State Found\n";
        }else
            cout<<"Accept State Not Found\n";
        
        printPath();
        printOrder();
        
        order_len = (int)order.size();
        path_len = (int)path.size();
        
        print_summary();
        return isFound;
    }
};


//            if(flag){
//                path.push_back(cur_state.stateSpace);
//
//            if(visited.find(cur_state.stateSpace)==visited.end()){
//                if(util())
//                    return true;
//            }
//            if(flag){
//                path.pop_back();
//                cur_state.performInverse(op, -1, -1);
//            }

#endif /* dfs_solution_header_h */
