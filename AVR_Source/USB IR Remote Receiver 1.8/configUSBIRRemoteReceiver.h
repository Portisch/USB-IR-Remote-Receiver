/* Name: usbconfig.h
 * Project: USB IR Remote Receiver for Atmel's(r) AVR(r) microcontrollers
 * Author: Portisch
 * Creation Date: 2010-04-16
 * Copyright: (c) 2010 by Portisch
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#ifndef __configUSBIRRemoteReceiver_h_included__
#define __configUSBIRRemoteReceiver_h_included__

#ifdef __cplusplus
extern "C"
{
#endif

#define USE_BOOTLOADER			1					/* 1 if boot loader option should be included (default), 0 to disable */

//define output pin for power on switch:
#define USE_PowerOnFunction		1					/* 1, use PowerOn function (default), 0 to disable */

#if USE_PowerOnFunction
#define SWITCH_PORT 		PORTC					/* PORTx - register for Switch output */
#define SWITCH_BIT  		PC5						/* bit where OK1 will be connected */
#define SWITCH_DDR  		DDRC					/* Switch data direction register */
#endif


#if USE_BOOTLOADER
	#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH    98
#else
	#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH    89
#endif
/* Define this to the length of the HID report descriptor, if you implement
 * an HID device. Otherwise don't define it or define it to 0.
 * If you use this define, you must add a PROGMEM character array named
 * "usbHidReportDescriptor" to your code which contains the report descriptor.
 * Don't forget to keep the array and this define in sync!
 */

#ifdef __cplusplus
}
#endif

#endif /* __configUSBIRRemoteReceiver_h_included__ */
