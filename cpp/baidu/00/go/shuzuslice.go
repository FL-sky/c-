package main

import "fmt"

func main() {
	a := [2]int{5, 6}
	b := [2]int{5, 6}
	if a == b {
		fmt.Println("equal")
	} else {
		fmt.Println("not equal")
	}
	/*
		invalid operation: cannot compare c[:] == d[:]
		(slice can only be compared to nil)
	*/
	//
	// c := []int{5, 6}
	// d := []int{5, 6}
	// if a[:] == b[:] {
	// 	fmt.Println("equal")
	// } else {
	// 	fmt.Println("not equal")
	// }

}
