#include "xparameters.h"
#include <stdio.h>
#include "xil_printf.h"
#include "sleep.h"
#include "XGpioPs.h"

#define BTN0_EMIO_Channel 54
#define LED0_EMIO_Channel 55

#define GPIO_DEVICE_ID XPAR_PS7_GPIO_0_DEVICE_ID

static u32 btn;
static XGpioPs Gpio;

int main()
{
int status;
XGpioPs_Config *ConfigPtr;

// INITIALIZE THE PERIPHERALS
ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
status = XGpioPs_CfgInitialize(&Gpio,ConfigPtr, ConfigPtr->BaseAddr);
if(status != XST_SUCCESS) return XST_FAILURE;

XGpioPs_SetDirectionPin(&Gpio, BTN0_EMIO_Channel,0);// set EMIO[54] as input to read PushButton 0
XGpioPs_SetOutputEnablePin(&Gpio, BTN0_EMIO_Channel,0); // disable OutputEnable

XGpioPs_SetDirectionPin(&Gpio, LED0_EMIO_Channel,1); // set EMIO[55] as output to write on LED0
XGpioPs_SetOutputEnablePin(&Gpio, LED0_EMIO_Channel,1); // enable OutputEnable

while(1){
	btn=XGpioPs_ReadPin(&Gpio, BTN0_EMIO_Channel);//read the pushbutton
	XGpioPs_WritePin(&Gpio, LED0_EMIO_Channel, btn); //write the btn value on LED0
	usleep(50000);
	}
return 0;
}
