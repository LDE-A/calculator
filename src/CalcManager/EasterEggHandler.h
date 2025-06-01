#pragma once

#include "Header Files/CalcEngine.h"
#include "Header Files/History.h"
#include "Header Files/IHistoryDisplay.h"
#include "../CalcManager/Command.h"
#include "../CalcManager/CalculatorManager.h"
#include <map>
#include <wchar.h>

using namespace std;
using namespace CalcEngine;
using namespace CalculationManager;

class EasterEggHandler
{
public:
    EasterEggHandler(CalculatorManager& calcManager);
    bool handle(Command& command);
    vector<Command> commands_lists = {}; // 最初に1個謎のコマンドが入る

private:
    CalculatorManager& _calcManager;
    bool _isFirstCommand = true; // プログラム開始時１度と、コマンド実行後の１文字スキップのため
    wchar_t _strPattern[100]; // パターンを保存する
    void _convertListToStrPattern();
    map<Command, wchar_t> _commandToWCharMap = {
        // 数字コマンド (0-9) - 既存OK
        { Command::Command0, L'0' },
        { Command::Command1, L'1' },
        { Command::Command2, L'2' },
        { Command::Command3, L'3' },
        { Command::Command4, L'4' },
        { Command::Command5, L'5' },
        { Command::Command6, L'6' },
        { Command::Command7, L'7' },
        { Command::Command8, L'8' },
        { Command::Command9, L'9' },

        // 16進数字（A-F）- 追加必要
        { Command::CommandA, L'A' },
        { Command::CommandB, L'B' },
        { Command::CommandC, L'C' },
        { Command::CommandD, L'D' },
        { Command::CommandE, L'E' },
        { Command::CommandF, L'F' },

        // 基本演算子 - 既存OK + 追加必要
        { Command::CommandADD, L'+' },
        { Command::CommandSUB, L'-' },
        { Command::CommandMUL, L'*' },
        { Command::CommandDIV, L'/' },
        { Command::CommandEQU, L'=' },
        { Command::CommandPNT, L'.' },
        { Command::CommandMOD, L'%' },         // 追加必要
        { Command::CommandPWR, L'^' },         // 追加必要

        // クリア・編集系 - 既存OK
        { Command::CommandCLEAR, L'C' },
        { Command::CommandCENTR, L'E' },
        { Command::CommandBACK, L'\u232B' },   // ⌫
        { Command::CommandSIGN, L'\u00B1' },   // ±

        // 括弧 - 既存OK
        { Command::CommandOPENP, L'(' },
        { Command::CommandCLOSEP, L')' },

        // 論理演算 - 追加必要
        { Command::CommandAnd, L'&' },         // 追加必要
        { Command::CommandOR, L'|' },          // 追加必要（CommandAbsと重複回避必要）
        { Command::CommandNot, L'~' },         // 追加必要

        // ビット演算 - 既存OK
        { Command::CommandXor, L'\u2295' },    // ⊕
        { Command::CommandNand, L'\u22BC' },   // ⊼
        { Command::CommandNor, L'\u22BD' },    // ⊽
        { Command::CommandLSHF, L'\u226A' },   // ≪
        { Command::CommandRSHF, L'\u226B' },   // ≫
        { Command::CommandRSHFL, L'\u2AA1' },  // ⪡
        { Command::CommandROL, L'\u21BA' },    // ↺
        { Command::CommandROR, L'\u21BB' },    // ↻
        { Command::CommandROLC, L'\u27F2' },   // ⟲
        { Command::CommandRORC, L'\u27F3' },   // ⟳

        // 数学関数 - 一部追加必要
        { Command::CommandSQRT, L'\u221A' },   // √
        { Command::CommandSQR, L'\u00B2' },    // 追加必要 - ²
        { Command::CommandCUB, L'\u00B3' },    // 追加必要 - ³
        { Command::CommandROOT, L'\u221B' },   // ∛
        { Command::CommandCUBEROOT, L'\u23B7' }, // ⎷
        { Command::CommandREC, L'\u215F' },    // 追加必要 - ⅟

        // その他数学 - 既存OK + 追加必要
        { Command::CommandCHOP, L'\u2702' },   // ✂
        { Command::CommandFloor, L'\u230A' },  // ⌊
        { Command::CommandCeil, L'\u2308' },   // ⌈
        { Command::CommandPERCENT, L'\u2030' }, // ‰
        { Command::CommandAbs, L'\u007C' },    // | (CommandORとの重複回避)
        { Command::CommandFAC, L'!' },
        { Command::CommandCOM, L'\u2201' },    // ∁

        // 三角関数 - 既存OK
        { Command::CommandSIN, L'S' },
        { Command::CommandCOS, L'Ç' },
        { Command::CommandTAN, L'T' },
        { Command::CommandASIN, L'Ś' },
        { Command::CommandACOS, L'Ć' },
        { Command::CommandATAN, L'Ť' },

        // 双曲線関数 - 既存OK
        { Command::CommandSINH, L'ş' },
        { Command::CommandCOSH, L'ç' },
        { Command::CommandTANH, L'ť' },
        { Command::CommandASINH, L'Ş' },
        { Command::CommandACOSH, L'Č' },
        { Command::CommandATANH, L'Ţ' },

        // 三角関数（その他）- 既存OK
        { Command::CommandSEC, L'\u2234' },    // ∴
        { Command::CommandASEC, L'\u2235' },   // ∵
        { Command::CommandCSC, L'\u2207' },    // ∇
        { Command::CommandACSC, L'\u2206' },   // ∆
        { Command::CommandCOT, L'\u2202' },    // ∂
        { Command::CommandACOT, L'\u222E' },   // ∮
        { Command::CommandSECH, L'\u2135' },   // ℵ
        { Command::CommandASECH, L'\u2136' },  // ℶ
        { Command::CommandCSCH, L'\u2137' },   // ℷ
        { Command::CommandACSCH, L'\u2138' },  // ℸ
        { Command::CommandCOTH, L'\u221E' },   // ∞
        { Command::CommandACOTH, L'\u221D' },  // ∝

        // 対数・指数 - 既存OK
        { Command::CommandLN, L'ℓ' },
        { Command::CommandLOG, L'ℊ' },
        { Command::CommandPOW10, L'⑩' },
        { Command::CommandPOW2, L'②' },
        { Command::CommandPOWE, L'ℯ' },
        { Command::CommandLogBaseY, L'⒴' },
        { Command::CommandEXP, L'Ε' },

        // 定数 - 既存OK
        { Command::CommandPI, L'π' },
        { Command::CommandEuler, L'℮' },

        // メモリ操作 - 既存OK
        { Command::CommandSTORE, L'Ⓜ' },
        { Command::CommandRECALL, L'Ⓡ' },
        { Command::CommandMPLUS, L'⊞' },
        { Command::CommandMMINUS, L'⊟' },
        { Command::CommandMCLEAR, L'⊠' },

        // モード関連 - 既存OK
        { Command::CommandDEG, L'°' },
        { Command::CommandRAD, L'ʳ' },
        { Command::CommandGRAD, L'ᵍ' },
        { Command::CommandDegrees, L'∘' },
        { Command::CommandHYP, L'ℋ' },
        { Command::CommandINV, L'§' },
        { Command::CommandFE, L'⟷' },

        // 進数モード - 既存OK
        { Command::CommandHex, L'ₕ' },
        { Command::CommandDec, L'ю' },
        { Command::CommandOct, L'₈' },
        { Command::CommandBin, L'₂' },

        // データサイズ - 既存OK
        { Command::CommandQword, L'Q' },
        { Command::CommandDword, L'W' },
        { Command::CommandWord, L'w' },
        { Command::CommandByte, L'ᵇ' },

        // その他 - 既存OK + 一部追加
        { Command::CommandDMS, L'″' },
        { Command::CommandRand, L'？' },
        { Command::CommandSET_RESULT, L'⟸' },

        // 基本モード - 追加必要
        { Command::ModeBasic, L'Ⓑ' },         // 追加必要
        { Command::ModeScientific, L'Ⓢ' },    // 追加必要
        { Command::ModeProgrammer, L'Ⓟ' },    // 追加必要

        // NULL命令 - 追加必要
        { Command::CommandNULL, L'\u2400' },   // 追加必要 - ␀
    };
};
