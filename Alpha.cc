#include "Alpha.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

Alpha::Alpha(string filename): Image(){
        Alpha::read(filename);
}

Alpha::Alpha(const Alpha &a): Image(){
        v = a.v;
        image = a.image;
        maxp = a.maxp;
}

Alpha::~Alpha(){}

Alpha &Alpha::operator=(const Alpha &a){
        v = a.v;
        image = a.image;
        maxp = a.maxp;
        return *this;
}

void Alpha::read(const string filename){
        string in;
        maxp = 25;
        ifstream input(filename);
        unsigned int stCount = 0;
        getline(input, in);
        if(in == "Alpha") image = in;
        else throw string("Bad file: expected \"Alpha\"");
        while(getline(input, in)){
                vector<int> temp;
                for(unsigned int i = 0; i < in.length(); i++){
                        if(in[i] == '#') break;
                        else if(isalpha(in[i])){
				int c(tolower(in[i]) - 122); 
                                temp.push_back(abs(c));
                        }
                        else if(in[i] == ' ' || in[i] == '\t') continue;
                        else if(in[i] == '*'){
                                if(v.empty() || v.back()[v.back().size()-1] == -1) temp.push_back(-1);
                                else{
                                        int diff = v.back().size() - temp.size();
                                        for(int j = 0; j < diff; j++) temp.push_back(temp[temp.size()-1]);
                                }
                        }
                        else if(in[i] != '\n') throw string("Bad File: bad character " + in[i]);
                }
                if(temp.empty()) continue;
                else if(v.empty() || (v.empty() && temp[temp.size()-1] == -1)){
                        if(temp[temp.size()-1] == -1) stCount++;
                        v.push_back(temp);
                }
                else if(v.back()[v.back().size()-1] == -1 && temp[temp.size()-1] != -1){
                        int c = v.back()[v.back().size()-2];
                        unsigned int diff = temp.size() - v.back().size();
                        v.back()[v.back().size()-1] = c;
                        for(unsigned int i = 0; i < diff; i++){
                                v.back().push_back(c);
                        }
                        v.push_back(temp);
                }
                else if(temp.size() > v[0].size() || temp.size() < v[0].size()) throw string("Bad File: incorrect line length of " + to_string(temp.size()) + "when expecting length of " + to_string(v[0].size()));
                else if(stCount == v.size()) throw string("Bad File: all lines contain asterisks");
                else v.push_back(temp);
        }
        w = v[0].size();
        h = v.size();
        input.close();
}

void Alpha::write(string filename) const{
        ofstream os;
        os.open(filename);
        os << image << "\n";
        for(auto i : v){
		for(auto j : i){
                	os << (char) ((j*-1) + 122);
                }
                os << "\n";
        }
        os.close();
}

void Alpha::write(ostream &stream) const{
        stream << image << "\n";
        for(auto i : v){
                        for(auto j : i){
                stream << (char)((j*-1) + 122);
                        }
                        stream << "\n";
        }
}

ostream &operator<<(ostream &os, const Alpha &a){
        string temp = "Alpha\n";
        for(auto i : a.v){
                for(auto j : i){
                        temp += to_string((char)((j*-1)+122));
                }
                temp += "\n";
        }
        return os << temp;
}
