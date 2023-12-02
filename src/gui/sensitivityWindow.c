#include "../controller.h"
static HWND hwnd = NULL;

// creates a sensitivity selection trackbar
HWND createSensitivityBar(HWND hwnd, LPCWSTR fancyTitle, int yPositionWindow, int yPositionBar, int value) {
    CreateWindowW(L"STATIC", fancyTitle, WS_CHILD | WS_VISIBLE, 5, yPositionWindow, 200, 20, hwnd, NULL, NULL, NULL);
    HWND trackBar = CreateWindowW(TRACKBAR_CLASSW, L"", WS_CHILD | WS_VISIBLE | TBS_HORZ, 0, yPositionBar, 200, 30, hwnd, (HMENU)1001, NULL, NULL);
    SendMessage(trackBar, TBM_SETPOS, TRUE, value);
    return trackBar;
}

// defines the window's behavior
LRESULT CALLBACK WndProcSensitivity(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND verticalMouseSensitivitySlider, horizontalMouseSensitivitySlider, verticalScrollSensitivitySlider, horizontalScrollSensitivitySlider;

    switch (msg) {

        // make the window
        case WM_CREATE: {

            // set background
            CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 215, 245, hwnd, NULL, NULL, NULL);

            // create trackbars
            verticalMouseSensitivitySlider = createSensitivityBar(hwnd, L"Vertical mouse sensitivity", 5, 20, controller.verticalMouseSensitivity);
            horizontalMouseSensitivitySlider = createSensitivityBar(hwnd, L"Horizontal mouse sensitivity", 55, 70, controller.horizontalMouseSensitivity);
            verticalScrollSensitivitySlider = createSensitivityBar(hwnd, L"Vertical scroll sensitivity", 105, 120, controller.verticalScrollSensitivity);
            horizontalScrollSensitivitySlider = createSensitivityBar(hwnd, L"Horizontal scroll sensitivity", 155, 170, controller.horizontalScrollSensitivity);

            break;
        }

        // on action
        case WM_HSCROLL: {
            char buffer[3];

            // get and set the slider values
            if ((HWND)lParam == verticalMouseSensitivitySlider) {
                controller.verticalMouseSensitivity = SendMessage(verticalMouseSensitivitySlider, TBM_GETPOS, 0, 0);
                sprintf(buffer, "%lld", SendMessage(verticalMouseSensitivitySlider, TBM_GETPOS, 0, 0));
                writeConfig("vertical mouse sensitivity", buffer);
            } else if ((HWND)lParam == horizontalMouseSensitivitySlider) {
                controller.horizontalMouseSensitivity = SendMessage(horizontalMouseSensitivitySlider, TBM_GETPOS, 0, 0);
                sprintf(buffer, "%lld", SendMessage(horizontalMouseSensitivitySlider, TBM_GETPOS, 0, 0));
                writeConfig("horizontal mouse sensitivity", buffer);
            } else if ((HWND)lParam == verticalScrollSensitivitySlider) {
                controller.verticalScrollSensitivity = SendMessage(verticalScrollSensitivitySlider, TBM_GETPOS, 0, 0);
                sprintf(buffer, "%lld", SendMessage(verticalScrollSensitivitySlider, TBM_GETPOS, 0, 0));
                writeConfig("vertical scroll sensitivity", buffer);
            } else if ((HWND)lParam == horizontalScrollSensitivitySlider) {
                controller.horizontalScrollSensitivity = SendMessage(horizontalScrollSensitivitySlider, TBM_GETPOS, 0, 0);
                sprintf(buffer, "%lld", SendMessage(horizontalScrollSensitivitySlider, TBM_GETPOS, 0, 0));
                writeConfig("horizontal scroll sensitivity", buffer);
            }

            break;
        }

        // on close
        case WM_CLOSE: {
            ShowWindow(hwnd, SW_HIDE);
            break;
        }

        // on exit
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// setting up the window
void sensitivityWindowThread() {

    // creating controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);

    // initializing window
    if (!hwnd) {
    WNDCLASSEX wcSensitivity = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProcSensitivity, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"sensitivityWindow", NULL };
    RegisterClassEx(&wcSensitivity);
    hwnd = CreateWindow(L"Sensitivity", "Sensitivity", WS_OVERLAPPEDWINDOW, ((GetSystemMetrics(SM_CXSCREEN) - 215) / 2), ((GetSystemMetrics(SM_CYSCREEN) - 245) / 2), 215, 245, NULL, NULL, wcSensitivity.hInstance, NULL);
    }
    ShowWindow(hwnd, SW_SHOW);

    // taking input
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}