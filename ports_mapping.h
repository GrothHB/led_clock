#include <stdio.h>
enum ports 
{
	PX0 = 0,
	PX1, PX2, PX3, PX4,
	PX5, PX6, PX7, PX8,
	PX9, PX10, PX11, PX12,
	PX13, PX14, PX15 
};

int
main(void)
{
	printf("%d\n", PX6);

	return 0;
}
