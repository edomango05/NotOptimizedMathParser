#ifndef MATH_PARSER_H
#define MATH_PARSER_H
// Math constants
#define M_PI 3.141592653589793238462643383279502884
#define M_NEPERO 2.71828182845904523536

#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <cmath>
#include <assert.h>

struct MathParser
{

    MathParser(const std::string &raw)
    {
        std::vector<Token> tokens;
        tokenize(raw, tokens);
        shuntingYard(tokens);
    }
    double integrate(double a, double b, size_t n)
    {
        double dx = (b - a) / n;
        double area = 0.0;
        for (int i = 0; i < n; i++)
        {
            area += evaluateFunctionInX(a + (i + 0.5) * dx) * dx;
        }
        return area;
    }
    double evaluate()
    {
        std::vector<double> stack;
        for (auto &t : output_stack)
        {
            switch (t.type)
            {
            case NodeType::Number:
                stack.push_back(std::stod(t.str));
                break;
            case NodeType::Function:
            {
                const double rhs = stack.back();
                stack.pop_back();
                if (t.str == "sin")
                {
                    stack.push_back(std::sin(rhs));
                }
                else if (t.str == "cos")
                {
                    stack.push_back(std::cos(rhs));
                }
                else if (t.str == "log")
                {
                    stack.push_back(std::log10(rhs));
                }
                else if (t.str == "ln")
                {
                    stack.push_back(std::log(rhs));
                }
            }
            break;
            case NodeType::Operator:
            {
                const double rhs = stack.back();
                stack.pop_back();
                if (stack.size() == 0)
                {
                    switch (t.str[0])
                    {
                    case '+':
                        stack.push_back(rhs);
                        break;
                    case '-':
                        stack.push_back(-rhs);
                        break;
                    }
                    continue;
                }
                const double lhs = stack.back();
                stack.pop_back();
                switch (t.str[0])
                {
                case '^':
                    stack.push_back(std::pow(lhs, rhs));
                    break;
                case '*':
                    stack.push_back(lhs * rhs);
                    break;
                case '/':
                    stack.push_back(lhs / rhs);
                    break;
                case '+':
                    stack.push_back(lhs + rhs);
                    break;
                case '-':
                    stack.push_back(lhs - rhs);
                    break;
                }
            }
            break;
            }
        }
        return stack.back();
    }
    double evaluateFunctionInX(double x)
    {
        std::vector<double> stack;
        for (auto &t : output_stack)
        {
            switch (t.type)
            {
            case NodeType::Number:
                stack.push_back(std::stod(t.str));
                break;
            case NodeType::Variable:
                stack.push_back(x);
                break;
            case NodeType::Function:
            {
                const double rhs = stack.back();
                stack.pop_back();
                if (t.str == "sin")
                {
                    stack.push_back(std::sin(rhs));
                }
                else if (t.str == "asin")
                {
                    stack.push_back(std::asin(rhs));
                }
                else if (t.str == "sinh")
                {
                    stack.push_back(std::sinh(rhs));
                }
                else if (t.str == "cos")
                {
                    stack.push_back(std::cos(rhs));
                }
                else if (t.str == "acos")
                {
                    stack.push_back(std::acos(rhs));
                }
                else if (t.str == "cosh")
                {
                    stack.push_back(std::cosh(rhs));
                }
                else if (t.str == "tan")
                {
                    stack.push_back(std::tan(rhs));
                }
                else if (t.str == "atan")
                {
                    stack.push_back(std::atan(rhs));
                }
                else if (t.str == "tanh")
                {
                    stack.push_back(std::tanh(rhs));
                }
                else if (t.str == "log")
                {
                    stack.push_back(std::log10(rhs));
                }
                else if (t.str == "ln")
                {
                    stack.push_back(std::log(rhs));
                }
                else if (t.str == "sqrt")
                {
                    stack.push_back(std::sqrt(rhs));
                }
                else if (t.str == "abs")
                {
                    stack.push_back(std::abs(rhs));
                }
            }
            break;
            case NodeType::Operator:
            {
                const double rhs = stack.back();
                stack.pop_back();
                const double lhs = stack.back();
                stack.pop_back();
                switch (t.str[0])
                {
                case '^':
                    stack.push_back(std::pow(lhs, rhs));
                    break;
                case '*':
                    stack.push_back(lhs * rhs);
                    break;
                case '/':
                    stack.push_back(lhs / rhs);

                    break;
                case '+':
                    stack.push_back(lhs + rhs);
                    break;
                case '-':
                    stack.push_back(lhs - rhs);
                    break;
                }
            }
            break;
            }
        }
        return stack.back();
    }
    double evaluateFunction(const std::map<std::string, double> &variables)
    {
        std::vector<double> stack;
        for (auto &t : output_stack)
        {
            switch (t.type)
            {
            case NodeType::Number:
                stack.push_back(std::stod(t.str));
                break;
            case NodeType::Variable:
                stack.push_back(variables.find(t.str)->second);
                break;
            case NodeType::Function:
            {
                const double rhs = stack.back();
                stack.pop_back();
                if (t.str == "sin")
                {
                    stack.push_back(std::sin(rhs));
                }
                else if (t.str == "asin")
                {
                    stack.push_back(std::asin(rhs));
                }
                else if (t.str == "sinh")
                {
                    stack.push_back(std::sinh(rhs));
                }
                else if (t.str == "cos")
                {
                    stack.push_back(std::cos(rhs));
                }
                else if (t.str == "acos")
                {
                    stack.push_back(std::acos(rhs));
                }
                else if (t.str == "cosh")
                {
                    stack.push_back(std::cosh(rhs));
                }
                else if (t.str == "tan")
                {
                    stack.push_back(std::tan(rhs));
                }
                else if (t.str == "atan")
                {
                    stack.push_back(std::atan(rhs));
                }
                else if (t.str == "tanh")
                {
                    stack.push_back(std::tanh(rhs));
                }
                else if (t.str == "log")
                {
                    stack.push_back(std::log10(rhs));
                }
                else if (t.str == "ln")
                {
                    stack.push_back(std::log(rhs));
                }
                else if (t.str == "sqrt")
                {
                    stack.push_back(std::sqrt(rhs));
                }
                else if (t.str == "abs")
                {
                    stack.push_back(std::abs(rhs));
                }
            }
            break;
            case NodeType::Operator:
            {
                const double rhs = stack.back();
                stack.pop_back();
                const double lhs = stack.back();
                stack.pop_back();
                switch (t.str[0])
                {
                case '^':
                    stack.push_back(std::pow(lhs, rhs));
                    break;
                case '*':
                    stack.push_back(lhs * rhs);
                    break;
                case '/':
                    stack.push_back(lhs / rhs);

                    break;
                case '+':
                    stack.push_back(lhs + rhs);
                    break;
                case '-':
                    stack.push_back(lhs - rhs);
                    break;
                }
            }
            break;
            }
        }
        return stack.back();
    }

private:
    enum NodeType
    {
        Variable,
        Operator,
        Number,
        Function,
        LParentesis,
        RParentesis
    };
    struct Token
    {
        std::string str;
        NodeType type;
        size_t precedence = 0;
        Token() = default;
        Token(const std::string &_value, const NodeType _type, size_t _precedence = 0)
            : str(std::move(_value)),
              type(_type),
              precedence(_precedence)
        {
        }
    };

