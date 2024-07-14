# 基于LVGL的图形化WiFi界面  
本仓库是学习LVGL的练手项目，使用三级屏幕可视化WiFi连接的过程，主要涉及LVGL图形库操作以及WiFi相关的API  
## 界面介绍  
UI界面分为三个部分  
+ 第一屏幕控制WiFi的开关，以及WiFi扫描结果，可选择WiFi进入第二屏幕
+ 第二屏幕可使用键盘输入WiFi密码进行连接，点击连接后自动跳转第三屏幕
+ 第三屏幕显示连接成功后的WiFi相关信息以及连接失败的相关原因
## 环境要求  
+ ESP-IDF 4.4.6  
+ ESP32S3 N16R8
+ ST7796 SPI显示器,分辨率为320*480
+ GT911电容触摸芯片
+ LVGL 8.3
+ lvgl_esp32_drivers  
+ 本项目使用维可思的3.5寸TFT电容开发板（可选）  
---  

## 更新  

#### V1.0（24.07.14） 
+ 新增ReadMe文件
+ 新增第三屏幕连接错误提示

## ToDo
+ 自动填充已保存的WiFi密码  
+ 解决开机花屏问题

# 博客
LVGL的移植以及优化教程文章,可参考以下  
[lvgl移植](https://github.com/herexiong/ESP32S3-LVGL-Port-IDF/blob/main/doc/lvgl%E7%A7%BB%E6%A4%8D/lvgl.md)  
[LVGL帧率优化](https://github.com/herexiong/ESP32S3-LVGL-Port-IDF/blob/main/doc/lvgl%E5%B8%A7%E7%8E%87%E4%BC%98%E5%8C%96/lvgl%E5%B8%A7%E7%8E%87%E4%BC%98%E5%8C%96.md)  
[使用Squareline并移植到ESP32](https://github.com/herexiong/ESP32S3-LVGL-Port-IDF/blob/main/doc/%E4%BD%BF%E7%94%A8Squareline%E5%B9%B6%E7%A7%BB%E6%A4%8D%E5%88%B0ESP32/%E4%BD%BF%E7%94%A8Squareline%E5%B9%B6%E7%A7%BB%E6%A4%8D%E5%88%B0ESP32.md)