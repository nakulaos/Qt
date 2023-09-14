## 知识要求
+ 三层架构/mvc/程序设计模式
+ qt基本语法和常用模块
+ cmake/makefile
+ 测试(googletest)
+ linux常用指令
  


## 类介绍

black 0 red 1
0-4 黑
5-9 红

+ AbstractBoard   
一个抽象的棋盘
私有变量：行和列
方法：两个公共接口去获取行和列这两个私有变量

+ ChessBoard
具体的象棋棋盘
使用两种存储形式：基于坐标的固定数组，基于红黑两方的动态数组

+ AbstractPiece
抽象的棋子
私有变量：坐标，id，死亡状态，阵容
方法：获取私有变量的接口和设置中文名和死亡状态的接口，以及移动这个纯虚函数

+ AbstractChessPiece
抽象象棋
私有变量：棋盘，因为与其紧密相连
方法：能不能过河，能不能移动，如何移动

+ chesspiece
  + Rook
  关注点：直线行走，判断中间有没有棋子
  + horse
  + Cannon
  + Pawn
  + Elephant
  + Adviser
  + King


+ chessgame
  变量：棋盘，红黑两方

## bug记录
1. 指针为初始化
2. 指针没有判断是否为空

  
## 收获
1. 派生类指针和基类指针之间的转换
   
2. 