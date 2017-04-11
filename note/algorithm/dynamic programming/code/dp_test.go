package dp

import (
    "testing"
    "reflect"
    "sort"
    "fmt"
)

func TestMinCoins(t *testing.T) {
    prices := []int { 3, 7, 11, 13 }
    minimum_number, map_price := MinCoins(100, prices)
    sort.Ints(map_price)
    if minimum_number != 8 || !reflect.DeepEqual(map_price, []int{11,11, 13, 13, 13, 13, 13, 13}) {
        t.Errorf("wrong min coins")
    }
}

func TestRMinCoins(t *testing.T) {
    prices := []int { 3, 7, 11, 13 }
    min_coin := RMinCoins(100, prices)
    fmt.Println(min_coin)
}

func TestLis(t *testing.T) {
    nums := []int{5, 3, 4, 8, 6, 7}
    llen, path := Lis(nums)
    sort.Ints(path)
    if llen != 4 || !reflect.DeepEqual(path, []int{1, 2, 4, 5}) {
        t.Errorf("lis works wrong")
    }
}

func Test2D(t *testing.T) {
    apple_matrix := [][]int{
        {1, 2, 3, 4, 5},
        {1, 2, 2, 4, 4},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
    }

    max_num := BiDimensional(apple_matrix)
    if max_num != 29 {
         t.Errorf("2d works wrong")
    }
}
