// DO NOT TOUCH THIS CODE! DON'T EDIT IT, DON'T MOVE SHIT AROUND, DON'T EVEN LOOK AT IT. IF YOU LOOK AT EVEN ONE LINE OF CODE THE WRONG WAY, THEN BAM! IT'LL BREAK. AND IT'LL HAVE TO BE *ME* WHO FIXES IT
// FOR YOU, WHICH WOULD JUST SUCK COS I DON'T HAVE TIME TO FIX IT RN, AND TRUTH BE TOLD EVEN I DON'T FUCKING KNOW HOW IT WORKS. AND I KNOW WHAT YOU'RE THINKING "Oh, but if i just move something then
// see if it works–" NO! I TOLD
// YOU BEFORE!
// TOUCH *ANYTHING*
// AND IT BREAKS! ALSO, DON'T EVEN THINK ABOUT HITTING CONTROL Z TO UNDO, COS THE CODE KNOWS, IT'LL REMEMBER, AND IT WON'T WORK! THIS IS THE MOST STABLE I COULD GET THIS CODE TO BE,
// IF IT DOESN'T RUN, *PLEASE* DON'T TRY TO DEBUG IT, JUST RUN IT AGAIN, AND IT'LL' WORK. HOW DOES THIS HAPPEN? FUCKING MAGIC, IDFK. JUST.... PLEASE.... HEED MY WARNING, DO NOT TOUCH THIS CODE.

#include "controller.h"
controllerData controller;

int main() {

    // constantly check controller state
    initializeController();
    while (1) {

        // DO NOT TOUCH THIS! I KNOW IT IS REDUNDANT BUT IF YOU FUCKING TOUCH IT EVERYTHING BREAKS! WHY? I DON'T FUCKING KNOW ASK THE POOR C DEV WHO WENT INSANE BUILDING THIS LIBRARY
        if (XInputGetState(0, &controller.controls) == ERROR_SUCCESS) {

            // if start pressed show the action menu
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_START && !controller.startButtonPressed) {
                HANDLE threadHandle = CreateThread(NULL, 0, actionsWindowThread, NULL, 0, NULL);
                controller.startButtonPressed = 1;
            } else if (controller.startButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_START)) { controller.startButtonPressed = 0; }

            // if select pressed show the sensitivity menu
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_BACK && !controller.selectButtonPressed) {
                HANDLE threadHandle = CreateThread(NULL, 0, sensitivityWindowThread, NULL, 0, NULL);
                controller.selectButtonPressed = 1;
            } else if (controller.selectButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)) { controller.selectButtonPressed = 0; }

            // if A pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_A && !controller.aButtonPressed) {
                controller.aButtonPressed = 1;
                doTask(controller.aButtonFunction);
                printf("A pressed");
            } else if (controller.aButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
                controller.aButtonPressed = 0;
                checkForRelease(controller.aButtonFunction);
            }

            // if B pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_B && !controller.bButtonPressed) {
                controller.bButtonPressed = 1;
                doTask(controller.bButtonFunction);
            } else if (controller.bButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
                controller.bButtonPressed = 0;
                checkForRelease(controller.bButtonFunction);
            }

            // if X pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_X && !controller.xButtonPressed) {
                controller.xButtonPressed = 1;
                doTask(controller.xButtonFunction);
            } else if (controller.xButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
                controller.xButtonPressed = 0;
                checkForRelease(controller.bButtonFunction);
            }

            // if Y pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_Y && !controller.yButtonPressed) {
                controller.yButtonPressed = 1;
                doTask(controller.yButtonFunction);
            } else if (controller.yButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
                controller.yButtonPressed = 0;
                checkForRelease(controller.yButtonFunction);
            }

            // if left joystick button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB && !controller.leftJoystickButtonPressed) {
                controller.leftJoystickButtonPressed = 1;
                doTask(controller.leftJoystickButtonFunction);
            } else if (controller.leftJoystickButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
                controller.leftJoystickButtonPressed = 0;
                checkForRelease(controller.leftJoystickButtonFunction);
            }

            // if right joystick button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB && !controller.rightJoystickButtonPressed) {
                controller.rightJoystickButtonPressed = 1;
                doTask(controller.rightJoystickButtonFunction);
            } else if (controller.rightJoystickButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
                controller.rightJoystickButtonPressed = 0;
                checkForRelease(controller.rightJoystickButtonFunction);
            }

            // if left shoulder button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && !controller.leftShoulderPressed) {
                controller.leftShoulderPressed = 1;
                doTask(controller.leftShoulderFunction);
            } else if (controller.leftShoulderPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
                controller.leftShoulderPressed = 0;
                checkForRelease(controller.leftShoulderFunction);
            }

            // if right shoulder button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && !controller.rightShoulderPressed) {
                controller.rightShoulderPressed = 1;
                doTask(controller.rightJoystickButtonFunction);
            } else if (controller.rightShoulderPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
                controller.rightShoulderPressed = 0;
                checkForRelease(controller.rightJoystickButtonFunction);
            }

            // update mouse based joystick positions
            moveMouse();
            scroll();

        }

        // this is how we *don't* hog the cpu
        Sleep(10);

    }
}

