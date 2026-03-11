
#include <stdint.h>

#define SRAM_addr 0x20000008U


int main(void)
{
	uint32_t *p = (uint32_t*)SRAM_addr;
	uint32_t value = 0;

	while(1){
		value = *p;
		if(value)break;
	}

	while(1);

	return 0;
}
