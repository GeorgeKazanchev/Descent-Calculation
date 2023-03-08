#pragma once
#include "Aerodynamics.h"

//	 Î‡ÒÒ —¿.
class Lander {
public:
	double mass;
	double lenght;
	double midshipArea;
	double midshipDiameter;
	double MomentsOfInertia[3];
	Aerodynamics aerodynamics;
	Lander();
	Lander(double mass, double length, double midshipArea, double momentsOfInertia[], const Aerodynamics& aerodynamics);
	Lander(const Lander& lander);
	Lander& operator =(const Lander& lander);
private:
	double PI = 3.1415926535;
};