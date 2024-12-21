/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

#include <string>
#include <memory>

#include "expression.h"

class Logarithm : public Expression {
    
public:
    // Konstruktorer
    Logarithm(); // Standardkonstruktor f�r log_2(x)
    Logarithm(const Expression& expr, double c1, double c2, int base); // Skapar logaritmuttryck
    Logarithm(const Logarithm& other); // Kopieringskonstruktor

    // Destruktor
    ~Logarithm();

    // Tilldelningsoperator
    Logarithm& operator=(const Logarithm& other);

    // Funktion f�r att �ndra bas
    void set_base(int new_base);

    // Virtuella funktioner fr�n Expression
    double operator()(double x) const override; // Ber�knar v�rdet av logaritmen vid x
    explicit operator std::string() const override; // Konverterar till std::string
    Logarithm* clone() const override; // Skapar en kopia av objektet

private:
    Expression* expression; // Pekare till inre uttrycket
    double c1; // Konstant term
    double c2; // Multiplikator
    int base;  // Logaritmens bas


};
