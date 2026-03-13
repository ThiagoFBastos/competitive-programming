package main

import (
	"bufio"
	"fmt"
	"os"
)

type Edge struct {
	u int
	v int
}

type UnionFind struct {
	parent []int
	rank   []uint32
	size   []uint32
}

func swap(u, v *int) {
	temp := *u
	*u = *v
	*v = temp
}

func NewUnionFind(n int) *UnionFind {
	uf := UnionFind{
		parent: make([]int, n),
		rank:   make([]uint32, n),
		size:   make([]uint32, n),
	}

	for i := 0; i < n; i++ {
		uf.parent[i] = i
		uf.rank[i] = 0
		uf.size[i] = 1
	}

	return &uf
}

func (uf *UnionFind) find_set(u int) int {
	if u == uf.parent[u] {
		return u
	}

	uf.parent[u] = uf.find_set(uf.parent[u])

	return uf.parent[u]
}

func (uf *UnionFind) unite(u, v int) {
	u = uf.find_set(u)
	v = uf.find_set(v)

	if u == v {
		return
	} else if uf.rank[u] > uf.rank[v] {
		swap(&u, &v)
	}

	uf.parent[u] = v
	uf.size[v] += uf.size[u]

	if uf.rank[u] == uf.rank[v] {
		uf.rank[v] += 1
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	for {
		var n int

		fmt.Fscan(reader, &n)

		if n == 0 {
			break
		}

		graph := make([]Edge, n)

		dict := map[int]int{}

		dict[1] = 0

		for i := 0; i < n; i++ {
			var input string
			var u, v int

			fmt.Fscan(reader, &input)
			fmt.Sscanf(input, "(%d,%d)", &u, &v)

			_, has_u := dict[u]

			if !has_u {
				dict[u] = len(dict)
			}

			_, has_v := dict[v]

			if !has_v {
				dict[v] = len(dict)
			}

			graph[i] = Edge{
				u: dict[u],
				v: dict[v],
			}
		}

		m := len(dict)

		uf := NewUnionFind(m)

		for _, e := range graph {
			uf.unite(e.u, e.v)
		}

		guest := uf.size[uf.find_set(0)]

		fmt.Fprintln(writer, guest)
	}
}
