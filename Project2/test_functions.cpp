#include <cmath>
# define M_PI           3.14159265358979323846  /* pi */

double testfunc1(double x) {
	return 3 * pow(x, 4) - 4 * pow(x, 3) - 12 * pow(x, 2) + 2;
}

double testfunc2(double x) {
	return x - (pow(x, 3) / 6) + (pow(x, 5) / 120);
}

double testfunc3(double x) {
	return (-1 * pow(x, 3)) + (12 * sin(x * 3)) - (5 * x);
}

double testfunc4(double x) {
	return sin(x) - x + 0.15;
}

double testfunc5(double x) {
	return pow(x,2) - (5*sin(x));
}

double testfunc6(double x) {
	return exp(-x) * cos(M_PI*x);
}