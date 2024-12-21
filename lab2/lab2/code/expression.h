/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <string>
#include <cmath>

 // Konstant f�r flyttalsj�mf�relser (decimaler och avrundningsfel)
constexpr double Epsilon = 1.0e-5;




//Expression �r en abstrakt basklass som anv�nds som grund 
// f�r att skapa olika typer av matematiska uttryck y = f(x)
//Det kan vara ett polynom, logaritm, tillexpel och d�rav s� 
// kommer vi implemetera dessa som subklasser

class Expression {
public:
    // Destructor, Virtuell destruktor f�r polymorfism
    virtual ~Expression() {
        --count_expressions;
    }

    //************************************** Detta nedan har jag lagt in
    // ADD OTHER MEMBER FUNCTIONS
    
    // Virtuella funktioner
    //En virtuell funktion som har en standardimplementation i basklassen, 
    // men som kan skrivas �ver av subklasser.
    // Polymorfism: G�r att vi kan behandla olika typer av objekt p� ett enhetligt s�tt 
    // via en basklasspekare eller -referens.
    virtual double operator()(double x) const = 0; // Utv�rderar uttrycket f�r ett givet x
    virtual Expression* clone() const = 0;        // Skapar en kopia av uttrycket
    virtual explicit operator std::string() const = 0; // Typkonvertering till std::string

    // Funktion f�r att kontrollera om ett v�rde �r en rot
    bool isRoot(double x) const {
        return std::abs((*this)(x)) < Epsilon;
    }

    // G�r s� att man enklare kan skriva ut Expression objekt direkt med std::cout
    // friend till�ter att kunna anv�nda privata funktioner i classen och subclasser
    friend std::ostream& operator<<(std::ostream& os, const Expression& expr) {
        os << static_cast<std::string>(expr);
        return os;
    }
    //********************************************

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:
    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }

    // total number of existing (instanser)expressions -- only to help to detect bugs in the code
    static std::size_t count_expressions;
    // Your code cannot manipulate this variable
};
