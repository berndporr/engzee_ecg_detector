#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import pathlib
from ecgdetectors import Detectors
import sys
import scipy.signal as signal

current_dir = pathlib.Path(__file__).resolve()

example_dir = current_dir.parent/'example_data'/'ECG.tsv'
unfiltered_ecg_dat = np.loadtxt(example_dir) 
unfiltered_ecg = unfiltered_ecg_dat[:, 0]
fs = 250

#####
## Mains removal
f1 = 48/fs
f2 = 52/fs
b, a = signal.butter(4, [f1*2, f2*2], btype='bandstop')
filtered_ecg = signal.lfilter(b, a, unfiltered_ecg)

detectors = Detectors(fs)

r_peaks = detectors.engzee_detector(filtered_ecg)
intervals = np.diff(r_peaks)
heart_rate = 60.0/(intervals/float(fs))

cpphr = np.loadtxt("hr.dat")

plt.figure()
plt.plot(heart_rate)
plt.plot(cpphr[2:])

plt.show()
