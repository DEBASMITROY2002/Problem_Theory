//
//  problem_spec_header.h
//  Problem_Solver
//
//  Created by DEBASMIT ROY on 02/03/23.
//

#ifndef problem_spec_header_h
#define problem_spec_header_h

#include <iostream>
#include <sstream>
#include <string>

pair<int,int> decode_0(string s){
    stringstream ss(s);
    string word;
    ss >> word;
    int a = stoi(word);
    ss >> word;
    int b = stoi(word);
    return {a,b};
}


#endif /* problem_spec_header_h */
