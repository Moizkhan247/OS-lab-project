#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Function declarations
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
std::string detectDeadlock(); // Declare detectDeadlock function here


HWND hAddProcess, hAddResource, hAllocate, hDetectDeadlock, hRecover, hOutput;
std::vector<std::vector<int> > allocation, request; 
std::vector<int> available;
int processCount = 0, resourceCount = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};
    
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"DeadlockDetectionRecovery";
    wc.lpfnWndProc = WindowProcedure;
    
    if (!RegisterClassW(&wc)) {
        return -1;
    }

    CreateWindowW(L"DeadlockDetectionRecovery", L"Deadlock Detection and Recovery Tool", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 800, 600, NULL, NULL, hInst, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0)) { // Fix GetMessage parameters
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case 1: {
                    // Add Process
                    processCount++;
                    allocation.resize(processCount, std::vector<int>(resourceCount, 0));
                    request.resize(processCount, std::vector<int>(resourceCount, 0));
                    break;
                }
                case 2: {
                    // Add Resource
                    resourceCount++;
                    for (int i = 0; i < allocation.size(); ++i) { // Use traditional loop
                        allocation[i].resize(resourceCount, 0);
                    }
                    for (int i = 0; i < request.size(); ++i) { // Use traditional loop
                        request[i].resize(resourceCount, 0);
                    }
                    available.push_back(0);
                    break;
                }
                case 3: {
                    // Allocate Resources (Simulate user input for demo purposes)
                    if (processCount > 0 && resourceCount > 0) {
                        allocation[0][0] = 1;
                        request[0][0] = 1;
                        available[0] = 1;
                    }
                    break;
                }
                case 4: {
                    // Detect Deadlock
                    std::string output = detectDeadlock();
                    SetWindowText(hOutput, output.c_str());
                    break;
                }
                case 5: {
                    // Recover from Deadlock (Simplified for demo purposes)
                    if (processCount > 0 && resourceCount > 0) {
                        allocation[0][0] = 0;
                        request[0][0] = 0;
                        available[0] = 1;
                    }
                    break;
                }
            }
            break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

void AddControls(HWND hWnd) {
    hAddProcess = CreateWindowW(L"Button", L"Add Process", WS_VISIBLE | WS_CHILD, 50, 50, 150, 36, hWnd, (HMENU)1, NULL, NULL);
    hAddResource = CreateWindowW(L"Button", L"Add Resource", WS_VISIBLE | WS_CHILD, 50, 100, 150, 36, hWnd, (HMENU)2, NULL, NULL);
    hAllocate = CreateWindowW(L"Button", L"Allocate Resource", WS_VISIBLE | WS_CHILD, 50, 150, 150, 36, hWnd, (HMENU)3, NULL, NULL);
    hDetectDeadlock = CreateWindowW(L"Button", L"Detect Deadlock", WS_VISIBLE | WS_CHILD, 50, 200, 150, 36, hWnd, (HMENU)4, NULL, NULL);
    hRecover = CreateWindowW(L"Button", L"Recover", WS_VISIBLE | WS_CHILD, 50, 250, 150, 36, hWnd, (HMENU)5, NULL, NULL);
    hOutput = CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            250, 50, 500, 400, hWnd, NULL, NULL, NULL);
}

// Deadlock detection algorithm (Banker's Algorithm for simplicity)
std::string detectDeadlock() {
    std::vector<bool> finish(processCount, false);
    std::vector<int> work = available;
    std::stringstream ss;

    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < processCount; ++i) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < resourceCount; ++j) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < resourceCount; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    bool deadlock = false;
    ss << "Deadlock Detection Result:\r\n";
    for (int i = 0; i < processCount; ++i) {
        if (!finish[i]) {
            deadlock = true;
            ss << "Process " << i << " is in deadlock.\r\n";
        }
    }
    if (!deadlock) {
        ss << "No deadlock detected.\r\n";
    }
    return ss.str();
}
