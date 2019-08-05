基于DSP车牌识别系统的使用说明

一、交叉编译环境配置

1.安装SDK
下载TI官方SDK包http://software-dl.ti.com/processor-sdk-linux/esd/AM57X/latest/index_FDS.html
 

2 下载JN-mini5728补丁包 
http://www.jiang-niu.com/download.html 

3 Ubuntu PC运行如下命令，安装TI官方SDK包 
Chmod 0777 ti-processor-sdk-linux-am57xx-evm-05.03.00.07-Linux-x86-Install.bin
./ti-processor-sdk-linux-am57xx-evm-05.03.00.07-Linux-x86-Install.bin 
注意：
安装路径最好选择家目录，即/home/xxx，xxx为Ubuntu PC用户名。

4 Ubuntu PC运行如下命令，安装JN-mini5728补丁包 
tar zxvf JN-mini5728_patch_4.3.tar.gz 
cp -r JN-mini5728_patch_4.3/* ~/ti-processor-sdk-linux-am57xx-evm-05.03.00.07 
sync 

5 打开.bashrc文件 
sudo vim ~/.bashrc 

6 添加如下命令到文件末尾，然后保存 
 

7 Ubuntu PC运行如下命令，使PATH环境变量生效 
source ~/.bashrc 

8 Ubuntu PC运行如下命令，测试交叉编译工具链是否安装成功 
arm-linux-gnueabihf-gcc -v 
 

解压系统文件（filesystem）

9 将程序放置在保存到/home/linux/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/JiangNiu-demo/Qt路径下

二、程序路径配置
 
1 利用Qt对程序进行编辑与修改

2 修改如图库函数路径，保证与镜像系统文件路径一致

3 修改makefile文件，添加Makefile.build 

键盘输入Ctrl+Alt+T，弹出命令行终端，在命令行终端输
入以下命令编译整个helloworld工程 
cd ~/ti-processor-sdk-linux-rt-am57xx-evm-03.03.00.04/JiangNiu-demo/Qt/EasyPR-master-video
make -f Makefile.build
三、导入开发板
1 开机登陆 
将USB转TTL模块连接到Ubuntu PC机USB接口，如下图所示：
 
注意串口线的顺序。

2 打开Ubuntu PC，安装minicom，键盘输入Ctrl+Alt+T，弹出命令行终端，在命令行终端输入
sudo minicom，进入minicom界面
 
如果Ubuntu PC打印错误信息，请重新插拔USB转TTL模块。 
minicom: cannot open /dev/ttyUSB0: No such file or directory 
Ubuntu PC安装minicom，请参考匠牛社区文档《Ubuntu 开发环境搭建》

连接电源线minicom显示Linux登录界面
JN-mini5728 LED显示绿色，表示JN-mini5728启动成功
 
进入Linux登录界面，输入账号root，密码为空，即可完成登录。

3 利用U盘拷贝含有可执行文件的文件夹Easy PR-master-video

查看U盘挂载信息 
root@am57xx-evm:~# df 
 
从3.0 U盘拷贝数据到JN-mini5728家目录 
root@am57xx-evm:~# cp -r /run/media/sdb1/EasyPR-master-video /home/root

卸载U盘root@am57xx-evm:~# umount /run/media/sdb1

4 打开根目录下的文件夹，赋予运行权限

root@am57xx-evm:~# cd /home/root/EasyPR-master-video

chmod 777 /home/root/EasyPR-master-video

本程序运用到外置摄像头，鼠标以及HDMI显示器

摄像头以及鼠标需要连接到USB上，HDMI连接到对应接口后重启开发板。

连接好外设后运行可执行文件即可

root@am57xx-evm:~# ./EasyPR-master-video
