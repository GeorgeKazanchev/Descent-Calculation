#include "pch.h"
#include "Aerodynamics.h"

//	Расчёт коэффициента продольной силы.
double Aerodynamics::Cx(double M, double attackAngle) {
	double al = attackAngle * 57.2957795130823;

	if (al < 0) {
		al *= -1;
	}

	const int TABLE_ELEMENTS = 19;

	double al_[TABLE_ELEMENTS] = { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0,
		140.0, 150.0, 160.0, 170.0, 180.0 };
	double Cx_[TABLE_ELEMENTS] = { 1.70, 1.64, 1.47, 1.24, 1.00, 0.86, 0.80, 0.80, 0.92, 1.04, 1.16, 1.20, 1.20,
		1.14, 1.03, 0.94, 0.83, 0.81, 0.80 };

	double Cx;

	for (int i = 0; i < TABLE_ELEMENTS; ++i) {
		if ((al >= al_[i]) && (al < al_[i + 1])) {
			Cx = Cx_[i] + (al - al_[i]) * (Cx_[i + 1] - Cx_[i]) / (al_[i + 1] - al_[i]);
		}
	}

	return Cx;
}

//	Расчёт коэффициента нормальной силы.
double Aerodynamics::Cy(double M, double attackAngle) {
	double al = attackAngle * 57.2957795130823;

	if (al < 0) {
		al *= -1;
	}

	const int TABLE_ELEMENTS = 19;

	double al_[TABLE_ELEMENTS] = { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0,
		140.0, 150.0, 160.0, 170.0, 180.0 };
	double Cy_[TABLE_ELEMENTS] = { 0.00, 0.22, 0.41, 0.46, 0.39, 0.20, 0.02, -0.14, -0.21, -0.21, -0.18, -0.02, 0.07,
		0.15, 0.19, 0.18, 0.14, 0.06, 0.00 };

	double Cy;

	for (int i = 0; i < TABLE_ELEMENTS; ++i) {
		if ((al >= al_[i]) && (al < al_[i + 1])) {
			Cy = Cy_[i] + (al - al_[i]) * (Cy_[i + 1] - Cy_[i]) / (al_[i + 1] - al_[i]);
		}
	}

	return Cy;
}

//	Расчёт коэффициента статического аэродинамического момента тангажа.
double Aerodynamics::mz() {
	return 0.00;
}

//	Расчёт коэффициента демпфирующего аэродинамического момента крена.
double Aerodynamics::mxOmx() {
	return 0.00;
}

//	Расчёт коэффициента демпфирующего аэродинамического момента рыскания.
double Aerodynamics::myOmy() {
	return 0.00;
}

//	Расчёт коэффициента демпфирующего аэродинамического момента тангажа.
double Aerodynamics::mzOmz() {
	return 0.00;
}

//	Конструктор без параметров.
Aerodynamics::Aerodynamics() {}

//	Конструктор.
Aerodynamics::Aerodynamics(double m0[]) {
	this->m0[0] = m0[0];
	this->m0[1] = m0[1];
	this->m0[2] = m0[2];
}

//	Конструктор копирования.
Aerodynamics::Aerodynamics(const Aerodynamics& aerodynamics):
	m0{aerodynamics.m0[0], aerodynamics.m0[1], aerodynamics.m0[2] } { };

//	Оператор присваивания.
Aerodynamics& Aerodynamics::operator =(const Aerodynamics& aerodynamics) {
	m0[0] = aerodynamics.m0[0];
	m0[1] = aerodynamics.m0[1];
	m0[2] = aerodynamics.m0[2];
	return *this;
}