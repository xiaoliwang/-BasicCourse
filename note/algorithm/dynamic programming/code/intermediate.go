package dp

func MostApples(apples_matrix [][]int) int{
    height := len(apples_matrix)
    width := len(apples_matrix[0])

    most_apples := make([][]int, height)

    for i, apples := range apples_matrix {
        most_apples[i] = make([]int, len(apples))
        for j, apple := range apples {
            if i == 0 && j == 0 {
                most_apples[i][j] = apple
                continue
            } else if (i == 0) {
                most_apples[i][j] = most_apples[i][j - 1] + apple
                continue
            } else if (j == 0) {
                most_apples[i][j] = most_apples[i - 1][j] + apple
                continue
            }

            if most_apples[i][j - 1] > most_apples[i - 1][j] {
                most_apples[i][j] = most_apples[i][j - 1] + apple
            } else {
                most_apples[i][j] = most_apples[i - 1][j] + apple
            }
        }
    }
    return most_apples[height - 1][width - 1]
}