bluetooth ergodone
====================
基本有线版的ergodone, 改造成了蓝牙版本.

改造流程参考教程 [bluetooth_ergodone_doc](https://github.com/shiqi-614/bluetooth_ergodone_doc)


使用了[Arduino IDE](https://www.arduino.cc/en/software), 基于[arduino_tmk_keyboard](https://github.com/bgould/arduino_tmk_keyboard).

代码使用方法是: 从Release里下载[bluetooth_ergodone.zip](https://github.com/shiqi-614/bluetooth_ergodone/releases/download/1.0/bluetooth_ergodone.zip), 在Arduino IDE里, 通过"项目" -> "加载库" -> "添加.zip库", 把本项目导入.

导入完成后, 还需要
1. **选择正确的示例程序**: 在Arduino IDE里, 通过"文件" -> "示例", 找到本项目名, 然后打开左手或者右手的示例程序,
2. **选择正确的开发板**: 在Arduino IDE里, 通过"工具" -> "开发板"里选择Arduino Leonardo,
3. **选择正确的端口**: 当电脑的USB连接到主控芯片(Arduino Pro Micro)后, 在"工具"->"端口"里会出现一个新的端口, 选择这个端口.

然后点Arduino IDE左上角的"上传"按钮, 就可以将代码上传到主控芯片里了.

在右手的示例程序里[right_hand.ino](../examples/right_hand/right_hand.ino), 可以通过ERGODONE_KEYMAP去定义自己的键盘布局, 支持多个键盘布局的切换, 比如我定义了三层, 第三层是鼠标的操作. 还可以自己定义一些宏操作, 比如在第二层里自定义了FN6, 按下这个键, 就会输出Hello, World. 更多玩法, 参考[tmk keymap](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/doc/keymap.md).

并且也是在右手的程序里[right_hand.ino](../examples/right_hand/right_hand.ino)通过各种hook函数控制LED灯.

我自己定义键盘布局里, 左手CAPS_LOCK按键的位置被我换了, 按成按着的时候, 会切换到第三层, 第三层是鼠标操作, 在第三层, 按下HJKL会移动鼠标. 原来Z键的位置, 被我换成按下切换到第二层, 这时候HJKL就变成方向键, 原来的Z向右移了一位.

### 二次开发
将代码及依赖库TMK下载下来.
<pre><code>git clone --recursive https://github.com/shiqi-614/bluetooth_ergodone.git</code></pre>
放到Arduino IDE的library文件夹中, 如在Mac系统里, 是
<pre><code>~/Documents/Arduino/libraries/</pre></code>

### Reference: 
* [Arduino IDE](https://www.arduino.cc/en/software/)
* [bgould/arduino_tmk_keyboard](https://github.com/bgould/arduino_tmk_keyboard)
* [tmk/tmk_keyboard](https://github.com/tmk/tmk_keyboard)
* [LSChyi/BlueErgo_Protype](https://github.com/LSChyi/BlueErgo_Protype)
* [ktec-hq/ErgoDone](https://github.com/ktec-hq/ErgoDone)
