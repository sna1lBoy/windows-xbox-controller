#include "controller.h"
static HWND verticalMouseSensitivitySlider, horizontalMouseSensitivitySlider, verticalScrollSensitivitySlider, horizontalScrollSensitivitySlider;
static HWND aComboBox, bComboBox, xComboBox, yComboBox, leftJoystickComboBox, rightJoystickComboBox, leftJoystickButtonComboBox, rightJoystickButtonComboBox, leftShoulderComboBox, rightShoulderComboBox;
static HWND hwnd = NULL;

// creates an action selection combo box
HWND createActionSelection(int joystick, HWND hwnd, char title[], LPCWSTR fancyTitle, int xPositionWindow, int yPositionWindow, int yPositionBox) {

    // make label and box based on parameters
    CreateWindowW(L"STATIC", fancyTitle, WS_CHILD | WS_VISIBLE, xPositionWindow, yPositionWindow, 150, 25, hwnd, NULL, NULL, NULL);
    HWND comboBox = CreateWindowW(L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 135, yPositionBox, 175, 150, hwnd, (HMENU) 1011, NULL, NULL);
    char* key = readConfig(title);


    // set options based on what's stored in the config
    if (joystick == 1) {
        char *actions[] = {"move mouse","scroll", "none"};
        for (size_t i = 0; i < sizeof(actions) / sizeof(actions[0]); i++) {
            SendMessage(comboBox, CB_ADDSTRING, 0, (LPARAM)_T(actions[i]));
            if (strcmp(key, actions[i]) == 0) {
                SendMessage(comboBox, CB_SETCURSEL, (WPARAM)i, 0);
            }
        }

    // hi yes i know i repeat the same code here twice just with different arrays but nothing else worked after hours of trying or any answer resulted in more lines of code because of reallocating memories and resizing arrays so shut up tom scott
    } else {
        char *actions[] = {"primary mouse button","secondary mouse button","middle mouse button","on-screen keyboard","windows key","screenshot","none"};
        for (size_t i = 0; i < sizeof(actions) / sizeof(actions[0]); i++) {
            SendMessage(comboBox, CB_ADDSTRING, 0, (LPARAM)_T(actions[i]));
            if (strcmp(key, actions[i]) == 0) {
                SendMessage(comboBox, CB_SETCURSEL, (WPARAM)i, 0);
            }
        }
    }
    free(key);
    return comboBox;
}

// creates a sensitivity selection trackbar
HWND createSensitivityBar(HWND hwnd, LPCWSTR fancyTitle, int yPositionWindow, int yPositionBar, int value) {
    CreateWindowW(L"STATIC", fancyTitle, WS_CHILD | WS_VISIBLE, 315, yPositionWindow, 200, 20, hwnd, NULL, NULL, NULL);
    HWND trackBar = CreateWindowW(TRACKBAR_CLASSW, L"", WS_CHILD | WS_VISIBLE | TBS_HORZ, 310, yPositionBar, 200, 30, hwnd, (HMENU)1001, NULL, NULL);
    SendMessage(trackBar, TBM_SETPOS, TRUE, value);
    return trackBar;
}

