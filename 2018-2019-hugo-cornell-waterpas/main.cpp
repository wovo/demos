//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "DisplayController.hpp"
#include "LedstripController.hpp"

int main()
{
	// MPU6050 I2C
	auto mpuSCL = hwlib::target::pin_oc(hwlib::target::pins::d21);
	auto mpuSDA = hwlib::target::pin_oc(hwlib::target::pins::d20);
	auto mpuBus = hwlib::i2c_bus_bit_banged_scl_sda(mpuSCL, mpuSDA);
	auto mpuChip = MPU6050(mpuBus, 90);

	// Buttons
	auto refreshButton = hwlib::target::pin_in_out(hwlib::target::pins::d5);
	auto powerButton = hwlib::target::pin_in_out(hwlib::target::pins::d4);
	bool powerButtonPressed = false;
	bool refreshButtonPressed = false;
	bool applicationOn = true;
	bool manualRefresh = true;

	// Controllers
	auto displayController  = DisplayController();
	auto ledstripController = LedstripController();

	// Main loop
	for (;;)
	{
		// Prompt power button press
		if (!powerButton.read() && !powerButtonPressed)
		{
			powerButtonPressed = true;
			applicationOn = !applicationOn;
			manualRefresh = true;

			// Power off
			if (!applicationOn)
			{
				displayController.killDisplays();
				ledstripController.killLedstrip();
			}
		} else if (powerButton.read()) { powerButtonPressed = false; } // Allow for button press again
		
		// Update application
		if (applicationOn)
		{
			// Print MPU6050 values
			mpuChip.printAccRotation();
			mpuChip.printGyroRotation();
			mpuChip.printTemperature();
			hwlib::cout << " " << hwlib::endl;

			// Refresh displays when button pressed
			if ((!refreshButton.read() && !refreshButtonPressed) || manualRefresh)
			{
				refreshButtonPressed = true;
				manualRefresh = false;

				// Update displays
				displayController.updateTemperatureDisplay(mpuChip.getTemperatureCelsius(), mpuChip.getTemperatureFahrenheit(), mpuChip.getTemperatureKelvin());
				displayController.updateWaterDisplay(mpuChip.getAccRotationY());
				displayController.updateRotationDisplay(mpuChip.getAccRotationX(), mpuChip.getAccRotationY(), mpuChip.getAccRotationZ());

			} else if (refreshButton.read()) { refreshButtonPressed = false; } // Allow for button press again

			// Update ledstrip
			ledstripController.update(mpuChip.getAccRotationY());
		}
	}
}