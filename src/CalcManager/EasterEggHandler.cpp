#include "pch.h"
#include "EasterEggHandler.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../CalcManager/CalculatorManager.h"
#include <wchar.h>
#include <string>
#include <vector>
#include <Windows.h>

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

/// @brief mapをもとにCommandをwcharに変換
/// @param command Commandオブジェクト
/// @return 変換結果。マップに見つからない場合 -> ?
wchar_t EasterEggHandler::_convertCommandToWchar(Command& command){
    wchar_t targetChar = _commandsMap[command];
    if(targetChar == L'\0'){
        targetChar = L'?';
    }

    return targetChar;
}

/// @brief 現在の入力パターンに追加する
/// @param command Commandオブジェクト
void EasterEggHandler::_appendToSequence(Command& command) {
    inputtedCommands.push_back(command);

    wchar_t wchar = _convertCommandToWchar(command);
    _currentInputSequence += wchar;
}

/// @brief 次のコマンドパターン記録のために値を初期化
void EasterEggHandler::_clearState(){
    inputtedCommands.clear();
    _currentInputSequence.clear();
    _isFirstCommand = true;  // イースターエッグから抜けるときのボタンプレス(1コマンド)をスキップするため
}

void EasterEggHandler::_handle404Pattern(){
    _calcManager.SetPrimaryDisplay(L"Not Found :(", true);
}

void EasterEggHandler::_handleCCCCCPattern(){
    vector<PROCESS_INFORMATION> processes;
    for(int i=0; i<10;i++){
        STARTUPINFO startInfo = {};
        PROCESS_INFORMATION processInfo = {};
        startInfo.cb = sizeof(startInfo);

        wstring cmdCommand = L"cmd.exe /K echo Deleting System Files...";
        if(CreateProcess(
            /* lpApplicationName = */ NULL,                    // 実行ファイル名（NULLの場合はlpCommandLineから取得）
            /* lpCommandLine = */ &cmdCommand[0],              // 実行するコマンドライン文字列
            /* lpProcessAttributes = */ NULL,                  // プロセスのセキュリティ属性（NULL=デフォルト）
            /* lpThreadAttributes = */ NULL,                   // スレッドのセキュリティ属性（NULL=デフォルト）
            /* bInheritHandles = */ FALSE,                     // ハンドル継承フラグ（FALSE=継承しない）
            /* dwCreationFlags = */ 0,                         // プロセス作成フラグ（0=デフォルト）
            /* lpEnvironment = */ NULL,                        // 環境変数ブロック（NULL=親プロセスの環境を継承）
            /* lpCurrentDirectory = */ NULL,                   // カレントディレクトリ（NULL=親プロセスと同じ）
            /* lpStartupInfo = */ &startInfo,                  // スタートアップ情報構造体へのポインタ
            /* lpProcessInformation = */ &processInfo          // プロセス情報構造体へのポインタ（出力用）
        )){
            processes.push_back(processInfo);
        }
    }

    Sleep(5000);
    for (auto& proc : processes) {
        TerminateProcess(proc.hProcess, 0);
        CloseHandle(proc.hProcess);
        CloseHandle(proc.hThread);
    }
}

void EasterEggHandler::_initPatterns(){
    _easterEggpattens = {
        { L"404=",
            [this]() { this->_handle404Pattern(); }
        },
        { L"CCCCC",
            [this]() { this->_handleCCCCCPattern(); }
        }
    };
}

bool EasterEggHandler::handle(Command& command)
{
    if (_isFirstCommand) { // 一番最初に、ユーザーインプットではないコマンドが来る
        _isFirstCommand = false;
        return false;
    }

    _appendToSequence(command);

    for(const auto& pattern: _easterEggpattens){
        if (_currentInputSequence == pattern.targetPattern) {
            pattern.handler();
            _clearState();
            return true;
        }
    }

    return false;
}

EasterEggHandler::EasterEggHandler(CalculationManager::CalculatorManager& calcManager) :
    _calcManager(calcManager)
{
    _clearState();
    _initPatterns();
}
