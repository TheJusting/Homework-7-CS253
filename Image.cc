#include "PGM.h"
#include "Image.h"
#include "Alpha.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

Image* Image::create(const string filename){
        Image* im;
	ifstream in;
	string name;
	in.open(filename);
	if(in.fail()) throw string("Bad File: file " + filename + " does not exist.");
	else{
		in >> name;
		if(name == "P2") im = new PGM(filename);
		else if(name == "Alpha") im = new Alpha(filename);
		else throw string("Bad File: Expected \"Alpha\" or \"P2\", got " + name);
	}
        return im;
}

Image::Image() : h(-1), w(-1), maxp(-1){}

Image::Image(const Image &a){
        Image::v = a.v;
        Image::w = a.w;
        Image::h = a.h;
        Image::maxp = a.maxp;
        Image::image = a.image;
}

Image &Image::operator=(const Image &a){
        Image::v = a.v;
        Image::image = a.image;
        Image::maxp = a.maxp;
        Image::h = a.h;
        Image::w = a.w;
        return *this;
}

Image::~Image(){}

Image::iterator(): row(0), it(v[0].begin(){}

Image::iterator(int rowVal, const vector<int>::iterator &iter) : row(rowVal), it(iter){}

Image::iterator(const Image::iterator &iter) : itr(iter.itr), itc(iter.itc){}

Image::iterator &operator=(const Image::iterator &iter){
	return Image::iterator(iter);
}

Image::iterator Image::iterator::begin() const{
	return Image::iterator(0, it.begin());
}

Image::iterator Image::iterator::end() const{
	return Image::iterator((int)v.size()-1, v[row].end());
}

Image::iterator &operator++(){
	if(*it == *(v[row].end()-1)){
		++row;
		it = v[row].begin();
	}
	else ++it;
	return *this;
}

Image::iterator &operator++(int){
	const auto temp = *this;
	++*this;
	return temp;
}

Image::iterator &operator--(){
	if(*it == *(v[row].begin())){
		--row;
		it = v[row].end()-1;
	}
	else --it;
	return *this;
}

Image::iterator &operator--(int){
	const auto temp = *this;
	--*this;
	return temp;
}

int &operator*() const{
	return *it;
}

bool &operator==(const Image::iterator &iter) const{
	return *it == *iter;
}

bool &operator!=(const Image::iterator &iter) const{
	return *it != *iter;
}

void Image::min(const Image &a){
	Image::min(Image::NW, a);
}

void Image::min(int direction, const Image &a){
	int col, row;
	if(a.width() < Image::width()) col = a.width();
	else col = Image::width();
	if(a.height() < Image::height()) row = a.height();
	else row = Image::height();
	switch(direction){
		case NW:
			for(auto i = 0; i < row; i++){
				for(auto j = 0; j < col; j++){
					Image::minHelper(a, j, i, j, i);
				}
			}
			break;
		case NE:
			for(auto i = 0; i < row; i++){
				for(auto j = 0; j < col; j++){
					Image::minHelper(a, Image::width()-(1+j), i, a.width()-(1+j), i);
				}
			}
			break;
		case SW:
			for(auto i = 0; i < row; i++){
				for(auto j = 0; j < col; j++){
					Image::minHelper(a, j,Image::height()-(1+i), j, a.height()-(1+i)); 
				}
			}
			break;
		case SE:
			for(auto i = 0; i < row; i++){
				for(auto j = 0; j < col; j++){
					Image::minHelper(a, Image::width()-(1+j), Image::height()-(1+i), a.width()-(1+j), a.height()-(1+i)); 
				}
			}
			break;
		default:
			throw string("Invalid direction declaration " + direction);
			break;
	}
}


void Image::minHelper(const Image &a, int j, int i, int j1, int i1){
	double lhs, rhs;
	bool lScaled = false;
	if(a.range() < Image::range()){
		rhs = Image::scale(a.get(j1, i1), a.range() - 1, Image::range() - 1);
		lhs = Image::get(j, i);
	}else if(Image::range() < a.range()){
		lhs = Image::scale(Image::get(j, i), Image::range() - 1, a.range() - 1);
		rhs = a.get(j1, i1);
		lScaled = true;
	}else{
		lhs = Image::get(j, i);
		rhs = a.get(j1, i1);
	}
	if(rhs < lhs){
		if(lScaled){
				rhs = Image::scale(rhs, a.range() - 1, Image::range() - 1);
				v[i][j] = rhs;
		}else v[i][j] = rhs;
	}
}

double Image::scale(double val, int range1, int range2){
	val /= (double)range1;
	val *= range2;
        return val;
}

void Image::max(const Image &a){
	Image::max(Image::NW, a);
}

void Image::max(int direction, const Image &a){
	int col, row;
	if(a.width() < Image::width()) col = a.width();
	else col = Image::width();
	if(a.height() < Image::height()) row = a.height();
	else row = Image::height();
	for(auto i = 0; i < row; i++){
		for(auto j = 0; j < col; j++){
			switch(direction){
			case NW:
				Image::maxHelper(a, j, i, j, i);
				break;
			case NE:
				Image::maxHelper(a, Image::width()-(1+j), i, a.width()-(1+j), i);
				break;
			case SW:
				Image::maxHelper(a, j,Image::height()-(1+i), j, a.height()-(1+i)); 
				break;
			case SE:
				Image::maxHelper(a, Image::width()-(1+j), Image::height()-(1+i), a.width()-(1+j), a.height()-(1+i)); 
				break;
			default:
				throw string("Invalid direction declaration " + direction);
				break;
			}
		}
	}
}


void Image::maxHelper(const Image &a, int j, int i, int j1, int i1){
	double lhs, rhs;
	bool lScaled = false;
	if(a.range() < Image::range()){
		rhs = Image::scale(a.get(j1, i1), a.range() - 1, Image::range() - 1);
		lhs = Image::get(j, i);
	}else if(Image::range() < a.range()){
		lhs = Image::scale(Image::get(j, i), Image::range() - 1, a.range() - 1);
		rhs = a.get(j1, i1);
		lScaled = true;
	}else{
		lhs = Image::get(j, i);
		rhs = a.get(j1, i1);
	}
	if(rhs > lhs){
		if(lScaled){
				rhs = Image::scale(rhs, a.range() - 1, Image::range() - 1);
				v[i][j] = rhs;
		}else v[i][j] = rhs;
	}
}

int Image::get(int column, int row) const{
	if(column >= Image::width() || column < 0 || row >= Image::width() || row < 0) throw string("Invalid parameters " + to_string(column) + ", " + to_string(row));
	return v[row][column]; 
}

bool Image::empty() const{
        if(v.empty()) return true;
        else return false;
}

int Image::height() const{
        return Image::h;
}

int Image::width() const{
        return Image::w;
}

int Image::range() const{
        return Image::maxp + 1;
}

void Image::mirror(){
    for(unsigned int i = 0; i < Image::v.size(); i++){
        for(unsigned int j = 0; j < (Image::v[i].size() / 2); j++){
            int c = Image::v[i][j];
            Image::v[i][j] = Image::v[i][Image::v[i].size()- j - 1];
            Image::v[i][Image::v[i].size()-j-1] = c;
        }
    }
}

void Image::rotate(int degrees){
        if(degrees % 90 != 0) throw string("Invalid degrees of rotation: must be a multiple of 90, but got " + to_string(degrees));
        else if(degrees == 0 || degrees % 360 == 0) return;
                else if(degrees % 270 == 0) degrees = 3;
        else if(degrees % 180 == 0) degrees = 2;
        else degrees = 1;
        while(degrees > 0){
                vector<vector<int>> v2;
                                vector<int> temp;
                for(unsigned int cols = 0; cols < Image::v[0].size(); cols++){
                        for(int rows = Image::v.size() - 1; rows >= 0; rows--){
                                temp.push_back(Image::v[rows][cols]);
                        }
                                                v2.push_back(temp);
                }
                Image::v = v2;
                                int swap = Image::h;
                                Image::h = Image::w;
                                Image::w = swap;
                degrees--;
        }
}

void Image::resize(double factor){
        if(factor == 2){
                        for(unsigned int i = 0; i < Image::v.size(); i += 2){
                                for(unsigned int j = 0; j < Image::v[i].size(); j += 2){
                                                Image::v[i].insert(Image::v[i].begin()+(j+1), Image::v[i][j]);
                                }
                                vector<int> temp(Image::v[i]);
                                Image::v.insert(Image::v.begin()+(i+1), temp);
                        }
                        Image::h *= 2;
                        Image::w *= 2;
        }
        else if(factor == 0.5){
                        vector<vector<int>> v2;
                        for(unsigned int i = 1; i < Image::v.size(); i+=2){
                                        vector<int> temp;
                                        for(unsigned int j = 1; j < Image::v[i].size(); j+=2){
                                                        int avg = (Image::v[i][j] + Image::v[i-1][j] + Image::v[i][j-1] + Image::v[i-1][j-1])/4;
                                                        temp.push_back(avg);
                                        }
                                        v2.push_back(temp);
                        }
                        Image::v = v2;
                        Image::h /= 2;
                        Image::w /= 2;
        }
        else throw string(to_string(factor) + "is an invalid factor for resize");
}

Image &Image::operator-=(const Image &a){
	Image::min(a);
	return *this;
}

Image &Image::operator+=(const Image &a){
	Image::max(a);
	return *this;
}

Image &Image::operator/=(const double d){
	if(d == 0) throw string("cannot divide by 0");
	Image::resize(1/d);
	return *this;
}

Image &Image::operator*=(const double d){
	Image::resize(d);
	return *this;
}

Image::operator bool() const{
	if(!Image::empty()) return true;
	else return false;
}

std::ostream &operator<<(std::ostream &os, const Image &a){
	string temp(a.image + "\n");
	if(h != -1 && w != -1 && maxp != -1){
		temp += a.w + " " + a.h + "\n" + maxp + "\n";
	}
	for(auto i : a.v){
		for(auto j : i){
			temp += j;
		}
		temp += "\n";
	}
	return temp;
}

std::istream &operator>>(std::istream &is, const Image &a){
	try{
		string temp;
		is >> temp;
		if((temp == "P2" && image == "Alpha") || (temp == "Alpha" && image == "P2")) throw string("err");
		
	catch(string err){
		is.setstate(failbit);
		return is;
	}
}
