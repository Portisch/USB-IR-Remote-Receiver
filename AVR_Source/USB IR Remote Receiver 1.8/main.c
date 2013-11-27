/* Name: main.c
 * Project: USB IR Remote Receiver with V-USB and Irmp
 * Author: Portisch
 * Creation Date: 15.03.2010
 * Copyright: (c) 2010 by Portisch
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.
*/

#include <avr/io.h>
#include <avr/wdt.h>		/* watchdog */
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/eeprom.h>
#include <string.h> 		/* for memcpy */

#include "configUSBIRRemoteReceiver.h"	/* main config file */

#include "Irmp\irmp.h"			/* ir remote handling */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"			/* v-usb driver */

#ifndef F_CPU
	#error F_CPU unkown
#endif

//enter here the Irmp build date:
const char IrmpVersion[] = "12.03.2013";



/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x0b, 0x01, 0x00, 0x00, 0xff,  // USAGE (Vendor Defined Page 1:Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x09, 0x00,                    //   USAGE (Undefined)
    0x82, 0x00, 0x01,              //   INPUT (Data,Ary,Abs,Buf)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x03,                    //   REPORT_ID (3)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x04,                    //   REPORT_ID (4)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x05,                    //   REPORT_ID (5)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x06,                    //   REPORT_ID (6)
    0x95, 0x02,                    //   REPORT_COUNT (2)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x07,                    //   REPORT_ID (7)
    0x95, 0x04,                    //   REPORT_COUNT (4)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x08,                    //   REPORT_ID (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
#if USE_BOOTLOADER
    0x85, 0x09,                    //   REPORT_ID (9)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
#endif
    0xc0                           // END_COLLECTION
};

/* The following variables store the status of the current data transfer */
static uchar			currentAddress   	= 0;
static unsigned short	bytesRemaining   	= 0;
static uchar			PowerOnEnabled   	= TRUE;

/* const for V-USB feature report ID handling */
const uchar	  NewIRCodeAvailable = 1;
const uchar	  ReadPowerOnEnabled = 2;
const uchar	  ReadTrainendIRCode = 3;
const uchar	  SetPowerOnEnabled  = 4;
const uchar	  SetTrainedIRCode 	 = 5;
//const uchar	  SetIRPollingTime   = 6;
const uchar	  ReadIrmpVersion    = 7;
const uchar	  SetMinRepeats 	 = 8;
#if USE_BOOTLOADER
const uchar	  ResetForBootloader = 9;
#endif

static uchar  DoWriteReport		 = 0;
static uchar  DoReadReport		 = 0;

/* Memory addresses in eeprom */
static uchar 	AdressPowerOn		= 0;
static uchar 	AdressTrainedCode 	= 1;
static uchar	AdressMinRepeats	= 7;
#if USE_BOOTLOADER
static uchar	AdressBootloader	= 8;
static uchar	EnableBootloader	= 1;
static uchar	DisableBootloader	= 0;
#endif

/* reapeat counters for received IR codes */
static uchar	RepeatCounter		= 0;
static uchar	MinRepeats			= 5;	// default minimum repeat counter

static IRMP_DATA irmp_data;
static IRMP_DATA trained_irmp_data;

/* reply buffer should be big enough to cover also the irmp version ! */
static uchar    replyBuf[16];

/* ------------------------------------------------------------------------- */
/* main functions for irmp
 */
