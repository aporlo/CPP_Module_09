#include "RPN.hpp"

RPN::RPN():_rpn(""), _result(0) {
    throw RPN::ErrorException();
}

RPN::RPN(std::string rpn):_rpn(rpn),_result(0) {
    calculate();
}

RPN::RPN(RPN const & src)
{
    *this = src;
}

RPN &RPN::operator=(RPN const & copy)
{
    if (this != & copy)
    {
        this->_rpn = copy._rpn;
        this->_result = copy._result;
        this->_stack = copy._stack;
    }
    return (*this);
}

RPN::~RPN(){}

std::string RPN::getRPN(void) const {
    return this->_rpn;
}

int RPN::getResult(void) const {
    return this->_result;
}

std::stack<int> RPN::getStack(void) const {
    return this->_stack;
}

const char *OPT = "+-*/";


void RPN::checkRPN(std::string &rpn, int i) {
    if (!isdigit(rpn[i]) &&  !strchr(OPT, rpn[i]))
        throw RPN::ErrorException();
    if (rpn[i + 1] != ' ' && rpn[i + 1] != '\0')
        throw RPN::ErrorException();
    if (strchr(OPT, rpn[i]) && this->_stack.size() < 2)
        throw RPN::ErrorException();

}
void RPN::calculate() {
    for ( int i = 0; i < (int) this->_rpn.length(); i += 2) {
        checkRPN(this->_rpn, i);
        if (isdigit(this->_rpn[i]))
            this->_stack.push(this->_rpn[i] - 48);
        else if (this->_stack.size() >= 2 && strchr(OPT,this->_rpn[i]))
        {
            int res;
            int a = this->_stack.top();
            this->_stack.pop();
            int b = this->_stack.top();
            this->_stack.pop();
            
            switch (this->_rpn[i]) {
                case '+':
                    res = b + a;
                    break;
                case '-':
                    res = b - a;
                    break;
                case '*':
                    res = b * a;
                    break;
                case '/':
                    res = b / a;
                    break;
            }
            this->_stack.push(res);
        }
    }
    if (this->_stack.size() != 1)
        throw RPN::ErrorException();
    this->_result = this->_stack.top();
}
