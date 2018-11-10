#ifndef ALPHA_H
#define ALPHA_H
#include "Image.h"
#include <vector>
#include <string>
using string = std::string;
class Alpha : public Image{
        public:
                Alpha(const string filename);
                Alpha(const Alpha &a);
                ~Alpha();
                Alpha &operator=(const Alpha &a);
                friend std::ostream &operator<<(std::ostream &os, const Alpha &a);
                void read(string filename);
                void write(string filename) const;
                void write(std::ostream &stream) const;
};
std::ostream &operator<<(std::ostream &os, const Alpha &a);
#endif /*ALPHA_H*/
