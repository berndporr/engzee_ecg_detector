#include "engzee.h"

#include <stdio.h>
#include "Iir.h"


struct MyCallback : HRCallback {
	virtual void hasHR(float hr) {
		printf("HR = %f\n",hr);
	}
};

int main (int,char**)
{
	const float fs = 250;
    const float mains = 50;
	Iir::RBJ::IIRNotch iirnotch;
	iirnotch.setup(fs,mains);

	MyCallback callback;

	Engzee engzee(fs,callback);

	FILE *finput = fopen("example_data/ECG.tsv","rt");
	for(;;) 
	{
		float a1,a2,a3,a4,a5,a6;
		if (fscanf(finput,"%f %f %f %f %f %f\n",&a1,&a2,&a3,&a4,&a5,&a6)<1) break;
		//printf("%f\n",a1);
		const float a = iirnotch.filter(a1);
		engzee.detect(a);
	}
	fclose(finput);
}
