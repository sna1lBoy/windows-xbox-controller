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
#include <tlhelp32.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Dwmapi.lib")

// defining the controller
typedef struct {
    XINPUT_STATE controls;
    int verticalMouseSensitivity;
    int horizontalMouseSensitivity;
    int verticalScrollSensitivity;
    int horizontalScrollSensitivity;
    char *leftJoystickFunction;
    char *rightJoystickFunction;
    char *blacklist[100];
    int blacklistLength;
} Controller;

// defining buttons
#define buttonCount 10
struct Button {
    int pressed;
    char* function;
    int id;
};

// setting up controller
extern Controller controller;
extern struct Button buttons[];

// ui functions
DWORD WINAPI settingsWindowThread(LPVOID lpParam);

// file functions
char *readConfig(char key[]);
void writeConfig(char key[], char value[]);
char *getActiveApplication();

// button functions
void initializeController();
void moveMouse();
void scroll();
void doTask(char *button);
void checkForRelease(char *button);

#endif