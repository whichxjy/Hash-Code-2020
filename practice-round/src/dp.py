import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', type=str, help='Input file path')
    parser.add_argument('-o', '--out', type=str, help='Ouput file path')
    args = parser.parse_args()

    with open(args.file, 'r') as fp:
        max_slices, type_num = [int(x) for x in next(fp).split()]
        slices = [int(s) for s in next(fp).split()]

        # dp[i][w]:
        # the maximum slices we get when choosing pizzas from pizzas[0:i - 1] the capacity w
        dp = [[0 for _ in range(max_slices + 1)] for _ in range(type_num + 1)]
        for w in range(1, max_slices + 1):
            for i in range(1, type_num + 1):
                # check if we can choose pizzas[i - 1]
                if slices[i - 1] <= w:
                    # choose pizzas[i - 1] or not
                    dp_choose = slices[i - 1] + dp[i - 1][w - slices[i - 1]]
                    dp_not_choose = dp[i - 1][w]
                    dp[i][w] = max(dp_choose, dp_not_choose)
                else:
                    # can not choose pizzas[i - 1]
                    dp[i][w] = dp[i - 1][w]

        selected = []
        curr_slices = dp[type_num][max_slices]
        capacity = max_slices
        for i in range(type_num, 0, -1):
            # check if pizzas[i - 1] was chosen
            if dp[i - 1][capacity] == curr_slices:
                # pizzas[i - 1] was not chosen
                continue
            else:
                # pizzas[i - 1] was chosen
                selected.append(i - 1)
                curr_slices -= slices[i - 1]
                capacity -= slices[i - 1]

        # output
        with open(args.out, 'w') as out_fp:
            selected_num = len(selected)
            idx_strs = [str(idx) for idx in sorted(selected)]
            out_fp.write(str(selected_num) + '\n')
            out_fp.write(" ".join(idx_strs))

if __name__ == '__main__':
    main()