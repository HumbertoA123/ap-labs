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
	maxHeight = 10
	n = 20
	m = 20
)

/*Global Variables*/
var voxelMap [][][]int
var wg sync.WaitGroup

func main() {
	rand.Seed(time.Now().UnixNano())
	voxelMap = generateVoxelMap()
	displayVoxelMap()
	go rain()
	time.Sleep(time.Second * 5)
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
			fmt.Printf("\033[%d;%dH", i  + 2, (j * 3) + 2)
			if voxelMap[i][j][1] == 0 {
				fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j][0]) % 5), "*")
			} else {
				fmt.Printf(PrintColor, 3, "o")
			}
		}
	}
}

func displayNumbers() {
	for i := 0; i < len(voxelMap); i++ {
		for j := 0; j < len(voxelMap); j++ {
			fmt.Print(voxelMap[i][j][1], "  ")
		}
		fmt.Println("")
	}
}


func rain() {
	for i := 0; i < 350; i++ {
		x := rand.Intn(n)
		y := rand.Intn(m)
		for voxelMap[x][y][1] == 1 {
			x = rand.Intn(n)
			y = rand.Intn(m)
		}
		voxelMap[x][y][1] = 1

		for true {
			displayVoxelMap()
			//displayNumbers()
			//time.Sleep(time.Millisecond * 500)
			if y < (m - 1) && voxelMap[x][y + 1][0] < voxelMap[x][y][0] && voxelMap[x][y + 1][1] == 0 {
				voxelMap[x][y][1] = 0
				y += 1
			} else if x < (n - 1) && voxelMap[x + 1][y][0] < voxelMap[x][y][0] && voxelMap[x + 1][y][1] == 0 {
				voxelMap[x][y][1] = 0
				x += 1
			} else if y > 0 && voxelMap[x][y - 1][0] < voxelMap[x][y][0] && voxelMap[x][y - 1][1] == 0 {
				voxelMap[x][y][1] = 0
				y -= 1
			} else if x > 0 && voxelMap[x - 1][y][0] < voxelMap[x][y][0] && voxelMap[x - 1][y][1] == 0 {
				voxelMap[x][y][1] = 0
				x -= 1
			} else {
				break
			}
			voxelMap[x][y][1] = 1
		}
	}
}
















