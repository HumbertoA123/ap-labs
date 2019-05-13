package main

import (
	"fmt"
	"math/rand"
	"time"
	"sync"
	)

/*Constants*/
const (
	PrintColor = "\033[38;5;%dm%s\033[39;49m\n"
	startingVal = 88
	maxHeight = 50
	n = 20
	numBalls = 50
	yOffset = 4
)

/*Global Variables*/
var voxelMap [][][]int
//var wg sync.WaitGroup
var balls = [][]int{}
var states = []string{}

func main() {
	print("\033[H\033[2J")
	rand.Seed(time.Now().UnixNano())
	initBalls()
	voxelMap = generateVoxelMap()
	go updateEverything()
	startRain()
	displayVoxelMap()
	fmt.Printf("\033[%d;%dH", numBalls * 10, 0)
}

func generateVoxelMap() [][][]int {
	newVoxelMap := [][][]int{}
	for i := 0; i < n; i++ {
		row := [][]int{}
		for j := 0; j < n; j++ {
			if i == 0 || i == n - 1 || j == 0 || j == n - 1 {
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
			fmt.Printf("\033[%d;%dH", i  + yOffset, (j * 3) + (n * 2))
			if voxelMap[i][j][1] == 0 {
				fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j][0]) % 5), "*")
			} else {
				fmt.Printf(PrintColor, 3, "o")
			}
		}
	}
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
	y := 1 + rand.Intn(n - 2)
	for voxelMap[x][y][1] == 1 {
		x = 1 + rand.Intn(n - 2)
		y = 1 + rand.Intn(n - 2)
	}
	voxelMap[x][y][1] = 1
	for true {
		balls[index][1] = x
		balls[index][2] = y
		time.Sleep(time.Millisecond * time.Duration(rand.Intn(1000)))
		if x == 0 || y == 0 || x == (n - 1) || y == (n - 1) {
			states[index] = "Ocean"
			break
		}else if y < (n - 1) && voxelMap[x][y + 1][0] < voxelMap[x][y][0] && voxelMap[x][y + 1][1] == 0 {
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
	}
	balls[index][1] = x
	balls[index][2] = y
	wg.Done()
}

func initBalls() {
	for i := 0; i < numBalls; i++ {
		ball := []int{i, 0, 0, rand.Intn(maxHeight) + (maxHeight * 2)}
		balls = append(balls, ball)
		states = append(states, "Move")
	}
}

func displayBallInfo() {
	for i := 0; i < len(balls); i++ {
		fmt.Printf("\033[%d;0H", i)
		fmt.Printf("%v", balls[i])
		fmt.Printf("\033[%d;20H", i)
		fmt.Printf(states[i])
	}
}

func updateScreen() {
  	displayVoxelMap()
  	displayBallInfo()
}

func updateEverything() {
  for {
    <-time.After(100 * time.Millisecond)
    go updateScreen()
  }
}































