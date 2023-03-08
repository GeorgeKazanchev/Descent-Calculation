#pragma once
#include "StateVector.h"

//	Класс предварительной обработки исходных данных для интегрирования уравнения движения СА.
class InitialData {
public:
	double time = 0.0;
	double v0 = 7800.0;
	double Theta0 = -8.0 * 0.0174532925;
	double Psi0 = 0.0 * 0.0174532925;
	//double theta0 = -90.0 * 0.0174532925;
	double theta0 = Theta0;
	double psi0 = 0.0 * 0.0174532925;
	double gamma0 = 0.0 * 0.0174532925;
	double omx = 0.0;
	double omy = 0.0;
	double omz = 0.0;
	double x = 0.0;
	double h = 84000.0;
	double z = 0.0;
	double midshipDiameter = 2.2;
	double mass = 2800.0;
	double length = 2.16;
	double momentsOfInertia[3]{ 200.0, 1000.0, 1000.0};
	double m0[3]{ 0.0, 0.0, 0.0 };
	const StateVector GetInitialData();
private:
	double y;
	double midshipArea;
	double a11, a12, a13, a21, a22, a23, a31, a32, a33;
	double vxi, vyi, vzi;
	double vx, vy, vz;
	const double EARTH_RADIUS = 6371000;
	const double PI = 3.1415926535;
	const double RADIANS_IN_DEGREE = 0.0174532925;
};