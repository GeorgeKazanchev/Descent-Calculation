#include "pch.h"
#include "Util.h"
#include "StateVector.h"
#include "Atmosphere.h"
#include <math.h>
#include <iostream>

//	Расчёт радиус-вектора ЦМ СА (по вектору состояния СА), м.
double Util::Radius(const StateVector& stateVector) const {
	double x = stateVector.X;
	double y = stateVector.Y;
	double z = stateVector.Z;
	return sqrt(x * x + y * y + z * z);
}

//	Расчёт радиус-вектора ЦМ СА (по координатам ЦМ СА в инерциальной системе координат), м.
double Util::Radius(double x, double y, double z) const {
	return sqrt(x * x + y * y + z * z);
}

//	Расчёт высоты ЦМ СА над поверхностью Земли (по вектору состояния СА), м.
double Util::Height(const StateVector& stateVector) const {
	double radius = Radius(stateVector);
	return radius - EARTH_RADIUS;
}

//	Расчёт высоты ЦМ СА над поверхностью Земли (по координатам ЦМ СА в инерциальной системе координат), м.
double Util::Height(double x, double y, double z) const {
	double radius = Radius(x, y, z);
	return radius - EARTH_RADIUS;
}

//	Расчёт высоты ЦМ СА над поверхностью Земли (по радиус-вектору ЦМ СА), м.
double Util::Height(double radius) const {
	return radius - EARTH_RADIUS;
}

//	Расчёт ускорения свободного падения (по вектору состояния СА), м/с^2.
double Util::GravityAcceleration(const StateVector& stateVector) const {
	double radius = Radius(stateVector);
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	Расчёт ускорения свободного падения (по радиус-вектору ЦМ СА), м/с^2.
double Util::GravityAcceleration(double radius) const {
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	Расчёт ускорения свободного падения (по координатам ЦМ СА в инерциальной системе координат), м/с^2.
double Util::GravityAcceleration(double x, double y, double z) const {
	double radius = Radius(x, y, z);
	return G0 * (EARTH_RADIUS / radius) * (EARTH_RADIUS / radius);
}

//	Расчёт скорости ЦМ СА относительно ЦМ Земли (и относительно воздуха - в данной версии программы), м/с.
//	Расчёт производится по вектору состояния СА.
double Util::Velocity(const StateVector& stateVector) const {
	double vx = stateVector.Vx;
	double vy = stateVector.Vy;
	double vz = stateVector.Vz;
	return sqrt(vx * vx + vy * vy + vz * vz);
}

//	Расчёт скорости ЦМ СА относительно ЦМ Земли (и относительно воздуха - в данной версии программы), м/с.
//	Расчёт производится по компонентам вектора скорости ЦМ СА в осях связанной системы координат.
double Util::Velocity(double vx, double vy, double vz) const {
	return sqrt(vx * vx + vy * vy + vz * vz);
}

//	Расчёт скоростного напора, кг/(м*с^2).
double Util::AirPressure(const StateVector& stateVector) const {
	double v = Velocity(stateVector);
	double h = Height(stateVector);
	double ro = _atmosphere.Density(h, false);
	return ro * v * v / 2;
}

//	Расчёт скоростного напора, кг/(м*с^2).
double Util::AirPressure(double v, double h) const {
	double ro = _atmosphere.Density(h, false);
	return ro * v * v / 2;
}

//	Расчёт косинуса аэродинамического угла крена.
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

//	Расчёт косинуса аэродинамического угла крена.
double Util::CosinusRoll(double vy, double vz) const {
	return -vy / sqrt(vy * vy + vz * vz);
}

//	Расчёт синуса аэродинамического угла крена.
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

//	Расчёт синуса аэродинамического угла крена.
double Util::SinusRoll(double vy, double vz) const {
	return vz / sqrt(vy * vy + vz * vz);
}

//	Расчёт аэродинамического угла крена, рад.
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

//	Расчёт пространственного угла атаки, рад.
double Util::Alpha(const StateVector& stateVector) const {
	double vx = stateVector.Vx;
	double v = Velocity(stateVector);
	return acos(vx / v);
}

//	Расчёт числа Маха.
double Util::Mach(const StateVector& stateVector) const {
	double h = Height(stateVector);
	double a = _atmosphere.SpeedOfSound(h, false);
	return Velocity(stateVector) / a;
}

//	Расчёт продольной угловой дальности, рад.
double Util::LongitudinalAngle(const StateVector& stateVector) const {
	double r = Radius(stateVector);
	return asin(sqrt(stateVector.X * stateVector.X + stateVector.Z * stateVector.Z) / r);
}

//	Расчёт продольной угловой дальности, рад.
double Util::LongitudinalAngle(double x, double y, double z) const {
	double r = Radius(x, y, z);
	return asin(sqrt(x * x + z * z) / r);
}

//	Расчёт боковой угловой дальности, рад.
double Util::LateralAngle(const StateVector& stateVector) const {
	double r = Radius(stateVector);
	return asin(-stateVector.Z / r);
}

//	Расчёт боковой угловой дальности, рад.
double Util::LateralAngle(double x, double y, double z) const {
	double r = Radius(x, y, z);
	return asin(-z / r);
}

//	Расчёт продольной дальности, м.
double Util::LongitudinalRange(const StateVector& stateVector) const {
	return LongitudinalAngle(stateVector) * EARTH_RADIUS;
}

//	Расчёт продольной дальности, м.
double Util::LongitudinalRange(double x, double y, double z) const {
	return LongitudinalAngle(x, y, z) * EARTH_RADIUS;
}

//	Расчёт боковой дальности, м.
double Util::LateralRange(const StateVector& stateVector) const {
	return LateralAngle(stateVector) * EARTH_RADIUS;
}

//	Расчёт боковой дальности, м.
double Util::LateralRange(double x, double y, double z) const {
	return LateralAngle(x, y, z) * EARTH_RADIUS;
}