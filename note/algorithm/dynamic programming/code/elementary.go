package dp

func Lis(nums []int) (llen int, path []int) {
    llens := make([]int, len(nums))
    all_paths := make([]int, len(nums))
    for i, v := range nums {
        llen := 0
        all_paths[i] = i
        for j := 0; j < i; j++ {
            if llens[j] > llen && v > nums[j] {
                llen = llens[j]
                all_paths[i] = j
            }
        }
        llens[i] = llen + 1
    }
    llen, lindex := max(llens)
    path = get_path(all_paths, lindex)
    return
}

func max(llens []int) (llen int, lindex int) {
    llen = 0
    lindex = 0
    for i, v := range llens {
        if llen < v {
            llen = v
            lindex = i
        }
    }
    return
}

func get_path(all_paths []int, lindex int) []int {
    path := make([]int, 0)
    path = append(path, lindex)
    for lindex != all_paths[lindex] {
        lindex = all_paths[lindex]
        path = append(path, lindex)
    }
    return path
}