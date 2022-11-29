#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt

cpphr = np.loadtxt("hr.dat")

plt.figure()
plt.plot(cpphr)
plt.ylabel("heartrate / beats per minute")
plt.xlabel("HR #")

plt.show()
