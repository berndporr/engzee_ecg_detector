#include "engzee.h"

#include <stdio.h>
#include "Iir.h"

struct MyCallback : HRCallback {
	FILE* f;
	MyCallback(FILE* hrFile) {
		f = hrFile;
	}
	virtual void hasHR(float hr) {
		printf("HR = %f\n",hr);
		fprintf(f,"%f\n",hr);
	}
};

int main (int,char**)
{
	const float fs = 250;
    const float mains = 50;
	Iir::RBJ::IIRNotch iirnotch;
	iirnotch.setup(fs,mains);

	FILE* f = fopen("hr.dat","wt");
	if (!f) {
		fprintf(stderr,"Could not open hr.dat\n");
		exit(1);
	}

	MyCallback callback(f);

	Engzee engzee(fs,callback);

	FILE *finput = fopen("example_data/ECG.tsv","rt");
	for(;;) 
	{
		float a1,a2,a3,a4,a5,a6;
		if (fscanf(finput,"%f %f %f %f %f %f\n",&a1,&a2,&a3,&a4,&a5,&a6)<1) break;
		const float a = iirnotch.filter(a1);
		engzee.detect(a);
	}
	fclose(finput);

	fclose(f);
}
