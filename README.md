# 自动巡线小车

## 简介

该项目是哈尔滨工业大学（深圳）自动化实践课程考核项目自动巡线小车的对应代码，由 [Chenx Dust](https://github.com/chenxijun) 编写，提供有需要的人士以参考。

## 授权

本项目依据 [The Unlicense](https://unlicense.org) 进行授权，不对任何形式的利用进行限制。

## 分支

 - `main` 分支提供稳定的巡线能力，用于完成考核
 - `speed` 分支提供高速的竞速能力，用于进行比赛

## 结构

```
-- AutoCar
 |- AutoCar.ino           主程序
 |- const.h               常数头文件
 |- encoder.h/ino         编码器模块
 |- ir_sensor.h/ino       红外传感器模块
 |- motor.h/ino           电机模块
 |- patrol.h/ino          巡线模块
 |- pid_controller.h/ino  PID控制器模块
```

## 用法

 1. 根据接线情况修改 `const.h` 文件
 2. 将代码刷入开发板
