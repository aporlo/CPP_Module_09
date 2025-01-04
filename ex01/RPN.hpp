#ifndef RPN_H
# define RPN_H

#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <cstdlib>


class RPN {
    private:
        std::string         _rpn;
        std::stack<int>     _stack;
        int                 _result;

    public:
        RPN(void);
        RPN(std::string rpn);
        RPN(RPN const & src);
        ~RPN(void);

        RPN & operator=(RPN const& copy);

        std::string getRPN(void) const;
        std::stack<int> getStack(void) const;
        int getResult(void) const;
        void    calculate(void);
        
        void    checkRPN(std::string &rpn, int i);
        class ErrorException: public std::exception
        {
            public:
                virtual const char* what() const throw() {return "Error";}
        };    

};

#endif
