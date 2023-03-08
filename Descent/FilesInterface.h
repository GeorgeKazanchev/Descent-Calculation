#pragma once
#include "StateVector.h"
#include "Util.h";
#include <fstream>
#include <string>

class FilesInterface {
public:
	std::ofstream FileOutput;
	void WriteToFile(std::ofstream& fileOutput, const StateVector& stateVector, const Util& util, const double deltaTimeIntegr,
		const double deltaTimeWrite, bool writeLongitudinalRange, bool writeLateralRange, bool writeRadius, bool writeHeight,
		bool writeVelocity, bool writeCoordinates, bool writeVelocityComponents);
	FilesInterface(std::string fileOutputName);
};