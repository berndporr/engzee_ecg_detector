# engzee_ecg_detector
C++ implementation of the Python Engzee detector (https://github.com/berndporr/py-ecg-detectors).

Engelse and Zeelenberg
----------------------

Implementation of W. Engelse and C. Zeelenberg, “A single scan algorithm for QRS detection and feature extraction”, IEEE Comp. in Cardiology, vol. 6, pp. 37-42, 1979 with modifications A. Lourenco, H. Silva, P. Leite, R. Lourenco and A. Fred, “Real Time Electrocardiogram Segmentation for Finger Based ECG Biometrics”, BIOSIGNALS 2012, pp. 49-54, 2012.

# Usage

The detector is a header only:
```
include "engzee.h"
```

Create a heartrate callback:

```
struct MyCallback : HRCallback {
        virtual void hasHR(float hr) {
		// do something with the heartrate
        }
};

```

Create an instance of the callback and the detector:
```
MyCallback callback(f);
Engzee engzee(fs,callback);
```

Call the detector sample by sample:

```
engzee.detect(a);
```

This will then call the heartrate callback whenever a
new heartrate is available.

# Credit

Bernd Porr
