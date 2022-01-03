import subprocess
import numpy as np
import matplotlib.pyplot as plt
import csv
import tqdm

iters = range(100)
micros = []

for iter in tqdm.tqdm(iters):
    idx = iter*1000
    out = int(subprocess.check_output(["diyDB","-s",f"{idx}"]))
    micros.append(out)

with open("speed.csv", "w") as FILE:
    csv.writer(FILE).writerows(list(zip(iters, micros)))

plt.plot(iters, micros)
plt.show()