#include "StdAfx.h"
#include "ErrorReporter.h"

std::string ErrorReporter::PublicStorage;

void ErrorReporter::Report()
{
    std::string text;
#pragma region Initialize text variable
    char itoaBuffer[12];
    if ( filename ) {
        text += filename;
        if ( 0xffffffff != linenum ) {
            text += '(';
            _itoa_s( linenum, itoaBuffer, 10 );
            text += itoaBuffer;
            text += ')';
        }
        text += '\n';
    }
    if ( function ) {
        text += "함수 이름 : ";
        text += function;
        text += '\n';
    }
    if ( command ) {
        text += "에러 문장 : ";
        text += command;
        text += '\n';
    }
    if ( 0xffffffff != hr ) {
        text += "HRESULT 코드 : 0x";
        _itoa_s( hr, itoaBuffer, 16 );
        text += itoaBuffer;
        text += '\n';
    }
    if ( message ) {
        text += message;
        if ( text.back() != '\n' ) text += '\n';
    }
#pragma endregion

#pragma region Display error
	if ( IsDebuggerPresent() ) {
		OutputDebugStringA ( "======================================"
            "========================================\n" );
        OutputDebugStringA( text.c_str() );
		OutputDebugStringA ( "------------------------------------------------------------------------------\n" );
        DebugBreak();
    } else {
		AllocConsole();
		AttachConsole( GetCurrentProcessId() );
		FILE* dummy;
		freopen_s(&dummy, "CON", "w", stdout);
        printf( "%s\n", text.c_str() );
		system("pause");
		FreeConsole();
	}
#pragma endregion

}
