# journal




## new project

1. git clone https://github.com/cocos2d/cocos2d-x.git
2. python download-deps.py
3. git submodule update --init
4. cocos new Journal -p com.test.journal -l cpp -d ../Journal



## question
* test 运行不了

	下载扩展依赖 去github下载对应版本坑爹
	https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin


## 分辨率

#### 概念

* 设计分辨率，可以天马行空，要多大有多大
* 资源分辨率(游戏背景资源分辨率)，理想情况是和设计分辨率一样，这样省得各种计算。但既然是资源，用它就有开销，所以实际情况和设计分辨率会有差异。
* 屏幕分辨率，即各种设备的真实分辨率。我们的目的是要自动适配，那在使用过程中是不需要考虑实际的分辨率的。 手机 16:9  ipad 4:3


#### 适配模式

* EXACT_FIT 就是铺满,不按照比例
* NO_BORDER 比例, 最小的铺满, 大的超出，设计分辨率并不是可见区域(VisibleSize)，我们布局精灵需要根据VisibleOrigin和VisibleSize来做判断处理。
* SHOW_ALL  比例  最大的铺满, 小的露黑边 
* FIXED_WIDTH  按比例放缩，宽度铺满屏幕 
* FIXED_HEIGHT 按比例放缩，高度铺满屏幕 
* 使用FIXED_WIDTH和FIXED_HEIGHT, 还是会黑边, 需要自己缩放一边, 只影响背景图不影响其他, 在某一向，完全可以使用魔鬼数字，320肯定是垂直居中的。




480      320 适中  | 960     3200 细长
------------- | -------------
屏幕分辨率（fWidth，fHeight）  | 计分辨率（dWidth，dHeight）
 放缩因子：k1 = fWidth/dWidth | k2 = fHeight/dHeight
  0.5 |	 0.1		                  
EXACT_FIT   |  dWidth* k1     dHeight*k2 //480 320
NO_BORDER	  | dWidth * max(k1,k2)   dHeight * max(k1,k2) 最大的算 //480 1600
SHOW_ALL    | dWidth * min(k1,k2)   dHeight * min(k1,k2) 最小的算 // 96 320
FIXED_WIDTH | dWidth * k1   dHeight*k1 // 480 1600 
FIXED_HEIGHT| dWidth * k2   dHeight*k2 // 96 320 



#### 代码

```
    //这种写法是为了winSize不同设备不同, 更好适配
    Size screenSize = glview->getFrameSize();
    Size designSize = Size(MY_DESIGNSIZE_W, MY_DESIGNSIZE_H);
    if(screenSize.width / screenSize.height < MY_DESIGNSIZE_W/MY_DESIGNSIZE_H)//说明屏幕的宽小了,分辨率的宽也应该也小点
    {
        designSize = Size(screenSize.width * MY_DESIGNSIZE_H / screenSize.height,MY_DESIGNSIZE_H);
    }
    else if(screenSize.width / screenSize.height > MY_DESIGNSIZE_W / MY_DESIGNSIZE_H)
    {
        designSize = Size(MY_DESIGNSIZE_W,screenSize.height * MY_DESIGNSIZE_W / screenSize.width);
    }
    glview->setDesignResolutionSize(designSize.width, designSize.height,ResolutionPolicy::NO_BORDER);
```


### TestFlight

1. 设置boundle id
2. xcode 登录帐号
3. add push
4. 网页开发者后台, connect->我的APP
5. APP消息 价格销售范围 各种app信息
6. Xcode : Generic ios Device
7. Xcode : Project Archive






### 启动页面

从第一代iPhone开始到现在的iPhone X，苹果提供了三套启动画面的配置方法，按时间周期分别为`Static Launch Images`、`Images Asset Catalog`和`Launch Screen Storyboard`。

#### Static Launch Images 在Info.plist中配置一下UILaunchImages就够了。

Cocos2d-x从1.0版本开始到最新的3.15版本，也一直都是使用这种方式来适配不同的分辨率。通过提供目标设备分辨率的启动图片并配置在Info.plist中，使游戏在目标设备上能够全屏显示。


这样做的弊端：

* 每出一款新分辨率的iOS设备，需要重新配置这个Info.plist，并提供新的启动图片

* 由于上一点，游戏需要重新适配，并出新包，提交AppStore审核

* 人工修改文本文件，容易出错

* 新添加的启动图片会增加游戏包体

#### 可视化资源管理（Images Asset Catalog）
Images.xcassets 可视化增加

此方法解决了人工修改Info.plist的麻烦，而且如果设置了错误分辨率的图片，Xcode打包的时候会提示出错。

但是此方法还是没法适配未来可能出现的新分辨率的设备，即针对新分辨率设备需要重新出包，也没解决包体增大的问题。


#### 布局文件（Launch Screen Storyboard)）强烈推荐

* 拷贝[LaunchScreen.storyboard](https://raw.githubusercontent.com/cocos2d/cocos2d-x/v3/tests/cpp-empty-test/proj.ios/LaunchScreen.storyboard)和[LaunchScreenBackground.png](https://github.com/cocos2d/cocos2d-x/raw/v3/tests/cpp-empty-test/proj.ios/LaunchScreenBackground.png)到`proj.ios`或者`ios`目录。

* 添加LaunchScreen.storyboard和LaunchScreenBackground.png进Xcode工程, 并确认在`Build Phases` -> `Copy Bundle Resource`存在这两个文件

* 工程配置中General -> App Icons and Launch Images中设置Launch Screen File为LaunchScreen。会出现info.plist里面

* 删除Info.plist中无用的UILaunchImages字段

* 删除无用的旧的启动图片，Default.png, Default@2x.png, Default-568h@2x.png等






