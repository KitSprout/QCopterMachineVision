[QCopterMV](https://github.com/QCopter/QCopterMachineVision)
========
* Author  : [Hom](https://about.me/hom)
* Version : v2.0(updating ...)
* Update  : 2016/07/07

Description
========
QCopteMV 是一個機械視覺開發板，用來實現影像處理的裝置，QCopterMV 搭配 MT9V034(灰階/彩色) 的攝像頭模組，用以實現光流、特徵辨識等演算法，同時透過板子拉出來的 FMC 接口，可以外接 TFT 螢幕模組，實現照相機功能。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> QCopterMV v2.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="http://about.me/Hom" property="cc:attributionName" rel="cc:attributionURL"> Hom </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F429ZG](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1577/LN11/PF252140) 144Pin 180MHz DSP FPU
* 感測器　 : [MT9V034](http://www.onsemi.cn/PowerSolutions/product.do?id=MT9V034)，使用 DCMI 操作
* 儲存紀錄 : micro SD(SDIO)、SDRAM IS42S16400J
* 外接介面 : 1xUSB ( Micro )、1xSPI ( FFC16 )、1xFSMC、7xPWM
* PCB 尺寸 : 38.1 x 38.1 mm
* 設計軟體 [Altium Designer 16](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.7](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.7) )

QCopterMV v2.0 預計修改： 
>1. 微控制器改為 LQFP144 的 STM32F42xZ 或 STM32F43xZ，增加運算速度及功能。  
>2. 加入 [SDRAM](http://www.issi.com/WW/pdf/42-45S16400J.pdf)，透過 FMC 操作，用以增加影像處理時所需的 RAM 空間。  
>3. 加入 SPI 操作的 6DOF IMU，並預計新增影像自動水平的功能。  
>4. 加入 [Microphone](http://www.analog.com/en/audiovideo-products/mems-microphones/admp522/products/product.html) 來做聲音紀錄，並預計加入聲控的功能，同時也可以用來做飛行器間的溝通。  
>5. 更改 CamSPI 名稱為 FFCSPI，並修改腳位，使其可以連接 [QFC v2.2](https://github.com/QCopter/QCopterFlightControl)、[QRC](https://github.com/QCopter/QCopterRemoteControl)、[TFT_2.2](https://github.com/OpenPCB/TFT_2.2-inch) 等裝置。  
>6. 設計 Camera 模組，使用 [MT9V034](https://www.aptina.com/products/image_sensors/mt9v034c12stc/) 8bit DCMI，預計會有灰階和彩色兩種版本，方便做不同的演算法實現。  
>7. 設計類似 [Boscam HD19 雲台](http://www.dronesvision.net/en/fpv/1333-boscam-hd19-explorerhd-fpv-camera-pan-tilt-mount-for-fixwing-aircrafts.html)的裝置，用來攜帶 QCopterMV。 ( 該結構預計透過 3D Printer 製做 )  

<img src="https://lh5.googleusercontent.com/-swW9VgqOZBU/UlA1hQbLx9I/AAAAAAAAD7s/co_2QQ1q5HY/s1200/QCopterMV_System.png" />

Related Documents
========
* [Update Records - Hackpad](https://hom.hackpad.com/QCopterMV-sQqGKy2RUlY)
* [Datasheet & BOM - Google Drive](https://drive.google.com/folderview?id=0BzL2wwAot6oPQWdKS3VMWmZ1Sjg&usp=drive_web)

Program
========
* QcopterMV Camera

View
========
<img src="https://lh3.googleusercontent.com/-Cy3CKYy0Y_w/Ud7K7XM_dFI/AAAAAAAAClc/evAgj8h4Sug/s1200/DSC_1179.jpg" />
<img src="https://lh5.googleusercontent.com/-LGxC8SM5YcU/Ud7K7xpP_8I/AAAAAAAAClc/WOheIGD4gww/s1200/DSC_1184.jpg" />
<img src="https://lh5.googleusercontent.com/-beekj574_I8/Ud7K5oIszrI/AAAAAAAAClc/P-EEJkbjrXs/s1200/DSC_1165.jpg" />
<img src="https://lh5.googleusercontent.com/-PonR56Y_DV8/Ud7K699bGII/AAAAAAAAClc/dmLREQBeU3w/s1200/DSC_1169.jpg" />
<img src="https://lh6.googleusercontent.com/-e9bpHqgJpKw/Ud7K7bGqDVI/AAAAAAAAClc/cZY7Y83zMEw/s1200/DSC_1173.jpg" />
<img src="https://lh3.googleusercontent.com/-JoVNYnuH20k/Ud7K9y_R4BI/AAAAAAAAClc/OCoD4AMalt0/s1200/DSC_1238.jpg" />
<img src="https://lh3.googleusercontent.com/-kZqt3l8fEWY/Ud7K-eDvCOI/AAAAAAAAClc/JQULeyFK128/s1200/DSC_1250.jpg" />
<br />
更多圖片 [Google+ albums](https://plus.google.com/u/0/photos/112822505513154783828/albums/5930570551599057185)

Config
========

Schematic
========
