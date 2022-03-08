#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>

using namespace std;

const double E = 0.0001;

void printVector(vector<double> vect) {
    for (const auto& it : vect)
        cout << it << " ";
    cout << endl << endl;
}

void strokeWrap(string& stroke, vector <double>& equation) {
    string buff = "";
    for (auto& it : stroke) {
        if (it == ' ') {
            if (buff.size() != 0) {
                equation.push_back(stod(buff));
                buff = "";
            }
            continue;
        }
        else
            buff += it;
    }
    equation.push_back(stod(buff));
}

double func(vector <double>& equation, double x, double mDegree) {
    double sum = 0;
    for (int i = 0; i < equation.size(); i++) {
        sum += equation[i] * pow(x, i + mDegree);
    }
    return sum;
}

void halfDivision(vector <double>& equation) {
    cout << "The method of half division: " << endl << endl;

    cout << "Equal:" << endl;
    printVector(equation);
    pair<double, double> interval = { 2, 3 };

    cout << "(a; b) = " << "(" << interval.first << "; " << interval.second << ")" << endl << endl;
    cout << "f(a) * f(b) = " << func(equation, interval.first, 0) * func(equation, interval.second, 0) << endl << endl;

    double c = (interval.first + interval.second) / 2.0;
    int i = 1;
    while (abs(func(equation, c, 0)) / 2 > E) {
        c = (interval.first + interval.second) / 2.0;
        cout << i << ") Interval = ( " << interval.first << "; " << interval.second << ") C = " << c << endl;
        if (func(equation, interval.first, 0) * func(equation, c, 0) < 0)
            interval.second = c;
        else
            interval.first = c;
        i++;
    }
    cout << endl << "X = " << c << endl << endl;
}

void chord(vector <double>& equation) {
    cout << "The chord method: " << endl << endl;

    cout << "Equal:" << endl;
    printVector(equation);
    pair<double, double> interval = { 2, 3 };

    cout << "(a; b) = " << "(" << interval.first << "; " << interval.second << ")" << endl << endl;

    double c = (interval.first * func(equation, interval.second, 0) - interval.second * func(equation, interval.first, 0))
        / (func(equation, interval.second, 0) - func(equation, interval.first, 0));
    double cPrev = 0;
    int i = 1;

    cout << i << ") Interval = ( " << interval.first << "; " << interval.second << ") C = " << c << endl;
    if (func(equation, interval.first, 0) * func(equation, c, 0) < 0)
        interval.second = c;
    else
        interval.first = c;
    i++;

    while (abs(c - cPrev) > E) {
        cPrev = c;
        c = (interval.first * func(equation, interval.second, 0) - interval.second * func(equation, interval.first, 0))
            / (func(equation, interval.second, 0) - func(equation, interval.first, 0));
        cout << i << ") Interval = ( " << interval.first << "; " << interval.second << ") C = " << c << endl;
        if (func(equation, interval.first, 0) * func(equation, c, 0) < 0)
            interval.second = c;
        else
            interval.first = c;
        i++;
    }
    cout << endl << "X = " << c << endl << endl;
}

vector <double> derivative(vector <double> equation) {
    for (int i = 0; i < equation.size(); i++) {
        equation[i] *=  i;
    }
    return equation;
}

void newton(vector <double>& equation) {
    cout << "The Newton method: " << endl << endl;

    cout << "Equal:" << endl;
    printVector(equation);
    pair<double, double> interval = { 2, 3 };
    vector <double> derivativeEq = derivative(equation);
    //cout.precision(10);

    cout << "(a; b) = " << "(" << interval.first << "; " << interval.second << ")" << endl << endl;

    
    double xPrev = interval.first;

    double x = xPrev - func(equation, xPrev, 0) / func(derivativeEq, xPrev, -1);
    int i = 1;

    cout << i << ") X" + to_string(i - 1) << " = " << xPrev << endl;
    i++;
    cout << i << ") X" + to_string(i - 1) << " = " << x << endl;
    i++;

    while (abs(x - xPrev) > E) {
        xPrev = x;
        x = x = xPrev - func(equation, xPrev, 0) / func(derivativeEq, xPrev, -1);
        cout << i << ") X" + to_string(i - 1) << " = " << x << endl;
        i++;
    }
    cout << endl << "X = " << x << endl << endl;
}

int main()
{
    fstream matrixData("equation.txt");
    vector <double> equation;

    while (!matrixData.eof()) {
        string buff;
        getline(matrixData, buff);
        strokeWrap(buff, equation);
    }
    reverse(equation.begin(), equation.end());

    halfDivision(equation);
    chord(equation);
    newton(equation);
}