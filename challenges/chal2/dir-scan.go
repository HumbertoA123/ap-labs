package main

import (
	"fmt"
	"os"
	"log"
	"strconv"
	"github.com/olekukonko/tablewriter"
)

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	return nil
}

func main() {

	dirCount := 0
	slCount  := 0
	oCount   := 0


	dirName := os.Args[1]


	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	f, err := os.Open(dirName)
    if err != nil {
        log.Fatal(err)
    }

    files, err := f.Readdir(-1)
    f.Close()
    if err != nil {
        log.Fatal(err)
    }

    for _, file := range files {

        if file.IsDir() {
        	dirCount++
        } else if file.Mode() & os.ModeSymlink != 0 {
  			slCount++
  		} else {
  			oCount++
  		}
    }


    data := [][]string{
    []string{"Directories", strconv.Itoa(dirCount)},
    []string{"SymbolicLinks", strconv.Itoa(slCount)},
    []string{"Other files", strconv.Itoa(oCount)},
	}

	table := tablewriter.NewWriter(os.Stdout)
	table.SetHeader([]string{"Path", dirName})

	for _, v := range data {
	    table.Append(v)
	}
	table.Render() // Send output


	scanDir(os.Args[1])
}
