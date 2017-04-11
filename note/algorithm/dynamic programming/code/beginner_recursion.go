package dp

func RMinCoins(sum int, face_values []int) int{
    if sum == 0 {
        return 0
    }

    min := 1 << 62 - 1
    for _, v := range face_values {
        if sum == v {
            return 1
        } else if v < sum {
            t_min := RMinCoins(sum - v, face_values) + 1
            if t_min != 1 && t_min < min {
                min = t_min
            }
        }
    }
    return min
}