QCopter Machine Vision
========
* Author      : [Hom](https://github.com/Hom19910422)
* Version     : v1.2
* Update      : 2013/11/26
* Wiki        : https://github.com/Hom19910422/QCopterMachineVision/wiki

攝像板　MachineVision
========
* 控制器　STM32F407V 100Pin 168MHz DSP FPU
* 攝像頭　MT9V022(灰階)，使用DCMI操作
* 儲存紀錄　micro SD，使用SDIO操作
* 1個SPI接口　與飛控板連接、外擴其他裝置
* 1個USB接口　外擴其他裝置
* 7個PWM通道　連接LED、伺服馬達、超音波測距
* 1個FSMC接口　可擴充TFT螢幕、RAM

攝像板　MachineVision( 預計 v2.0 版 )
========
* 控制器　STM32F439V 100Pin 180MHz DSP FPU
* 攝像頭　MT9V022(灰階)，使用DCMI操作
* 外擴RAM　IS42S16400J-5TL 64M SDRAM，使用FSMC操作
* 儲存紀錄　micro SD，使用SDIO操作
* 1個SPI接口　與飛控板連接、外擴其他裝置
* 1個USB接口　外擴其他裝置
* 7個PWM通道　連接LED、伺服馬達、超音波測距
* 1個FSMC接口　可擴充TFT螢幕

Hardware
========
* Use Altium Designer 13
* PCB Size : 68 * 33mm

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
* QCopterMV OV7725(Use 480*272 SSD1963)  
  
  
<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">QCopter MachineVision</span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL">Hom</a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW">創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款</a>釋出。<br />此作品衍生自<a xmlns:dct="http://purl.org/dc/terms/" href="https://github.com/Hom19910422" rel="dct:source">Hom-GitHub</a>