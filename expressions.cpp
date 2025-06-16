#include "expressions.h"
#include <sstream>
#include <stdexcept>

Expression::Expression(const std::string& expressionStr)
{
	std::stringstream ss(expressionStr);
	ss >> operand1 >> operation >> operand2;
};

double Expression::evaluate() const {
	switch (operation) {
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1 * operand2;
		case '/': return operand2 != 0 ? operand1 / operand2 : throw std::runtime_error("Divisão por zero.");
		default: throw std::invalid_argument("Operador Inválido.");
	}
};

std::string Expression::toString() const {
	return std::to_string(operand1) + " " + operation + " " + std::to_string(operand2);
};
