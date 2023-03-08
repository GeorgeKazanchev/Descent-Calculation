#include "pch.h"
#include "Integration.h"
#include "FilesInterface.h"
#include "StateVector.h"
#include "Util.h"
#include <math.h>
#include <iostream>
#include <fstream>

//	Интегрирование движения СА из исходного вектора состояния initStateVector до высоты heightEnd.
//	При превышении СА высоты heightExit будет произведён выход из метода, т.к. СА не будет захвачен атмосферой.
//	deltaTime - шаг интегрирования по времени.
StateVector Integration::Integrate(StateVector initStateVector, double heightEnd, double heightExit, double deltaTime) {

	//	Инициализация вектора состояния, используемого в процессе интегрирования
	StateVector stateVector = initStateVector;
	//	Инициализация вспомогательного вектора состояния, используемого для сохранения
	//	вектора состояния СА на начало шага интегрирования
	StateVector utilStateVector = initStateVector;
	//	Расчёт начального значения высоты ЦМ СА над поверхностью Земли
	Util util;
	stateVector.Height = util.Height(stateVector);
	//	Создание экземпляра класса, используемого для взаимодействия с файлами (для вывода рассчитанных параметров движения)
	FilesInterface file = FilesInterface("Results.xls");
	const double deltaTimeWrite = 0.1;		//	Шаг вывода параметров движения в файл Эксель
	file.WriteToFile(file.FileOutput, stateVector, util, deltaTime, deltaTimeWrite, true, true, true, true, true, true, true);

	//	Объявление вспомогательных переменных, используемых в расчётах
	double k[18][4];	//	Матрица коэффициентов метода Рунге-Кутты

	//	Цикл интегрирования уравнения движения СА
	while (stateVector.Height > heightEnd) {

		//	При отсутствии захвата СА атмосферой выходит из цикла интегрирования
		stateVector.Height = util.Height(stateVector);
		if (stateVector.Height > heightExit)
			break;

		//	Сохранение вектора состояния СА на начало шага интегрирования
		utilStateVector = stateVector;

		//	Непосредственно интегрирование на текущей итерации цикла
		K(stateVector, utilStateVector, k, deltaTime);
		Increment(stateVector, k, deltaTime);

		//	Вывод параметров движения в файл Excel
		file.WriteToFile(file.FileOutput, stateVector, util, deltaTime, deltaTimeWrite, true, true, true, true, true, true, true);
		std::cout << stateVector.Time << "  " << util.Height(stateVector) << "  " << util.Velocity(stateVector) <<
			"  " << util.Alpha(stateVector) * 57.2957795130823 << "\n";
		//std::cout << stateVector.Time << "  " << util.Height(stateVector) << "  " << util.Velocity(stateVector) << "  " <<
		//	stateVector.lander.aerodynamics.Cx(util.Mach(stateVector), util.Alpha(stateVector)) << "  " <<
		//	stateVector.lander.aerodynamics.Cy(util.Mach(stateVector), util.Alpha(stateVector)) << "\n";
		//std::cout << stateVector.Time << "  " << util.Height(stateVector) << "  " << stateVector.A31 << "  " << stateVector.A32 <<
		//	"  " << stateVector.A33 << "\n";
	}

	file.FileOutput.close();
	return stateVector;
}

//	Расчёт матрицы коэффициентов метода Рунге-Кутты.
void Integration::K(StateVector& stateVector, const StateVector& utilStateVector, double k[18][4], const double deltaTime) {
	double rightSides[18];

	for (int j = 0; j < 4; ++j) {
		RightSides(stateVector, utilStateVector, k, rightSides, deltaTime, j);
		for (int i = 0; i < 18; ++i) {
			k[i][j] = deltaTime * rightSides[i];
		}
	}
}

//	Расчёт вектора значений правых частей дифференциальных уравнений движения.
void Integration::RightSides(StateVector& stateVector, const StateVector& utilStateVector, const double k[18][4],
	double rightSides[18], const double deltaTime, int j) {
	
	stateVector = utilStateVector;

	if (j == 0) {
		UtilCalcRightSides(stateVector, rightSides);
	}
	else if (((j == 1)) || ((j == 2))) {
		AddK(stateVector, k, deltaTime, j - 1);
		UtilCalcRightSides(stateVector, rightSides);
	}
	else if (j == 3) {
		AddK(stateVector, k, deltaTime, j - 1);
		UtilCalcRightSides(stateVector, rightSides);
		stateVector = utilStateVector;
	}
	else {
		throw "В метод передано неверное значение переменной j.";
	}
}

