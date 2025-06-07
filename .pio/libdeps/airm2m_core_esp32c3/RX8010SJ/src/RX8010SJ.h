#ifndef RX8010SJ_ADAPTER
    #define RX8010SJ_ADAPTER

    #include "Arduino.h"
	#include "Wire.h"

	#define RX8010_FCT_FREQ_4096   0b000
	#define RX8010_FCT_FREQ_64     0b001
	#define RX8010_FCT_FREQ_1      0b010
	#define RX8010_FCT_FREQ_1_60   0b011
	#define RX8010_FCT_FREQ_1_3600 0b100

	#define RX8010_FCT_OUT_IRQ1    0b01
	#define RX8010_FCT_OUT_IRQ2    0b00
	#define RX8010_FCT_OUT_OFF     0b10

	#define RX8010_ALARM_IGNORE    0b11111111
	#define RX8010_ALARM_MOD_MONTH 0b0
	#define RX8010_ALARM_MOD_WEEK  0b1

	#define RX8010_TUI_MOD_SEC     0b0
	#define RX8010_TUI_MOD_MIN     0b1

	#define RX8010_FOUT_FREQ_OFF   0b00
	#define RX8010_FOUT_FREQ_1     0b01
	#define RX8010_FOUT_FREQ_1024  0b10
	#define RX8010_FOUT_FREQ_32768 0b11
	#define RX8010_FOUT_IRQ1       0b01
	#define RX8010_FOUT_IRQ2       0b00

    namespace RX8010SJ {
		#define RX8010_SEC     0x10
		#define RX8010_MIN     0x11
		#define RX8010_HOUR    0x12
		#define RX8010_WDAY    0x13
		#define RX8010_MDAY    0x14
		#define RX8010_MONTH   0x15
		#define RX8010_YEAR    0x16
		#define RX8010_RESV17  0x17
		#define RX8010_ALMIN   0x18
		#define RX8010_ALHOUR  0x19
		#define RX8010_ALWDAY  0x1A
		#define RX8010_TCOUNT0 0x1B
		#define RX8010_TCOUNT1 0x1C
		#define RX8010_EXT     0x1D
		#define RX8010_FLAG    0x1E
		#define RX8010_CTRL    0x1F
		/* 0x20 to 0x2F are user registers */
		#define RX8010_RESV30  0x30
		#define RX8010_RESV31  0x31
		#define RX8010_IRQ     0x32

		/* Default values for reseting the module */
		#define RX8010_ADDR17_DEF_VAL 0xD8
		#define RX8010_ADDR30_DEF_VAL 0x00
		#define RX8010_ADDR31_DEF_VAL 0x08
		#define RX8010_ADDR31_DEF_VAL 0x08
		#define RX8010_IRQ_DEF_VAL    0x04
		#define RX8010_CTRL_DEF_VAL   0x04

		#define RX8010_VLF_POS    1
		#define RX8010_TE_POS     4
		#define RX8010_TSEL0_POS  0
		#define RX8010_TSEL1_POS  1
		#define RX8010_TSEL2_POS  2
		#define RX8010_TIE_POS    4
		#define RX8010_TMPIN_POS  2
		#define RX8010_TF_POS     4
		#define RX8010_STOP_POS   6
		#define RX8010_TSTP_POS   2
		#define RX8010_AIE_POS    3
		#define RX8010_WADA_POS   3
		#define RX8010_AF_POS     3
		#define RX8010_USEL_POS   5
		#define RX8010_UF_POS     5
		#define RX8010_UIE_POS    5
		#define RX8010_FSEL0_POS  6
		#define RX8010_FSEL1_POS  7
		#define RX8010_FOPIN0_POS 0
		#define RX8010_FOPIN1_POS 1

		#define RX8010_AL_DISABLED 0b10000000

		struct DateTime {
			byte second;
			byte minute;
			byte hour;
			byte dayOfWeek; // 必须设置
			byte dayOfMonth;
			byte month;
			byte year; // 两位数
		};

        class Adapter {
            public:
                // 构造函数/析构函数
                Adapter(byte i2cSlaveAddr);
                virtual ~Adapter();

                // 方法
				bool initAdapter();						 // 初始化地址
				bool initModule();						 // 初始化模块
				void resetModule(void);					 // 重置模块
				void toggleGlobalStop(bool stopEnabled); // 切换全局停止

				// 日历
                DateTime readDateTime(void);
				void writeDateTime(DateTime dateTime);

				// 固定周期中断
				void setFCTCounter(uint16_t multiplier, byte frequency);
				uint16_t getFCTCounter();
				void setFCTOutput(byte pin);
				void enableFCT();
				void disableFCT();
				bool checkFCT();

				// 警报
				void setAlarm(DateTime time, byte mode);
				void enableAlarm();
				void disableAlarm();
				bool checkAlarm();

				// 时间更新中断
				void setTUIMode(byte mode);
				void enableTUI();
				void disableTUI();
				bool checkTUI();

				// 频率输出
				void enableFOUT(byte frequency, byte pin);
				void disableFOUT();

            private:
                byte i2cAddress;

				byte readFromModule(byte address);
				void writeToModule(byte address, byte data);
				void writeFlag(byte address, byte pos, byte value);
				byte getSingleBit(byte binary);
				byte getValueFromBinary(byte binary, byte pos);
				byte getValueFromBinary(byte binary, byte pos, byte val);
				byte sumValueFromBinary(byte binary, byte length);
				byte setEightyBinary(byte binary, byte val);
				byte setFortyBinary(byte binary, byte val);
				byte setTwentyBinary(byte binary, byte val);
				byte setTenBinary(byte binary, byte val);
				byte setBinary(byte binary, byte pos, byte flagVal);
        };
    }

#endif