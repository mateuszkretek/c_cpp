#include "signal.h"

void Signal::czyt(Machine& machine) {
	std::map<int, int>::iterator it;
	it = machine.PO.find(machine.A);
	if (it != machine.PO.end())
		machine.S = it->second;
}

void Signal::pisz(Machine& machine) {
	std::map<int, int>::iterator it;
	it = machine.PO.find(machine.A);
	if (it != machine.PO.end())
		it->second = machine.S;
}

void Signal::wes(Machine& machine) {
	machine.S = machine.M_S;
}

void Signal::wys(Machine& machine) {
	machine.M_S = machine.S;
}

void Signal::wei(Machine& machine) {
	machine.KOD = (machine.M_S / 64);
	machine.AD = (machine.M_S % 64);
}

void Signal::wyad(Machine& machine) {
	machine.M_A = machine.AD;
}

void Signal::wea(Machine& machine) {
	machine.A = machine.M_A;
}

void Signal::wel(Machine& machine) {
	machine.L = machine.M_A;
}

void Signal::wyl(Machine& machine) {
	machine.M_A = machine.L;
}

void Signal::il(Machine& machine) {
	++machine.L;
}

void Signal::weja(Machine& machine) {
	machine.JAL = machine.M_S;
}

void Signal::dod(Machine& machine) {
	machine.JAL += machine.AK;
}

void Signal::ode(Machine& machine) {
	int buffer = machine.JAL;
	machine.JAL = machine.AK - buffer;
}

void Signal::przep(Machine& machine) {
	machine.JAL = machine.JAL;
}

void Signal::weak(Machine& machine)
{
	machine.AK = machine.JAL;
}

void Signal::wyak(Machine& machine) {
	machine.M_S = machine.AK;
}

void Signal::as(Machine& machine) {
	machine.M_S = machine.M_A;
}

void Signal::sa(Machine& machine) {
	machine.M_A = machine.M_S;
}