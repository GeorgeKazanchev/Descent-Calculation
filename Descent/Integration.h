#pragma once
#include "StateVector.h"
#include "Util.h"

//	Класс интегрирования движения СА.
class Integration {
public:
	StateVector Integrate(StateVector initStateVector, double heightEnd, double heightExit, double deltaTime);
	Util util;
private:
	void K(StateVector& stateVector, const StateVector& utilStateVector, double k[18][4], const double deltaTime);
	void RightSides(StateVector& stateVector, const StateVector& utilStateVector, const double k[18][4], double rightSides[18],
		const double deltaTime, int j);
	void AddK(StateVector& stateVector, const double k[18][4], const double deltaTime, int j);
	void UtilCalcRightSides(StateVector& sv, double rightSides[18]);
	void Increment(StateVector& stateVector, double k[18][4], double deltaTime);
};