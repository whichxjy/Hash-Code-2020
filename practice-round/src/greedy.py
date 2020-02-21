import argparse
import heapq

class Pizza:
    def __init__(self, idx, slices):
        self.idx = idx
        self.slices = slices

    def __lt__(self, other):
        return self.slices < other.slices

    def __eq__(self, other):
        return self.slices == self.slices

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', type=str, help='Input file path')
    parser.add_argument('-o', '--out', type=str, help='Ouput file path')
    args = parser.parse_args()

    with open(args.file, 'r') as fp:
        max_slices, type_num = [int(x) for x in next(fp).split()]
        pizzas = [Pizza(i, int(s)) for i, s in enumerate(next(fp).split())]

        heapq._heapify_max(pizzas)
        need = max_slices
        selected = []
        for _ in range(type_num):
            if need == 0:
                break
            else:
                curr_pizza = heapq._heappop_max(pizzas)
                if curr_pizza.slices <= need:
                    need -= curr_pizza.slices
                    selected.append(curr_pizza.idx)

        # output
        with open(args.out, 'w') as out_fp:
            selected_num = len(selected)
            idx_strs = [str(idx) for idx in sorted(selected)]
            out_fp.write(str(selected_num) + '\n')
            out_fp.write(" ".join(idx_strs))

if __name__ == '__main__':
    main()