#include "pch.h"
#include "Atmosphere.h"
#include "StateVector.h"
#include "Util.h"
#include <math.h>

//	������ ��������� ��������� ����� ��� �������� ������ (������� ��������� ��������� - ��/�^3).
//	isGeopotential - ������� ����, ��� ���������� � ����� ������ �������� ����������������.
double Atmosphere::Density(double height, bool isGeopotential = true) const {
	double H = height;

	if (!isGeopotential)	//	���� � �������� ��������� � ����� �������� ��������������� ������
		H = GeopotentialHeight(height);

	return Pressure(H, true) / (R * Temperature(H, true));
}

//	������ �������� ��������� ����� ��� �������� ������ (������� ��������� �������� - ��).
	//	isGeopotential - ������� ����, ��� ���������� � ����� ������ �������� ����������������.
double Atmosphere::Pressure(double height, bool isGeopotential = true) const {
	double H = height;

	if (!isGeopotential)	//	���� � �������� ��������� � ����� �������� ��������������� ������
		H = GeopotentialHeight(height);

	double H_[9] = { -2000, 0, 11000, 20000, 32000, 47000, 51000, 71000, 85000.1 };
	double T_[8] = { 301.15, 288.15, 216.65, 216.65, 228.65, 270.65, 270.65, 214.65 };
	double P_[8] = { 1.27774e+5, 1.01325e+5, 2.26320e+4, 5.47487e+3, 8.68014e+2, 1.10906e+2, 6.69384e+1, 3.95639e+0 };
	double gradient[8] = { -0.0065, -0.0065, 0.0000, 0.0010, 0.0028, 0.0000, -0.0028, -0.0020 };

	double T, P;

	for (int i = 0; i < 9; ++i) {
		if ((H >= H_[i]) && (H < H_[i + 1])) {
			T = T_[i] + gradient[i] * (H - H_[i]);
			if ((gradient[i]) == 0)
				P = P_[i] * exp(-G0 * (H - H_[i]) / (R * T));
			else
				P = P_[i] * pow((1 + gradient[i] * (H - H_[i]) / T_[i]), -G0 / (R * gradient[i]));
			break;
		}
	}

	return P;
}

//	������ ����������� ��������� ����� ��� �������� ������ (������� ��������� - �).
//	isGeopotential - ������� ����, ��� ���������� � ����� ������ �������� ����������������.
double Atmosphere::Temperature(double height, bool isGeopotential = true) const {
	double H = height;

	if (!isGeopotential)	//	���� � �������� ��������� � ����� �������� ��������������� ������
		H = GeopotentialHeight(height);

	double H_[9] = { -2000, 0, 11000, 20000, 32000, 47000, 51000, 71000, 85000.1 };
	double T_[8] = { 301.15, 288.15, 216.65, 216.65, 228.65, 270.65, 270.65, 214.65 };
	double gradient[8] = { -0.0065, -0.0065, 0.0000, 0.0010, 0.0028, 0.0000, -0.0028, -0.0020 };

	double T;

	for (int i = 0; i < 9; ++i) {
		if ((H >= H_[i]) && (H < H_[i + 1])) {
			T = T_[i] + gradient[i] * (H - H_[i]);
			break;
		}
	}

	return T;
}

//	������ �������� �����, �/�.
double Atmosphere::SpeedOfSound(double height, bool isGeopotential = true) const {
	double H = height;

	if (!isGeopotential)	//	���� � �������� ��������� � ����� �������� ��������������� ������
		H = GeopotentialHeight(height);

	return 20.046796 * sqrt(Temperature(H, true));
}

//	������ ���������������� ������ �� ��������������� ������
double Atmosphere::GeopotentialHeight(double height) const {
	return EARTH_CONDITIONAL_RADIUS * height / (EARTH_CONDITIONAL_RADIUS + height);
}

//	������ ��������������� ������ �� ���������������� ������
double Atmosphere::GeocentricHeight(double geopotentialHeight) const {
	return EARTH_CONDITIONAL_RADIUS * geopotentialHeight / (EARTH_CONDITIONAL_RADIUS - geopotentialHeight);
}