//	Изменение вектора состояния внутри одного шага интегрирования методом Рунге-Кутты.
void Integration::AddK(StateVector& stateVector, const double k[18][4], const double deltaTime, int j) {
	if ((j == 0) || (j == 1)) {
		stateVector.Time += deltaTime / 2;
		stateVector.Vx += k[0][j] / 2;
		stateVector.Vy += k[1][j] / 2;
		stateVector.Vz += k[2][j] / 2;
		stateVector.Omx += k[3][j] / 2;
		stateVector.Omy += k[4][j] / 2;
		stateVector.Omz += k[5][j] / 2;
		stateVector.X += k[6][j] / 2;
		stateVector.Y += k[7][j] / 2;
		stateVector.Z += k[8][j] / 2;
		stateVector.A11 += k[9][j] / 2;
		stateVector.A12 += k[10][j] / 2;
		stateVector.A13 += k[11][j] / 2;
		stateVector.A21 += k[12][j] / 2;
		stateVector.A22 += k[13][j] / 2;
		stateVector.A23 += k[14][j] / 2;
		stateVector.A31 += k[15][j] / 2;
		stateVector.A32 += k[16][j] / 2;
		stateVector.A33 += k[17][j] / 2;
	}
	else if (j == 2) {
		stateVector.Time += deltaTime;
		stateVector.Vx += k[0][j];
		stateVector.Vy += k[1][j];
		stateVector.Vz += k[2][j];
		stateVector.Omx += k[3][j];
		stateVector.Omy += k[4][j];
		stateVector.Omz += k[5][j];
		stateVector.X += k[6][j];
		stateVector.Y += k[7][j];
		stateVector.Z += k[8][j];
		stateVector.A11 += k[9][j];
		stateVector.A12 += k[10][j];
		stateVector.A13 += k[11][j];
		stateVector.A21 += k[12][j];
		stateVector.A22 += k[13][j];
		stateVector.A23 += k[14][j];
		stateVector.A31 += k[15][j];
		stateVector.A32 += k[16][j];
		stateVector.A33 += k[17][j];
	}
	else {
		throw "В метод передано неверное значение переменной j.";
	}
}

//	Вспомогательный метод для расчёта вектора значений правых частей дифференциальных уравнения движения
void Integration::UtilCalcRightSides(StateVector& sv, double rightSides[18]) {
	rightSides[0] = (-sv.Omy * sv.Vz + sv.Omz * sv.Vy) - util.AirPressure(sv) * sv.lander.midshipArea / sv.lander.mass
		* sv.lander.aerodynamics.Cx(util.Mach(sv), util.Alpha(sv)) - util.GravityAcceleration(sv) / util.Radius(sv) * (sv.X * sv.A11 +
			sv.Y * sv.A12 + sv.Z * sv.A13);
	rightSides[1] = (-sv.Omz * sv.Vx + sv.Omx * sv.Vz) - util.AirPressure(sv) * sv.lander.midshipArea / sv.lander.mass
		* sv.lander.aerodynamics.Cy(util.Mach(sv), util.Alpha(sv)) * util.CosinusRoll(sv) - util.GravityAcceleration(sv) / util.Radius(sv) *
		(sv.X * sv.A21 + sv.Y * sv.A22 + sv.Z * sv.A23);
	rightSides[2] = (-sv.Omx * sv.Vy + sv.Omy * sv.Vx) + util.AirPressure(sv) * sv.lander.midshipArea / sv.lander.mass
		* sv.lander.aerodynamics.Cy(util.Mach(sv), util.Alpha(sv)) * util.SinusRoll(sv) - util.GravityAcceleration(sv) / util.Radius(sv) *
		(sv.X * sv.A31 + sv.Y * sv.A32 + sv.Z * sv.A33);
	rightSides[3] = sv.lander.midshipArea * util.AirPressure(sv) * sv.lander.lenght * 
		(sv.lander.aerodynamics.m0[0] - sv.lander.lenght * fabs(sv.lander.aerodynamics.mxOmx() * sv.Omx / util.Velocity(sv))) /
		sv.lander.MomentsOfInertia[0] + (sv.lander.MomentsOfInertia[1] - sv.lander.MomentsOfInertia[2]) * sv.Omy * sv.Omz / sv.lander.MomentsOfInertia[0];
	rightSides[4] = sv.lander.midshipArea * util.AirPressure(sv) * sv.lander.lenght / sv.lander.MomentsOfInertia[1] *
		(sv.lander.aerodynamics.m0[1] + sv.lander.aerodynamics.mz() * util.SinusRoll(sv) - sv.lander.lenght / util.Velocity(sv)
			* fabs(sv.lander.aerodynamics.myOmy()) * sv.Omy) - (sv.lander.MomentsOfInertia[0] - sv.lander.MomentsOfInertia[2]) /
		sv.lander.MomentsOfInertia[1] * sv.Omx * sv.Omz;
	rightSides[5] = sv.lander.midshipArea * util.AirPressure(sv) * sv.lander.lenght / sv.lander.MomentsOfInertia[2] *
		(sv.lander.aerodynamics.m0[2] + sv.lander.aerodynamics.mz() * util.CosinusRoll(sv) - sv.lander.lenght / util.Velocity(sv)
			* fabs(sv.lander.aerodynamics.mzOmz()) * sv.Omz) - (sv.lander.MomentsOfInertia[1] - sv.lander.MomentsOfInertia[0]) /
		sv.lander.MomentsOfInertia[2] * sv.Omx * sv.Omy;
	rightSides[6] = sv.Vx * sv.A11 + sv.Vy * sv.A21 + sv.Vz * sv.A31;
	rightSides[7] = sv.Vx * sv.A12 + sv.Vy * sv.A22 + sv.Vz * sv.A32;
	rightSides[8] = sv.Vx * sv.A13 + sv.Vy * sv.A23 + sv.Vz * sv.A33;
	rightSides[9] = sv.Omz * sv.A21 - sv.Omy * sv.A31;
	rightSides[10] = sv.Omz * sv.A22 - sv.Omy * sv.A32;
	rightSides[11] = sv.Omz * sv.A23 - sv.Omy * sv.A33;
	rightSides[12] = -sv.Omz * sv.A11 + sv.Omx * sv.A31;
	rightSides[13] = -sv.Omz * sv.A12 + sv.Omx * sv.A32;
	rightSides[14] = -sv.Omz * sv.A13 + sv.Omx * sv.A33;
	rightSides[15] = sv.Omy * sv.A11 - sv.Omx * sv.A21;
	rightSides[16] = sv.Omy * sv.A12 - sv.Omx * sv.A22;
	rightSides[17] = sv.Omy * sv.A13 - sv.Omx * sv.A23;
}

