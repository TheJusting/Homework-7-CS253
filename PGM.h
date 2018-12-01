#ifndef PGM_H
#define PGM_H
#include "Image.h"
#include <vector>
#include <string>
#include <ostream>
using string = std::string;
class PGM : public Image{
        public:
                PGM(const string filename);
                PGM(const PGM &a);
                ~PGM();
                PGM &operator=(const PGM &a);
                friend std::ostream &operator<<(std::ostream &os, const PGM &a);
                void read(const string filename);
                void write(const string filename) const;
                void write(std::ostream &stream) const;
};
std::ostream &operator<<(std::ostream &os, const PGM &a);
#endif /*PGM_H*/
