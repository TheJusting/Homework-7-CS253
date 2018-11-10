#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <string>
using string = std::string;
class Image{
        public:
                const static int NW = 0, NE = 1, SW = 2, SE = 3;
                static Image* create(const string filename);
                virtual ~Image();
                bool empty() const;
                int height() const;
                int width() const;
                int range() const;
                int get(int column, int row) const;
                void min(const Image &a);
		double scale(int val, int range1, int range2);
                void mirror();
                void rotate(int degrees);
                void resize(double factor);
                virtual void read(const string filename) = 0;
                virtual void write(const string filename) const = 0;
                virtual void write(std::ostream &stream) const = 0;
        protected:
                Image();
                Image(const Image &a);
                Image &operator=(const Image &a);
                std::vector<std::vector<int>> v;
                string image;
                int h, w, maxp;
};
#endif
