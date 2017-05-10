#include <iostream>
#include <stdio.h>
#include <cmath>
#include <complex>
#include <pngwriter.h>
#include <sstream>
#include <iomanip>

using namespace std;

struct color {
        double h;
        double s;
        double v;
} col;

// declare constants
const int imgWidth = 8000;
const int imgHeight = 8000;
const int max_iter = 1024;
const double scale = 6/(sqrt(pow(imgWidth/2,2) + pow(imgHeight/2,2)));
const double rad = 3.1415/180.0;

color iter(complex<double> z,complex<double> c) {

	int iter = 0;
	int samecount = 0;
	complex<double> z1;

	while (abs(z)<4 && iter<max_iter && samecount<3) {
		z1 = c*z*(cos(z));
		if(abs(z1-z)<0.001) {
			samecount++;
		}
		z = z1;
		iter++;
	}

	// return a color tuple
	double deg = rad*iter;
	col.h = sin(deg);
	col.s = .75;
	col.v = .75;

	return col;
}

int render() {	
	complex<double> c(1.0,0.1);
	//define png name
	stringstream ss;
	cout << c;
	ss << "out/julia" << c << ".png";
	// init image
	pngwriter png(imgWidth,imgHeight,0,ss.str().c_str());
	
	// iterate through each pixel
	for(int i=-imgWidth/2; i<imgWidth; i++) {
		for(int j=-imgHeight/2; j<imgHeight; j++) {
			// get color for given pixel
			complex<double> z(i-imgWidth/2,j-imgHeight/2);
			z = scale*z;	
			color pix = iter(z,c);
			// draw pixel
			png.plotHSV(i,j,col.h,col.s,col.v);
		}
		cout << i << "\n";
	}
	png.close();
	return 0;
}

int main() {
        render();
}
