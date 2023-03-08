#include "pch.h"
#include "FilesInterface.h"
#include "StateVector.h"
#include <fstream>
#include <math.h>

//	Вывод параметров движения в файл Excel.
void FilesInterface::WriteToFile(std::ofstream& fileOutput, const StateVector& stateVector, const Util& util, const double deltaTimeIntegr,
	const double deltaTimeWrite, bool writeLongitudinalRange = false, bool writeLateralRange = false, bool writeRadius = false,
	bool writeHeight = false, bool writeVelocity = false, bool writeCoordinates = false, bool writeVelocityComponents = false) {

	//	Если выводятся параметры в начальный момент времени, формируется "шапка" файла
	if (abs(stateVector.Time) < 1e-7) {
		fileOutput << "Time, sec";
		if (writeLongitudinalRange) fileOutput << "\t" << "L, km";
		if (writeLateralRange) fileOutput << "\t" << "B, km";
		if (writeRadius) fileOutput << "\t" << "r, km";
		if (writeVelocity) fileOutput << "\t" << "V, m/s";
		if (writeCoordinates) fileOutput << "\t" << "x, km" << "\t" << "y, km" << "\t" << "z, km";
		if (writeVelocityComponents) fileOutput << "\t" << "Vx, m/s" << "\t" << "Vy, m/s" << "\t" << "Vz, m/s";
		fileOutput << "\n";
	}

	//	Вывод параметров движения в файл Эксель с заданным шагом
	if (static_cast<int>(round(stateVector.Time / deltaTimeIntegr)) % static_cast<int>(round(deltaTimeWrite / deltaTimeIntegr)) == 0) {
		fileOutput << stateVector.Time;
		if (writeLongitudinalRange) fileOutput << "\t" << util.LongitudinalRange(stateVector) / 1000;
		if (writeLateralRange) fileOutput << "\t" << util.LateralRange(stateVector) / 1000;
		if (writeRadius) fileOutput << "\t" << util.Radius(stateVector) / 1000;
		if (writeVelocity) fileOutput << "\t" << util.Velocity(stateVector);
		if (writeCoordinates) fileOutput << "\t" << stateVector.X / 1000 << "\t" << stateVector.Y / 1000 << "\t" << stateVector.Z / 1000;
		if (writeVelocityComponents) fileOutput << "\t" << stateVector.Vx << "\t" << stateVector.Vy << "\t" << stateVector.Vz;
		fileOutput << "\n";
	}
}

//	Конструктор.
FilesInterface::FilesInterface(std::string fileOutputName) {
	FileOutput.open(fileOutputName);
	FileOutput.precision(10);
}