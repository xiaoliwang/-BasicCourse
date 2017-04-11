package dp

func BiDimensional(apple_matrix [][]int) int{
    height := len(apple_matrix)
    width := len(apple_matrix[0])
    sum_matrix := make([][]int, height)
    for i, apples := range apple_matrix {
        sum_matrix[i] = make([]int, len(apples))
        for j, apple := range apples {
            if i == 0 && j == 0 {
                sum_matrix[i][j] = apple
                continue
            } else if (i == 0) {
                sum_matrix[i][j] = sum_matrix[i][j - 1] + apple
                continue
            } else if (j == 0) {
                sum_matrix[i][j] = sum_matrix[i - 1][j] + apple
                continue
            }

            if sum_matrix[i][j - 1] > sum_matrix[i - 1][j] {
                sum_matrix[i][j] = sum_matrix[i][j - 1] + apple
            } else {
                sum_matrix[i][j] = sum_matrix[i - 1][j] + apple
            }
        }
    }
    return sum_matrix[height - 1][width - 1]
}