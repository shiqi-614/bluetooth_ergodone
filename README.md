bluetooth ergodone
====================
基本有线版的ergodone, 改造成了蓝牙版本.

改造流程参考教程 [bluetooth_ergodone_doc](https://github.com/shiqi-614/bluetooth_ergodone_doc)

代码使用方法是: 从Release里下载[bluetooth_ergodone.zip](https://github.com/shiqi-614/bluetooth_ergodone/releases/download/1.0/bluetooth_ergodone.zip), 在Arduino IDE里, 通过"项目" -> "加载库" -> "添加.zip库", 把本项目导入.

然后在Arduino IDE里, 通过"文件" -> "示例", 找到本项目名, 然后打开左手或者右手的示例程序, 在"工具" -> "开发板"里选择Arduino Leonardo, 用电脑的USB连接到主控芯片(Arduino Pro Micro)后, 在"工具"->"端口"里会出现一个新的端口, 选择这个端口, 然后点左上角的"上传"按钮, 就可以将代码上传到主控芯片里了.

在右手的程序里[right_hand.ino](./examples/right_hand/right_hand.ino), 可以通过ERGODONE_KEYMAP去定义自己的键盘布局, 支持多个键盘布局的切换, 比如我定义了三层, 第三层是鼠标的操作. 还可以自己定义一些宏操作, 比如在第二层里自定义了FN6, 按下这个键, 就会输出Hello, World. 更多玩法, 参考[tmk keymap](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/doc/keymap.md).

### Reference: 
* [Arduino IDE](https://www.arduino.cc/en/software/)
* [bgould/arduino_tmk_keyboard](https://github.com/bgould/arduino_tmk_keyboard)
* [tmk/tmk_keyboard](https://github.com/tmk/tmk_keyboard)
* [LSChyi/BlueErgo_Protype](https://github.com/LSChyi/BlueErgo_Protype)
* [ktec-hq/ErgoDone](https://github.com/ktec-hq/ErgoDone)
