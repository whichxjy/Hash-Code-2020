import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', type=str, help='Input file path')
    parser.add_argument('-o', '--out', type=str, help='Ouput file path')
    args = parser.parse_args()

    with open(args.file, 'r') as fp:
        max_slices, type_num = [int(x) for x in next(fp).split()]
        slices = [int(s) for s in next(fp).split()]

        max_slices_count = 0
        selected = []

        # check pizzas[i:j]
        for j in range(type_num - 1, -1, -1):
            slices_count = 0
            curr_selected = []
            for i in range(j, -1, -1):
                # check if we can choose pizzas[i]
                if slices_count + slices[i] <= max_slices:
                    # choose pizzas[i]
                    slices_count += slices[i]
                    curr_selected.append(i)
                    if slices_count == max_slices:
                        break
            if slices_count > max_slices_count:
                max_slices_count = slices_count
                selected = curr_selected

        # output
        with open(args.out, 'w') as out_fp:
            selected_num = len(selected)
            idx_strs = [str(idx) for idx in selected]
            out_fp.write(str(selected_num) + '\n')
            out_fp.write(" ".join(idx_strs))


if __name__ == '__main__':
    main()