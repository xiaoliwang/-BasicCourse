package dp

func MinCoins(sum int, face_values []int)(min_coin int, min_coin_detail []int) {
  min_coins := make([]int, sum + 1)
  min_coin_details := make([][]int, sum + 1)
  
  // 给可以使用一个硬币的值附上默认值
  for _, v := range face_values {
    min_coins[v] = 1
    min_coin_details[v] = []int {v}
  }
  
  for i := 0; i <= sum; i++ {
    if min_coins[i] != 0 {
      continue
    }
    min_coin := 1 << 62 - 1
    face_value := 0
    for _, v := range face_values {
      if i > v && min_coins[i - v] != 0 && min_coins[i - v] < min_coin {
        face_value = v
        min_coin = min_coins[i - v]
      }
    }

    if face_value == 0 {
      min_coins[i] = 0
    } else {
      min_coins[i] = min_coin + 1
      min_coin_details[i] = append_one(min_coin_details[i - face_value], face_value)
    }
  }
  
  
  min_coin = min_coins[sum]
  min_coin_detail = min_coin_details[sum]
  return
}

func append_one(oldSlice []int, num int) []int {
    length := len(oldSlice)
    newSlice := make([]int, length + 1)
    copy(newSlice, oldSlice)
    newSlice[length] = num
    return newSlice
}