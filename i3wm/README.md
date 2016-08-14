# i3使用

## 安装
Debian,Ubuntu:<br />
`sudo apt-get install i3`<br />
如果电脑本身已经安装了图形化桌面(如gnome),安装完i3之后在启动界面可以选择i3，即可启动i3.<br />
如果电脑本身没有安装图形化桌面(如archlinux),安装完i3之后要安装一个启动器，如slim,然后在启动器里面添加i3.<br />
第一次启动会让你选择Mod键，选完之后后面经常要用到这个键.

## 常用快捷键
```
Mod d               运行程序，调用 dmenu
Mod Enter           启动虚拟终端
Mod num             切换到不同工作区
Mod Shift num       移动一个窗口到指定工作区
Mod j/k/l/;         移动焦点
Mod Shift j/k/l/;   切换不同窗口位置
Mod r               进入窗口大小调整模式
j/k/l/;             在大小调整模式下调整窗口大小，合适后按“Enter”退出
Mod a               焦点转移支交窗口
Mod e               默认正常分列
Mod w               标签式布局
Mod s               堆叠布局
Mod f               全屏当前窗口
Mod h               水平分割窗口
Mod v               垂直分割窗口
Mod Shift q         杀死当前窗口的进程
Mod Shift c         当场重载i3config，无需重启
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

* i3status添加温度：<br />
i3status的配置文件为：/etc/i3status.conf<br />
添加内容：<br />
```
order += "cpu_temperature 0"
cpu_temperature 0 {
        format = "T: %degrees °C"
    max_threshold = 65
        path = "/sys/devices/platform/coretemp.0/temp1_input" #该路径可能与电脑或系统有关
}
```

* 屏幕保护及电源管理：<br />
闲置十分钟后自动休眠：<br />
在.i3/config 最后添加：<br />
`exec --no-startup-id xset dpms 600`<br />
自定义锁屏：<br />
在.i3/config 添加：<br />
`bindsym $mod+Shift+x exec i3lock`<br />
之后用Mod+Shitf+x组合键即可锁屏.<br />

* 修改工作区的名称：<br />
修改.i3/config 具体如下：
```
# Workspace names
set $workspace1 "1:Shell"
set $workspace2 "2:Web"
set $workspace3 "3:Editor"
# switch to workspace
bindsym $mod+1 workspace $workspace1
bindsym $mod+2 workspace $workspace2
bindsym $mod+3 workspace $workspace3
bindsym $mod+4 workspace 4
bindsym $mod+5 workspace 5
bindsym $mod+6 workspace 6
bindsym $mod+7 workspace 7
bindsym $mod+8 workspace 8
bindsym $mod+9 workspace 9
bindsym $mod+0 workspace 10
# move focused container to workspace
bindsym $mod+Shift+1 move container to workspace $workspace1
bindsym $mod+Shift+2 move container to workspace $workspace2
bindsym $mod+Shift+3 move container to workspace $workspace3
bindsym $mod+Shift+4 move container to workspace 4
bindsym $mod+Shift+5 move container to workspace 5
bindsym $mod+Shift+6 move container to workspace 6
bindsym $mod+Shift+7 move container to workspace 7
bindsym $mod+Shift+8 move container to workspace 8
bindsym $mod+Shift+9 move container to workspace 9
bindsym $mod+Shift+0 move container to workspace 10
```

* 让程序在指定工作区启动：<br />
在.i3/config 中添加：<br />
如果没有重命名工作区名称：<br />
`assign [class="(?i)google"] 2` <br />
如果重命名了工作区名称：<br />
`assign [class="(?i)google"] $workspace2` <br />

* 使用Mod+Tab键切换工作区：<br />
在.i3/config 中添加：<br />
```
bindsym $mod+Tab workspace next
bindsym $mod+Shift+Tab workspace prev
```

* 亮度调节：<br />
在.i3/config 中添加：<br />
`bindsym XF86MonBrightnessUp exec /usr/bin/xbacklight -inc 10` <br />
`bindsym XF86MonBrightnessDown exec /usr/bin/xbacklight -dec 5` <br />

## 相关推荐
* 文件管理器：ranger <br />
* 文件管理器：gentoo <br />
* gnome常用软件：<br />
```
cheese 摄像头工具
evince 文档查看
gnome-control-center 设置界面
gnome-dictionary 字典
gnome-nettool 网络诊断工具
gnome-screenshot 屏幕截图
gnome-sound-recorder 录音机
gnome-system-monitor 进程与资源监视
gnome-terminal 虚拟终端
gnome-tweak-tool 系统优化
nautilus 文件管理器
totem 多媒体播放器
```
