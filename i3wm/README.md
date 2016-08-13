# i3使用

## 安装
Debian,ubuntu:<br />
`sudo apt-get install i3`<br />
如果电脑本身已经安装了图形化桌面(如gnome),安装完i3之后在启动界面可以选择i3，即可启动i3.<br />
第一次启动会让你选择Mod键，选完之后后面经常要用到这个键

## 常用快捷键
```
Mod d               运行程序，调用 dmenu
Mod Enter           创建一个新终端
Mod num             切换到不同工作区
Mod Shift num       移动一个窗口到指定工作区
Mod j/k/l/;         移动焦点
Mod Shift j/k/l/;   切换不同窗口位置
Mod r               进入窗口大小调整模式
j/k/l/;             在大小调整模式下调整窗口大小，合适后按“Enter”退出
Mod e               默认正常分列
Mod w               标签式布局
Mod s               堆叠布局
Mod f               全屏当前窗口
Mod Shift r         重启i3
Mod Shift e         退出i3
Mod Shift Space     切换浮动/非浮动
```

## 配置相关
i3桌面管理器默认没有声音及网络管理插件，这里可以手动安装

* 声音控制插件:<br />
`sudo apt-get install volumeicon-alsa pulseaudio pavucontrol`<br />
然后在.i3/config 最后添加：<br />
`exec --no-startup-id volumeicon`<br />

* 网络管理插件:<br />
`sudo apt-get install network-manager-gnome`<br />
然后在.i3/config 最后添加：<br />
`exec --no-startup-id nm-applet`<br />

* 添加桌面壁纸：<br />
`sudo apt-get install feh`<br />
然后选择一张壁纸，如：/home/linjc/Pictures/Cool-Wallpaper-Background-HD-Dekstop.jpg 然后在.i3/config 最后添加：<br />
`exec --no-startup-id feh --bg-scale /home/linjc/Pictures/Cool-Wallpaper-Background-HD-Dekstop.jpg`

## 相关推荐
