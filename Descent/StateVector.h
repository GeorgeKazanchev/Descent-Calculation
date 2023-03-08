#pragma once
#include "Lander.h"

//	Класс вектора состояния СА.
class StateVector {
public:
	double Time;
	double Vx;
	double Vy;
	double Vz;
	double Omx;
	double Omy;
	double Omz;
	double X;
	double Y;
	double Z;
	double A11;
	double A12;
	double A13;
	double A21;
	double A22;
	double A23;
	double A31;
	double A32;
	double A33;
	double Height;
	Lander lander;
	StateVector(double time, double vx, double vy, double vz, double omx, double omy, double omz, double x, double y, double z,
		double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double height,
		const Lander& lander);
	StateVector(const StateVector& stateVector);
	StateVector& operator =(const StateVector& stateVector);
};