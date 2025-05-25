# [硬件地址oshwhub.com](https://oshwhub.com/jie326513988/cyber-pendant)
IDE：VScode+platformio<br>
框架：Arduino<br>
芯片：ESP32C3<br>
GUI：LVGL9<br>
屏幕：JDI Memory LCD 不息屏也能保持极低功耗<br>
交互方式：3向拨轮，ADC分压采样模式（开机长按10秒进入按键ADC校准）<br>
可TYPEC外接扩展模块，目前支持NMEA0183定位协议<br>
* [单屏幕底板链接](https://oshwhub.com/jie326513988/jdi_mip_arduino)<br>
* [扩展模块链接](https://oshwhub.com/jie326513988/dian-yuan-tong-xun-mo-kuai-_bq24074)<br>
* [学习笔记](https://oshwhub.com/jie326513988/dian-yuan-tong-xun-mo-kuai-_bq24074)<br>
* [BILIBILI视频合集](https://space.bilibili.com/16758526/lists?sid=4472852)<br>
* [固件下载地址](https://oshwhub.com/jie326513988/dian-yuan-tong-xun-mo-kuai-_bq24074)<br>
<img src="/Introducing pictures/1 (3).jpg" width="500">
<br>
<img src="/Introducing pictures/1 (1).jpg" width="500">

### 制作注意事项
- 板厚1.0<br>
- ESP32-C3要后缀为FH4的版本，因为自带4mb的Flash，板子没有Flash芯片<br>
- ESP32-C3FH4用锡膏+热风枪或加热台比较好焊<br>
- 屏幕插座带点的一端对应PCB丝印的点<br>
- 先使用加热台或热风枪焊接ESP32-C3和屏幕插座，再使用热风枪将加速度计和电量计吹上去<br>
- 光固化打印建议：上壳窗口太薄易变形需要硬一点的材料<br>
- FDM打印建议：螺丝柱易断裂最好就涂点橡胶胶水强化<br>
- 尼龙打印建议：打印了两套，一个上壳有缝一个正常，推荐尼龙<br>
### 外壳安装步骤<br>
1.安装打印的拨杆<br>
2.安装屏幕，放不下的用刀片刮一下屏幕卡位四周角落即可<br>
3.安装屏幕支架和PCB<br>
4.安装电池支架和电池（电池支架4款自己打印一个合适的装）<br>
5.上下壳装配打螺丝，4颗 PA1.0x3mm<br>
<img src="/Introducing pictures/1 (6).jpg" width="500">
<br><br>
其他物料（无广告成分）<br>
501430-210毫安<br>
PA1.0x3mm螺丝<br>
2.4G天线<br>
蜂鸣器<br>
三向拨轮 FT-007<br>
AXE510127D座子<br>
裸屏已被倒完，现在只剩带背光触摸的封装屏（还未做接口适配）<br>
<img src="/Introducing pictures/1 (2).jpg" width="500">
<br>
<img src="/Introducing pictures/1 (4).jpg" width="200">
### 关于扩展模块<br>
依然使用捡垃圾捡来电池管理板子，拆出上面的BQ24074芯片，做成带TYPEC带通讯带电池管理的模块（模块完善后开放），<br>
再飞线加上各功能模块，加上外壳即可组成一个一个不同的模块，使用TYPEC接口与主机进行通讯，<br>
因带电池管理，可以实现模块的独立供电，从而不需要耗费主机那可怜的200mah电量。<br>
目前实现卫星模块，是NMEA0183协议的都行。<br>
自己做模块的话将模块的TX接主控typec的DP，需要共地。<br>
左：一体式，右：分体式<br>
<img src="/Introducing pictures/1 (1).webp" width="300">
<br>
<img src="/Introducing pictures/1 (5).jpg" width="300">
<br>
<img src="/Introducing pictures/1 (1).png" width="300">
### 项目属性<br>
本项目为首次公开，为本人原创项目。项目未曾在别的比赛中获奖。<br>
本项目不公开源码，但提供配置好的带LVGL框架的源码<br>
本项目为爱发电，不需要激活码不需要授权，自制要拿去卖的标记来源作者即可<br>

### 烧录说明<br>
空片上电会一直断开连接不用理会，直接烧录即可<br>
注意，由于win7系统不自带winusb驱动，请升级至win8以上系统，或前往乐鑫原厂手册安装驱动<br>
1.选择esp32-c3，USB模式<br>
2.选择路径，记得打钩，烧录地址0x0，注意是零叉零，不是欧叉欧<br>
3.选择com口，没有就多点几次<br>
4.选择波特率，直接拉满<br>
5.点击START开始，失败就多点几次<br>
烧录成功首次开机会进入按键校准界面<br>
<img src="/Introducing pictures/1 (2).jpg" width="300">
<br>
<img src="/Introducing pictures/1 (7).jpg" width="300">
### 项目进度<br>
* 软件<br>
  * LVGL9
  * 时钟（可用一个月）
  * 闹钟
  * 加速度计、角度计、抬手唤醒
  * WEB配网
  * 文件管理器
  * 设置菜单
  * NMEA0183定位信息读取、简单码表
  * 自定义铃声
  * 自定义休眠壁纸
  * 自定义低电量壁纸
  * 备忘录、时钟交替显示、休眠显示
  * 串口空气质量模块读取
  * 前置光、触摸（另外一个完整版的屏幕，固件一样）
  * 气压计（进行中）
  * 自定义设备持有者（进行中）
  * 卫星校准时钟（进行中）
* 硬件
  * V0.9版本为发布版本，除蜂鸣器的电磁干扰较大外，其他功能正常（软件降低屏幕频率后有所改善）
  * 硬件设计
  * 主控 ESP32-C3FH4   集成4MBFlash
  * 贴片天线，陶瓷和PCB天线都没毛病，但未做阻抗匹配
  * TYPE-C接口，充电、烧录程序外接扩展板用
  * 锂电池充电管理 LTH7R/4054
  * USB/电池自动切换电路，二极管+PMOS管实现
  * 3.3V-LDO ME6210A33M3G
  * 时钟 RX8010SJ
  * 加速度计 ，唤醒过于灵敏 LIS2DW12TR
  * 电量计，小容量电池一点都不准，进行8次方曲线拟合补偿稍微准点 MAX17048G
  * 三向波轮开关交互
  * 复位按键使用小侧按
  * 使用贴片蜂鸣器，三极管驱动，用于播放midi音乐和闹钟
### 其他
屏幕驱动库
<br>
LVGL
