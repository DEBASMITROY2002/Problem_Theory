//
//  solution_common.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef solution_common_h
#define solution_common_h
#include "state_header.h"

class solution{
public:
    STATE::State init_state;
    STATE::State goal_state;
    vector<STATE_ADT>path;
    vector<STATE_ADT>order;
    int path_len;
    int order_len;
    int verbose;
    
    solution(STATE::State _init_state, STATE::State _goal_state, int _verbose=2){
        path = vector<STATE_ADT>();
        order = vector<STATE_ADT>();
        init_state = _init_state;
        goal_state = _goal_state;
        verbose = _verbose;
    }
    
    void set_operation_to_all_state(vector<pair<string,function<int(STATE::State*,int,int)>>> named_operation){
        init_state.setOperationRule(named_operation);
        goal_state.setOperationRule(named_operation);
    }
    
    void set_query_to_all_state(vector<pair<string,function<string(STATE::State*,int,int)>>> named_query){
        init_state.setQuery(named_query);
        goal_state.setQuery(named_query);
    }
    
    void set_inv_to_all_state(vector<pair<string,string>> named_inv_operations){
        init_state.setInverseMapping(named_inv_operations);
        goal_state.setInverseMapping(named_inv_operations);
    }
    
    void print2d(STATE_ADT cur_state){
        for(int col=init_state.min_col;col<=init_state.max_col;col++)cout<<"--";
        cout<<"\n";
        for(int i=init_state.min_row;i<=init_state.max_row;i++){
            for(int j=init_state.min_col;j<=init_state.max_col;j++)
                cout<<cur_state[i][j]<<" ";
            cout<<"|"<<endl;
        }
        for(int col=init_state.min_col;col<=init_state.max_col;col++)cout<<"--";
        cout<<"\n";
    }
    
    void printOrder(){
        cout<<"--------------------- Order --------------------\n";
        for(STATE_ADT x:order){
            print2d(x);
        }
        cout<<"<Order Length> "<<order.size()<<endl;
        cout<<"--------------------- **** ---------------------\n";
    }
    
    void printPath(){
        cout<<"--------------------- Path ---------------------\n";
        for(STATE_ADT x:path){
            print2d(x);
        }
        cout<<"<Path Length> "<<path.size()<<endl;
        cout<<"--------------------- **** ---------------------\n";
    }
    
    void print_summary(){
        cout<<"    <Summary>     \n------------------\n"<<"Oder Length = "<<order_len<<" \nPath Length = "<<path_len<<" \n------------------\n\n";
    }
};

#endif /* solution_common_h */
