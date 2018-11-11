#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <string>
using string = std::string;
class Image{
        public:
<<<<<<< HEAD
                const static int NW = 0, NE = 1, SW = 2, SE = 3;
=======
                string NW = "NW", NE = "NE", SW = "SW", SE = "SE";
>>>>>>> 98a0ccacac415534d3a1121d23e88efa1a8c0b3f
                static Image* create(const string filename);
                static void scale(int val, int range1, int range2);
                virtual ~Image();
                bool empty() const;
                int height() const;
                int width() const;
                int range() const;
                int get(int column, int row) const;
                void min(const Image &a);
<<<<<<< HEAD
		double scale(int val, int range1, int range2);
=======
				void min(string direction, const Image &a);
				void minHelper(const Image &a, int j, int i, int j1, int i1)
				void scale(int val, int range1, int range2);
>>>>>>> 98a0ccacac415534d3a1121d23e88efa1a8c0b3f
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

