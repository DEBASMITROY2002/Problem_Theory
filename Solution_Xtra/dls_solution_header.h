//
//  dls_solution_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef dls_solution_header_h
#define dls_solution_header_h
#include "state_header.h"
#include "solution_common.h"
#include "problem_spec_header.h"

class dls_solution:public solution{
public:
    int cutoff;
    STATE::State cur_state;
    map<STATE_ADT,bool>visited;
    
    
    dls_solution(STATE::State _init_state,
                 STATE::State _goal_state,
                 int _cutoff,
                 int _verbose=2):solution(_init_state, _goal_state,_verbose){cutoff=_cutoff;}

    bool util(int cur_depth){
        if(cur_depth>cutoff)
            return false;
        visited[cur_state.stateSpace]=true;
        order.push_back(cur_state.stateSpace);
        
        if(verbose>=3)
            cout<<".";
        if(verbose>=4)
            cout<<"Cur Depth: "<<cur_depth<<endl;
        
        if(cur_state.equal(goal_state)){
            cout<<"\n                                     [Accepted(DLS)]\n"<<endl;
            return true;
        }
        
        for(auto op:cur_state.named_operationIndex_opp){
            STATE::State temp_state = cur_state;
            bool flag = cur_state.performOperation(op, -1, -1);
        
            if(flag){
                path.push_back(cur_state.stateSpace);

                if(visited.find(cur_state.stateSpace)==visited.end()){
                    if(util(cur_depth+1))
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
        bool isFound = util(0);
        order_len = (int)order.size();
        path_len = (int)path.size();
        
        if(verbose>=1){
                if(isFound){
                    cout<<"Accept State Found\n";
                }else
                    cout<<"Accept State Not Found\n";
            if(verbose>=2){
                printPath();
                printOrder();
                print_summary();
            }
        }
        
        return isFound;
    }
};


#endif /* dls_solution_header_h */
