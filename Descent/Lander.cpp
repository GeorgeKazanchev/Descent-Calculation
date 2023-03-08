#include "pch.h"
#include "Lander.h"
#include "Aerodynamics.h"
#include <math.h>

//	Конструктор без параметров.
Lander::Lander() { };

//	Конструктор.
Lander::Lander(double mass, double length, double midshipArea, double momentsOfInertia[], const Aerodynamics& aerodynamics) {
	this->mass = mass;
	this->lenght = length;
	this->midshipArea = midshipArea;
	this->midshipDiameter = 2 * sqrt(midshipArea / PI);
	MomentsOfInertia[0] = momentsOfInertia[0];
	MomentsOfInertia[1] = momentsOfInertia[1];
	MomentsOfInertia[2] = momentsOfInertia[2];
	this->aerodynamics = aerodynamics;
}

//	Конструктор копирования.
Lander::Lander(const Lander& lander) :
	mass(lander.mass), lenght(lander.lenght), midshipArea(lander.midshipArea), midshipDiameter(lander.midshipDiameter),
	MomentsOfInertia{ lander.MomentsOfInertia[0], lander.MomentsOfInertia[1], lander.MomentsOfInertia[2] },
	aerodynamics(Aerodynamics(lander.aerodynamics)) { };

//	Оператор присваивания.
Lander& Lander::operator =(const Lander& lander) {
	this->mass = lander.mass;
	this->lenght = lander.lenght;
	this->midshipArea = lander.midshipArea;
	this->midshipDiameter = lander.midshipDiameter;
	MomentsOfInertia[0] = lander.MomentsOfInertia[0];
	MomentsOfInertia[1] = lander.MomentsOfInertia[1];
	MomentsOfInertia[2] = lander.MomentsOfInertia[2];
	aerodynamics = lander.aerodynamics;
	return *this;
}