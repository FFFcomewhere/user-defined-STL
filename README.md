# user-defined-STL
这是一个蒟蒻自定义的STL库，主要用于学习STL库及其底层实现，熟悉其使用。目前暂时只写了Vector，其他容器会陆续上传。
Vector:
    实现了STL库的vector基本的一些功能
    使用了allocator来实现动态数组内存的缩放，避免了内存泄漏的风险。

更新：2020.8.28
List：
    实现了头尾不相接的双向链表
    待改进的几个点：
    1.内存的分配没有使用较为安全的allocator
    2.没有重载++运算符
