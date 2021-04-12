# Elevator-Simulation
This is an elevator-simulation program builded in Qt5. Contain door control and elevator up-down control. Since I'm using win32 api in it, the MSVC should be choice for build. For now, a small bug is still exists in it which is always caused by nearest out-call panel signal. One more thing, you must click the Starting up button at first when system is ready for starting, otherwise a unexpected error will be happen.
构建说明
第一步：新建你的Qt项目
第二步：删除项目所有.cpp和.h和.ui文件
第三步：将.h添加进你项目中的Headers(注：头文件),将.cpp添加进你的Sources(源文件),将.ui文件添加进你的Forms(界面)中。
第四步：构建你的项目并运行
第五步：点击开机按钮，开始体验模拟电梯吧
