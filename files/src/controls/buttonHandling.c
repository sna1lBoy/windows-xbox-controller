#include "../controller.h"

void initilizeController() {
    controller.verticalMouseSensitivity = atoi(readConfig("vertical mouse sensitivity"));
    controller.horizontalMouseSensitivity = atoi(readConfig("horizontal mouse sensitivity"));
    controller.verticalScrollSensitivity = atoi(readConfig("vertical scroll sensitivity"));
    controller.horizontalScrollSensitivity = atoi(readConfig("horizontal scroll sensitivity"));
    controller.aButtonFunction = readConfig("A");
    controller.bButtonFunction = readConfig("B");
    controller.xButtonFunction = readConfig("X");
    controller.yButtonFunction = readConfig("Y");
    controller.leftJoystickFunction = readConfig("left joystick");
    controller.rightJoystickFunction = readConfig("right joystick");
    controller.leftJoystickButtonFunction = readConfig("left joystick button");
    controller.rightJoystickButtonFunction = readConfig("right joystick button");
    controller.leftShoulderFunction = readConfig("left shoulder");
    controller.rightShoulderFunction = readConfig("right shoulder");
}

// move mouse based on joystick position
void moveMouse() {

    if (strcmp(controller.leftJoystickFunction, "movemouse") == 0) {
        INPUT mouseInput = {0};
        mouseInput.type = INPUT_MOUSE;
        mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;
        mouseInput.mi.dx = (controller.controls.Gamepad.sThumbLX / ((101 - controller.horizontalMouseSensitivity) * 100));
        mouseInput.mi.dy = -(controller.controls.Gamepad.sThumbLY / ((101 - controller.verticalMouseSensitivity) * 100));
        SendInput(1, &mouseInput, sizeof(INPUT));
    }

    if (strcmp(controller.rightJoystickFunction, "movemouse") == 0) {
        INPUT mouseInput = {0};
        mouseInput.type = INPUT_MOUSE;
        mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;
        mouseInput.mi.dx = (controller.controls.Gamepad.sThumbRX / ((101 - controller.horizontalMouseSensitivity) * 100));
        mouseInput.mi.dy = -(controller.controls.Gamepad.sThumbRY / ((101 - controller.verticalMouseSensitivity) * 100));
        SendInput(1, &mouseInput, sizeof(INPUT));
    }
}

// scroll based on joystick position
void scroll() {

    if (strcmp(controller.leftJoystickFunction, "scroll") == 0) {
        INPUT verticalWheelInput = {0};
        verticalWheelInput.type = INPUT_MOUSE;
        verticalWheelInput.mi.dwFlags = MOUSEEVENTF_WHEEL;
        verticalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbLY / ((101 - controller.verticalScrollSensitivity) * 25));
        SendInput(1, &verticalWheelInput, sizeof(INPUT));

        INPUT horizontalWheelInput = {0};
        horizontalWheelInput.type = INPUT_MOUSE;
        horizontalWheelInput.mi.dwFlags = MOUSEEVENTF_HWHEEL;
        horizontalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbLX / ((101 - controller.horizontalScrollSensitivity) * 25));
        SendInput(1, &horizontalWheelInput, sizeof(INPUT));
    }

    if (strcmp(controller.rightJoystickFunction, "scroll") == 0) {

        INPUT verticalWheelInput = {0};
        verticalWheelInput.type = INPUT_MOUSE;
        verticalWheelInput.mi.dwFlags = MOUSEEVENTF_WHEEL;
        verticalWheelInput.mi.mouseData = (controller.controls.Gamepad.sThumbRY / ((101 - controller.verticalScrollSensitivity) * 25));
        SendInput(1, &verticalWheelInput, sizeof(INPUT));

        INPUT horizontalWheelInput = {0};
        horizontalWheelInput.type = INPUT_MOUSE;
        horizontalWheelInput.mi.dwFlags = MOUSEEVENTF_HWHEEL;
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