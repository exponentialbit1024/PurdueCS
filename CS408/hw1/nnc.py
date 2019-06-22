import sys
import math
import time

def read_data(input_file = None):
    try:
        n = 0
        b = 0
        a = 0
        X = []
        max_t = 0
        t = []
        if input_file is None:
            input_file = "input.txt"
        with open(input_file) as fileobject:
            line_counter = 0
            for idx, line in enumerate(fileobject):
                if len(line) == 0:
                    continue
                line_counter += 1
                if idx == 0:
                    n, a, b = line.split(" ")
                    try:
                        n = int(n)
                    except:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if n > 50000:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if n < 1:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    try:
                        a = int(a)
                    except:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if a > 1000000000:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if a < 1:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    try:
                        b = int(b)
                    except:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if b > 1000000000:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if b < 1:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if a > b:
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)
                else:
                    finf = line.split()
                    ftime = int(finf[1])
                    if finf[0] != "NS" and finf[0] != 'S':
                        f = open("output.txt", "w")
                        f.write("INVALID INPUT")
                        f.close()
                        sys.exit(-1)

                    if ftime > max_t:
                        max_t = ftime

                    X.append((ftime, finf[0]))
                    t.append(ftime)

            if line_counter == 0:
                f = open("output.txt", "w")
                f.write("INVALID INPUT")
                f.close()
                sys.exit(-1)

            if line_counter - 1 != n:
                f = open("output.txt", "w")
                f.write("INVALID INPUT")
                f.close()
                sys.exit(-1)

        if len(t) != len(set(t)):
            f = open("output.txt", "w")
            f.write("INVALID INPUT")
            f.close()
            sys.exit(-1)

        X = sorted(X)
        return X, max_t, a, b, n
    except Exception as e:
        f = open("output.txt", "w")
        f.write("INVALID INPUT")
        f.close()
        sys.exit(-1)


def get_sword_hit(X, a, b):
    range_max = 0
    s_count = 0
    for idx, x in enumerate(X[:-1]):
        if idx == len(X) - 2:
            range_max = X[idx + 1][0]
        r_avg = int((x[0] + X[idx + 1][0]) / 2)
        if x[1] == 'S' and X[idx + 1][1] == 'S':
            if r_avg >= a and r_avg <= b:
                if X[idx + 1][0] > b:
                    s_count += b - x[0] + 1
                else:
                    s_count += X[idx + 1][0] - x[0] + 1
        elif x[1] == 'S':
            if r_avg >= a and r_avg <= b:
                if X[idx + 1][0] > b:
                    s_count += b - x[0] + 1
                else:
                    s_count += int(r_avg - x[0] + 1)
        elif X[idx + 1][1] == 'S':
            if r_avg >= a and r_avg <= b:
                if X[idx + 1][0] > b:
                    s_count += b - x[0] + 1
                else:
                    s_count += int(X[idx + 1][0] - r_avg + 1)
    if a == b:
        min_dist = math.inf
        closest = None
        for x in X:
            if abs(x[0] - a) <= min_dist:
                min_dist = abs(x[0] - a)
                if x[1] == 'S':
                    return 1, range_max
    return s_count, range_max

def runner(input_file = None):
    X, max_t, a, b, n = read_data(input_file = input_file)
    s_count, range_max = get_sword_hit(X, a, b)
    if b > range_max:
        if X[-1][1] == 'S':
            s_count += b - range_max
    # print(s_count)
    try:
        f = open("output.txt", "w")
        f.write(str(s_count))
        f.close()
    except:
        print("CANNOT WRITE OUTPUT")
        sys.exit(-1)

if __name__ == '__main__':
    input_file = None
    if len(sys.argv) == 2:
        input_file = sys.argv[1]
    runner(input_file)
