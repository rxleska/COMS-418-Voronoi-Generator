
#ifndef CALLBACK_HPP
#define CALLBACK_HPP

namespace OGLcallbacks{

bool rayIntersectsSegment(double x, double y, double theta, double x1, double y1, double x2, double y2, double *ix, double *iy);
void initOpenGL();
void update(int value);
void handleKeypress(unsigned char key, int x, int y);
void display();
void writeDCELStoFile();


}


#endif // CALLBACK_HPP