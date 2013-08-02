QCopter Machine Vision
========
* File Name   : Readme.md
* Author      : Hom19910422
* Version     : v1.1
* Date        : 2013/08/01
* Description : QCopterMachineVision Information
* Wiki        : https://github.com/Hom19910422/QCopterMachineVision/wiki

攝像板　MachineVision
========
* 控制器　STM32F407VE 100Pin 168MHz DSP FPU
* 攝像頭　預計使用MT9V022(灰階)，使用DCMI操作
* 儲存紀錄　SD卡，使用SDIO操作
* 1個SPI接口　與飛控板連接、外擴其他裝置
* 1個USB接口　與飛控板連接、外擴其他裝置
* 7個PWM通道　連接LED、伺服馬達、超音波測距
* 1個FSMC接口　可擴充TFT螢幕、RAM
* 1個USART接口　可擴充藍芽模組、電腦傳輸RS232

Hardware
========
* Use Altium Designer 13

Program
========
* QcopterMV Camera Pre-Alpha

Test
========
* QCopterMV LED
* QCopterMV USART
* QCopterMV PWM
* QCopterMV CamSPI-Slave
* QCopterMV SDIO
* QCopterMV SCCB
* QCopterMV FSMC
* QCopterMV OV7725