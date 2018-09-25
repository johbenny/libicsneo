#ifndef __IDEVICESETTINGS_H_
#define __IDEVICESETTINGS_H_

#include <stdint.h>

#ifdef __cplusplus
#include "communication/include/communication.h"
#include <iostream>

namespace icsneo {

class IDeviceSettings {
public:
	static uint16_t CalculateGSChecksum(const std::vector<uint8_t>& settings);

	IDeviceSettings(std::shared_ptr<Communication> com) : com(com) {}
	virtual void refresh();
	//virtual void commit() = 0;
	virtual void* getStructure() { return settings.data(); }
	//virtual bool setBaudrate(int baud) = 0;
protected:
	bool settingsLoaded = false;
	std::vector<uint8_t> settings;
	std::shared_ptr<Communication> com;
};

#endif

/* SetBaudrate in CAN_SETTINGS */
enum
{
	AUTO,
	USE_TQ
};

/* Baudrate in CAN_SETTINGS/CANFD_SETTINGS */
enum
{
	BPS20,
	BPS33,
	BPS50,
	BPS62,
	BPS83,
	BPS100,
	BPS125,
	BPS250,
	BPS500,
	BPS800,
	BPS1000,
	BPS666,
	BPS2000,
	BPS4000,
	CAN_BPS5000,
	CAN_BPS6667,
	CAN_BPS8000,
	CAN_BPS10000,
};

/* Mode in CAN_SETTINGS */
enum
{
	NORMAL = 0,
	DISABLE = 1,
	LOOPBACK = 2,
	LISTEN_ONLY = 3,
	LISTEN_ALL = 7
};

typedef struct
{
	uint8_t Mode;
	uint8_t SetBaudrate;
	uint8_t Baudrate;
	uint8_t transceiver_mode;
	uint8_t TqSeg1;
	uint8_t TqSeg2;
	uint8_t TqProp;
	uint8_t TqSync;
	uint16_t BRP;
	uint8_t auto_baud;
	uint8_t innerFrameDelay25us;
} CAN_SETTINGS;
#define CAN_SETTINGS_SIZE 12

/* FDMode in CANFD_SETTINGS */
enum
{
	NO_CANFD,
	CANFD_ENABLED,
	CANFD_BRS_ENABLED,
	CANFD_ENABLED_ISO,
	CANFD_BRS_ENABLED_ISO
};

typedef struct _CANFD_SETTINGS
{
	uint8_t FDMode; /* mode, secondary baudrate for canfd */
	uint8_t FDBaudrate;
	uint8_t FDTqSeg1;
	uint8_t FDTqSeg2;
	uint8_t FDTqProp;
	uint8_t FDTqSync;
	uint16_t FDBRP;
	uint8_t FDTDC;
	uint8_t reserved;
} CANFD_SETTINGS;
#define CANFD_SETTINGS_SIZE 10

/* high_speed_auto_switch in SWCAN_SETTINGS */
enum
{
	SWCAN_AUTOSWITCH_DISABLED,
	SWCAN_AUTOSWITCH_NO_RESISTOR,
	SWCAN_AUTOSWITCH_WITH_RESISTOR,
	SWCAN_AUTOSWITCH_DISABLED_RESISTOR_ENABLED
};

typedef struct
{
	uint8_t Mode;
	uint8_t SetBaudrate;
	uint8_t Baudrate;
	uint8_t transceiver_mode;
	uint8_t TqSeg1;
	uint8_t TqSeg2;
	uint8_t TqProp;
	uint8_t TqSync;
	uint16_t BRP;
	uint16_t high_speed_auto_switch;
	uint8_t auto_baud;
	uint8_t RESERVED;
} SWCAN_SETTINGS;
#define SWCAN_SETTINGS_SIZE 14

/* Baudrate in LIN_SETTINGS / ISO9141_KEYWORD2000_SETTINGS / UART_SETTINGS */
enum
{
	BPS5000,
	BPS10400,
	BPS33333,
	BPS50000,
	BPS62500,
	BPS71429,
	BPS83333,
	BPS100000,
	BPS117647
};

/* MasterResistor in LIN_SETTINGS */
enum
{
	RESISTOR_ON,
	RESISTOR_OFF
};

/* Mode in LIN_SETTINGS */
enum
{
	SLEEP_MODE,
	SLOW_MODE,
	NORMAL_MODE,
	FAST_MODE
};

typedef struct _LIN_SETTINGS
{
	uint32_t Baudrate; /* New products since FIREVNETEP should rely on this only */
	uint16_t spbrg; /* Precompiled to be 40Mhz/Baudrate/16 - 1.  Only used in neoVI FIRE/FIREVNET(4dw) */
	uint8_t brgh; /* Must be zero */
	uint8_t numBitsDelay;
	uint8_t MasterResistor;
	uint8_t Mode;
} LIN_SETTINGS;
#define LIN_SETTINGS_SIZE 10

typedef struct
{
	uint16_t time_500us;
	uint16_t k;
	uint16_t l;
} ISO9141_KEYWORD2000__INIT_STEP;
#define ISO9141_KEYWORD2000__INIT_STEP_SIZE 6

typedef struct
{
	uint32_t Baudrate;
	uint16_t spbrg;
	uint16_t brgh;
	ISO9141_KEYWORD2000__INIT_STEP init_steps[16];
	uint8_t init_step_count;
	uint16_t p2_500us;
	uint16_t p3_500us;
	uint16_t p4_500us;
	uint16_t chksum_enabled;
} ISO9141_KEYWORD2000_SETTINGS;
#define ISO9141_KEYWORD2000_SETTINGS_SIZE 114

typedef struct _UART_SETTINGS
{
	uint16_t Baudrate;
	uint16_t spbrg;
	uint16_t brgh;
	uint16_t parity;
	uint16_t stop_bits;
	uint8_t flow_control; /* 0- off, 1 - Simple CTS RTS */
	uint8_t reserved_1;
	union {
		uint32_t bOptions;
		struct
		{
			unsigned invert_tx : 1;
			unsigned invert_rx : 1;
			unsigned half_duplex : 1;
			unsigned reserved_bits : 13;
			unsigned reserved_bits2 : 16;
		};
	};
} UART_SETTINGS;
#define UART_SETTINGS_SIZE 16

#ifdef __cplusplus
} // End of the namespace
#endif

#endif