//	Приращение параметров вектора состояния.
void Integration::Increment(StateVector& stateVector, double k[18][4], double deltaTime) {
	stateVector.Time += deltaTime;
	stateVector.Vx += (k[0][0] + 2 * k[0][1] + 2 * k[0][2] + k[0][3]) / 6;
	stateVector.Vy += (k[1][0] + 2 * k[1][1] + 2 * k[1][2] + k[1][3]) / 6;
	stateVector.Vz += (k[2][0] + 2 * k[2][1] + 2 * k[2][2] + k[2][3]) / 6;
	stateVector.Omx += (k[3][0] + 2 * k[3][1] + 2 * k[3][2] + k[3][3]) / 6;
	stateVector.Omy += (k[4][0] + 2 * k[4][1] + 2 * k[4][2] + k[4][3]) / 6;
	stateVector.Omz += (k[5][0] + 2 * k[5][1] + 2 * k[5][2] + k[5][3]) / 6;
	stateVector.X += (k[6][0] + 2 * k[6][1] + 2 * k[6][2] + k[6][3]) / 6;
	stateVector.Y += (k[7][0] + 2 * k[7][1] + 2 * k[7][2] + k[7][3]) / 6;
	stateVector.Z += (k[8][0] + 2 * k[8][1] + 2 * k[8][2] + k[8][3]) / 6;
	stateVector.A11 += (k[9][0] + 2 * k[9][1] + 2 * k[9][2] + k[9][3]) / 6;
	stateVector.A12 += (k[10][0] + 2 * k[10][1] + 2 * k[10][2] + k[10][3]) / 6;
	stateVector.A13 += (k[11][0] + 2 * k[11][1] + 2 * k[11][2] + k[11][3]) / 6;
	stateVector.A21 += (k[12][0] + 2 * k[12][1] + 2 * k[12][2] + k[12][3]) / 6;
	stateVector.A22 += (k[13][0] + 2 * k[13][1] + 2 * k[13][2] + k[13][3]) / 6;
	stateVector.A23 += (k[14][0] + 2 * k[14][1] + 2 * k[14][2] + k[14][3]) / 6;
	stateVector.A31 += (k[15][0] + 2 * k[15][1] + 2 * k[15][2] + k[15][3]) / 6;
	stateVector.A32 += (k[16][0] + 2 * k[16][1] + 2 * k[16][2] + k[16][3]) / 6;
	stateVector.A33 += (k[17][0] + 2 * k[17][1] + 2 * k[17][2] + k[17][3]) / 6;
}