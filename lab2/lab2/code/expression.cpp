/*********************************************************
 * Class Expression member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "expression.h"

// Initialize the counter of the total number of existing Expressions(instanser)
std::size_t Expression::count_expressions = 0;

// Used only for debug purposes
// Return number of existing Expressions
std::size_t Expression::get_count_expressions() {
    return Expression::count_expressions;
}

/* ************************* */

//Basklassen Expression ska representera en generell matematisk funktion av formen ??=??(??) d�r x
//�r en variabel.Den �r designad f�r att anv�ndas som grund f�r specifika typer av uttryck(t.ex.polynom och logaritmer).

// Eftersom de flesta funktionerna i Expression �r virtuella och m�ste implementeras i subklasser (t.ex. Polynomial och Logarithm), 
// �r det begr�nsat vad som beh�vs i basklassens implementation.

// Test kommentar