static void
timer_init (void)
{
																			/* IR polling timer */		
	TCCR1B  = (1 << WGM12) | (1 << CS10);									// switch CTC Mode on, set prescaler to 1

	// may adjust IR polling rate here to optimize IR receiving:
	OCR1A   =  (F_CPU / F_INTERRUPTS) - 1;                                  // compare value: 1/10000 of CPU frequency

	// enable Timer1 for IR polling
	#if defined (__AVR_ATmega8__) || defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) || defined (__AVR_ATmega64__) || defined (__AVR_ATmega162__)
		TIMSK = 1 << OCIE1A;   												// Timer1A ISR activate 		
	#else										 				
		TIMSK1  = 1 << OCIE1A;                 								// Timer1A ISR activate
	#endif	// __AVR...
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * init all io pins of the AVR, first all to input with pullups. then config USB and output pin
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
init_io(void) 
{
	/* first set all pins to input */
    PORTB = 0xFF;   													/* activate all pull-ups */
    DDRB = 0;       													/* all pins input */
    PORTC = 0xFF;   													/* activate all pull-ups */
    DDRC = 0;       													/* all pins input */
    PORTD = 0xFF;   													/* activate all pull-ups */
    DDRD = 0;    														/* all pins input */

	/* USB pins */
	USBOUT ^= _BV (USB_CFG_DMINUS_BIT) | _BV (USB_CFG_DPLUS_BIT);   	/* deactivate pull-ups on USB lines */

	#if USE_PowerOnFunction
		/* config PowerOn pin */
		SWITCH_PORT ^=	_BV (SWITCH_BIT);								/* deactivate pull-ups on PowerOn pin */ 	
		SWITCH_DDR ^= _BV (SWITCH_BIT);									/* set switch pin as digital output */
	#endif
}
 

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * timer 1 compare handler, should be called every 1/10000 sec
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void TIMER1_COMPA_vect(void) __attribute__((interrupt));
void TIMER1_COMPA_vect(void)
{
	/* ------------------------------------------------------------------------- */
	/* main functions for irmp
	 */
  	irmp_ISR();                                                     // call irmp ISR
  	// call other timer interrupt routines...
}

/* ------------------------------------------------------------------------- */

/* usbFunctionRead() is called when the host requests a chunk of data from
 * the device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar   usbFunctionRead(uchar *data, uchar len)
{
    if(len > bytesRemaining)
        len = bytesRemaining;
		
	if ( DoReadReport == ReadIrmpVersion)
	{
		memcpy(data, &replyBuf[currentAddress], len);	
	}

    currentAddress += len;
    bytesRemaining -= len;
    return len;
}

/* ------------------------------------------------------------------------- */

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar   usbFunctionWrite(uchar *data, uchar len)
{
    if(bytesRemaining == 0)
        return 1;               /* end of transfer */
    if(len > bytesRemaining)
        len = bytesRemaining;

	if ( DoWriteReport == SetPowerOnEnabled )
	{
		eeprom_write_block(&data[1], (uchar *)0 + currentAddress, len);						// store new value of PowerOn in eeprom
		memcpy(&PowerOnEnabled, &data[1], sizeof(PowerOnEnabled));							// update PowerOn flag:			
	}
	else if ( DoWriteReport == SetTrainedIRCode )
	{
		eeprom_write_block(&data[1], (uchar *)0 + currentAddress, len);						// store new trained IR code in eeprom
		memcpy(&trained_irmp_data, &data[1], sizeof(trained_irmp_data));					// update trained IR code:
	} 
	/*
	else if ( DoWriteReport == SetIRPollingTime )
	{
		OCR1A = (F_CPU / ((data[2] << 8 ) | data[1])) - 1;									// update new IR polling time, data[1-2] = new frequency
	} 
	*/
	else if ( DoWriteReport == SetMinRepeats )
	{
		eeprom_write_block(&data[1], (uchar *)0 + currentAddress, len);						// store new MinRepeats in eeprom
		memcpy(&MinRepeats, &data[1], sizeof(MinRepeats));									// update new MinRepeats received from host
	} 
    currentAddress += len;
    bytesRemaining -= len;
    return bytesRemaining == 0; 															/* return 1 if this was the last chunk */
}


/* ------------------------------------------------------------------------- */

uchar   usbFunctionSetup(uchar data[8]) 
{ 

usbRequest_t    *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    // HID class request 
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  // wValue: ReportType (highbyte), ReportID (lowbyte)

		usbMsgPtr = replyBuf;

            if(rq->wValue.bytes[0] == ReadPowerOnEnabled){ 									/* ReportID 2 ReadPowerOnEnabled */ 
				memcpy(&replyBuf[0], &rq->wValue.bytes[0], sizeof(uchar));					// copy report id
				eeprom_read_block(&replyBuf[1], (uchar *)0 +AdressPowerOn, sizeof(PowerOnEnabled));		// copy PowerOn flag to reply buffer 
                return sizeof(PowerOnEnabled) + sizeof(uchar);  							// 1 bytes PowerOnEnabled struct + 1 byte ID

            }else if(rq->wValue.bytes[0] == ReadTrainendIRCode){ 							/* ReportID 3 ReadTrainendIRCode */ 
				memcpy(&replyBuf[0], &rq->wValue.bytes[0], sizeof(uchar));					// copy report id
				eeprom_read_block(&replyBuf[1], (uchar *)0 +AdressTrainedCode, sizeof(trained_irmp_data));		// copy trained IR code to reply buffer  
                return (sizeof(trained_irmp_data) + sizeof(uchar));							// 6 bytes irmp struct + 1 byte ID

            }else if(rq->wValue.bytes[0] == ReadIrmpVersion){ 								/* ReportID 7 ReadIrmpVersion */ 
				memcpy(&replyBuf[0], &rq->wValue.bytes[0], sizeof(uchar));					// copy report id
				memcpy(&replyBuf[1], &IrmpVersion, sizeof(IrmpVersion));					// copy Irmp version			
	            bytesRemaining = sizeof(IrmpVersion);
	            currentAddress = 0;
				DoReadReport = ReadIrmpVersion;
	            return USB_NO_MSG;  														// use usbFunctionRead() to obtain data
            }	 
        }else if(rq->bRequest == USBRQ_HID_SET_REPORT){ 
            if(rq->wValue.bytes[0] == SetPowerOnEnabled){   								/* ReportID 4 SetPowerOnEnabled */	
	            bytesRemaining = sizeof(PowerOnEnabled);									//store PowerOnEnabled in EEProm:
	            currentAddress = (int)AdressPowerOn;
				DoWriteReport = SetPowerOnEnabled;											// set report id flag for usbFunctionWrite
	            return USB_NO_MSG;  														// use usbFunctionWrite() to receive data from host	
            }else if(rq->wValue.bytes[0] == SetTrainedIRCode){  							/* ReportID 5 SetTrainedIRCode */
			    bytesRemaining = sizeof(trained_irmp_data);									// store IR Code in EEProm
	            currentAddress = (int)AdressTrainedCode;
				DoWriteReport = SetTrainedIRCode;											// set report id flag for usbFunctionWrite
	            return USB_NO_MSG;  														// use usbFunctionWrite() to receive data from host	    
			/*
            }else if(rq->wValue.bytes[0] == SetIRPollingTime){  							// ReportID 6 SetIRPollingTime 				
	            bytesRemaining = sizeof(OCR1A);												// update new IR polling time
				DoWriteReport = SetIRPollingTime;											// set report id flag for usbFunctionWrite
	            return USB_NO_MSG;  														// use usbFunctionWrite() to receive data from host	
			*/
            }else if(rq->wValue.bytes[0] == SetMinRepeats){  								/* ReportID 8 SetMinRepeats */				
				currentAddress = (int)AdressMinRepeats;
	            bytesRemaining = sizeof(MinRepeats);										// update new max repeat counter
				DoWriteReport = SetMinRepeats;												// set report id flag for usbFunctionWrite
	            return USB_NO_MSG;  														// use usbFunctionWrite() to receive data from host	
		#if USE_BOOTLOADER
            }else if(rq->wValue.bytes[0] == ResetForBootloader){  							/* ReportID 9 host is requesting the bootloader */				
				eeprom_write_block(&EnableBootloader, (uchar *)0 + AdressBootloader, sizeof(uchar));					
				for(;;);   																	// Reset from watchdog	            
		#endif
            }			    			         
		}
    }else{ 
        // ignore vendor type requests, we don't use any
    } 
    return 0; 
} 
/* ------------------------------------------------------------------------- */
static void SendINTData(void)
{
	
	if (!(irmp_data.flags & IRMP_FLAG_REPETITION))											// first check if the IR command is repeated
	{
		RepeatCounter = 0;																	// new command received, reset RepeatCounter
	}																	
	else
	{	
		RepeatCounter++;																	// still the same command, inc RepeatCounter
	}																

	if ((RepeatCounter == 0) | ( RepeatCounter >= MinRepeats))								// only send interrupt if first command, or Repeatcounter >= MinRepeats
	{
		if (RepeatCounter >= MinRepeats)	
			RepeatCounter = MinRepeats;														// fix overflow for long key push

		memcpy(&replyBuf[0], &NewIRCodeAvailable, sizeof(uchar));							// copy report id to reply buffer
		memcpy(&replyBuf[1], &irmp_data, sizeof(irmp_data)); 								// copy received IR code to reply buffer
	    
	    usbSetInterrupt(&replyBuf[0], sizeof(irmp_data) + sizeof(uchar));					// send ReportID + IR data
	}
}
/* ------------------------------------------------------------------------- */
/* main function
*/
int main(void)
{
uchar   i;
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */
	wdt_disable();																						// first disable watchdog
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */

	#if USE_BOOTLOADER
	eeprom_write_block(&DisableBootloader, (uchar *)0 + AdressBootloader, sizeof(uchar));
	#endif


    wdt_enable(WDTO_1S);																				// enable again watchdog

	init_io();

	memset(&irmp_data, 0x00, sizeof(irmp_data));  														// clear irmp_data

	memset(&trained_irmp_data, 0x00, sizeof(trained_irmp_data));										// clear trained_irmp_data

	irmp_init();                                                            							// initialize irmp code
	timer_init();                                                           							// initialize timer

    usbDeviceDisconnect();  																			/* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i){             																			/* fake USB disconnect for > 500 ms */
        wdt_reset();
        _delay_ms(5);
    }
    usbDeviceConnect();

    usbInit();																							// initialize v-usb
    sei();																								// enable global int

	#if USE_PowerOnFunction
		/* read stored variables, use uchar i for temp buffer */
		eeprom_read_block(&i, (uchar *)0 +AdressPowerOn, sizeof(PowerOnEnabled));						// read if PowerOn is already set

		if ( i == 0xFF )
		{																								// power on isn't stored yet, save the init value
			eeprom_write_block(&PowerOnEnabled, (uchar *)0 +AdressPowerOn, sizeof(PowerOnEnabled));		// set PowerOn Enabled to default
		}else{ memcpy(&PowerOnEnabled, &i, sizeof(PowerOnEnabled)); }									// update actual value
	#endif	
	
	eeprom_read_block(&i, (uchar *)0 +AdressMinRepeats, sizeof(MinRepeats));							// read if MinRepeats is already set

	if ( i == 0xFF )
	{																									// MinRepeats isn't stored yet, save the init value
		eeprom_write_block(&MinRepeats, (uchar *)0 +AdressMinRepeats, sizeof(MinRepeats));				// set MinRepeats to default: 5
	}else{ memcpy(&MinRepeats, &i, sizeof(MinRepeats)); }												// update actual value


	eeprom_read_block(&trained_irmp_data, (uchar *)0 +AdressTrainedCode, sizeof(irmp_data));			// read last saved trained IR code in eeprom

    for(;;){                			/* main event loop */
        wdt_reset();

	    if (irmp_get_data (&irmp_data))																	// check if new IR code is aviable
	    {
	        /* ir signal decoded, do something here...*/
	        /* irmp_data.protocol is the protocol, see irmp.h*/
	        /* irmp_data.address is the address/manufacturer code of ir sender*/
	        /* irmp_data.command is the command code*/
			/* */
			#if USE_PowerOnFunction
				if ((trained_irmp_data.protocol != 0xFF) & (trained_irmp_data.protocol != 0x00))		// check if code is already trained:
				{
					// IR code trained,
					// if PowerOn function is enabled check it
					if (PowerOnEnabled)
					{
						//compare trained code with last received code
						if (memcmp(&irmp_data, &trained_irmp_data, sizeof(irmp_data) - 1) == 0)				 
						{
							SWITCH_PORT ^= _BV(SWITCH_BIT);												// switch on output pin form ~250ms
						    while(--i)
							{
						        wdt_reset();															// watchdog reset
								usbPoll();																// do a USB poll
						        _delay_us(500);															// delay
						    }
							SWITCH_PORT ^= _BV(SWITCH_BIT);												// switch off output pin
						}else{ SendINTData(); }															// set flag for received new IR code					
					}else{ SendINTData(); }																// set flag for received new IR code				
				}else{
					eeprom_write_block(&irmp_data,(uchar *)0 + AdressTrainedCode, sizeof(irmp_data));	// no IR code trained, save it:		
					memcpy(&trained_irmp_data, &irmp_data, sizeof(irmp_data));							// update trained_irmp_data
				}
			#else
				SendINTData();
			#endif
	    }
        	usbPoll();																					// do a USB poll
    }
    return 0;
}

/* ------------------------------------------------------------------------- */
