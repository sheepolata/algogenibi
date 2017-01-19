#include <stdio.h>
#include <time.h>
#include "../headers/Parameters.h"
#include "../headers/ProtoEye.h"

int main(int argc, char const *argv[])
{
	/* initialize random seed: */
	srand(time(NULL));

	Parameters* p = new Parameters(50, 0, 100);
	Parameters* p2 = new Parameters(50, 2, 100);
	Parameters* p3 = new Parameters(50, 0, 100);

	/*printf("%f == %f\n",p->getValue(), p3->getValue());
	printf("%f == %f\n",p->getMin(), p3->getMin());
	printf("%f == %f\n",p->getMax(), p3->getMax());
	printf("%d\n", p == p3);*/

	delete p;
	return 0;
}