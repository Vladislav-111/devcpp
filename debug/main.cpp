#include <iostream>
#include <windows.h>

#pragma comment(lib, "advapi32.lib")

using namespace std;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wchar_t cmdLine[] = L"D:\\Qt\\devcpp\\1\\build-main-Desktop_Qt_6_4_3_MSVC2019_64bit-Release\\lab1\\release\\lab1.exe";

    if (CreateProcess(cmdLine, NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
        cout << "Success!" << endl;
        cout << "pid = " << dec << pi.dwProcessId << endl;
    } else {
        cout << "Failed!" << endl;
    }

    bool isAttached = DebugActiveProcess(pi.dwProcessId);
    if (isAttached) {
        DWORD lastError = GetLastError();
        cout << hex << "DebugActiveProcess() Failed!" << endl;
        cout << "GetLastError() = " << lastError << endl;
    } else {
        cout << "DebugActiveProcess() Success!" << endl;
    }

    DEBUG_EVENT debugEvent;
    while (true) {
        bool result1 = WaitForDebugEvent(&debugEvent, INFINITE);
        bool result2 = ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
    }
    return 0;
}
