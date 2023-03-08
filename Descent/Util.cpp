#include "pch.h"
#include "Util.h"
#include "StateVector.h"
#include "Atmosphere.h"
#include <math.h>
#include <iostream>

//	������ ������-������� �� �� (�� ������� ��������� ��), �.
double Util::Radius(const StateVector& stateVector) const {
	double x = stateVector.X;
	double y = stateVector.Y;
	double z = stateVector.Z;
	return sqrt(x * x + y * y + z * z);
}

//	������ ������-������� �� �� (�� ����������� �� �� � ������������ ������� ���������), �.
double Util::Radius(double x, double y, double z) const {
	return sqrt(x * x + y * y + z * z);
}

//	������ ������ �� �� ��� ������������ ����� (�� ������� ��������� ��), �.
double Util::Height(const StateVector& stateVector) const {
	double radius = Radius(stateVector);
	return radius - EARTH_RADIUS;
}

//	������ ������ �� �� ��� ������������ ����� (�� ����������� �� �� � ������������ ������� ���������), �.
double Util::Height(double x, double y, double z) const {
	double radius = Radius(x, y, z);
	return radius - EARTH_RADIUS;
}

//	������ ������ �� �� ��� ������������ ����� (�� ������-������� �� ��), �.
double Util::Height(double radius) const {
	return radius - EARTH_RADIUS;
}

//	������ ��������� ���������� ������� (�� ������� ��������� ��), �/�^2.
double Util::GravityAcceleration(const StateVector& stateVector) const {
	double radius = Radius(stateVector);
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	������ ��������� ���������� ������� (�� ������-������� �� ��), �/�^2.
double Util::GravityAcceleration(double radius) const {
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	������ ��������� ���������� ������� (�� ����������� �� �� � ������������ ������� ���������), �/�^2.
double Util::GravityAcceleration(double x, double y, double z) const {
	double radius = Radius(x, y, z);
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	������ �������� �� �� ������������ �� ����� (� ������������ ������� - � ������ ������ ���������), �/�.
//	������ ������������ �� ������� ��������� ��.
double Util::Velocity(const StateVector& stateVector) const {
	double vx = stateVector.Vx;
	double vy = stateVector.Vy;
	double vz = stateVector.Vz;
	return sqrt(vx * vx + vy * vy + vz * vz);
}

//	������ �������� �� �� ������������ �� ����� (� ������������ ������� - � ������ ������ ���������), �/�.
//	������ ������������ �� ����������� ������� �������� �� �� � ���� ��������� ������� ���������.
double Util::Velocity(double vx, double vy, double vz) const {
	return sqrt(vx * vx + vy * vy + vz * vz);
}

//	������ ����������� ������, ��/(�*�^2).
double Util::AirPressure(const StateVector& stateVector) const {
	double v = Velocity(stateVector);
	double h = Height(stateVector);
	double ro = _atmosphere.Density(h, false);
	return ro * v * v / 2;
}

//	������ ����������� ������, ��/(�*�^2).
double Util::AirPressure(double v, double h) const {
	double ro = _atmosphere.Density(h, false);
	return ro * v * v / 2;
}

//	������ �������� ����������������� ���� �����.
double Util::CosinusRoll(const StateVector& stateVector) const {
	double vy = stateVector.Vy;
	double vz = stateVector.Vz;
	
	if ((vy == 0) && (vz == 0)) {
		return 0;
	}
	else {
		return -vy / sqrt(vy * vy + vz * vz);
	}
}

//	������ �������� ����������������� ���� �����.
double Util::CosinusRoll(double vy, double vz) const {
	return -vy / sqrt(vy * vy + vz * vz);
}

//	������ ������ ����������������� ���� �����.
double Util::SinusRoll(const StateVector& stateVector) const {
	double vy = stateVector.Vy;
	double vz = stateVector.Vz;

	if ((vy == 0) && (vz == 0)) {
		return 0;
	}
	else {
		return vz / sqrt(vy * vy + vz * vz);
	}
}

//	������ ������ ����������������� ���� �����.
double Util::SinusRoll(double vy, double vz) const {
	return vz / sqrt(vy * vy + vz * vz);
}

//	������ ����������������� ���� �����, ���.
double Util::Roll(const StateVector& stateVector) const {
	double cosinus = CosinusRoll(stateVector);
	double sinus = SinusRoll(stateVector);

	if (cosinus > 0) {
		return asin(sinus);
	}
	else if (cosinus < 0) {
		return PI - asin(sinus);
	}
	else {
		if (sinus > 0) {
			return PI / 2;
		}
		else {
			return -PI / 2;
		}
	}
}

//	������ ����������������� ���� �����, ���.
double Util::Alpha(const StateVector& stateVector) const {
	double vx = stateVector.Vx;
	double v = Velocity(stateVector);
	return acos(vx / v);
}

//	������ ����� ����.
double Util::Mach(const StateVector& stateVector) const {
	double h = Height(stateVector);
	double a = _atmosphere.SpeedOfSound(h, false);
	return Velocity(stateVector) / a;
}

//	������ ���������� ������� ���������, ���.
double Util::LongitudinalAngle(const StateVector& stateVector) const {
	double r = Radius(stateVector);
	return asin(sqrt(stateVector.X * stateVector.X + stateVector.Z * stateVector.Z) / r);
}

//	������ ���������� ������� ���������, ���.
double Util::LongitudinalAngle(double x, double y, double z) const {
	double r = Radius(x, y, z);
	return asin(sqrt(x * x + z * z) / r);
}

//	������ ������� ������� ���������, ���.
double Util::LateralAngle(const StateVector& stateVector) const {
	double r = Radius(stateVector);
	return asin(-stateVector.Z / r);
}

//	������ ������� ������� ���������, ���.
double Util::LateralAngle(double x, double y, double z) const {
	double r = Radius(x, y, z);
	return asin(-z / r);
}

//	������ ���������� ���������, �.
double Util::LongitudinalRange(const StateVector& stateVector) const {
	return LongitudinalAngle(stateVector) * EARTH_RADIUS;
}

//	������ ���������� ���������, �.
double Util::LongitudinalRange(double x, double y, double z) const {
	return LongitudinalAngle(x, y, z) * EARTH_RADIUS;
}

//	������ ������� ���������, �.
double Util::LateralRange(const StateVector& stateVector) const {
	return LateralAngle(stateVector) * EARTH_RADIUS;
}

//	������ ������� ���������, �.
double Util::LateralRange(double x, double y, double z) const {
	return LateralAngle(x, y, z) * EARTH_RADIUS;
}