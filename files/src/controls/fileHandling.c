#include "../controller.h"

// removes spaces and new lines
void removeWhitespace(char* line) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == ' ' || line[i] == '\n') {
            for (int j = i; j < strlen(line); j++) {
                line[j] = line[j+1];
            }
        }
    }
}

// extracts all the values from config.ini
char *readConfig(char key[]) {

    // open the file
    FILE *file = fopen("config.ini", "r");

    // create one if none
    if (file == NULL) {
        fclose(file);
        file = fopen("config.ini", "w");
        fprintf(file, "vertical mouse sensitivity = 0\nhorizontal mouse sensitivity = 0\nvertical scroll sensitivity = 0\nhorizontal scroll sensitivity = 0\nA = primary mouse button\nB = secondary mouse button\nX = middle mouse button\nY = windows key\nleft joystick button = on-screen keyboard\nright joystick button = screenshot\nleft shoulder = none\nright shoulder = none\nleft joystick = move mouse\nright joystick = scroll\n");
        fclose(file);
        file = fopen("config.ini", "r");
    }

    // remove whitespace from key
    char formattedKey[1000];
    strcpy(formattedKey, key);
    removeWhitespace(formattedKey);

    // read the lines
    char line[1000];
    while (fgets(line, sizeof(line), file)) {

        removeWhitespace(line);

        //split the lines
        char *token = strtok(line, "=");

        // check if key is found
        if (strcmp(token, formattedKey) == 0) {
            char *value = strtok(NULL, "=");
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
        fprintf(file, "vertical mouse sensitivity = 0\nhorizontal mouse sensitivity = 0\nvertical scroll sensitivity = 0\nhorizontal scroll sensitivity = 0\nA = primary mouse button\nB = secondary mouse button\nX = middle mouse button\nY = windows key\nleft joystick button = on-screen keyboard\nright joystick button = screenshot\nleft shoulder = none\nright shoulder = none\nleft joystick = move mouse\nright joystick = scroll\n");
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