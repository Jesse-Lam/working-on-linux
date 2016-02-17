# dialog使用说明
在交互式的shell脚本中，图形化界面可以使用户更方便的使用，让不懂得编程的用户轻松的使用。dialog是在文本界面下创建对话框，这不仅简洁，还可以不启动系统图形化界面的情况下使用。当然，dialog的界面就没有Xwindow下的图形化界面好看，但可以快捷地实现很多基本功能。
## 环境搭建
安装dialog:
* ubuntu下：sudo apt=get install dialog
* arch下：sudo pacman -S dialog
* 手动编译：

    $ wget http://invisible-island.net/datafiles/release/dialog.tar.gz
    $ tar xzf dialog.tar.gz
    $ cd dialog-1.1-20100428
    $ ./configure
    $ make
    $ sudo make install

## 输出
每个对话框提供的输出有两种形式：
* 将所有输出到stderr 输出，不显示到屏幕。
* 使用退出状态码，"OK"为0，"NO"为1,"ESC"为255

## 通用选项
    [--title <title>]  指定将在对话框的上方显示的标题字符串
    [--colors]  解读嵌入式“\Z”的对话框中的特殊文本序列，序列由下面的字符 0-7, b  B, u, U等，恢复正常的设置使用“\Zn”。
    [--no-shadow]  禁止阴影出现在每个对话框的底部
    [--shadow]  应该是出现阴影效果
    [--insecure]  输入部件的密码时，明文显示不安全，使用星号来代表每个字符
    [--no-cancel]  设置在输入框，菜单，和复选框中，不显示“cancel”项
    [--clear]  完成清屏操作。在框体显示结束后，清除框体。这个参数只能单独使用，不能和别的参数联合使用。
    [--ok-label <str>]  覆盖使用“OK”按钮的标签，换做其他字符。
    [--cancel-label <str>]  功能同上
    [--backtitle <backtitle>]  指定的backtitle字符串显示在背景顶端。
    [--begin <y> <x>]  指定对话框左上角在屏幕的上的做坐标
    [--timeout <secs>]  超时（返回的错误代码），如果用户在指定的时间内没有给出相应动作，就按超时处理
    [--defaultno]  使的是默认值 yes/no，使用no
    [--sleep <secs>]  休眠
    [--stderr]  以标准错误方式输出
    [--stdout]  以标准方式输出
    [--default-item <str>]  设置在一份清单，表格或菜单中的默认项目。通常在框中的第一项是默认

##窗体类型
    [ --calendar ]     提供了一个日历，让你可以选择日期
    [ --checklist ]    允许你显示一个选项列表，每个选项都可以被单独的选择  (复选框)
    [ --from ]           允许您建立一个带标签的文本字段，并要求填写
    [ --fselect ]    提供一个路径，让你选择浏览的文件
    [ --gauge ]    显示一个表，呈现出完成的百分比，就是显示出进度。
    [ --infobox ]     显示消息后，（没有等待响应）对话框立刻返回，但不清除屏幕  (信息框)
    [ --inputbox ]   让用户输入文本  (输入框  )
    [ --inputmenu ]    提供一个可供用户编辑的菜单  （可编辑的菜单框）
    [ --menu ]       显示一个列表供用户选择   (菜单框)
    [ --msgbox ]   显示一条消息，并要求用户选择一个确定按钮  (消息框  )
    [ --pause ]      显示一个表格用来显示一个指定的暂停期的状态
    [ --passwordbox ]    显示一个输入框，它隐藏文本
    [ --passwordfrom ]  显示一个来源于标签并且隐藏的文本字段
    [ --radiolist ]      提供一个菜单项目组，只有一个项目，可以选择  (单选框 )
    [ --tailbox ]        在一个滚动窗口文件中使用tail命令来显示文本
    [ --tailboxbg]     跟tailbox类似，但是在background模式下操作
    [ --textbox ]       在带有滚动条的文本框中显示文件的内容  (文本框)
    [ --timebox ]      提供一个窗口，选择小时，分钟，秒
    [ --yesno ]     提供一个带有yes和no按钮的简单信息框  (是/否框)

##命令示例
###消息框：
格式：dialog --msgbox text height width
    dialog --title TESTING --msgbox "this is a test dialog" 10 20
###yesno框： 
格式：dialog --yesno text height width
    dialog --title "yes/no" --yesno "delet the file?" 10 20
###输入框：
格式：dialog --inputbox text height width
    dialog --title "Input your name" --inputbox "please input your name:" 10 30 2>/tmp/name.txt
