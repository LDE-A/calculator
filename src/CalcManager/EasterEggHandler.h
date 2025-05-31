#pragma once

#include "Header Files/CalcEngine.h"
#include "Header Files/History.h"
#include "Header Files/IHistoryDisplay.h"

using namespace std;
using namespace CalcEngine;

class EasterEggHandler
{
public:
    EasterEggHandler(Rational m_currentVal,ICalcDisplay& display);
    /// <summary>
    /// Checks if the current value is an Easter Egg.
    /// </summary>
    /// <param name="m_currentVal">current Value<Rational></param>
    /// <returns>true to EasterEgg</returns>
    static bool isEasterEgg(const Rational& m_currentVal);
    void handle();

private:
    Rational _currentVal;
    ICalcDisplay& _calcDisplay;
    static vector<Rational> _easterEggs; // List of Easter Eggs.
};
