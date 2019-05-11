package main

import (
	"fmt"
	"math/rand"
	"time"
	)

/*Constants*/
const (
	PrintColor = "\033[38;5;%dm%s\033[39;49m\n"
	startingVal = 88
	maxHeight = 10
	n = 40
	m = 40
)

/*Global Variables*/
var voxelMap [][]int

func main() {
	rand.Seed(time.Now().UnixNano())
	voxelMap = generateVoxelMap()
	displayVoxelMap()
	rain()
}

func generateVoxelMap() [][]int {
	newVoxelMap := [][]int{}
	for i := 0; i < n; i++ {
		row := []int{}
		for j := 0; j < m; j++ {
			row = append(row, rand.Intn(maxHeight))
		}
		newVoxelMap = append(newVoxelMap, row)
	}
	return newVoxelMap
}

func displayVoxelMap() {
	for i := 0; i < len(voxelMap); i++ {
		for j := 0; j < len(voxelMap); j++ {
			fmt.Printf("\033[%d;%dH", i + 2, (j * 3) + 2)
			fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j]) % 5), "*")
		}
	}
}

func rain() {
	x := rand.Intn(n)
	y := rand.Intn(m)

	for true {

		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				if i == x && j == y {
					fmt.Printf("\033[%d;%dH", x + 2, (y * 3) + 2)
					fmt.Printf(PrintColor, 4, "o")
				}else {
					fmt.Printf("\033[%d;%dH", i + 2, (j * 3) + 2)
					fmt.Printf(PrintColor, startingVal + (5 - (voxelMap[i][j]) % 5), "*")
				}
			}
		}

		if (y + 1) <= (m - 1) && voxelMap[x][y + 1] < voxelMap[x][y] {
			y += 1
		} else if (y + 1) <= (m - 1) && (x + 1) <= (n - 1) && voxelMap[x + 1][y + 1] < voxelMap[x][y] {
			x += 1
			y += 1
		} else if (x + 1) <= (n - 1) && voxelMap[x + 1][y] < voxelMap[x][y] {
			x += 1
		} else if (y - 1) >= 0 && (x + 1) <= (n - 1) && voxelMap[x + 1][y - 1] < voxelMap[x][y] {
			x += 1
			y -= 1
		} else if (y - 1) >= 0 && voxelMap[x][y -1] < voxelMap[x][y] {
			y -= 1
		} else if (y - 1) >= 0 && (x - 1) >= 0 && voxelMap[x - 1][y - 1] < voxelMap[x][y] {
			x -= 1
			y -= 1
		} else if (x - 1) >= 0 && voxelMap[x - 1][y] < voxelMap[x][y] {
			x -= 1
		} else if (y + 1) <= (m - 1) && (x + 1) >= 0 && voxelMap[x - 1][y + 1] < voxelMap[x][y] {
			x -= 1
			y += 1
		} else {
			break
		}
		time.Sleep(3000 * time.Millisecond)
	}
}
















