package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func binary_search(nums []int32, target int32) int {
	lo := 0
	hi := len(nums) - 1

	for lo < hi {
		mid := (lo + hi) / 2

		if nums[mid] >= target {
			hi = mid
		} else {
			lo = mid + 1
		}
	}

	if nums[hi] != target {
		return -1
	}

	return hi
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	tc := 1

	for {
		var n, q int

		fmt.Fscan(reader, &n, &q)

		if n == 0 && q == 0 {
			break
		}

		fmt.Fprintf(writer, "CASE# %d:\n", tc)
		tc += 1

		marbles := make([]int32, n)

		for i := 0; i < n; i++ {
			fmt.Fscan(reader, &marbles[i])
		}

		marbles = marbles[:]

		sort.Slice(marbles, func(i, j int) bool {
			return marbles[i] < marbles[j]
		})

		for i := 0; i < q; i++ {
			var query int32

			fmt.Fscan(reader, &query)

			pos := binary_search(marbles, query)

			if pos < 0 {
				fmt.Fprintf(writer, "%d not found\n", query)
			} else {
				fmt.Fprintf(writer, "%d found at %d\n", query, pos+1)
			}
		}
	}
}
