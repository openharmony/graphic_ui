202106：
摘要：
1. 新增DFX维测能力：UIKit支持显示控件轮廓
2. 移除AmimanatorManager对外接口，封装到Animator类

详情：
1. 新增DFX维测能力：UIKit支持显示控件轮廓
    代码路径 **graphic_ui/interfaces/kits/dfx/ui_view_bounds.h**；
    
    使用方式：调用 SetShowState 控制是否显示边框

2. 移除AmimanatorManager对外接口，封装到Animator类

   直接使用Animator Start和Stop接口，不需要手动去调用AmimanatorManager的Add/Remove添加Animator类。

