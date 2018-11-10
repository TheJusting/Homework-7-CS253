#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <string>
using string = std::string;
class Image{
        public:
                string NW = "NW", NE = "NE", SW = "SW", SE = "SE";
                static Image* create(const string filename);
                static void scale(int val, int range1, int range2);
                virtual ~Image();
                bool empty() const;
                int height() const;
                int width() const;
                int range() const;
                int get(int column, int row) const;
                void min(const Image &a);
				void min(string direction, const Image &a);
				void minHelper(const Image &a, int j, int i, int j1, int i1)
				void scale(int val, int range1, int range2);
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

