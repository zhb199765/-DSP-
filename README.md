# -DSP-
DSP 车牌识别 新能源车牌

运行Demo：

$ ./demo // 进入菜单交互界面
$ ./demo ? // 查看CLI帮助

如何开始
当进入交互界面以后，首先是主目录，下面是主目录各个功能的解释：

名称  说明
测试  分别测试车牌识别中每个环节。要想更改测试的图片，可以替换resources/image下的图片；
批量测试    跑完整个general_test下所有图片，输出准确率等指标，用于评估EasyPR的效果；
SVM训练   用SVM训练车牌判断模型；
ANN训练   用ANN训练字符识别和中文识别模型，对应ann.xml和ann_chinese.xml；
中文训练    1.6版新增，用ANN模型训练灰度中文字符，生成annCh.xml；
生成字符    需要配合plates_200k这个数据集才能作用；
当成功运行EasyPR后，首先运行批量测试功能。如果最后的指标跟readme一致，说明EasyPR安装成功。

可以在accuracy.hpp中修改 pr.setResultShow(false) 为 pr.setResultShow(true)， 让批量测试显示出车牌定位的效果。

Note:

在批量测试下有一个选项，native_test。可以把自己的图片放到resources/image/native_test下测试用的。如果你自己的图片没有ground_truth，无法计算准确率指标。但是可以打开车牌定位的效果。

如果想评估车牌定位的指标。需要生成GroundTruth_windows.xml和GroundTruth_others.xml。可以参考general_test下的同名文件来了解下这个文件的格式该如何定义。例如下面的一个xml节点：

<taggedRectangle x="170" y="184" width="96" height="27" rotation="-1" locateType="1">蓝牌:京A88731</taggedRectangle>
taggedRectangle对应一个车牌，属性x和y表示的是车牌外接矩形的中心点的坐标。width和height是宽度和高度。另外两个属性目前没用到。

GroundTruth_windows.xml的编码需要设置为ANSI，而GroundTruth_others.xml的编码要设置为UTF-8，否则会出现乱码。

命令行示例
可以向 demo[.exe] 传递命令行参数来完成你想要的工作，目前Demo支持5个子命令。对于每个子命令的帮助信息可以传入 -h 参数来获取。

车牌识别

# 利用提供的SVM和ANN模型来识别一张图片里面的所有车牌

$ ./demo recognize -p resources/image/plate_recognize.jpg --svm model/svm.xml --ann model/ann.xml

# 或者更简单一些(注意模型路径)
$ ./demo recognize -p resources/image/plate_recognize.jpg
SVM训练

新版本的EasyPR大大简化了SVM训练：

# 首先准备好车牌图片集合plates/
#    是车牌的放在plates/has/
#    不是车牌的放在plates/no/
#    车牌可从项目resources/train/svm.7z中解压得到。

$ ./demo svm --plates=path/to/your/plates --svm=save/to/svm.xml

# 该命令将70%的车牌作为训练数据，另外30%的车牌作为测试数据，
# 这个只可在 include/easypr/config.h 修改。
# 将训练好的模型存放在 save/to/svm.xml。
首先在easypr的主目录下面新建了一个tmp文件夹，并且把svm.7z解压得到的svm文件夹移动到tmp文件夹下面，

执行 $ demo svm --plates=tmp/svm --svm=tmp/svm.xml，生成得到的tmp文件夹下面的svm.xml就是训练好的模型，

替换model/svm.xml就可以达到替换新模型的目的，替换前请先备份原始模型。

ANN训练

先准备好字符图片集合，可从项目resources/train/ann.7z中解压得到。

每类字符都存放在以其名称命名的子文件夹中，命名规则请参考 resources/text/province_mapping。

一切准备就绪后，运行下面这条命令即可：

$ ./demo ann --chars=path/to/chars --ann=save/to/ann.xml
首先在easypr的主目录下面新建了一个tmp文件夹，并且把ann.7z解压得到的ann文件夹移动到tmp文件夹下面，

执行 $ demo ann --chars=tmp/ann --ann=tmp/ann.xml，生成得到的tmp文件夹下面的svm.xml就是训练好的模型，

替换model/ann.xml就可以达到替换新模型的目的，替换前请先备份原始模型。

注意

train文件夹下有3个ann压缩包，解释一下：

文件  用途
ann.7z  包括黑白的字符和中文数据，ann以及ann_chinese.xml由这个训练得到；
annCh.7z    仅仅包括中文的灰度数据，annCh.xml由这个训练得到；
annGray.7z  包括了灰度的字符数据，目前没有任何模型由这个训练得到，主要是为未来的CNN做准备