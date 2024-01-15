// DO NOT TOUCH THIS CODE! DON'T EDIT IT, DON'T MOVE SHIT AROUND, DON'T EVEN LOOK AT IT. IF YOU LOOK AT EVEN ONE LINE OF
// CODE THE WRONG WAY, THEN BAM! IT'LL BREAK. AND IT'LL HAVE TO BE *ME* WHO FIXES IT
// FOR YOU, WHICH WOULD JUST SUCK COS I DON'T HAVE TIME TO FIX IT RN, AND TRUTH BE TOLD EVEN I DON'T FUCKING KNOW HOW IT
// WORKS. AND I KNOW WHAT YOU'RE THINKING "Oh, but if i just move something then
// see if it works–" NO! I TOLD YOU BEFORE! TOUCH *ANYTHING* AND IT BREAKS! # ALSO, DON'T EVEN THINK ABOUT HITTING CTRL+Z
// TO UNDO, COS THE CODE KNOWS, IT'LL REMEMBER, AND IT WON'T WORK! THIS IS THE MOST STABLE I COULD GET THIS CODE TO BE,
// IF IT DOESN'T RUN, *PLEASE* DON'T TRY TO DEBUG IT, JUST RUN IT AGAIN, AND IT'LL WORK. HOW DOES THIS HAPPEN?
// FUCKING MAGIC, IDFK. JUST.... PLEASE.... HEED MY WARNING, DO NOT TOUCH THIS CODE.

#include "controller.h"

int main() {

    // constantly check controller state
    initializeController();
    while (1) {

        // DO NOT TOUCH THIS! I KNOW IT IS REDUNDANT BUT IF YOU FUCKING TOUCH IT EVERYTHING BREAKS! WHY? I DON'T FUCKING KNOW ASK THE POOR C DEV WHO WENT INSANE BUILDING THIS LIBRARY
        if (XInputGetState(0, &controller.controls) == ERROR_SUCCESS) {

            // check if  the controller is allowed to make inputs
            char *activeApplication = getActiveApplication();
            int blacklistedApplicationActive = 0;
                for (int j = 0; j < controller.blacklistLength; j++) {
                    if (strcmp(controller.blacklist[j], activeApplication) == 0) {
                        blacklistedApplicationActive = 1;
                    }
                }
            free(activeApplication);

            // watch for button presses
            for (int i = 0; i < buttonCount; ++i) {

                if (!blacklistedApplicationActive || i == 1) {
                    if (controller.controls.Gamepad.wButtons & buttons[i].id && !buttons[i].pressed) {
                        buttons[i].pressed = 1;
                        doTask(buttons[i].function);
                    } else if (buttons[i].pressed && !(controller.controls.Gamepad.wButtons & buttons[i].id)) {
                        buttons[i].pressed = 0;
                        checkForRelease(buttons[i].function);
                    }
                }

                // update mouse based joystick positions
                if (!blacklistedApplicationActive) {
                    moveMouse();
                    scroll();
                }
            }
        }

        Sleep(10);

    }
}