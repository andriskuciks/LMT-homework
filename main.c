//Main
#define START_ADDRESS 0x1800
#define END_ADDRESS   0x1FFF

#include <stdint.h>
#include <stdio.h>

uint8_t checkSRAM (uint8_t * sram)
{
	uint16_t address;
	uint8_t data = 1;
	
	//Set chip select
	//Write
	for(address = START_ADDRESS; address <= END_ADDRESS; address++)
	{
		
		//Set actual SRAM address
		//Set write enable
		//Set value in address
		sram[address - START_ADDRESS] = data++;
		//Reset write enable
		
		if(data == 0) 
		{
			//Avoids SRAM default values
			data = 1;
		}
	}
	
	data = 1;
	//No wait necessary, read and check values
	for(address = START_ADDRESS; address <= END_ADDRESS; address++)
	{
		//Set actual address
		//Set read enable
		//Read data
		if(sram[address - START_ADDRESS] != data++)
		{
			printf("Error: SRAM read/write values do not match");
			return 1;
		}
		else if(data == 0)
		{
			data = 1;
		}
		//Reset read enable
	}
	
	//Reset chip select
	return 0;
}

int main() 
{
	uint8_t testArray [END_ADDRESS - START_ADDRESS + 1];
	
	if (checkSRAM(testArray))
	{
		//Memory error
		return 1;
	}
	
	return 0;
}
	
	