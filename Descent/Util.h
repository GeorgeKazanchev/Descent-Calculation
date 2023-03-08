#pragma once
#include "StateVector.h"
#include "Atmosphere.h"

//	Класс вспомогательных методов.
class Util {
public:
	double Radius(const StateVector& stateVector) const;
	double Radius(double x, double y, double z) const;
	double Height(const StateVector& stateVector) const;
	double Height(double x, double y, double z) const;
	double Height(double radius) const;
	double GravityAcceleration(const StateVector& stateVector) const;
	double GravityAcceleration(double radius) const;
	double GravityAcceleration(double x, double y, double z) const;
	double Velocity(const StateVector& stateVector) const;
	double Velocity(double vx, double vy, double vz) const;
	double AirPressure(const StateVector& stateVector) const;
	double AirPressure(double v, double h) const;
	double CosinusRoll(const StateVector& stateVector) const;
	double CosinusRoll(double vy, double vz) const;
	double SinusRoll(const StateVector& stateVector) const;
	double SinusRoll(double vy, double vz) const;
	double Roll(const StateVector& stateVector) const;
	double Alpha(const StateVector& stateVector) const;
	double Mach(const StateVector& stateVector) const;
	double LongitudinalAngle(const StateVector& stateVector) const;
	double LongitudinalAngle(double x, double y, double z) const;
	double LateralAngle(const StateVector& stateVector) const;
	double LateralAngle(double x, double y, double z) const;
	double LongitudinalRange(const StateVector& stateVector) const;
	double LongitudinalRange(double x, double y, double z) const;
	double LateralRange(const StateVector& stateVector) const;
	double LateralRange(double x, double y, double z) const;
private:
	Atmosphere _atmosphere;
	const double EARTH_RADIUS = 6371000;
	const double G0 = 9.80665;
	const double PI = 3.1415926535;
};