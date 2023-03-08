#include "pch.h"
#include "InitialData.h"
#include "Integration.h"
#include "StateVector.h"
#include <iostream>

int main()
{
	InitialData initialData = InitialData();
	StateVector stateVector = initialData.GetInitialData();

	const double heightEnd = 0.0;
	const double heightExit = 85000.0;
	const double deltaTime = 0.01;

	Integration integration = Integration();
	integration.Integrate(stateVector, heightEnd, heightExit, deltaTime);
}