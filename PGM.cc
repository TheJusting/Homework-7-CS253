#include "PGM.h"
#include "Image.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

PGM::PGM(const string filename) : Image(){
        PGM::read(filename);
}

PGM::PGM(const PGM &a) : Image(){
        PGM::v = a.v;
        PGM::image = a.image;
        PGM::maxp = a.maxp;
        PGM::h = a.h;
        PGM::w = a.w;
}

PGM::~PGM(){}

PGM &PGM::operator=(const PGM &a){
        PGM::v = a.v;
        PGM::image = a.image;
        PGM::maxp = a.maxp;
        PGM::h = a.h;
        PGM::w = a.w;
        return *this;
}

int PGM::get(int column, int row) const{
        if(column > PGM::width() || column < 0 || row > PGM::height() || row < 0) throw string("Invalid arguments");
        return v[row][column];
}

void PGM::read(const string filename){
        string in;
        vector<int> temp;
        ifstream input;
        input.open(filename);
        getline(input, in);
        if(in == "P2") image = in;
        else throw string("Bad File: expected \"P2\" but got" + in);
        while(input >> in){
                        if(isdigit(in[0])){
                                if(w == -1) w = stoi(in);
                                else if (h == -1) h = stoi(in);
                                else if (maxp == -1) maxp = stoi(in);
                                else if(stoi(in) > maxp || stoi(in) < 0) throw string("Integer out of bounds");
                                else temp.push_back(stoi(in));
                        }
                        else if(in[0] == '#'){
                                if(in.length() == 1) getline(input, in);
                                continue;
                        }
                        else throw string("Bad File: unexpected character");
                        if(temp.size() == (unsigned int)w){
                                v.push_back(temp);
                                temp.clear();
                        }
        }
        if(v.size() < (unsigned int)h || v[0].size() < (unsigned int)w || v.size() > (unsigned int)h || v[0].size() > (unsigned int)w) throw string("Bad File: incorrect image size");
        input.close();
}

void PGM::write(const string filename) const{
        ofstream os;
        os.open(filename);
        os << PGM::image << "\n" << PGM::w << " " << PGM::h << "\n" << PGM::maxp << "\n";
                for(auto i : PGM::v){
                        for(auto j : i){
                                os << j << " ";
                        }
                        os << "\n";
                }
        os.close();
}

void PGM::write(ostream &stream) const{
        stream << PGM::image << "\n" << PGM::w << " " << PGM::h << "\n" << PGM::maxp << "\n";
        for(auto i : v){
                        for(auto j : i){
                                stream << j << " ";
                        }
                        stream << "\n";
                }
}

ostream &operator<<(ostream &os, const PGM &a){
        string temp;
        temp = a.image + "\n" + to_string(a.w) + " " + to_string(a.h) + "\n" + to_string(a.maxp) + "\n";
        for(auto i : a.v){
                        for(auto j : i){
                                temp += j + " ";
                        }
                        temp += "\n";
                }
        return os << temp;
}