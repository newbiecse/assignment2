#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <stack>
using namespace std;

bool isOperator(char currentChar)
{
    switch (currentChar) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
        return true;
    default:
        return false;
    }
}

// returns whether a `lOp` b `rOp` c == (a `lOp` b) `rOp` c
bool precedence(char leftOperator, char rightOperator)
{
    if ( leftOperator == '^' ) {
        return true;
    } else if ( rightOperator == '^' ) {
        return false;
    } else if ( leftOperator == '*' || leftOperator == '/' || leftOperator == '%' ) {
        return true;
    } else if ( rightOperator == '*' || rightOperator == '/' || rightOperator == '%' ) {
        return false;
    }

    return true;
}

std::string convertToPostfix(const std::string& infix)
{
    std::stringstream postfix; // Our return string
    std::stack<char> stack;
    stack.push('('); // Push a left parenthesis ‘(‘ onto the stack.

    for(std::size_t i = 0, l = infix.size(); i < l; ++i) {
        const char current = infix[i];

        if (isspace(current)) {
            // ignore
        }
        // If it's a digit or '.' or a letter ("variables"), add it to the output
        else if(isalnum(current) || '.' == current) {
            postfix << current;
        }

        else if('(' == current) {
            stack.push(current);
        }

        else if(isOperator(current)) {
            char rightOperator = current;
            while(!stack.empty() && isOperator(stack.top()) && precedence(stack.top(), rightOperator)) {
                postfix << ' ' << stack.top();
                stack.pop();
            }
            postfix << ' ';
            stack.push(rightOperator);
        }

        // We've hit a right parens
        else if(')' == current) {
            // While top of stack is not a left parens
            while(!stack.empty() && '(' != stack.top()) {
                postfix << ' ' << stack.top();
                stack.pop();
            }
            if (stack.empty()) {
                throw std::runtime_error("missing left paren");
            }
            // Discard the left paren
            stack.pop();
            postfix << ' ';
        } else {
            throw std::runtime_error("invalid input character");
        }
    }


    // Started with a left paren, now close it:
    // While top of stack is not a left paren
    while(!stack.empty() && '(' != stack.top()) {
        postfix << ' ' << stack.top();
        stack.pop();
    }
    if (stack.empty()) {
        throw std::runtime_error("missing left paren");
    }
    // Discard the left paren
    stack.pop();

    // all open parens should be closed now -> empty stack
    if (!stack.empty()) {
        throw std::runtime_error("missing right paren");
    }

    return postfix.str();
}


int performOperation(int op1, int op2, char op)
{
    int ans;
    switch(op){
    case '+':
        ans = op2 + op1;
        break;
    case '-':
        ans = op2 - op1;
        break;
    case '*':
        ans = op2 * op1;
        break;
    case '/':
        ans = op2 / op1;
        break;
    case '^':
		ans = pow(static_cast<double>(op2), op1);
		break;
    case '%':
		ans = op2 % op1;
		break;
    }
    return ans;
}


int evaluate(string exp)
{
	//char exp[1000];
	char buffer[15];
    int i,op1, op2, len, j, x;
    stack<int> s;
    printf("Enter a Postfix Expression: ( e.g. 23 34 * )\n");
    //gets(exp);
	len = exp.size();//strlen(exp);
    j = 0;
    for(i=0; i<len;i++){

        if(exp[i]>='0' && exp[i]<='9'){
            buffer[j++] = exp[i];
        }
        else if(exp[i]==' '){
            if(j>0){
                buffer[j] = '\0';
                x = atoi(buffer);
                s.push(x);
                j = 0;
            }
        }

        else if(isOperator(exp[i])){
            op1 = s.top();
            s.pop();
            op2 = s.top();
            s.pop();
            s.push(performOperation(op1, op2, exp[i]));
        }
    }

    printf("Answer is %d\n", s.top());

    return 0;
}



int main()
{
    for (;;) {
        if (!std::cout.good()) break;
        std::cout << "Enter the Arithmetic Expression: ";
        std::string infix;
        std::getline(std::cin, infix);
        if (infix.empty()) break;

		string postFix = convertToPostfix(infix);

        std::cout << "Postfix: '" << postFix << "'\n";

		//string test = "1 2 3 * +";

		evaluate(postFix);
    }


    return 0;
}
