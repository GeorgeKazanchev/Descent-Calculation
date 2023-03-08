#include "pch.h"
#include "InitialData.h"
#include "Lander.h"
#include <math.h>

const StateVector InitialData::GetInitialData() {
	y = h + EARTH_RADIUS;

	midshipArea = PI * midshipDiameter * midshipDiameter / 4;

	a11 = cos(theta0) * cos(psi0);
	a12 = sin(theta0);
	a13 = -cos(theta0) * sin(psi0);
	a21 = -sin(theta0) * cos(psi0) * cos(gamma0) + sin(psi0) * sin(gamma0);
	a22 = cos(theta0) * cos(gamma0);
	a23 = cos(psi0) * sin(gamma0) + sin(theta0) * sin(psi0) * cos(gamma0);
	a31 = sin(theta0) * cos(psi0) * sin(gamma0) + sin(psi0) * cos(gamma0);
	a32 = -cos(theta0) * sin(gamma0);
	a33 = cos(psi0) * cos(gamma0) - sin(gamma0) * sin(psi0) * sin(theta0);

	vxi = v0 * cos(Theta0) * cos(Psi0);
	vyi = v0 * sin(Theta0);
	vzi = -v0 * cos(Theta0) * sin(Psi0);

	vx = vxi * a11 + vyi * a12 + vzi * a13;
	vy = vxi * a21 + vyi * a22 + vzi * a23;
	vz = vxi * a31 + vyi * a32 + vzi * a33;

	Aerodynamics aerodynamics = Aerodynamics(m0);
	Lander lander = Lander(mass, length, midshipArea, momentsOfInertia, aerodynamics);
	StateVector stateVector(time, vx, vy, vz, omx, omy, omz, x, y, z, a11, a12, a13, a21, a22, a23, a31, a32, a33, h, lander);

	return stateVector;
}
