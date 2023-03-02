//
//  bls_solution_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef bls_solution_header_h
#define bls_solution_header_h
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/state_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/solution_common.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/problem_spec_header.h"

class bls_solution:public solution{
public:
    STATE::State cur_state;
    map<STATE_ADT,bool>visited;
    int cutoff;
    
    bls_solution(STATE::State _init_state,
                 STATE::State _goal_state,
                 int _cutoff,
                 int _verbose=2):solution(_init_state, _goal_state,_verbose){cutoff=_cutoff;}
    
    
    bool util(){
        visited[cur_state.stateSpace]=true;
        
        if(verbose>=3)
            cout<<".";
        
        order.push_back(cur_state.stateSpace);
        
        if(cur_state.equal(goal_state)){
            cout<<"\n                                     [Accepted(BLS)]\n"<<endl;
            return true;
        }
        
        int breadth=0;
        
        for(auto op:cur_state.named_operationIndex_opp){
            breadth++;
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
            
            if(breadth>cutoff)
                break;
        }
        return false;
    }
    
    bool search(){
        cur_state = init_state;
        bool isFound = util();
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


#endif /* bls_solution_header_h */
