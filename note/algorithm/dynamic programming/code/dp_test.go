package dp

import (
    "testing"
    "reflect"
    "sort"
    _"fmt"
)

func TestMinCoins(t *testing.T) {
    prices := []int { 3, 7, 11, 13 }
    for i := 1; i < 500; i++ {
        min_coin1 := RMinCoinsImp(i, prices)
        min_coin2, _ := MinCoins(i, prices)
        if min_coin1 != min_coin2 {
            t.Errorf("wrong min coins")
        }
    }
    
    min_coin2, map_price := MinCoins(50, prices)
    sort.Ints(map_price)
    if min_coin2 != 4 || !reflect.DeepEqual(map_price, []int{11, 13, 13, 13}) {
        t.Errorf("wrong min coins")
    }
}

func TestLis(t *testing.T) {
    nums := []int{3, 4, 5, 2, 3, 4, 5, 6, 1, 2, 3, 2, 1}
    llen1, path := Lis(nums)
    llen2 := RLis(nums)
    if llen1 != llen2 || !reflect.DeepEqual(path, []int{7, 6, 5, 4, 3}) {
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
