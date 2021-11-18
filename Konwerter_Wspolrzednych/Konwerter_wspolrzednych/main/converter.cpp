#include "converter.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

void Converter::Lagrange(const long double& B, const long double& L, long double& phi, long double& lambda) const noexcept {
	long double U = 1 - e * sin(DegToRad(B));
	long double V = 1 + e * sin(DegToRad(B));
	long double K = pow((U / V), (e / 2));
	long double C = K * (tan(DegToRad(B / 2) + M_PI_4));
	phi = 2 * atan(C) - M_PI_2;
	lambda = fmod(L, 3.0);
	if (lambda > 1.5) {
		lambda -= 3.0;
	}
}
void Converter::Mercator(long double& phi, long double& lambda) const noexcept {
	long double p = sin(phi);
	long double q = cos(phi) * cos(DegToRad(lambda));
	long double r = 1 + cos(phi) * sin(DegToRad(lambda));
	long double s = 1 - cos(phi) * sin(DegToRad(lambda));
	phi = R0 * atan(p / q);
	lambda = 0.5 * R0 * log(r / s);
}
void Converter::Kruger(long double& xmer, long double& ymer) const noexcept  {
	long double a2 = 0.0008377318247344;
	long double a4 = 0.0000007608527788826;
	long double a6 = 0.000000001197638019173;
	long double a8 = 0.00000000000244337624241;
	xmer = xmer / R0;
	xmer = R0 * (xmer + a2 * sin(2 * xmer) + a4 * sin(4 * xmer) + a6 * sin(6 * xmer) + a8 * sin(8 * xmer));
	ymer = ymer / R0;
	ymer = R0 * (ymer + a2 * sin(2 * ymer) + a4 * sin(4 * ymer) + a6 * sin(6 * ymer) + a8 * sin(8 * ymer));
}
void Converter::PL2000(const long double& B, const long double& L, long double& N, long double& E) const noexcept {
	this->Lagrange(B, L, N, E);
	long double lambda = E;
	this->Mercator(N, E);
	this->Kruger(N, E);
	N = m0 * N;
	E = m0 * E + 500000 + round(L - lambda) / 3 * 1000000;
}
void Converter::WGS84(const long double& N, const long double& E, long double& B, long double& L) const noexcept {
	B = N / m0;
	L = (fmod(E, 1000000.0) - 500000) / m0;
	long double ygk = L;
	this->ReverseKruger(B, L);
	this->ReverseMercator(B, L);
	this->ReverseLagrange(B, L, E, ygk);
}
void Converter::ReverseKruger(long double& xgk, long double& ygk) const noexcept {
	long double b2 = -0.0008377321681641;
	long double b4 = -0.00000005905869626083;
	long double b6 = -0.0000000001673488904988;
	long double b8 = -0.0000000000002167737805597;
	xgk = xgk / R0;
	xgk = R0 * (xgk + b2 * sin(2 * xgk) + b4 * sin(4 * xgk) + b6 * sin(6 * xgk) + b8 * sin(8 * xgk));
	ygk = ygk / R0;
	ygk = R0 * (ygk + b2 * sin(2 * ygk) + b4 * sin(4 * ygk) + b6 * sin(6 * ygk) + b8 * sin(8 * ygk));
}
void Converter::ReverseMercator(long double& xmer, long double& ymer) const noexcept  {
	long double a = xmer / R0;
	long double b = ymer / R0;
	long double w = 2 * atan(exp(b)) - M_PI_2;
	xmer = asin(cos(w) * sin(a));
	ymer = atan(tan(w) / cos(a));
}
void Converter::ReverseLagrange(long double& phi, long double& lambda, const long double& E, const long double& ygk) const noexcept {
	long double c2 = 0.0033565514856;
	long double c4 = 0.0000065718731;
	long double c6 = 0.0000000176466;
	long double c8 = 0.000000000054;
	
	phi = RadToDeg(phi + c2 * sin(2 * phi) + c4 * sin(4 * phi) + c6 * sin(6 * phi) + c8 * sin(8 * phi));
	lambda = round(E - ygk * m0 - 500000) / 1000000 * 3 + RadToDeg(lambda);
}
long double DegToRad(long double value) {
	value = M_PI * value / 180.0;
	return value;
}
long double RadToDeg(long double value) {
	value = 180 * value / M_PI;
	return value;
}
