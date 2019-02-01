package main

import "fmt"

type Point struct{ x, y float64 }


func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

func printPoint(p Point) {
	fmt.Printf("x: %f\n", p.X())
	fmt.Printf("y: %f\n", p.Y())
}


func main() {
	p := Point{1.0, 1.0}
	printPoint(p)
}

