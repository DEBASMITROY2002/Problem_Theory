//
//  bfs_solution_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 03/03/23.
//

#ifndef bfs_solution_header_h
#define bfs_solution_header_h
#include <iostream>
#include <queue>
#include "state_header.h"
#include "solution_common.h"

class bfs_solution:public solution{
public:
    bfs_solution(STATE::State _init_state,
                 STATE::State _goal_state,
                 int _verbose=2):solution(_init_state, _goal_state,_verbose){}
    
    map<STATE_ADT,bool>visited;
    map<STATE_ADT,STATE_ADT> parent_state;
    
    void generate_path(STATE_ADT cur, STATE_ADT source){
        path.push_back(cur);
        if(parent_state.find(cur)==parent_state.end())
            return;
        if(parent_state[cur]==cur)
            return;
        generate_path(parent_state[cur],source);
    }
    
    bool util(){
        queue<STATE::State>open_queue;
        open_queue.push(init_state);
        parent_state[init_state.stateSpace] = init_state.stateSpace;
        STATE::State cur_state = init_state;
        
        while (!open_queue.empty()) {
            int open_queue_size = (int)open_queue.size();
            if(verbose>=2)
                cout<<".";
            cur_state = open_queue.front();
            open_queue.pop();
            order.push_back(cur_state.stateSpace);
            
            if(cur_state.equal(goal_state)){
                cout<<"\n                                     [Accepted(BFS)]\n"<<endl;
                break;
            }
            
            while (open_queue_size--) {
                for(auto op:cur_state.named_operationIndex_opp){
                    STATE::State temp_state = cur_state;
                    bool flag = cur_state.performOperation(op, -1, -1);
                    if(flag){
                        if((visited.find(cur_state.stateSpace)==visited.end())){
                            visited[cur_state.stateSpace] = true;
                            open_queue.push(cur_state);
                        }
                        
                        if(parent_state.find(cur_state.stateSpace)==parent_state.end()){
                            parent_state[cur_state.stateSpace] = temp_state.stateSpace;
                        }
                        
                        cur_state = temp_state;
                    }
                }
            }
        }
        
        if(cur_state.equal(goal_state)){
            generate_path(cur_state.stateSpace,init_state.stateSpace);
            reverse(path.begin(), path.end());
            return true;
        }
        return false;
    }
    
    bool search(){
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


#endif /* bfs_solution_header_h */
