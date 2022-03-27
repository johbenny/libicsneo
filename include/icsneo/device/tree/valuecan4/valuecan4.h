#ifndef __VALUECAN4_H_
#define __VALUECAN4_H_

#ifdef __cplusplus

#include "icsneo/device/device.h"
#include "icsneo/device/devicetype.h"

namespace icsneo {

class ValueCAN4 : public Device {
public:
	// All ValueCAN 4 devices share a USB PID of 0x1101

protected:
	using Device::Device;

	virtual void setupEncoder(Encoder& encoder) override {
		Device::setupEncoder(encoder);
		encoder.supportCANFD = true;
	}

	bool requiresVehiclePower() const override { return false; }
};

}

#endif // __cplusplus

#endif