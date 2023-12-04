#include "../controller.h"
static HWND aComboBox, bComboBox, xComboBox, yComboBox, leftJoystickComboBox, rightJoystickComboBox, leftJoystickButtonComboBox, rightJoystickButtonComboBox, leftShoulderComboBox, rightShoulderComboBox;
static HWND hwnd = NULL;

// creates an action selection combo box
HWND createActionSelection(int joystick, HWND hwnd, char title[], LPCWSTR fancyTitle, int xPositionWindow, int yPositionWindow, int yPositionBox) {

    // make label and box based on parameters
    CreateWindowW(L"STATIC", fancyTitle, WS_CHILD | WS_VISIBLE, xPositionWindow, yPositionWindow, 150, 25, hwnd, NULL, NULL, NULL);
    HWND comboBox = CreateWindowW(L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 135, yPositionBox, 175, 150, hwnd, (HMENU) 1011, NULL, NULL);

    // set options based on what's stored in the config
    if (joystick == 1) {
        char *actions[] = {"move mouse","scroll", "none"};
        for (size_t i = 0; i < sizeof(actions) / sizeof(actions[0]); i++) {
            SendMessage(comboBox, CB_ADDSTRING, 0, (LPARAM)_T(actions[i]));

            char formattedAction[100];
            strcpy(formattedAction, actions[i]);
            removeWhitespace(formattedAction);

            if (strcmp(readConfig(title), formattedAction) == 0) {
                SendMessage(comboBox, CB_SETCURSEL, (WPARAM)i, 0);
            }
        }

    // hi yes i know i repeat the same code here twice just with different arrays but nothing else worked after hours of trying or any answer resulted in more lines of code because of reallocating memories and resizing arrays so shut up
    } else {
        char *actions[] = {"primary mouse button","secondary mouse button","middle mouse button","on-screen keyboard","windows key","screenshot","none"};
        for (size_t i = 0; i < sizeof(actions) / sizeof(actions[0]); i++) {
            SendMessage(comboBox, CB_ADDSTRING, 0, (LPARAM)_T(actions[i]));

            char formattedAction[100];
            strcpy(formattedAction, actions[i]);
            removeWhitespace(formattedAction);

            if (strcmp(readConfig(title), formattedAction) == 0) {
                SendMessage(comboBox, CB_SETCURSEL, (WPARAM)i, 0);
            }
        }
    }

    return comboBox;
}

// defines the window's behavior
LRESULT CALLBACK WndProcActions(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    // make the window
    case WM_CREATE: {

        // set background
        CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 330, 295, hwnd, NULL, NULL, NULL);

        // create selection boxes
        aComboBox = createActionSelection(0, hwnd, "A", L"A", 60, 8, 5);
        bComboBox = createActionSelection(0, hwnd, "B", L"B", 60, 33, 30);
        xComboBox = createActionSelection(0, hwnd, "X", L"X", 60, 58, 55);
        yComboBox = createActionSelection(0, hwnd, "Y", L"Y", 60, 83, 80);
        leftJoystickButtonComboBox = createActionSelection(0, hwnd, "left joystick button", L"left joystick button", 8, 108, 105);
        rightJoystickButtonComboBox = createActionSelection(0, hwnd, "right joystick button", L"right joystick button", 5, 133, 130);
        leftShoulderComboBox = createActionSelection(0, hwnd, "left shoulder", L"left shoulder", 25, 158, 155);
        rightShoulderComboBox = createActionSelection(0, hwnd, "right shoulder", L"right shoulder", 20, 183, 180);
        leftJoystickComboBox = createActionSelection(1, hwnd, "left joystick", L"left joystick", 30, 208, 205);
        rightJoystickComboBox = createActionSelection(1, hwnd, "right joystick", L"right joystick", 25, 233, 230);

        break;

    // getting slider values
    } case WM_COMMAND: {

            // check if a box has changed selections
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                HWND comboBox = (HWND)lParam;
                char action[1000];

                // update controls
                if (comboBox == aComboBox) {
                    SendMessage(aComboBox, CB_GETLBTEXT, SendMessage(aComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.aButtonFunction, "%s", action);
                    writeConfig("A", action);
                } else if (comboBox == bComboBox) {
                    SendMessage(bComboBox, CB_GETLBTEXT, SendMessage(bComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.bButtonFunction, "%s", action);
                    writeConfig("B", action);
                } else if (comboBox == xComboBox) {
                    SendMessage(xComboBox, CB_GETLBTEXT, SendMessage(xComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.xButtonFunction, "%s", action);
                    writeConfig("X", action);
                } else if (comboBox == yComboBox) {
                    SendMessage(yComboBox, CB_GETLBTEXT, SendMessage(yComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.yButtonFunction, "%s", action);
                    writeConfig("Y", action);
                } else if (comboBox == leftJoystickButtonComboBox) {
                    SendMessage(leftJoystickButtonComboBox, CB_GETLBTEXT, SendMessage(leftJoystickButtonComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.leftJoystickButtonFunction, "%s", action);
                    writeConfig("left joystick button", action);
                } else if (comboBox == rightJoystickButtonComboBox) {
                    SendMessage(rightJoystickButtonComboBox, CB_GETLBTEXT, SendMessage(rightJoystickButtonComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.rightJoystickButtonFunction, "%s", action);
                    writeConfig("right joystick button", action);
                } else if (comboBox == leftShoulderComboBox) {
                    SendMessage(leftShoulderComboBox, CB_GETLBTEXT, SendMessage(leftShoulderComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.leftShoulderFunction, "%s", action);
                    writeConfig("left shoulder", action);
                } else if (comboBox == rightShoulderComboBox) {
                    SendMessage(rightShoulderComboBox, CB_GETLBTEXT, SendMessage(rightShoulderComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.rightShoulderFunction, "%s", action);
                    writeConfig("right shoulder", action);
                } else if (comboBox == leftJoystickComboBox) {
                    SendMessage(leftJoystickComboBox, CB_GETLBTEXT, SendMessage(leftJoystickComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.leftJoystickFunction, "%s", action);
                    writeConfig("left joystick", action);
                } else if (comboBox == rightJoystickComboBox) {
                    SendMessage(rightJoystickComboBox, CB_GETLBTEXT, SendMessage(rightJoystickComboBox, CB_GETCURSEL, 0, 0), (LPARAM)action);
                    removeWhitespace(action);
                    sprintf(controller.rightJoystickFunction, "%s", action);
                    writeConfig("right joystick", action);
                }
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
DWORD WINAPI actionsWindowThread(LPVOID lpParam) {

    // creating controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    // initializing window
    if (!hwnd) {
        WNDCLASSEXW wcActions = { sizeof(WNDCLASSEXW), CS_CLASSDC, WndProcActions, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"actionsWindow", NULL };
        RegisterClassExW(&wcActions);
        hwnd = CreateWindowW(L"actionsWindow", L"Actions", WS_OVERLAPPEDWINDOW, ((GetSystemMetrics(SM_CXSCREEN) - 330) / 2), ((GetSystemMetrics(SM_CYSCREEN) - 295) / 2), 330, 295, NULL, NULL, wcActions.hInstance, NULL);
    }
    ShowWindow(hwnd, SW_SHOW);

    // taking input
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}