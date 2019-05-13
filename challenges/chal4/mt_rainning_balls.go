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
	maxHeight = 100
	n = 13
	numBalls = 10
	yOffset = 2
)

/*Global Variables*/
var voxelMap [][][]int
var balls = [][]int{}
var states = []string{}
var tOffset int

func main() {
	print("\033[H\033[2J")
	rand.Seed(time.Now().UnixNano())
	finalOffset()
	initBalls()
	voxelMap = generateVoxelMap()
	go updateEverything()
	startRain()
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
			fmt.Printf("\033[%d;%dH", i  + yOffset, (j * 3) + 50)
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
	for i := 0; i < numBalls; i++ {
		wg.Add(1)
		go rain(i, &wg)
	}
	wg.Wait()
	updateScreen()
}

func rain(index int, wg *sync.WaitGroup) {
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
			states[index] = seaBalls(index, x, y)
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
			states[index] = "Lake"
			break
		}
	}
	balls[index][1] = y
	balls[index][2] = x
	wg.Done()
}

func seaBalls(index int, x int, y int)string {
	if x == 0 { return "North" }
	if y == 0 { return "West" }
	if x == (n - 1) { return "South" } else {return "East"}
}

func initBalls() {
	for i := 0; i < numBalls; i++ {
		ball := []int{i, 0, 0, rand.Intn(maxHeight) + (maxHeight * 2), 0, 0, 0}
		balls = append(balls, ball)
		states = append(states, "Move")
	}
}

func displayBallInfo() {
	fmt.Printf("\033[2;0H")
	fmt.Printf("ID | Xp | Yp |  Zp  | Vx | Vy | Vz | State |")
	fmt.Printf("\033[3;0H")
	fmt.Printf("---+----+----+------+----+----+----+-------+")
	for i := 0; i < len(balls); i++ {
		/*Print Ball ID*/
		fmt.Printf("\033[%d;0H", i+4)
		fmt.Printf("%d", balls[i][0])
		/*Separator*/
		fmt.Printf("\033[%d;4H", i+4)
		fmt.Printf("|")
		/*Print Ball X Position*/
		fmt.Printf("\033[%d;6H", i+4)
		fmt.Printf("%d", balls[i][1])
		/*Separator*/
		fmt.Printf("\033[%d;9H", i+4)
		fmt.Printf("|")
		/*Print Ball Y Position*/
		fmt.Printf("\033[%d;11H", i+4)
		fmt.Printf("%d", balls[i][2])
		/*Separator*/
		fmt.Printf("\033[%d;14H", i+4)
		fmt.Printf("|")
		/*Print Ball Z Position*/
		fmt.Printf("\033[%d;16H", i+4)
		fmt.Printf("%d", balls[i][3])
		/*Separator*/
		fmt.Printf("\033[%d;21H", i+4)
		fmt.Printf("|")
		/*Print Ball X Velocity*/
		fmt.Printf("\033[%d;23H", i+4)
		fmt.Printf("%d", balls[i][4])
		/*Separator*/
		fmt.Printf("\033[%d;26H", i+4)
		fmt.Printf("|")
		/*Print Ball Y Velocity*/
		fmt.Printf("\033[%d;28H", i+4)
		fmt.Printf("%d", balls[i][5])
		/*Separator*/
		fmt.Printf("\033[%d;31H", i+4)
		fmt.Printf("|")
		/*Print Ball Y Velocity*/
		fmt.Printf("\033[%d;33H", i+4)
		fmt.Printf("%d", balls[i][6])
		/*Separator*/
		fmt.Printf("\033[%d;36H", i+4)
		fmt.Printf("|")

		fmt.Printf("\033[%d;38H", i+4)
		fmt.Printf(states[i])
		/*Separator*/
		fmt.Printf("\033[%d;44H", i+4)
		fmt.Printf("|")
	}
}



func updateScreen() {
	print("\033[H\033[2J")
  	displayVoxelMap()
  	displayBallInfo()
  	fmt.Printf("\033[%d;0H", tOffset * 2)
}

func updateEverything() {
  for {
    <-time.After(200 * time.Millisecond)
    go updateScreen()
  }
}

func finalOffset() {
	if numBalls > n { tOffset = numBalls } else { tOffset = n }
}



















