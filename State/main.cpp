//
//  main.cpp
//  State
//
//  Created by DEBASMIT ROY on 01/03/23.
//
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

using STATE_ADT = vector<vector<int>>;

class State{
private:
    STATE_ADT stateSpace;
    function<bool(int,int,State*)> is_valid_lambda;
    vector<function<void(int,int,State*)>>operations;
    unordered_map<string,int>named_operationIndex;
    int min_x, max_x;
    int min_y, max_y;
    
public:
    State(
          STATE_ADT _stateSpace
          ){
        stateSpace = _stateSpace;
    }
     
    State(
          STATE_ADT _stateSpace,
          vector<pair<string,function<void(int,int,State*)>>> named_operation
          ){
        stateSpace = _stateSpace;
        for(int i=0;i <named_operation.size();i++){
            auto[nm,op] = named_operation[i];
            
            named_operationIndex[nm] = i;
            operations[i] = op;
        }
    }
    
    
    void setOperationRule(vector<pair<string,function<void(int,int,State*)>>> named_operation){
        for(int i=0;i <named_operation.size();i++){
            auto[nm,op] = named_operation[i];
            
            named_operationIndex[nm] = i;
            operations[i] = op;
        }
    }
    
    void performRule(int op_index, int x,int y){
        try{
            if(op_index>=operations.size())
                throw op_index;
            operations[op_index](x,y,this);
        }catch(string e){
            cout<<"Operation Index Out-of-bound\n";
            exit(-1);
        }
    }
    
    void performRule(string op_name, int x,int y){
        try{
            if(named_operationIndex.find(op_name)==named_operationIndex.end())
                throw op_name;
            operations[named_operationIndex[op_name]](x,y,this);
        }catch(string e){
            cout<<"Operation Undefined\n";
            exit(-1);
        }
    }
    
    void performAllOperation(int x,int y){
        for(auto op:operations){
            op(x,y,this);
        }
    }
    
    bool operator = (const State& st){
        return st.stateSpace == this->stateSpace;
    }
    
    
    friend ostream& operator<<(ostream& os, const State& st);
};

ostream& operator<<(ostream& os, const State& st){
    for(int y=st.min_y;y<=st.max_y;y++)cout<<"--";
    for(int x=st.min_x;x<=st.max_x;x++){
        for(int y=st.min_y;y<=st.max_y;y++){
            cout<<st.stateSpace[x][y]<<" ";
        }
        cout<<"        |\n";
    }
    for(int y=st.min_y;y<=st.max_y;y++)cout<<"--";
    cout<<"\n";
    return os;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    State s({{1,2,3},{},{}});
    return 0;
}
