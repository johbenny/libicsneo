#ifndef __VALUECAN4_H_
#define __VALUECAN4_H_

#include "device/include/device.h"
#include "platform/include/stm32.h"

namespace icsneo {

class ValueCAN4 : public Device {
public:
	// Serial numbers are V0 for 4-4, VE for 4-2EL, V2 for 4-2, and V1 for 4-1
	static constexpr const char* PRODUCT_NAME = "ValueCAN 4";
	static constexpr const uint16_t USB_PRODUCT_ID = 0x1101;
	ValueCAN4(neodevice_t neodevice) : Device(neodevice) {
		com = std::make_shared<Communication>(std::make_shared<STM32>(getWritableNeoDevice()));
		setProductName(PRODUCT_NAME);
		usbProductId = USB_PRODUCT_ID;
	}

	static std::vector<std::shared_ptr<Device>> Find() {
		std::vector<std::shared_ptr<Device>> found;

		for(auto neodevice : STM32::FindByProduct(USB_PRODUCT_ID))
			found.push_back(std::make_shared<ValueCAN4>(neodevice));

		return found;
	}
};

};

#endif