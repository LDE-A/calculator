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

void EasterEggHandler::_showCurrentSequence() // デバッグ用
{
    int i = 0;
    for (i = 0; i < inputtedCommands.size(); i++) {
        auto it = _commandsMap.find(inputtedCommands[i]);
        if (it != _commandsMap.end()) {
            _currentInputSequence[i] = it->second;
        } else {
            // 未定義コマンドの場合はスキップまたはデフォルト文字を使用
            _currentInputSequence[i] = L'?';  // またはcontinueでスキップ
        }
    }
    _currentInputSequence[i] = L'\0';
    _calcManager.SetPrimaryDisplay(_currentInputSequence, true); // debug用
}

wchar_t EasterEggHandler::_convertCommandToWchar(Command& command){
    wchar_t targetChar = _commandsMap[command];
    if(targetChar == L'\0'){
        targetChar = L'?';
    }

    return targetChar;
}

void EasterEggHandler::_appendCommand(Command& command) {
    inputtedCommands.push_back(command);

    wchar_t wchar = _convertCommandToWchar(command);
    _currentInputSequence += wchar;
}

void EasterEggHandler::_clearState(){
    inputtedCommands.clear();
    _currentInputSequence.clear();
    _isFirstCommand = true;  // イースターエッグから抜けるときのボタンプレス(1コマンド)をスキップするため
}

bool EasterEggHandler::handle(Command& command)
{
    if (_isFirstCommand) { // 一番最初に、ユーザーインプットではないコマンドが来る
        _isFirstCommand = false;
        return false;
    }

    _appendCommand(command);

    if(_currentInputSequence == L"404"){
        _calcManager.SetPrimaryDisplay(L"Not Found", true);
        _clearState();
        return true;
    }else if(_currentInputSequence == L"/**/"){
        _calcManager.SetPrimaryDisplay(L"Comment is not allowed", true);
        _clearState();
        return true;
    }

    return false;
}

EasterEggHandler::EasterEggHandler(CalculationManager::CalculatorManager& calcManager) :
    _calcManager(calcManager)
{
    _currentInputSequence.clear();
}