###密码框： 
格式：dialog --passwordbox text height width
    dialog --title "Password" --insecure --passwordbox "please input the password" 10 30
###文本框： 
格式：dialog --textbox file height width
    dialog --title "the fstab" --textbox /etc/fstab 10 40
###菜单框： 
格式：dialog --menu text height width menu-height tag1 item1 tag2 item2 ...
    dialog --title "Pick a choice" --menu "please choose one" 12 35 5 1 "say hello to everyone" 2 "thank you for your support" 3 "exit"
###文件选框：
格式：dialog --fselect filepath height width
    dialog --title "Pick one file" --fselect /root/ 7 40
###复选框：
格式： dialog --checklist text height width menu-height tag1 item1 tag2 item2 ...
    dialog --title "checklist" --checklist "test" 20 50 10 Memory Memory_size Disk Disk_size
###日历框：
格式： dialog --calendar text height width day month year
    dialog --title "Calendar" --calendar "Date" 5 50
###进度框：
格式： dialog --gauge text height width [<percent>]
    dialog --title "installation pro" --gauge "installation" 10 30 10
###实时进度：
    for i in {1..100} ;do echo $i;done | dialog --title "installation pro" --gauge "installation" 10 30
###表单框：
格式：dialog --from text height width fromheight [ label y x item y x flen ilen ] ...
flen 表示field length，定义了：选定字段中显示的长度
ilen 表示 input-length, 定义了：在外地输入的数据允许的长度
使用up/down（或ctrl/ N，ctrl/ P）在使用领域之间移动。使用tab键在窗口之间切换。
    dialog --title "Add a user" --form "Please input the infomation of new user:" 12 40 4  \
    "Username:"  1  1 "" 1  15  15  0  \
    "Full name:" 2  1 "" 2  15  15  0  \
    "Home Dir:"  3  1 "" 3  15  15  0  \
    "Shell:"     4  1 "" 4  15  15  0

###实例：
gauge.sh
#!/bin/bash
# vim gauge.sh
declare -i PERCENT=0
(
    for I in /etc/*;do
        if [ $PERCENT -le 100 ];then
            cp -r $I /tmp/test 2> /dev/null
            echo "XXX"
            echo "Copy the file $I ..."
            echo "XXX"
            echo $PERCENT
        fi
    let PERCENT+=1
    sleep 0.1
    done
) | dialog --title "coping" --gauge "starting to copy files..." 6 50 0
###综合实例：
#!/bin/bash
yesno() {
 dialog --title "First screen" --backtitle "Test Program" --clear --yesno \
 "Start this test program or not ? \nThis decesion have to make by you. " 16 51
 # yes is 0, no is 1 , esc is 255
 result=$?
 if [ $result -eq 1 ] ; then
 exit 1;
 elif [ $result -eq 255 ]; then
 exit 255;
 fi
 username
}
username() {
 cat /dev/null >/tmp/test.username
 dialog --title "Second screen" --backtitle "Test Program" --clear --inputbox \
 "Please input your username (default: hello) " 16 51 "hello" 2>/tmp/test.username
 result=$?
 if [ $result -eq 1 ] ; then
 yesno
 elif [ $result -eq 255 ]; then
 exit 255;
 fi
 password
}
password() {
 cat /dev/null >/tmp/test.password
 dialog --insecure --title "Third screen" --backtitle "Test Program" --clear --passwordbox \
 "Please input your password (default: 123456) " 16 51 "123456" 2>/tmp/test.password
 result=$?
 if [ $result -eq 1 ] ; then
 username
 elif [ $result -eq 255 ]; then
 exit 255;
 fi
 occupation
}
occupation() {
 cat /dev/null >/tmp/test.occupation
 dialog --title "Forth screen" --backtitle "Test Program" --clear --menu \
 "Please choose your occupation: (default: IT)" 16 51 3 \
 IT "The worst occupation" \
 CEO "The best occupation" \
 Teacher "Not the best or worst" 2>/tmp/test.occupation
 result=$?
 if [ $result -eq 1 ] ; then
 password
 elif [ $result -eq 255 ]; then
 exit 255;
 fi
 finish
}
finish() {
 dialog --title "Fifth screen" --backtitle "Test Program" --clear --msgbox \
 "Congratulations! The test program has finished!\n Username: $(cat /tmp/test.username)\n Password: $(cat /tmp/test.password)\n Occupation: $(cat /tmp/test.occupation)" 16 51
 result=$?
 if [ $result -eq 1 ] ; then
 occupation
 elif [ $result -eq 255 ]; then
 exit 255;
 fi
}
yesno
