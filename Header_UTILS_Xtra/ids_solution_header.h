//
//  ids_solution_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef ids_solution_header_h
#define ids_solution_header_h

#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/state_header.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/solution_common.h"
#include "/Users/debasmitroy/Desktop/programming/XcodePrj/Problem_Solver/Header_UTILS/problem_spec_header.h"

class ids_solution:public solution{
public:
    int max_cutoff;
    vector<vector<STATE_ADT>> merged_order;
    
    ids_solution(STATE::State _init_state,
                 STATE::State _goal_state,
                 int _max_cutoff,
                 int _verbose=2):solution(_init_state, _goal_state,_verbose){
        max_cutoff=_max_cutoff;
        merged_order = vector<vector<STATE_ADT>>();
    }
    
    void printMergedOrder(){
        cout<<"--------------------- Order --------------------\n";
        order_len=0;
        for(auto m:merged_order){
            for(auto o:m)
                print2d(o);
            cout<<"(Respawn)\n";
            order_len+=m.size();
        }
        cout<<"<Order Length> "<<order_len<<endl;
        cout<<"--------------------- **** ---------------------\n";
    }
    
    bool search(){
        path_len =  -404;
        for(int d=0;d<=max_cutoff;d++){
            cout<<"Current Cutoff: "<<d<<endl;
            dls_solution s(init_state,goal_state,d,0);
            bool isFound = s.search();
            merged_order.push_back(s.order);
            if(isFound){
                cout<<"================ IDS FOUND GOAL STATE ================\n";
                s.printPath();
                path_len = (int)s.path.size();
                break;
            }else{
                cout<<"No Solution within depth="<<d<<endl;
            }
        }
        
        printMergedOrder();
        print_summary();
        
        return false;
    }
};


#endif /* ids_solution_header_h */
