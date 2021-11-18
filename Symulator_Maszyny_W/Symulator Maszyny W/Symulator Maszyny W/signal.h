#pragma once
#include "machine.h"
#include <vector>

class Signal {
public:
	virtual void czyt(Machine& machine);
	virtual void pisz(Machine& machine);
	virtual void wes(Machine& machine);
	virtual void wys(Machine& machine);
	virtual void wei(Machine& machine);
	virtual void wyad(Machine& machine);
	virtual void wea(Machine& machine);
	virtual void wel(Machine& machine);
	virtual void wyl(Machine& machine);
	virtual void il(Machine& machine);
	virtual void weja(Machine& machine);
	virtual void dod(Machine& machine);
	virtual void ode(Machine& machine);
	virtual void przep(Machine& machine);
	virtual void weak(Machine& machine);
	virtual void wyak(Machine& machine);
	virtual void as(Machine& machine);
	virtual void sa(Machine& machine);
};