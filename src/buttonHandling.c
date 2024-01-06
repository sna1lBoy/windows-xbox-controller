#include "controller.h"

// declare structs and types
struct Button buttons[buttonCount];
Controller controller;

void initializeController() {

    // set up buttons
    char *buttonFunctions[] = {"start", "select", readConfig("A"), readConfig("B"), readConfig("X"), readConfig("Y"), readConfig("left joystick button"), readConfig("right joystick button"),readConfig("left shoulder"), readConfig("right shoulder")};
    int buttonIds[] = {XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y, XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB, XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER};
    for (int i = 0; i < buttonCount; i++) {
        buttons[i].pressed = 0;
        buttons[i].function = buttonFunctions[i];
        buttons[i].id = buttonIds[i];
    }

    // set up controller
    controller.verticalMouseSensitivity = atoi(readConfig("vertical mouse sensitivity"));
    controller.horizontalMouseSensitivity = atoi(readConfig("horizontal mouse sensitivity"));
    controller.verticalScrollSensitivity = atoi(readConfig("vertical scroll sensitivity"));
    controller.horizontalScrollSensitivity = atoi(readConfig("horizontal scroll sensitivity"));
    controller.leftJoystickFunction = readConfig("left joystick");
    controller.rightJoystickFunction = readConfig("right joystick");

    // read blacklist
    char* configBlacklist = readConfig("blacklist");
    int i = 0;
    if (strcmp(configBlacklist, "\n") != 0 && strcmp(configBlacklist, " \n") != 0) {
        const char delimiter[2] = ", ";
        char *token;
        token = strtok(configBlacklist, delimiter);
        while (token != NULL) {
            controller.blacklist[i++] = token;
            token = strtok(NULL, delimiter);
        }
    }
    controller.blacklistLength = i;

}

// move mouse based on joystick position
void moveMouse() {

    INPUT mouseInput = {0};
    mouseInput.type = INPUT_MOUSE;
    mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;

    if (strcmp(controller.leftJoystickFunction, "move mouse") == 0) {
        mouseInput.mi.dx = (controller.controls.Gamepad.sThumbLX / ((101 - controller.horizontalMouseSensitivity) * 200));
        mouseInput.mi.dy = -(controller.controls.Gamepad.sThumbLY / ((101 - controller.verticalMouseSensitivity) * 200));
        SendInput(1, &mouseInput, sizeof(INPUT));
    }

    if (strcmp(controller.rightJoystickFunction, "move mouse") == 0) {
        mouseInput.mi.dx = (controller.controls.Gamepad.sThumbRX / ((101 - controller.horizontalMouseSensitivity) * 200));
        mouseInput.mi.dy = -(controller.controls.Gamepad.sThumbRY / ((101 - controller.verticalMouseSensitivity) * 200));
        SendInput(1, &mouseInput, sizeof(INPUT));
    }

}

// scroll based on joystick position
void scroll() {

    INPUT verticalWheelInput = {0};
    verticalWheelInput.type = INPUT_MOUSE;
    verticalWheelInput.mi.dwFlags = MOUSEEVENTF_WHEEL;

    INPUT horizontalWheelInput = {0};
    horizontalWheelInput.type = INPUT_MOUSE;
    horizontalWheelInput.mi.dwFlags = MOUSEEVENTF_HWHEEL;


    if (strcmp(controller.leftJoystickFunction, "scroll") == 0) {
        verticalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbLY / ((101 - controller.verticalScrollSensitivity) * 25));
        SendInput(1, &verticalWheelInput, sizeof(INPUT));
        horizontalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbLX / ((101 - controller.horizontalScrollSensitivity) * 25));
        SendInput(1, &horizontalWheelInput, sizeof(INPUT));
    }

    if (strcmp(controller.rightJoystickFunction, "scroll") == 0) {
        verticalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbRY / ((101 - controller.verticalScrollSensitivity) * 25));
        SendInput(1, &verticalWheelInput, sizeof(INPUT));
        horizontalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbRX / ((101 - controller.horizontalScrollSensitivity) * 25));
        SendInput(1, &horizontalWheelInput, sizeof(INPUT));
    }

}

// presses the windows key
void windowsKey() {
    keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
}

// opens the on screen keyboard
void onScreenKeyboard() {
    system("start osk.exe");
}

// takes a screenshot with control+shift+s
void screenshot() {
    keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(0x53, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
}

// holds down the primary mouse button
void holdPrimaryMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

// releases down the primary mouse button
void releasePrimaryMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// holds down the secondary mouse button
void holdSecondaryMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

// releases the secondary mouse button
void releaseSecondaryMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// holds down the middle mouse button
void holdMiddleMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

// releases the middle mouse button
void releaseMiddleMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    SendInput(1, &input, sizeof(INPUT));
}

// perform the given button's assigned task
void doTask(char *task) {
    if (strcmp(task, "start") == 0) {
        CreateThread(NULL, 0, settingsWindowThread, NULL, 0, NULL);

    } else if (strcmp(task, "select") == 0) {
        char *processName = getActiveApplication();
        char line[10000];
        line[0] = '\0';

        // see if application needs to be unblacklisted
        int blacklisted = 0;
        for (int i = 0; i < controller.blacklistLength; i++) {
            if (strcmp(processName, controller.blacklist[i]) == 0) {
                blacklisted = 1;
                for (int j = i; j < controller.blacklistLength - 1; j++) {
                    strcpy(controller.blacklist[j], controller.blacklist[j + 1]);
                }
                controller.blacklistLength--;
                i--;
            }
        }

        // if not blacklisted then blacklist
        if (!blacklisted) {
            controller.blacklist[controller.blacklistLength] = processName;
            controller.blacklistLength++;
        }

        // write updated list to file
        for (int i = 0; i < controller.blacklistLength; i++) {
            strcat(line, controller.blacklist[i]);
            strcat(line, ", ");
        }
        writeConfig("blacklist", line);

    } else if (strcmp(task, "primary mouse button") == 0) {
        holdPrimaryMouseButton();
    } else if (strcmp(task, "secondary mouse button") == 0) {
        holdSecondaryMouseButton();
    } else if (strcmp(task, "middle mouse button") == 0) {
        holdMiddleMouseButton();
    } else if (strcmp(task, "on-screen keyboard") == 0) {
        onScreenKeyboard();
    } else if (strcmp(task, "windows key") == 0) {
        windowsKey();
    } else if (strcmp(task, "screenshot") == 0) {
        screenshot();
    }
}

// when a button is release see if a mouse button needs to be released as well
void checkForRelease(char *button) {
    if (strcmp(button, "primary mouse button") == 0) {
        releasePrimaryMouseButton();
    } else if (strcmp(button, "secondary mouse button") == 0) {
        releaseSecondaryMouseButton();
    } else if (strcmp(button, "middle mouse button") == 0) {
        releaseMiddleMouseButton();
    }
}