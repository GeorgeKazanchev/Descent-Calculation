#include "pch.h"
#include "StateVector.h"

//	Конструктор.
StateVector::StateVector(double time, double vx, double vy, double vz, double omx, double omy, double omz, double x, double y, double z,
	double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double height,
	const Lander& lander) {
	Time = time;
	Vx = vx;
	Vy = vy;
	Vz = vz;
	Omx = omx;
	Omy = omy;
	Omz = omz;
	X = x;
	Y = y;
	Z = z;
	A11 = a11;
	A12 = a12;
	A13 = a13;
	A21 = a21;
	A22 = a22;
	A23 = a23;
	A31 = a31;
	A32 = a32;
	A33 = a33;
	Height = height;
	this->lander = lander;
}

//	Конструктор копирования.
StateVector::StateVector(const StateVector& stateVector) :
	Time(stateVector.Time), Vx(stateVector.Vx), Vy(stateVector.Vy), Vz(stateVector.Vz),
	X(stateVector.X), Y(stateVector.Y), Z(stateVector.Z), Height(stateVector.Height),
	Omx(stateVector.Omx), Omy(stateVector.Omy), Omz(stateVector.Omz),
	A11(stateVector.A11), A12(stateVector.A12), A13(stateVector.A13),
	A21(stateVector.A11), A22(stateVector.A22), A23(stateVector.A23),
	A31(stateVector.A11), A32(stateVector.A32), A33(stateVector.A33),
	lander(Lander(stateVector.lander)) { };

//	Оператор присваивания.
StateVector& StateVector::operator =(const StateVector& stateVector) {
	Time = stateVector.Time;
	Vx = stateVector.Vx;
	Vy = stateVector.Vy;
	Vz = stateVector.Vz;
	Omx = stateVector.Omx;
	Omy = stateVector.Omy;
	Omz = stateVector.Omz;
	X = stateVector.X;
	Y = stateVector.Y;
	Z = stateVector.Z;
	A11 = stateVector.A11;
	A12 = stateVector.A12;
	A13 = stateVector.A13;
	A21 = stateVector.A21;
	A22 = stateVector.A22;
	A23 = stateVector.A23;
	A31 = stateVector.A31;
	A32 = stateVector.A32;
	A33 = stateVector.A33;
	Height = stateVector.Height;
	lander = stateVector.lander;
	return *this;
}