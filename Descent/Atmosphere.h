#pragma once

//	Класс модели стандартной атмосферы Земли.
class Atmosphere {
public:
	double Density(double height, bool isGeopotential) const;
	double Pressure(double height, bool isGeopotential) const;
	double Temperature(double height, bool isGeopotential) const;
	double SpeedOfSound(double height, bool isGeopotential) const;
	double GeopotentialHeight(double height) const;
	double GeocentricHeight(double geopotentialHeight) const;
private:
	const double EARTH_CONDITIONAL_RADIUS = 6356767;
	const double R = 287.05287;
	const double G0 = 9.80665;
};