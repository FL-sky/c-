package main

import "fmt"

/*
Go 语言切片是对数组的抽象。
Go 数组的长度不可改变，在特定场景中这样的集合就不太适用，

Go 中提供了一种灵活，功能强悍的内置类型切片("动态数组")，
与数组相比切片的长度是不固定的，可以追加元素，在追加时可能使切片的容量增大。
*/
func main() {
	////定义切片
	{
		var identifier []int
		// 切片不需要说明长度。
		fmt.Println(len(identifier))
		//或使用 make() 函数来创建切片:
		//也可以指定容量，其中 capacity 为可选参数。
		length := 5
		capacity := 9
		var slice1 []int = make([]int, length, capacity)
		fmt.Println(len(slice1), cap(slice1))
	}
	////初始化切片
	{
		s := []int{1, 2, 3}
		fmt.Println(len(s))
	}
	arr := [...]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	{
		s := arr[:]
		fmt.Println(len(s))
	}
	{
		startIndex := 1
		endIndex := 9
		s := arr[startIndex:endIndex]
		for i := 0; i < len(s); i++ {
			fmt.Print(s[i], " ")
		}
		fmt.Println()
		/*
			s := arr[startIndex:]
			默认 endIndex 时将表示一直到arr的最后一个元素。

			s := arr[:endIndex]
			默认 startIndex 时将表示从 arr 的第一个元素开始。
		*/
	}
	{
		var numbers = make([]int, 3, 5)

		printSlice(numbers)
	}
	//
	//	append() 和 copy() 函数
	{
		/*
			如果想增加切片的容量，我们必须创建一个新的更大的切片并把原分片的内容都拷贝过来。

			下面的代码描述了从拷贝切片的 copy 方法和向切片追加新元素的 append 方法。
		*/
		var numbers []int
		printSlice(numbers)

		/* 允许追加空切片 */
		numbers = append(numbers, 0)
		printSlice(numbers)

		/* 向切片添加一个元素 */
		numbers = append(numbers, 1)
		printSlice(numbers)

		/* 同时添加多个元素 */
		numbers = append(numbers, 2, 3, 4)
		printSlice(numbers)

		/* 创建切片 numbers1 是之前切片的两倍容量*/
		numbers1 := make([]int, len(numbers), (cap(numbers))*2)

		/* 拷贝 numbers 的内容到 numbers1 */
		copy(numbers1, numbers)
		printSlice(numbers1)
	}
}

func printSlice(x []int) {
	fmt.Printf("len=%d cap=%d slice=%v\n", len(x), cap(x), x)
}
