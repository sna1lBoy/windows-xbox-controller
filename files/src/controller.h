#ifndef controllerH
#define controllerH

// imports
#include <windows.h>
#include <dwmapi.h>
#include <commctrl.h>
#include <stdio.h>
#include <xinput.h>
#include <string.h>
#include <tchar.h>
#include <process.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Dwmapi.lib")

// defining the controller
typedef struct {
    XINPUT_STATE controls;
    int aButtonPressed;
    int bButtonPressed;
    int yButtonPressed;
    int xButtonPressed;
    int leftJoystickButtonPressed;
    int rightJoystickButtonPressed;
    int startButtonPressed;
    int selectButtonPressed;
    int leftShoulderPressed;
    int rightShoulderPressed;
    int verticalMouseSensitivity;
    int horizontalMouseSensitivity;
    int verticalScrollSensitivity;
    int horizontalScrollSensitivity;
    char *aButtonFunction;
    char *bButtonFunction;
    char *xButtonFunction;
    char *yButtonFunction;
    char *leftJoystickFunction;
    char *rightJoystickFunction;
    char *leftJoystickButtonFunction;
    char *rightJoystickButtonFunction;
    char *leftShoulderFunction;
    char *rightShoulderFunction;
} controllerData;

extern controllerData controller;

// ui functions
DWORD WINAPI sensitivityWindowThread(LPVOID lpParam);
DWORD WINAPI actionsWindowThread(LPVOID lpParam);

// file functions
void removeWhitespace(char* line);
char *readConfig(char key[]);
void writeConfig(char key[], char value[]);

// button functions
void initializeController();
void moveMouse();
void scroll();
void holdPrimaryMouseButton();
void releasePrimaryMouseButton();
void holdSecondaryMouseButton();
void releaseSecondaryMouseButton();
void holdMiddleMouseButton();
void releaseMiddleMouseButton();
void onScreenKeyboard();
void windowsKey();
void screenshot();
void doTask(char *button);
void checkForRelease(char *button);

#endif