// defines the window's behavior
LRESULT CALLBACK WndProcActions(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    // make the window
    case WM_CREATE: {

        // set background
        CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 525, 295, hwnd, NULL, NULL, NULL);

        // create selection boxes
        aComboBox = createActionSelection(0, hwnd, "A", L"A", 120, 8, 5);
        bComboBox = createActionSelection(0, hwnd, "B", L"B", 120, 33, 30);
        xComboBox = createActionSelection(0, hwnd, "X", L"X", 120, 58, 55);
        yComboBox = createActionSelection(0, hwnd, "Y", L"Y", 120, 83, 80);
        leftJoystickButtonComboBox = createActionSelection(0, hwnd, "left joystick button", L"left joystick button", 13, 108, 105);
        rightJoystickButtonComboBox = createActionSelection(0, hwnd, "right joystick button", L"right joystick button", 5, 133, 130);
        leftShoulderComboBox = createActionSelection(0, hwnd, "left shoulder", L"left shoulder", 50, 158, 155);
        rightShoulderComboBox = createActionSelection(0, hwnd, "right shoulder", L"right shoulder", 40, 183, 180);
        leftJoystickComboBox = createActionSelection(1, hwnd, "left joystick", L"left joystick", 55, 208, 205);
        rightJoystickComboBox = createActionSelection(1, hwnd, "right joystick", L"right joystick", 45, 233, 230);

        //create trackbars
        verticalMouseSensitivitySlider = createSensitivityBar(hwnd, L"vertical mouse sensitivity", 5, 20, controller.verticalMouseSensitivity);
        horizontalMouseSensitivitySlider = createSensitivityBar(hwnd, L"horizontal mouse sensitivity", 55, 70, controller.horizontalMouseSensitivity);
        verticalScrollSensitivitySlider = createSensitivityBar(hwnd, L"vertical scroll sensitivity", 105, 120, controller.verticalScrollSensitivity);
        horizontalScrollSensitivitySlider = createSensitivityBar(hwnd, L"horizontal scroll sensitivity", 155, 170, controller.horizontalScrollSensitivity);

        break;

    // getting box values
    } case WM_COMMAND: {

        // check if a box has changed selections
        if (HIWORD(wParam) == CBN_SELCHANGE) {
            HWND comboBox = (HWND)lParam;
            char action[1000];

            // update controls
            if (comboBox == aComboBox) {
                SendMessage(aComboBox, CB_GETLBTEXT, SendMessage(aComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[2].function, "%s", action);
                writeConfig("A", action);
            } else if (comboBox == bComboBox) {
                SendMessage(bComboBox, CB_GETLBTEXT, SendMessage(bComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[3].function, "%s", action);
                writeConfig("B", action);
            } else if (comboBox == xComboBox) {
                SendMessage(xComboBox, CB_GETLBTEXT, SendMessage(xComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[4].function, "%s", action);
                writeConfig("X", action);
            } else if (comboBox == yComboBox) {
                SendMessage(yComboBox, CB_GETLBTEXT, SendMessage(yComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[5].function, "%s", action);
                writeConfig("Y", action);
            } else if (comboBox == leftJoystickButtonComboBox) {
                SendMessage(leftJoystickButtonComboBox, CB_GETLBTEXT, SendMessage(leftJoystickButtonComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[6].function, "%s", action);
                writeConfig("left joystick button", action);
            } else if (comboBox == rightJoystickButtonComboBox) {
                SendMessage(rightJoystickButtonComboBox, CB_GETLBTEXT, SendMessage(rightJoystickButtonComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[7].function, "%s", action);
                writeConfig("right joystick button", action);
            } else if (comboBox == leftShoulderComboBox) {
                SendMessage(leftShoulderComboBox, CB_GETLBTEXT, SendMessage(leftShoulderComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[8].function, "%s", action);
                writeConfig("left shoulder", action);
            } else if (comboBox == rightShoulderComboBox) {
                SendMessage(rightShoulderComboBox, CB_GETLBTEXT, SendMessage(rightShoulderComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(buttons[9].function, "%s", action);
                writeConfig("right shoulder", action);
            } else if (comboBox == leftJoystickComboBox) {
                SendMessage(leftJoystickComboBox, CB_GETLBTEXT, SendMessage(leftJoystickComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(controller.leftJoystickFunction, "%s", action);
                writeConfig("left joystick", action);
            } else if (comboBox == rightJoystickComboBox) {
                SendMessage(rightJoystickComboBox, CB_GETLBTEXT, SendMessage(rightJoystickComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                sprintf(controller.rightJoystickFunction, "%s", action);
                writeConfig("right joystick", action);
            }
        }

        break;

    // on scroll
    } case WM_HSCROLL: {
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

    // on close
    } case WM_CLOSE: {
        ShowWindow(hwnd, SW_HIDE);
        break;

    // on exit
    } case WM_DESTROY: {
        PostQuitMessage(0);
        break;

    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// setting up the window
DWORD WINAPI settingsWindowThread(LPVOID lpParam) {

    // creating controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    // initializing window
    if (!hwnd) {
        WNDCLASSEXW wcActions = { sizeof(WNDCLASSEXW), CS_CLASSDC, WndProcActions, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"settingsWindow", NULL };
        RegisterClassExW(&wcActions);
        hwnd = CreateWindowW(L"settingsWindow", L"", WS_OVERLAPPEDWINDOW, ((GetSystemMetrics(SM_CXSCREEN) - 525) / 2), ((GetSystemMetrics(SM_CYSCREEN) - 295) / 2), 525, 295, NULL, NULL, wcActions.hInstance, NULL);
    }
    ShowWindow(hwnd, SW_SHOW);

    // taking input
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}