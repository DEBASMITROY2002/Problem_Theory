//
//  main.cpp
//  State
//
//  Created by DEBASMIT ROY on 01/03/23.
//

// All indexes are started from 0

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;
using STATE_ADT = vector<vector<int>>;
namespace  STATE{

    class State{
    public:
        STATE_ADT stateSpace;
        
        vector<function<int(State*,int,int)>>operations;
        unordered_map<string,int>named_operationIndex;
        
        vector<function<string(State*,int,int)>>queries;
        unordered_map<string,int>named_queryIndex;
        
        int min_row, max_row;
        int min_col, max_col;
        
        State(STATE_ADT _stateSpace,
              int _min_row,
              int _max_row,
              int _min_col,
              int _max_col){
            stateSpace = _stateSpace;
            min_row = _min_row;
            max_row = _max_row;
            min_col = _min_col;
            max_col = _max_col;
        }
         
        State(STATE_ADT _stateSpace,
              vector<pair<string,function<int(State*,int,int)>>> named_operation,
              int _min_row,
              int _max_row,
              int _min_col,
              int _max_col){
            stateSpace = _stateSpace;
            for(int i=0;i <named_operation.size();i++){
                auto[nm,op] = named_operation[i];
                
                named_operationIndex[nm] = i;
                operations[i] = op;
            }
            min_row = _min_row;
            max_row = _max_row;
            min_col = _min_col;
            max_col = _max_col;
        }
        
        bool isValidDomain(int row,
                           int col){
            return (row>=min_row && row<=max_row)
                            &&
                   (col>=min_col && col<=max_col);
        }
        
        
        void setOperationRule(
                              vector<pair<string,function<int(State*,int,int)>>> named_operations){
            for(int i=0;i <named_operations.size();i++){
                auto[nm,op] = named_operations[i];
                
                named_operationIndex[nm] = i;
                operations.push_back(op);
            }
        }
        
        void setQuery(
                      vector<pair<string,function<string(State*,int,int)>>> named_queries){
            for(int i=0;i <named_queries.size();i++){
                auto[nm,q] = named_queries[i];
                
                named_queryIndex[nm] = i;
                queries.push_back(q);
            }
        }
        
        int performOperation(
                         int op_index,
                         int row,
                         int col){
            try{
                if(op_index>=operations.size())
                    throw op_index;
                return operations[op_index](this,row,col);
            }catch(string e){
                cout<<"Operation Index Out-of-bound\n";
                exit(-1);
                return -1;
            }
        }
        
        int performOperation(string op_name,
                         int row,
                         int col){
            try{
                if(named_operationIndex.find(op_name)==named_operationIndex.end())
                    throw op_name;
                return operations[named_operationIndex[op_name]](this,row,col);
            }catch(string e){
                cout<<"Operation Undefined\n";
                exit(-1);
                return -1;
            }
        }
        
        void performAllOperation(int row,
                                 int col){
            for(auto op:operations){
                op(this,row,col);
            }
        }
        
        
        string performQuery(int q_index, int row,int col){
            try{
                if(q_index>=queries.size())
                    throw q_index;
                return queries[q_index](this,row,col);
            }catch(string e){
                cout<<"Operation Index Out-of-bound\n";
                exit(-1);
            }
            return "$";
        }
        
        string performQuery(string q_name, int row,int col){
            try{
                if(named_queryIndex.find(q_name)==named_queryIndex.end())
                    throw q_name;
                return queries[named_queryIndex[q_name]](this,row,col);
            }catch(string e){
                cout<<"Operation Index Out-of-bound\n";
                exit(-1);
            }
            return "$";
        }
        
        void print(){
            for(int col=min_col;col<=max_col;col++)cout<<"--";
            cout<<"\n";
            for(int row=min_row;row<=max_row;row++){
                for(int col=min_col;col<=max_col;col++){
                    cout<<stateSpace[row][col]<<" ";
                }
                cout<<"|\n";
            }
            for(int col=min_col;col<=max_col;col++)cout<<"--";
            cout<<"\n";
        }
        
        bool operator = (const State& st){
            return st.stateSpace == this->stateSpace;
        }
        
        
        friend ostream& operator<<(ostream& os, const State& st);
    };

    ostream& operator<<(ostream& os, const State& st){
        for(int col=st.min_col;col<=st.max_col;col++)cout<<"--";
        cout<<"\n";
        for(int row=st.min_row;row<=st.max_row;row++){
            for(int col=st.min_col;col<=st.max_col;col++){
                cout<<st.stateSpace[row][col]<<" ";
            }
            cout<<"|\n";
        }
        for(int col=st.min_col;col<=st.max_col;col++)cout<<"--";
        cout<<"\n";
        return os;
    }
}


pair<int,int> decode_0(string s){
    stringstream ss(s);
    string word;
    ss >> word;
    int a = stoi(word);
    ss >> word;
    int b = stoi(word);
    return {a,b};
}

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
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank-1]);
                return true;
            }else
                return false;
        }},
        {"SOUTH",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank, col_blank+1);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank][col_blank+1]);
                return true;
            }else
                return false;
        }},
        {"EAST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank-1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank-1][col_blank]);
                return true;
            }else
                return false;
        }},
        {"WEST",[](STATE::State *st,int row,int col){
            auto [row_blank,col_blank] = decode_0(st->performQuery("Where is the blank space?",-1,-1));
            bool isValid = st->isValidDomain(row_blank+1, col_blank);
            if(isValid){
                swap(st->stateSpace[row_blank][col_blank], st->stateSpace[row_blank+1][col_blank]);
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
