#include "pch.h"
#include "EasterEggHandler.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../CalcManager/CalculatorManager.h"
#include <wchar.h>
#include <string>

using namespace CalcEngine;
using namespace CalculationManager;

void EasterEggHandler::_convertListToStrPattern()
{
    int i = 0;
    for (i = 0; i < commands_lists.size(); i++) {
        auto it = _commandToWCharMap.find(commands_lists[i]);
        if (it != _commandToWCharMap.end()) {
            _strPattern[i] = it->second;
        } else {
            // 未定義コマンドの場合はスキップまたはデフォルト文字を使用
            _strPattern[i] = L'?';  // またはcontinueでスキップ
        }
    }
    _strPattern[i] = L'\0';
    //_calcManager.SetPrimaryDisplay(_strPattern, true); // debug用
}

bool EasterEggHandler::handle(Command& command)
{
    if (_isFirstCommand) { // 一番最初に、ユーザーインプットではないコマンドが来る
        _isFirstCommand = false;
        return false;
    }

    commands_lists.push_back(command);
    if(commands_lists.size() > 4){
        _convertListToStrPattern();
        if(wcsstr(_strPattern,L"404")){
            _calcManager.SetPrimaryDisplay(L"Not Found",true);
        }
        commands_lists.clear();
        _isFirstCommand = true; // イースターエッグから抜けるときのボタンプレス(1コマンド)をスキップするため
        return true;
    }

    return false;
}

EasterEggHandler::EasterEggHandler(CalculationManager::CalculatorManager& calcManager) :
    _calcManager(calcManager)
{
    _strPattern[0] = L'\0';
}

    /* if (_currentVal == 404)
    {
        _calcDisplay.SetPrimaryDisplay(L"Not Found", false);
    } // 壁紙変更
    */

/*
 m_easterEggHandler->commands_lists.push_back(cmdenum);
    if (m_easterEggHandler->commands_lists.size() > 2 && m_easterEggHandler->commands_lists[1] == Command::Command1 && m_easterEggHandler->commands_lists[2] ==
 Command::Command1)
    {
        m_standardCalculatorManager.Reset();
        m_easterEggHandler->commands_lists.clear();
        return;
    }*/
