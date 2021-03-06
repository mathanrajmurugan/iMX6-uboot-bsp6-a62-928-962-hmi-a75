/*
 * (C) Copyright 2015 Seco
 *
 * Author: Davide Cardillo <davide.cardillo@seco.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __MX6_UQ7_J_A75_CONFIG_H
#define __MX6_UQ7_J_A75_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>



/* ____________________________________________________________________________
   |                                                                            |
   |                            BOARD CONFIGURATION                             |
   |____________________________________________________________________________|
*/
#define MACH_SECO_TYPE                           4900
#define CONFIG_MACH_TYPE                         MACH_SECO_TYPE

#ifdef CONFIG_MX6Q
	#define CONFIG_MX6Q_SECO_A75
#elif defined (CONFIG_MX6DL)
	#define CONFIG_MX6DL_SECO_A75
#elif defined (CONFIG_MX6S)
	#define CONFIG_MX6S_SECO_A75
#endif


#define CONFIG_SYS_USE_SPI_BUS
#define CONFIG_SYS_USE_SPINOR
#define CONFIG_SYS_USE_I2C_BUS
#define CONFIG_SYS_USE_SATA
#define CONFIG_SYS_USE_ETHERNET
#define CONFIG_ENV_IS_IN_MMC


/*  SECO COMPILATION MODULES */
#define CONFIG_SECO_COMMON_BOARD                 1
#define CONFIG_SECO_COMMON_USDHC                 1
#define CONFIG_SECO_COMMON_RGMII                 0
#define CONFIG_SECO_COMMON_RMII                  1
#define CONFIG_SECO_COMMON_PFUZE                 1
#define CONFIG_SECO_COMMON_DISPLAY               0


/* Boot device:
 * 	eMMC
 * 	external SD
 * 	SPI Flash
 */
#define SECO_NUM_BOOT_DEV                        3


/* ____________________________________________________________________________
  |                                                                            |
  |                                   DEBUG UART                               |
  |____________________________________________________________________________|
*/
#define CONFIG_MXC_UART_BASE                     UART2_BASE
#define CONFIG_CONSOLE_DEV                       "ttymxc1"



/* ____________________________________________________________________________
  |                                                                            |
  |                                       SPI                                  |
  |____________________________________________________________________________|
*/
#ifdef CONFIG_SYS_USE_SPI_BUS

#ifdef CONFIG_SYS_USE_SPINOR
	#define CONFIG_SPI_FLASH_SST
	#define CONFIG_SF_DEFAULT_BUS                0
#endif

#ifdef CONFIG_SYS_USE_SPINOR
	#define CONFIG_SF_DEFAULT_CS                 (0|(IMX_GPIO_NR(3, 19)<<8))
#endif

#endif


/* ____________________________________________________________________________
  |                                                                            |
  |                                       I2C                                  |
  |____________________________________________________________________________|
*/
#ifdef CONFIG_SYS_USE_I2C_BUS

	#define CONFIG_SYS_I2C_BASE                  I2C1_BASE_ADDR
	#define CONFIG_SYS_I2C_SPEED                 100000


	/* PMIC */
	#define CONFIG_PFUZE100_PMIC_I2C
	#ifdef CONFIG_PFUZE100_PMIC_I2C
		#define CONFIG_PMIC_I2C_BUS		         1
		#define CONFIG_PMIC_I2C_SLAVE		     0x8
	#endif

#endif



/* ____________________________________________________________________________
  |                                                                            |
  |                                     SATA                                   |
  |____________________________________________________________________________|
*/
#ifdef CONFIG_SYS_USE_SATA

	#define CONFIG_SYS_SATA_MAX_DEVICE           1
	#define CONFIG_DWC_AHSATA_PORT_ID            0

#endif



/* ____________________________________________________________________________
  |                                                                            |
  |                                    ETHERNET                                |
  |____________________________________________________________________________|
*/
#ifdef CONFIG_SYS_USE_ETHERNET

	#define CONFIG_FEC_XCV_TYPE		             RMII
	#define CONFIG_FEC_MXC_PHYADDR		         0
	#define CONFIG_PHY_MICREL

#endif



/* ____________________________________________________________________________
  |                                                                            |
  |                                    PROMPT                                  |
  |____________________________________________________________________________|
*/
#ifdef CONFIG_MX6Q
	#define CONFIG_SECO_PROMPT                   "MX6Q uQ7-J U-Boot > "
#elif defined (CONFIG_MX6DL)
	#define CONFIG_SECO_PROMPT                   "MX6DL uQ7-J U-Boot > "
#elif defined (CONFIG_MX6S)
	#define CONFIG_SECO_PROMPT                   "MX6S uQ7-J U-Boot > "
#endif



/* ____________________________________________________________________________
  |                                                                            |
  |                                    DISPLAY                                 |
  |____________________________________________________________________________|
*/


/* ____________________________________________________________________________
  |                                                                            |
  |                                ENVIRONMENT                                 |
  |____________________________________________________________________________|
*/
/*
#define ENV_MMC
*/
#ifdef CONFIG_ENV_MMC
	#define CONFIG_ENV_IS_IN_MMC
#elif CONFIG_ENV_SPI
	#define CONFIG_ENV_IS_IN_SPI_FLASH
#elif CONFIG_ENV_SATA
	#define CONFIG_ENV_IS_IN_SATA
#endif



#define CONFIG_BOOT_ID_EMMC                      0
#define CONFIG_BOOT_ID_EXT_SD                    1

#define CONFIG_ROOT_ID_EMMC                      0
#define CONFIG_ROOT_ID_EXT_SD                    1


#define CONFIG_MMCROOT                           "/dev/mmcblk0p3"  /* SDHC3 */

#include "mx6seco_common.h"

/* USB Configs */
#define CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC                    (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS                     0
#define CONFIG_USB_MAX_CONTROLLER_COUNT          2       /* Enabled USB controller number */

#define CONFIG_SYS_FSL_USDHC_NUM                 2
#define CONFIG_SYS_MMC_ENV_DEV                   0	     /* SDHC1 */
#define CONFIG_SYS_MMC_ENV_PART                  0       /* user partition */


/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
/* #define CONFIG_CMD_PCI */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	             IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	             IMX_GPIO_NR(3, 19)
#endif

#endif                       /*  __MX6_UQ7_J_A75_CONFIG_H  */
