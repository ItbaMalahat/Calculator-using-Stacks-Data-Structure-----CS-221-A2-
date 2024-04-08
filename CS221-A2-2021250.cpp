#include <iostream>
using namespace std;
#include <string>
#define size 50

int addition(int a, int b){ //addition function
    return a+b;
}

int subtraction(int a, int b){  //subtraction function
    return a-b;
}

int multiplication(int a, int b){  //multiplication function
    return a*b;
}

int division(int a, int b){ //division function
    return a/b;
}

int power(int a, int b){    //power function
    int temp=1;
    for(int i=0; i < a; i++)
    {
        temp*=b;
    };
    return temp;
}

char inttoChar(int num)  //function to convert a variable from integer to character
{                       //used in evaluation of postfix expression
    char temp;
    temp = num + 48;

    return temp;
}

int chartoInt(char ch)  //function to convert a variable from character to integer 
{                       //used in evaluation of postfix expression
    int temp;
    temp = ch - 48;
    return temp;
}

class Stack
{
public:
    int top;
    char *arr;
    Stack() {   //constructor
        arr = new char[size];
        top = -1;
    }
    void Push(char value)   //function to push elements into the stack
    {
        if (top >= size)
        {
            cout << "stack overflow\n";
            return;
        }
        else
        {
            top++;
            arr[top] = value;
        }
    }
    void Pop()  //function to pop elements from stack
    {

        if (top <= -1)
        {
            cout << "stack underflow\n";
        }
        else
        {
           // cout << arr[top] << endl;
            top--;
        }
    }
    bool isEmpty()  //function to check if stack is empty
    {
        if (top == -1)
        {
            return true;
        }

        return false;
    }
};

//integer stack
class IntStack
{
public:
    int top;
    int *arr;
    IntStack(){ //constructor
        arr = new int[size];
        top = -1;
    }
    void Push(char value)   //function to push elements into the integer stack
    {
        if (top >= size)
        {
            cout << "stack overflow\n";
            return;
        }
        else
        {
            top++;
            arr[top] = value;
        }
    }
    void Pop()  //function to pop elements from interger stack
    {

        if (top <= -1)
        {
            cout << "stack underflow\n";
        }
        else
        {
           // cout << arr[top] << endl;
            top--;
        }
    }
    bool isEmpty()  //function to check if stack is empty
    {
        if (top == -1)
        {
            return true;
        }

        return false;
    }
};
class infixToPostfix    //class containing all functions to convert infix expression to postfix
{
public:
    string infix;
    string postfix;

    infixToPostfix(string exp)  //constructor
    {
        infix = exp;
        postfix = "";
        infix += ")";
        // postfix= " ";
    }

    //function to check if the character is an operand
    bool isOperand(char o)
    {
        if (o == '0' || o == '1' || o == '2' || o == '3' || o == '4' || o == '5' || o == '6' || o == '7' || o == '8' || o == '9')
        {
            return true;
        }
        if (o >= 'A' && o <= 'Z')
        {
            return true;
        }
        if (o >= 'a' && o <= 'z')
        {
            return true;
        }

        return false;
    }
//function to check if character is operator
    bool isOperator(char o)
    {
        if (o == '*' || o == '/' || o == '^' || o == '+' || o == '-')
        {
            return true;
        }

        return false;
    }
//function to check if there is an opening bracket in string
    bool isOpeningBracket(char o)
    {
        if (o == '(')
        {
            return true;
        }

        return false;
    }

//function to check if there is a closing bracket in string
    bool isClosingBracket(char o)
    {
        if (o == ')')
        {
            return true;
        }

        return false;
    }
//function to determine precedence of operator
    int operatorPrecedence(char o)
    {
        if (o == '^') // highest precedence
        {
            return 3;
        }
        if (o == '/' || o == '*')
        {
            return 2;
        }
        if (o == '+' || o == '-') // lowest precedence
        {
            return 1;
        }

        return -1; // for () brackets
    }

    //function for infix to postfix conversion
    string infixToPostfixConversion()
    {
        Stack st;
        st.Push('(');

        for (int i = 0; i < infix.length(); i++)
        {
            // check for (
            // if first character of infix is bracket push it onto stack
            if (isOpeningBracket(infix[i]))
            {
                st.Push(infix[i]);
            }
            // check for operands
            else if (isOperand(infix[i]))
            {
                postfix += infix[i];
            }
            // check for operator
            else if (isOperator(infix[i]))
            {
                // check for precedence of operator

                {
                    while (operatorPrecedence(st.arr[st.top]) >= operatorPrecedence(infix[i]))
                    {
                        postfix += st.arr[st.top];
                        st.Pop();
                    }
                    st.Push(infix[i]);
                }
            }
            // check for )
            else if (isClosingBracket(infix[i]))
            {
                while (!st.isEmpty() && !isOpeningBracket(st.arr[st.top]))
                {
                    postfix += st.arr[st.top];
                    st.Pop();
                }
                if (!st.isEmpty())
                {
                    st.Pop();
                }
            }
        }
        while (!st.isEmpty())
        {
            postfix += st.arr[st.top];
            st.Pop();
        }
        
        cout << postfix;
        return postfix;
    }

    //function to evaluate the postfix expression
    int evaluatePostfix()
    {
        IntStack int_st;
        char symbol;
        int opnd1, opnd2;
        int value, opnd;
        for (int i = 0; i < postfix.length(); i++)
        {
            symbol = postfix[i];

            if (isOperand(symbol))
            {
                opnd = chartoInt(symbol);
                int_st.Push(opnd);
            }

            else if (isOperator(symbol))
            {
                int temp = int_st.top;
                opnd1 = int_st.arr[temp];

                int_st.Pop();
                temp--;
                opnd2 = int_st.arr[temp];
                int_st.Pop();


                if (symbol == '*')
                    value = multiplication(opnd1, opnd2);
                else if (symbol == '/')
                    value = division(opnd1, opnd2);
                else if (symbol == '+')
                    value = addition(opnd1, opnd2);
                else if (symbol == '-')
                    value = subtraction(opnd1, opnd2);
                else if (symbol == '^')
                    value = power(opnd1, opnd2);

                    cout << value << endl;

                int_st.Push(value);
            }
        }
        int temp= int_st.top;
      //  int_st.Pop();
        return int_st.arr[temp];
      
    }
    
};


int main()
{

    string s;
    cout << "enter the infix operation\n";
    cin >> s;
    infixToPostfix testCase(s);
    cout << "postfix expression : ";
    testCase.infixToPostfixConversion();
    cout << "\nthe evaluated expression : ";
    cout<<testCase.evaluatePostfix();
}
