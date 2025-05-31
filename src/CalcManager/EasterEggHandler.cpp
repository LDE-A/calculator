#include "pch.h"
#include "EasterEggHandler.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace CalcEngine;

vector<Rational> EasterEggHandler::_easterEggs = {
    Rational(404),  // Not Found

};

bool EasterEggHandler::isEasterEgg(const Rational& m_currentVal)
{
    for (int i = 0; i < _easterEggs.size(); i++)
    {
        if (m_currentVal == _easterEggs[i])
        {
            return true;
        }
    }
    return false;
}

EasterEggHandler::EasterEggHandler(Rational m_currentVal,ICalcDisplay& display)
    : _currentVal(m_currentVal)
    , _calcDisplay(display)
{
    ;
}

void EasterEggHandler::handle()
{
    if (_currentVal == 404)
    {
        _calcDisplay.SetPrimaryDisplay(L"Not Found", false);
    }
}
