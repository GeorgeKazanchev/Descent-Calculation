#pragma once

//	Класс модели аэродинамических характеристик СА.
class Aerodynamics {
public:
	double Cx(double M, double attackAngle);
	double Cy(double M, double attackAngle);
	double mz();
	double mxOmx();
	double myOmy();
	double mzOmz();
	double m0[3];
	Aerodynamics();
	Aerodynamics(double m0[]);
	Aerodynamics(const Aerodynamics& aerodynamics);
	Aerodynamics& operator =(const Aerodynamics& aerodynamics);
};