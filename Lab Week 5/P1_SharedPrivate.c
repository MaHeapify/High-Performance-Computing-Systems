// Write an OpenMP program to use variables as shared or private.

#include <stdio.h>
#include <omp.h>

int main() {
	int sharedVariable = 10;
	int privateVariable = 20;
	
	#pragma omp parallel shared(sharedVariable) private(privateVariable)
	{
		// Fetch the thread ID of the current thread
		privateVariable = omp_get_thread_num();
		
		printf("\nThread %d: Shared Variable = %d, Private Variable = %d\n", omp_get_thread_num(), sharedVariable, privateVariable);
	}
		
	printf("\nAfter parallel region:");
		
	printf("\nShared Variable = %d", sharedVariable);
	printf("\nPrivate Variable = %d\n", privateVariable);
	
	return 0;
}
