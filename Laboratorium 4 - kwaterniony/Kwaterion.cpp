// Kwaterion.cpp

#define _USE_MATH_DEFINES

#include "Kwaterion.h"
#include <cmath>


Kwaternion::Kwaternion(double skalar, double x, double y, double z) : skalar(skalar), x(x), y(y), z(z) {}


Kwaternion Kwaternion::operator+(const Kwaternion& q) const {
	return Kwaternion(skalar + q.skalar, x + q.x, y + q.y, z + q.z);
}


Kwaternion Kwaternion::operator-(const Kwaternion& q) const {
	return Kwaternion(skalar - q.skalar, x - q.x, y - q.y, z - q.z);
}


Kwaternion Kwaternion::operator*(const Kwaternion& q) const {
	return Kwaternion(
		skalar * q.skalar - x * q.x - y * q.y - z * q.z,
		skalar * q.x + x * q.skalar + y * q.z - z * q.y,
		skalar * q.y - x * q.z + y * q.skalar + z * q.x,
		skalar * q.z + x * q.y - y * q.x + z * q.skalar
	);
}


Kwaternion Kwaternion::sprzez() const {
	return Kwaternion(skalar, -x, -y, -z);
}


double Kwaternion::norma() const {
	return std::sqrt(skalar * skalar + x * x + y * y + z * z);
}


void Kwaternion::normalizuj() {
	double n = norma();
	if (n > 0) {
		skalar /= n; x /= n; y /= n; z /= n;
	}
}


void Kwaternion::obrocPunkt(double& px, double& py, double& pz) const {
	Kwaternion punkt(0, px, py, pz);
	Kwaternion q_spr = this->sprzez();
	Kwaternion wynik = (*this) * punkt * q_spr;
	px = wynik.x;
	py = wynik.y;
	pz = wynik.z;
}


void Kwaternion::wypisz() const {
	std::cout << "(" << skalar << " + " << x << "i + " << y << "j + " << z << "k)" << std::endl;
}


Kwaternion kwaternionRotacji(double katStopnie, double ax, double ay, double az) {
	double katRad = katStopnie * M_PI / 180.0;
	double polowa = katRad / 2.0;
	double s = std::sin(polowa);
	Kwaternion q(std::cos(polowa), ax * s, ay * s, az * s);
	q.normalizuj();
	return q;
}