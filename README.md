[QCopterMV](https://github.com/QCopter/QCopterMachineVision)
========
* Author  : [Hom](https://about.me/hom)
* Version : v2.0
* Update  : 2016/07/10

Description
========
QCopteMV 是一個機械視覺開發板，用來實現影像處理的裝置，QCopterMV 搭配 MT9V034 ( 灰階 / 彩色 ) 的攝像頭模組，用以實現光流、特徵辨識等演算法，同時透過板子拉出來的 FMC 接口，可以外接 TFT 螢幕模組，實現照相機功能。

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

Related Documents
========
* [Google Drive](https://goo.gl/fuyLuI)

View
========
<img src="https://lh3.googleusercontent.com/ue6zPvTZ3z9VI1eWQtJl3It5LIeV-sV-56b178vrD5NzY6ASAr090aUUhJ_BbtQby-CAoIUp114ydna3E6OPN9FIPSahUJ7c4iJkSYAbUqpcM2ZfE7Z9hH3cBzNkyMmBxMuZgcLXee7467L8MT798Q9kf1QArcCjtOsoo37hNoQORx_hXAXghHYe-qcAsxzGyrc398KBMU9RuTTVeuABkvdXd58kFqYr_ZRf9yg9q6CO__UzNd-LZ565zdSp3ccz7-DzvZOYkJCzIy7AeUZe_uPvgmYFr9PaFbRaZ2-Fqs-KszVl4FSOOUvlQfXUgfYpmfPiSpyAADaXHMnqW12ldBQYMC8r-aZakdho8wkHTFb35fyJ68ivSOe_rfHAA2KX45mr7gXiheJakCAO2KLo2BDMwqqF38P19LU-XetZQiVraqAr4UBnbe4Q_pK4igFalZKaLh2YjzDxKbOIqZy1H5ebu3pPz5s-RHiEfCEOGJA13sn0j2-zLy2e64Ed_rqMj0kAELfNpK4jVi-8yY74NbbTvSCUJiGEmeL_WU-cwrV3N8YU5MJgJMJehDwDzmpQ5EIx3v3-J7vOyy-iu6OhUco3zisdKixI=w1034-h775-no" />
<img src="https://lh3.googleusercontent.com/DCbW94yBTGVT5zWZttmClBILkq6TUM5sgCaP0QeHRCKTmShS88CXgZ4XfzCpqJFHBasQGLTMLvcYyAYRhmrYofAhqA1mOFSAgJLKoqv_fkONCpCGa0MyVDcsEpfya9Z9QiZMlajM-MfzbEXXflJw67tmrnRuE3PbCzqpamLK5tZi8Dd7DKeAkAPpp-B9fEiI4YlGFttJHBhcCeVkg_bb8rEG5Zn_9TXDHveJht8hJMSkO1QlfthyNTmR2PmdZ7AO0Y3fEsd1o16RzcuiAnC0W_szpe923jZ_uuIGgl1ixjWTNI76BBR7b57WsEY6t_XIguQBnIOJh1_LJGDlT68KYWtgO1CAs5JkAcC7Aj_IAf3ikYb1kcotBfx-UUv9kHs2y1i5qrpoGg7hbBH2Xhyj6nGEGh49pSULAklDeR3PAOKdOQpUu5VM5qMYtXziGg5ZBWTjE4qKaD2yu3obY7-jSP835jZes07ynIX970i5ZuwX0r3hLk0lBC2bYufaFCCg-kZ4WIZyMxeLAleNCZPtZdUecxKXTDRMLl3A_DkhH0x7GOr4we-TqArhxOsgGdM9XFt0rsHtb2MrTAT2ZGQhOa-mftT9F27w=w1034-h775-no" />
<img src="https://lh3.googleusercontent.com/1Sw_CvDjMI6NH4_1F4HMcRpAUrVuvjA6O-nHo9JvFfiRIQcvHaILRWJUbRaphnmL8xWPrkFF4vB16AjCYMGzb5fbqf9Qx8kpgfy3w1ReJhzposCZfWQU0CDE-5hCWuqnBLhBsrP4I6NFgEsHEVO16bFptAlpB9pc085Y5MNel3JgqWp142JlyJVUMZfZMwNJ7hunSgRBtqJgZNvWMm0IVc95EG6qjGo3x_LQ_8JugyBCyH3hhxG3Q6mGUqWSeh_1VRQpD17j4u_3Vnw1xHTJN1OwQhj_pHtV9-kgO2KITOZCozmcoNV04_6BZijsxiYhODJl5BMp9ZEaetpC2D7cdT3DU-eVXYAP88p488PHPCmbnM-tXPbEYU5_m7KQcv6-qspjGXaCUVYaQp7HO2-hwwgiGDLfbOZnJNc_10aDAFviicrnlFLQxJy-DbND8ZE65FZ2jBwbzpWeJDHpgsGquzslF5bGlvdz8-jYSlS2fMvOHKUPXH3Ig3pEVKgl9zIXGJigkcficnxIjaKqsE5IV1UxhvpVVKEKLM_RfQLjSmBmyo0oywBaXtiFj9WCfRzSv9z9UFYyu6NNRGh2qHyUR8a7KI8mR7I8=w1034-h775-no" />
<img src="https://lh3.googleusercontent.com/ec8oIE2dwcr0_s0QZCXFnyh7BF5DpkSi4BUbh89zMOVRPE3HgvSdlD34t0rrZdmVF5AKAI9P9Jjkm3YbF4VfRNVeiVY-FCSNRtQeACs_vNy1bJkGHt6TdIpSt9BNBfABo00FHWMIU2SYwS3BZPtbBFexO4kqFGIzyFOuxYey4FJqwkU-v7eA9oXHvQfBnJuo6YiqcIdHrPJco2rJpVTrjWv3K83H12as80HdnWQHH8i9Zbgke-PSImvUlYIPCeSb6ywrp02t2TCqXyKNz6O076_Xk-WlZ-F5BoxTShHe69GDQFmpNkykxSpbB3Tg249-3uEEOY9A72z5NOv4P8Polf7dOjG7F5GcYwf5_DSjLs2_xTKXgCu_TAFxx77rIiLf_enIb-T0h604xVg1KQPxbUDgit0MScGfj1kI5TeS6nv8KsXp4vMDu-K-72MEudjfbMBqewXegFrd7_sjvTdUIvuiPZbOHzrzua3GiZ2Zs10GjuW_7SPWx0hgAzujnNA4XVaxh0CCKLHlCZkSmQPtJEzNLr4X3yy5EKvlRdooWyxTh58pyHdqp4nBh-OwhnqjrCxTK-k4shp0SaOIEAi-vMepAGvEyzKL=w1034-h775-no" />
<br />
更多圖片 [Google+ albums](https://goo.gl/photos/MrFFJ4m715SMSjAVA)

Config
========
<img src="https://lh3.googleusercontent.com/4Po7337NoiWxhgMfG1vXHk9g2MSbqrtmTYOuSxLJeKZ0neD7i8UhdLEBi-zh7o_OlIyE6LptnLwTlfTR0QQcLGpj76mubFZldpNuhaTk4S8WSh93DCo_EL0zeGwzk45yuOO5k1D1YoBsK9HlN9JgReyy0_ROZNisTyc1ihbVri03aGUbQi3UIhV0Cyvg2FprYW_NB_J5bVoq5iUeAwNqniZaKuv9m8J62Xe5l8Vf0ga07Fc08jDM3dipsZ-acrCzpcUBtwlfvKsx0UpPfsG_gubri8v_2P66ftkTSED4rNLT8GQmTIxCVe6RUSwpJyXenYHhPTqPzTSKVxe5-mfULlnYNiaRrP4tRnVAWq94DcKN7JiE9pWMC3EJRyh5BMUnAJixUQnExrOFAmD9Hf1RC6Ih_Xqe5982aXG4HEjID3Fp0-zV6vGIr90sf37VzKV4VMowsEUCR3-rdjVHt7iToCUUrXkq6aFRFd3AikI8O2RKq18QfA8B2QmeEObWBk6aiQZWBVj_S1D-_X9EzLGOSUC3YnxMtbsAbKZ_kdtSCER7PtZsP8VxLmci4zgTbVk7-LaNvo7eg1rJlCqvMH-mr7erBoAmZZXt=w1520-h1550-no" />

Schematic
========
<img src="https://lh3.googleusercontent.com/JYEH6oaqF5HxJ-IpjEClijKtH1v2w919OY0XC80aiO0e26gNOEMFgAnEkak252IfexXOoVE1XtrCGwBkDIPHK4YzrW1DZ46Ym9-e8U9Hpx6JZuxl-f0fK44rD_Qlsw5Vvt__CH66OAdHMBinQC7_pHuiM_ieQE8RGdBfmqwtyyV2Ny1z_tRedYFG12OE2hGHMU0-WgolJpUxMvuw6E-Hxr9IpwkyjFlKK2CgybAw6Noa8CV0XvSOl0PWdC70qEmWpYUDsgOWSn7fj8pyER_2GmaIuTUOOfd_FTgv-cldA3cfTg9L5WoEe28qhjwvHz092NK7FF-N-rYtVrm2izFXsRKEi-nxXnsD6u34d7wseMI97Mekwqg_Zm5eho-jscS2sQaahuQkunDFdrPHJrDmWZFhDE5gQVHLX63dFKba5V8hge92VlBheOTZd0zhjWoXlewIJTZYB7Bw2rAY2XEcTURfeFcsrqosW7oAhVKMZ989PBGmg9kOOjd2l0LdmvJENFoP5WYzpP8XmuoIDfhKDgmmJ0kv9cZCRJoqrqmRkZd0zy5XyV8PIhj6_aBg4qOsM4bjWo8BBaMRarNv_roGK8cVGtqtaT02=w2336-h1200-no" />
