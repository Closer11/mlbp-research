import subprocess
from tqdm import tqdm
from itertools import takewhile

ms = [1, 2, 3]
ns = [5, 10, 15, 20]
ps = [40, 120]
qs = [20, 40, 60]
ninst = 10  # total = 720 instances

t = 900
result = ""
infeasible = 0

for m in tqdm(ms, desc="m"):
    for n in tqdm(ns, desc="n"):
        for p in tqdm(ps, desc="p"):
            for q in tqdm(qs, desc="q"):
                avg_v = 0
                avg_t = 0
                for i in tqdm(range(ninst), desc="inst"):
                    inst = "m{:02d}_n{:03d}_p{:03d}_q{:03d}__{:03d}".format(m, n, p, q, i)
                    input_str = "..\\x64\\Debug\\MLBP.exe ifile ..\\inst\\mlbpfc\\{}.inst prob MLBPFC ttime {}".format(inst, t)

                    try:
                        res = subprocess.run(input_str, shell=True, capture_output=True, text=True)  # , timeout=1
                        output = res.stdout
                        err = res.stderr

                        a1 = output[output.index('best objective value:') + len('best objective value:'):]
                        value = a1[:a1.index('\n')].strip()
                        avg_v += float(value)

                        a2 = output[output.index('CPU time:') + len('CPU time:'):]
                        time = a2[:a2.index('\n')].strip()
                        avg_t += float(time)

                        a3 = output[output.index('CPLEX status:') + len('CPLEX status:'):]
                        b = a3[:a3.index('\n')].strip()
                        status = ''.join(takewhile(lambda x: str.isalpha(x), b))

                        if status != "Optimal":
                            result += "error: {} -> Status: {} -> Value: {} -> Time: {}".format(inst, status, value, time) + '\n'
                            print(" encountered status: " + status + " on inst: " + inst)

                        if err:
                            print(" encountered error: " + err + " in inst: " + inst)
                            infeasible += 1

                    except ValueError:
                        print("error in inst: " + inst)

                    except subprocess.TimeoutExpired:
                        break

                result += "m{:02d}_n{:03d}_p{:03d}_q{:03d}".format(m, n, p, q) + \
                          " -> Value: " + str(avg_v / ninst) + \
                          " -> Time: " + str(round(avg_t / ninst, 4)) + '\n'

if infeasible > 0:
    result += str(infeasible) + " infeasible solutions"
print(result)

file = open("test_{}.txt".format("MLBPFC"), "w")
file.write(result)
file.close()
