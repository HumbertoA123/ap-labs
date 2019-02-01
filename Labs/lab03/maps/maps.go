package main

import (
	"golang.org/x/tour/wc"
	"fmt"
	"strings"
)

func WordCount(s string) map[string]int {
	
	wordlst := strings.Fields(s)
	wordMap := make(map[string]int)

	for i := 0; i < len(wordlst); i++ {
		fmt.Printf("%s\n", wordlst[i])
		
		if wordMap[wordlst[i]] == 0 {
			wordMap[wordlst[i]] = 1
		} else {
			wordMap[wordlst[i]] += 1
		}
	}
	
	return wordMap
}

func main() {
	wc.Test(WordCount)
}