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

* 登录app帐号, 设置boundle id
* 