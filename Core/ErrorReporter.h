#pragma once
#include <string>

struct ErrorReporter {
    static std::string PublicStorage;

    const char* filename;
    const UINT linenum;
    const char* function;
    const char* command;
    const HRESULT hr;
    const char* message;

    explicit ErrorReporter(const char* message)
        : filename(nullptr), linenum(0xffffffff), function(nullptr), command(nullptr), hr(0xffffffff), message(message) { }

    ErrorReporter(const char* filename, UINT linenum, const char* function,
        const char* command = nullptr, HRESULT hr = 0xffffffff, const char* message = nullptr)
        : filename(filename), linenum(linenum), function(function), command(command), hr(hr), message(message) { }

    void Report();
};
