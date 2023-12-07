#include "controller.h"

// extracts all the values from config.ini
char *readConfig(char key[]) {

    // open the file
    FILE *file = fopen("config.ini", "r");

    // create one if none
    if (file == NULL) {
        fclose(file);
        file = fopen("config.ini", "w");
        fprintf(file, "vertical mouse sensitivity = 0\nhorizontal mouse sensitivity = 0\nvertical scroll sensitivity = 0\nhorizontal scroll sensitivity = 0\nA = primary mouse button\nB = secondary mouse button\nX = middle mouse button\nY = windows key\nleft joystick button = on-screen keyboard\nright joystick button = screenshot\nleft shoulder = none\nright shoulder = none\nleft joystick = move mouse\nright joystick = scroll\nblacklist = \n");
        fclose(file);
        file = fopen("config.ini", "r");
    }

    // read the lines
    char line[1000];
    while (fgets(line, sizeof(line), file)) {

        //split the lines
        char *token = strtok(line, "=");
        token[strlen(token) - 1] = '\0';

        // check if key is found
        if (strcmp(token, key) == 0) {
            char *value = strtok(NULL, "=");
            memmove(value, value + 1, strlen(value) - 1);
            value[strlen(value) - 2] = '\0';
            return strdup(value);
        }
    }

    // otherwise return none
    fclose(file);
    return strdup("none");

}

// writes a new key and value or replaces the one previously there
void writeConfig(char key[], char value[]) {

    // open the file
    FILE *file = fopen("config.ini", "r");

    // create one if none
    if (file == NULL) {
        fclose(file);
        file = fopen("config.ini", "w");
        fprintf(file, "vertical mouse sensitivity = 0\nhorizontal mouse sensitivity = 0\nvertical scroll sensitivity = 0\nhorizontal scroll sensitivity = 0\nA = primary mouse button\nB = secondary mouse button\nX = middle mouse button\nY = windows key\nleft joystick button = on-screen keyboard\nright joystick button = screenshot\nleft shoulder = none\nright shoulder = none\nleft joystick = move mouse\nright joystick = scroll\nblacklist = \n");
        fclose(file);
        file = fopen("config.ini", "r");
    }

    // store and edit contents of the config
    int found = 0;
    char line[1000];
    char *lines[100];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {

        // extract key of the line
        static char lineKey[100];
        char *equalsPosition = strchr(line, '=') - 1;
        if (equalsPosition != NULL) {
            int keyLength = equalsPosition - line;
            strncpy(lineKey, line, keyLength);
            lineKey[keyLength] = '\0';
        }

        // update key if found
        if (!found && strcmp(key, lineKey) == 0) {
            snprintf(line, sizeof(line), "%s = %s\n", key, value);
            found = 1;
        }

        lines[index] = strdup(line);
        index++;
    }

    // add line if not found
    if (!found) {
        snprintf(line, sizeof(line), "%s = %s\n", key, value);
        lines[index] = strdup(line);
        index ++;
    }

    fclose(file);

    // write over old config with changes
    file = fopen("config.ini", "w");
    for (int i = 0; i < index; i++) {
        fprintf(file, "%s", lines[i]);
        free(lines[i]);
    }

    fclose(file);

}

// returns the active application
char *getActiveApplication() {
    char processName[MAX_PATH];
    HWND hwnd = GetForegroundWindow();
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);
    if (processId != 0) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    if (pe32.th32ProcessID == processId) {
                        strcpy(processName, pe32.szExeFile);
                        break;
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }
            CloseHandle(hSnapshot);
        }
    }
    return strdup(processName);
}