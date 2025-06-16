#pragma once
#include <string>

class Expression {
private:
	double operand1;
	double operand2;
	char operation;

public:
	Expression(const std::string& expressionStr);
	double evaluate() const;
	std::string toString() const;

};