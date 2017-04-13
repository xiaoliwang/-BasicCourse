package dp

func countBits(num int) []int{
	nums := make([]int, num + 1)
	for i := 0; i <= num; i++ {
		nums[i] = nums[i >> 1] + i % 2
	}
	return nums
}