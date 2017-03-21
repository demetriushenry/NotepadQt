/*
 * ICalc.h
 *
 *  Created on: 15 de mar de 2017
 *      Author: sirineo
 */

#ifndef ICALC_H_
#define ICALC_H_

#include <memory>

class Calc;

class ICalc {

private:
	std::unique_ptr<Calc> pimpl;

public:
	ICalc();
	~ICalc();
	int Sum(int, int);
};

#endif /* ICALC_H_ */