    using ContantIt = std::string::const_iterator;

    struct Range
    {
        ContantIt m_start;
        ContantIt m_end;
    };

    std::vector<Token> output_stack;

    Range readToken(ContantIt &it, int (*condition)(int))
    {
        ContantIt m_start = it;
        char m_currChar = *it;
        do
        {
            ++it;
            m_currChar = *it;
        } while (condition(m_currChar));

        return {m_start, it};
    }

    void tokenize(const std::string &raw, std::vector<Token> &tokens)
    {
        for (ContantIt it = raw.begin(); it < raw.end(); ++it)
        {
            const char c = *it;
            if (isdigit(c) || c == '.')
            {
                Range r = readToken(it,
                                    [](int _c)
                                    {
                                        return (int)(isdigit(_c) || _c == '.');
                                    });
                Token token(std::string(r.m_start, r.m_end), NodeType::Number);
                tokens.push_back(token);
                --it;
            }
            else if (isalpha(c))
            {
                Range r = readToken(it, isalpha);
                if (unsigned(r.m_end - r.m_start) == 1)
                {
                    Token token;
                    char st = *r.m_start;
                    token.type = NodeType::Number;
                    if (st == 'π')
                    {
                        token.str = std::to_string(M_PI);
                    }
                    else if (st == 'e')
                    {
                        token.str = std::to_string(M_NEPERO);
                    }
                    else
                    {
                        token.str = {st};
                        token.type = NodeType::Variable;
                    }
                    tokens.push_back(token);
                    --it;
                    continue;
                };
                std::string value(r.m_start, r.m_end);
                // check whenever the function exists
                // assert(value == "sin"|| value == "cos");
                Token token(std::move(value), NodeType::Function);
                tokens.push_back(token);
                --it;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!')
            {
                size_t prec = 0;
                NodeType _t = NodeType::Operator;
                switch (c)
                {
                case '+':
                    prec = 2;
                    break;
                case '-':
                    prec = 2;
                    break;
                case '*':
                    prec = 3;
                    break;
                case '/':
                    prec = 3;
                    break;
                case '^':
                    prec = 4;
                    break;
                default:
                    break;
                }
                Token token({c}, _t, prec);
                tokens.push_back(token);
            }
            else if (c == '(' || c == ')')
            {
                Token token({c}, c == '(' ? NodeType::LParentesis : NodeType::RParentesis);
                tokens.push_back(token);
            }
        }
    }
    void shuntingYard(std::vector<Token> &tokens)
    {
        std::vector<Token> operator_stack;
        for (auto &t : tokens)
        {
            switch (t.type)
            {
            case NodeType::Number:
                output_stack.push_back(t);
                break;
            case NodeType::Variable:
                output_stack.push_back(t);
                break;
            case NodeType::Function:
                operator_stack.push_back(t);
                break;
            case NodeType::Operator:
                while ((!operator_stack.empty() && operator_stack.back().type != NodeType::LParentesis) && (operator_stack.back().precedence > t.precedence || (operator_stack.back().precedence == t.precedence && t.str != "^")))
                {
                    Token &top = operator_stack.back();
                    output_stack.push_back(top);
                    operator_stack.pop_back();
                }
                operator_stack.push_back(t);
                break;
            case NodeType::LParentesis:
                operator_stack.push_back(t);
                break;
            case NodeType::RParentesis:
                while (!operator_stack.empty() && operator_stack.back().type != NodeType::LParentesis)
                {
                    Token &top = operator_stack.back();
                    output_stack.push_back(top);
                    operator_stack.pop_back();
                }
                if (!operator_stack.empty())
                {
                    operator_stack.pop_back();
                }
                if (!operator_stack.empty() && operator_stack.back().type == NodeType::Function)
                {
                    Token &top = operator_stack.back();
                    output_stack.push_back(top);
                    operator_stack.pop_back();
                }
                break;
            }
        }
        while (!operator_stack.empty())
        {
            output_stack.push_back(std::move(operator_stack.back()));
            operator_stack.pop_back();
        }
    }
};

#endif