package main

import (
	"fmt"
	"math/rand"
	"time"
	"sync"
	"github.com/olekukonko/tablewriter"
	"os"
	"strconv"
	"strings"
	)

/*Constants*/
const (
	PrintColor = "\033[38;5;%dm%s\033[39;49m\n"
	startingVal = 88
	maxHeight = 500
	n = 20
	m = 20
	numBalls = 25
	yOffset = 4
)

/*Global Variables*/
var voxelMap [][][]int
//var wg sync.WaitGroup
var data = [][]string{}

func main() {
	rand.Seed(time.Now().UnixNano())
	voxelMap = generateVoxelMap()

	printBallInfo()

	displayVoxelMap()
	startRain()
	displayVoxelMap()
	fmt.Printf("\033[%d;%dH", m * 2, 0)
}

func generateVoxelMap() [][][]int {
	newVoxelMap := [][][]int{}
	for i := 0; i < n; i++ {
		row := [][]int{}
		for j := 0; j < m; j++ {
			if i == 0 || i == n - 1 || j == 0 || j == m - 1 {
				s := []int{0, 0}
				row = append(row, s)
			} else {
				s := []int{rand.Intn(maxHeight), 0}
				row = append(row, s)
			}
		}
		newVoxelMap = append(newVoxelMap, row)
	}
	return newVoxelMap
}

func displayVoxelMap() {
	for i := 0; i < len(voxelMap); i++ {
		for j := 0; j < len(voxelMap); j++ {
			fmt.Printf("\033[%d;%dH", i  + yOffset, (j * 3) + (m * 2))
			if voxelMap[i][j][1] == 0 {
				fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j][0]) % 5), "*")
			} else {
				fmt.Printf(PrintColor, 3, "o")
			}
		}
	}
}

func updateVoxelMap(wg *sync.WaitGroup){
	for i := 0; i < len(voxelMap); i++ {
		for j := 0; j < len(voxelMap); j++ {
			fmt.Printf("\033[%d;%dH", i  + yOffset, (j * 3) + (m * 2))
			if voxelMap[i][j][1] == 0 {
				fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j][0]) % 5), "*")
			} else {
				fmt.Printf(PrintColor, 3, "o")
			}
		}
	}
	wg.Done()
}

func startRain() {
	var wg sync.WaitGroup
	var wgrp sync.WaitGroup
	for i := 0; i < numBalls; i++ {
		wg.Add(1)
		go rain(i, &wg, &wgrp)
	}
	wg.Wait()
}

func rain(index int, wg *sync.WaitGroup, wgrp *sync.WaitGroup) {
	x := 1 + rand.Intn(n - 2)
	y := 1 + rand.Intn(m - 2)
	for voxelMap[x][y][1] == 1 {
		x = 1 + rand.Intn(n - 2)
		y = 1 + rand.Intn(m - 2)
	}
	voxelMap[x][y][1] = 1

	fmt.Printf("\033[%d;%dH", x + yOffset, (y * 3) + (m * 2))
	fmt.Printf(PrintColor, 3, "o")

	for true {
		
		/*Data for table*/

		//updateTable(index, x ,y)
		

		/*\Data for table*/
		time.Sleep(time.Millisecond * time.Duration(rand.Intn(1000)))
		if y < (m - 1) && voxelMap[x][y + 1][0] < voxelMap[x][y][0] && voxelMap[x][y + 1][1] == 0 {
			voxelMap[x][y][1] = 0
			voxelMap[x][y+1][1] = 1
			y += 1
		} else if x < (n - 1) && voxelMap[x + 1][y][0] < voxelMap[x][y][0] && voxelMap[x + 1][y][1] == 0 {
			voxelMap[x][y][1] = 0
			voxelMap[x+1][y][1] = 1
			x += 1
		} else if y > 0 && voxelMap[x][y - 1][0] < voxelMap[x][y][0] && voxelMap[x][y - 1][1] == 0 {
			voxelMap[x][y][1] = 0
			voxelMap[x][y-1][1] = 1
			y -= 1
		} else if x > 0 && voxelMap[x - 1][y][0] < voxelMap[x][y][0] && voxelMap[x - 1][y][1] == 0 {
			voxelMap[x][y][1] = 0
			voxelMap[x-1][y][1] = 1
			x -= 1
		} else {
			break
		}

/*
		wgrp.Add(1)
		print("\033[H\033[2J")
		go updateVoxelMap(&wgrp)
		wgrp.Wait()
*/
		wgrp.Add(2)
		print("\033[H\033[2J")
		updateTable(index, x, y, wgrp)
		updateVoxelMap(wgrp)
		wgrp.Wait()
		time.Sleep(time.Millisecond * time.Duration(rand.Intn(1000)))
	}
	wgrp.Add(2)
	print("\033[H\033[2J")
	updateTable(index, x, y, wgrp)
	updateVoxelMap(wgrp)
	wgrp.Wait()
	wg.Done()
}


func printBallInfo() {
	for i := 0; i < numBalls; i++ {
		ball := strconv.Itoa(i)
		data = append(data, []string{ball, "Hey", "400"})
	}

	table := tablewriter.NewWriter(os.Stdout)
	table.SetHeader([]string{"ID", "Position", "Speed"})

	for _, v := range data {
	    table.Append(v)
	}
	table.Render() // Send output

}

func updateTable(index int, x int, y int, wg *sync.WaitGroup) {

	var str strings.Builder
	str.WriteString(strconv.Itoa(x))
	str.WriteString(", ")
	str.WriteString(strconv.Itoa(y))

	data[index][1] = str.String()
	table := tablewriter.NewWriter(os.Stdout)
	table.SetHeader([]string{"ID", "Position", "Speed"})
	for _, v := range data {
	    table.Append(v)
	}
	fmt.Printf("\033[0;0H")
	table.Render()
	wg.Done()
}















