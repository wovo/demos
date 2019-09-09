
/*
##############################################################
#                 (c) Jippe Heijnen 2019                     #
#                                                            #
#   Distributed under the Boost Software License v1.0.       #
#   (See accompanying file LICENSE_1_0.txt or copy at        #
#          https://www.boost.org/LICENSE_1_0.txt)            #
##############################################################
*/

#ifndef MATRIXLIB
#define MATRIXLIB


/*!
	\file matrixLib.hpp
	\brief This file contains Library classes.
	 * 
	 * I have created a library which suoports a matrix of LEDs
	 * with a size of 16x24, controlled by a HT1632 chip.
*/

#include "hwlib.hpp"
#include "spi.hpp"

namespace matrix {

	/*!
		\addtogroup matrix
		@{
	*/


	/*!
		\author jippe
		\class commands
		\brief matrix::commands
		 * 
		 * These command codes are used to initiate the matrix so that the HT1632
		 * chip knows what it needs to do and what it's task is.
	 */

struct commands {

/*!
	\addtogroup commands
	@{
*/


static constexpr const uint8_t HT1632_COMMAND		= 0x04;

static constexpr const uint8_t HT1632_SYS_DIS		= 0x00;
static constexpr const uint8_t HT1632_SYS_EN		= 0x01;
static constexpr const uint8_t HT1632_LED_OFF		= 0x02;
static constexpr const uint8_t HT1632_LED_ON		= 0x03;
static constexpr const uint8_t HT1632_BLINK_OFF		= 0x08;
static constexpr const uint8_t HT1632_BLINK_ON		= 0x09;
static constexpr const uint8_t HT1632_SLAVE_MODE	= 0x10;
static constexpr const uint8_t HT1632_MASTER_MODE 	= 0x14;
static constexpr const uint8_t HT1632_INT_RC		= 0x18;
static constexpr const uint8_t HT1632_EXT_CLK		= 0x1C;
static constexpr const uint8_t HT1632_PWM_CONTROL	= 0xA0;

static constexpr const uint8_t HT1632_COMMON_8NMOS	= 0x20;
static constexpr const uint8_t HT1632_COMMON_16NMOS	= 0x24;
static constexpr const uint8_t HT1632_COMMON_8PMOS	= 0x28;
static constexpr const uint8_t HT1632_COMMON_16PMOS	= 0x2C;

static constexpr const uint8_t HT1632_READ			= 0x06;
static constexpr const uint8_t HT1632_WRITE			= 0x05;

/*! @} End of Doxygen Groups*/

};

/*!
	\class HT_1632
	\brief matrix::HT_1632
	 * 
	 * This is the library part of my iPass project. The matrix is 16 x 32 in size,
	 * and it is controlled by an HT1632 chip. This chip works with spi so thats why
	 * I created a spi implementation as well.
 */

class HT_1632 {

/*!
	\addtogroup HT_1632
	@{
*/

protected:
//! \brief This array is the memory-buffer to store data temporarily before it gets written.
uint16_t ledmatrix[24] = {0};
spi::bus spi_bus;
uint16_t type;

/*!
	\brief sendCommand function.
	 * 
	 * This function is quite simple, and it is only used internally in the background.
	 * 
	 * It does the following:
	 * 		- Create a temporary spi transaction using the bus reference member variable.
	 * 		- Put the matrix::commands::HT_1632_command code in first 3 bits.
	 * 		- OR (the bit operator) the actual command in the following, and remaining 9 bits.
	 * 		- transmit the 12 bit sequence to the HT1632 chip.
	 * 
 * 	@param cmd this is the matrix::commands command-code that needs to be sent.
*/

void sendCommand(uint16_t cmd);

/*!
	\brief WriteRam function.
	 * 
	 * The writeRam function writes data to the ram register directly.
	 * 
	 * This is how it works.
	 * The complete transaction has a total of 14 bits, they are arranged as following:
	 * 		- 3 bits matrix::commands::HT_1632_WRITE command.
	 * 		- 7 address bits. This is the register address on the HT1632 chip.
	 * 		- 4 data bits.
	 * 
	 * When the data is in the correct order,
	 * it is sent using a single spi transaction.
	 * 
 * @param addr The 7 bit register address.
 * @param data The 4 bit data, these bits are linked directly to  the LEDs.
 * If you enter 1000 (8 in decimal) as data, the first bit will be enabled.
 */

void writeRam(uint8_t addr, uint8_t data);

/*!
	\brief DumpMem function.
	 * 
	 * This function loops over the internal memory buffer and clears it.
	 * If the 'debug' define is set to true in the header file, the function 
	 * shows the previous bitvalues stored in the buffer before clearing it.
	 * If debug is left as is, no output will be generated and the memory
	 * will be cleared without confirmation.
	
 */

void dumpMem();
friend class matrixWindow;

public:

/*!
	\brief The constructor.
	 * 
	 * This is the constructor of my library, 
	
 * @param spi_bus this is the spi::bus in which the pins are stored.
 * @param type This is the MOS-FET type of the matrix.
 * There are four types:
 * 		-HT1632_COMMON_8NMOS
 * 		-HT1632_COMMON_16NMOS
 * 		-HT1632_COMMON_8PMOS
 * 		-HT1632_COMMON_16PMOS
 * They represent the physical presence of the amount of PMOS or NMOS transistors.
 * I added this functionality because I was not sure if all HT1632 matrices have the
 * same transistors in them. For the one I used HT1632_COMMON_16NMOS seemed to work.
 */

HT_1632(spi::bus spi_bus, uint16_t type);

/*!
	\brief SetPixel function.
	 * 
	 * The setPixel function is quite self-explanatory,
	 * it sets pixels at location x, y.
 * @param x The pixel's x location, from 0 to 15.
 * @param y The pixel's y locatino, from 0 to 23.
 */

void setPixel(uint16_t x, uint16_t y);

/*!
	\brief ClearPixel function.
	 * 
	 * The reverse of the setPixel function.
 * @param x The pixel's x location, from 0 to 15.
 * @param y The pixel's y locatino, from 0 to 23
 */

void clearPixel(uint16_t x, uint16_t y);

/*!
	\brief Blink function.
	 * 
	 * This function lets you blink the whole matrix
	 * for x amount of seconds.
	
 * @param seconds Amount of seconds to let the  matrix blink.
 */

void blink(uint16_t seconds);

/*!
	\brief WriteScreen function.
	 * 
	 * WriteScreen is similar to hwlib::window::flush(),
	 * what it does is send the data stored in the memory buffer to the HT1632
	 * chip.
	 * What's so special about this function is the following:
	 * 	It uses 'successive writing' which is a particular way of writing data over spi.
	 * 	Successive writing enables you to send data far more quickly than writing
	 * 	per register. This is because with successive writing only the first register
	 * 	address is sent, after that comes only data. I first used writeRam to write to each
	 * 	register individually but this was much slower because I had to sent each address too.
	 * 	With successive writing that's not required.
	 * 
	 * What makes this difficult? you may ask to yourself,
	 * 	The difficult part is that for this way of writing data, you must use different amounts
	 * 	of bitlengths after eachother, and all in but 1 spi transaction.
	 * 	So that's why I store the transaction in a temp variable, and destruct the transaction after
	 * 	I'm done.
 */

void writeScreen();

/*!
	\brief SetBrightness function.
	 * 
	 * With the setBrightness function, the user can adjust the brightness of the whole matrix.
	 * This works with a PWM signal which is sent using the the matrix::HT_1632_PWM_CONTROL command.
 * @param b This is the brightness value.
 * The highest value is 0xF (15 in decimal).
 * The lowest value  is 0x0 (0 in decimal).
 */

void setBrightness(uint8_t b);

/*! @} End of Doxygen Groups*/

};  // end of HT_1632 class.

/*!
	\class matrixWindow
	\brief matrix::matrixWindow
	 * 
	 * This class is a way to use my matrices as hwlib::window's.
	 * The cool part about this is that you can use a matrixWindow to draw hwlib::drawable's.
	 * Apart from the constructor, I won't go into depth how the class works because it basically
	 * is a hwlib::window. The functions are mostly self-explanatory.
 */

class matrixWindow : public hwlib::window {

/*!
	\addtogroup matrixWindow
	@{
*/

	private:

	HT_1632 &matrix;

	public:

	/*!
		\brief The constructor.
		 * 
		 * The constructor requires a width and height to know how large
		 * the quote unquote window is. The HT_1632 reference is self explanatory.
		 * (without a matrix reference this class couldn't change pixels on it even if it
		 * wanted to).
		
	 * @param x The width in pixels. (my matrix was 16px wide)
	 * @param y The height in pixels. (my matrix was 24px in height)
	 * @param matrix The matrix object (obviously)
	 */

	matrixWindow(int x, int y, HT_1632 &matrix);
	
	void write_implementation(hwlib::xy pos, hwlib::color col) override;
	void flush() override;
	void clear( hwlib::color col ) override;

/*! @} End of Doxygen Groups*/

};  // end of class matrixWindow

	/*! @} End of Doxygen Groups*/

}  // end of namespace matrix

#endif  // MATRIXLIB
