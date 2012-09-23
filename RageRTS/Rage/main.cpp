#include "rage.h"
#include "test1.h"

#include <stdio.h>

using namespace rage;

int main()
{
	Rage rts;

	printf("Init...\n");
	rts.init();

	//double t = MPI_Wtime();

	printf("Run...\n");
	rts.start(1);

	printf("Load program...\n");	
	CodeId code = rts.registerCode<test1::Test1>("test1");
	rts.loadProgram(0, code, vector<int>());
	//rts.loadProgram(1, code, vector<int>(1, 500));

	printf("Shutdown...\n");
	rts.stop();

	//printf("Total time %.5f\n", MPI_Wtime() - t);

	printf("Exit...\n");
	rts.finalize();

return 0;
}
