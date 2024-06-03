#include <iostream>
#include <filesystem>
#include <urlmon.h>

using namespace std;

// Paths
filesystem::path lokiDllPath = filesystem::temp_directory_path() / "loki.dll";
filesystem::path injectorPath = filesystem::temp_directory_path() / "loki.exe";

bool downloadFile(const char* url, const char* path) {
    return SUCCEEDED(URLDownloadToFileA(NULL, url, path, 0, NULL));
}

int main() {
    cout << "Welcome to LokiLoader ^_^" << endl;
    cout << "This is the simple loader for easy LokiSCPSL injection." << endl;
    cout << endl;
    cout << ">==============================<" << endl;
    cout << "Cheat made by: Cringengineer (https://t.me/cringengineer_was_taken)" << endl;
    cout << "Loader made by: MeltingCoffee (https://t.me/MeltinCoffee)" << endl;
    cout << ">==============================<" << endl;
    cout << endl;

    // Downloading cheat files
    cout << "Downloading cheat files..." << endl;

    string lang = PRIMARYLANGID(GetUserDefaultUILanguage()) == LANG_RUSSIAN ? "RUS" : "ENG";
    cout << "Downloading LokiSCPSL dll in " + lang + " language..." << endl;
    bool dllResult = downloadFile(("https://raw.githubusercontent.com/MeltingCoffee/LokiSCPSL/main/Loki" + lang + ".dll").c_str(), lokiDllPath.string().c_str());

    cout << "Downloading Injector..." << endl;
    bool injectorResult = downloadFile("https://raw.githubusercontent.com/MeltingCoffee/LokiSCPSL/main/Injector.exe", injectorPath.string().c_str());

    if (!dllResult || !injectorResult) {
        cout << "Download failed! The program will now exit :(" << endl;
        return 1;
    }

    cout << "Download finished :)" << endl;

    // Checking if the game is running
    if (FindWindowA(NULL, "SCPSL") == NULL) {
        cout << "SCPSL is not running. Starting..." << endl;
        system(R"(start "" "C:\Program Files (x86)\Steam\Steam.exe" -applaunch 700330)");
    }
    else {
        cout << "SCPSL is running. No need to start" << endl;
    }

    // Waiting for the game window to appear so it's safe to inject
    cout << "Waiting for the game window to appear..." << endl;
    while (true) {
        HWND hwnd = FindWindow(NULL, L"SCPSL");

        if (hwnd != NULL && IsWindowVisible(hwnd)) {
            break;
        }
        Sleep(8000);
    }
    cout << "Game window found. Injecting cheat..." << endl;

    // Injecting the cheat
    system((injectorPath.string() + " " + lokiDllPath.string() + " SCPSL.exe").c_str());

    return 0;
}