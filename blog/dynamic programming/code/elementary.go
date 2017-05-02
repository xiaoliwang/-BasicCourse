package dp

func Lis(seq []int) (max_len int, path []int) {
    max_lens := make([]int, len(seq))
    paths := make([]int, len(seq))
    for i, v := range seq {
        llen := 0
        paths[i] = i
        for j := 0; j < i; j++ {
            if max_lens[j] > llen && v > seq[j] {
                llen = max_lens[j]
                paths[i] = j
            }
        }
        max_lens[i] = llen + 1
    }
    max_len, lindex := max(max_lens)
    path = get_path(paths, lindex)
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

var max_seq_tails = []int{}
func RLis(seq []int) int {
    length := len(seq)
    if length == 1 {
        max_seq_tails = append(max_seq_tails, seq[0])
        return 1
    }

    max_len := RLis(seq[:length - 1])
    s_n := seq[length - 1]
    s_k := (max_seq_tails)[max_len - 1]
    
    if s_n > s_k {
        max_seq_tails = append(max_seq_tails, s_n)
        return max_len + 1
        
    }

    for i, v := range max_seq_tails {
        if v >= s_n {
            (max_seq_tails)[i] = s_n
            break;
        }
    }

    return max_len
}