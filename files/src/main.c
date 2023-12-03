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
    ShowWindow( GetConsoleWindow(), SW_HIDE );

    // constantly check controller state
    initilizeController();
    while (1) {

        // DO NOT TOUCH THIS! I KNOW IT IS REDUNDANT BUT IF YOU FUCKING TOUCH IT EVERYTHING BREAKS! WHY? I DON'T FUCKING KNOW ASK THE POOR C DEV WHO WENT INSANE BUILDING THIS LIBRARY
        if (XInputGetState(0, &controller.controls) == ERROR_SUCCESS) {

            // if start pressed show the action menu
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_START && !controller.startButtonPressed) {
                _beginthread(actionsWindowThread, 0, NULL);
                controller.startButtonPressed = 1;
            } else if (controller.startButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_START)) { controller.startButtonPressed = 0; }

            // if select pressed show the sensitivity menu
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_BACK && !controller.selectButtonPressed) {
                _beginthread(sensitivityWindowThread, 0, NULL);
                controller.selectButtonPressed = 1;
            } else if (controller.selectButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)) { controller.selectButtonPressed = 0; }

            // if A pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_A && !controller.aButtonPressed) {
                controller.aButtonPressed = 1;
                if (strcmp(controller.aButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.aButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.aButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.aButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.aButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.aButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.aButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
                controller.aButtonPressed = 0;
                if (strcmp(controller.aButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.aButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.aButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if B pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_B && !controller.bButtonPressed) {
                controller.bButtonPressed = 1;
                if (strcmp(controller.bButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.bButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.bButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.bButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.bButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.bButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.bButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
                controller.bButtonPressed = 0;
                if (strcmp(controller.bButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.bButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.bButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if X pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_X && !controller.xButtonPressed) {
                controller.xButtonPressed = 1;
                if (strcmp(controller.xButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.xButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.xButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.xButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.xButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.xButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.xButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
                controller.xButtonPressed = 0;
                if (strcmp(controller.xButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.xButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.xButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if Y pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_Y && !controller.yButtonPressed) {
                controller.yButtonPressed = 1;
                if (strcmp(controller.yButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.yButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.yButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.yButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.yButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.yButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.yButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
                controller.yButtonPressed = 0;
                if (strcmp(controller.yButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.yButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.yButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if left joystick button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB && !controller.leftJoystickButtonPressed) {
                controller.leftJoystickButtonPressed = 1;
                if (strcmp(controller.leftJoystickButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.leftJoystickButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.leftJoystickButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.leftJoystickButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.leftJoystickButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.leftJoystickButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.leftJoystickButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
                controller.leftJoystickButtonPressed = 0;
                if (strcmp(controller.leftJoystickButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.leftJoystickButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.leftJoystickButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if right joystick button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB && !controller.rightJoystickButtonPressed) {
                controller.rightJoystickButtonPressed = 1;
                if (strcmp(controller.rightJoystickButtonFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.rightJoystickButtonFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.rightJoystickButtonFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.rightJoystickButtonFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.rightJoystickButtonFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.rightJoystickButtonFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.rightJoystickButtonPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
                controller.rightJoystickButtonPressed = 0;
                if (strcmp(controller.rightJoystickButtonFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.rightJoystickButtonFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.rightJoystickButtonFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if left shoulder button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && !controller.leftShoulderPressed) {
                controller.leftShoulderPressed = 1;
                if (strcmp(controller.leftShoulderFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.leftShoulderFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.leftShoulderFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.leftShoulderFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.leftShoulderFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.leftShoulderFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.leftShoulderPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
                controller.leftShoulderPressed = 0;
                if (strcmp(controller.leftShoulderFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.leftShoulderFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.leftShoulderFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // if right shoulder button pressed
            if (controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && !controller.rightShoulderPressed) {
                controller.rightShoulderPressed = 1;
                if (strcmp(controller.rightShoulderFunction, "primarymousebutton") == 0) {
                    holdPrimaryMouseButton();
                } else if (strcmp(controller.rightShoulderFunction, "secondarymousebutton") == 0) {
                    holdSecondaryMouseButton();
                } else if (strcmp(controller.rightShoulderFunction, "middlemousebutton") == 0) {
                    holdMiddleMouseButton();
                } else if (strcmp(controller.rightShoulderFunction, "on-screenkeyboard") == 0) {
                    onScreenKeyboard();
                } else if (strcmp(controller.rightShoulderFunction, "windowskey") == 0) {
                    windowsKey();
                } else if (strcmp(controller.rightShoulderFunction, "screenshot") == 0) {
                    screenshot();
                }
            } else if (controller.rightShoulderPressed && !(controller.controls.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
                controller.rightShoulderPressed = 0;
                if (strcmp(controller.rightShoulderFunction, "primarymousebutton") == 0) {
                    releasePrimaryMouseButton();
                } else if (strcmp(controller.rightShoulderFunction, "secondarymousebutton") == 0) {
                    releaseSecondaryMouseButton();
                } else if (strcmp(controller.rightShoulderFunction, "middlemousebutton") == 0) {
                    releaseMiddleMouseButton();
                }
            }

            // update mouse based joystick positions
            moveMouse();
            scroll();
        }

        // this is how we *don't* hog the cpu
        Sleep(10);
    }
}

