#项目说明

此项目为“C++程序设计与训练”课程大作业。

开发环境

	Ubuntu 16.04.3 LTS [linux version 4.8.0-41-generic]
	Qt 5.9.1 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 5.3.1 20160406 (Red Hat 5.3.1-6)) on "xcb"
	Qt Creator 4.3.1 based on Qt 5.9.1
	QMake version 3.1
	GNU Make 4.1 Built for x86_64-pc-linux-gnu
	MySQL: 5.7.19-0ubuntu0.16.04.1 (Ubuntu)

在`restaurant.pro`中修改`MySQL` `lib`、`include`路径，执行

	qmake
	make
	./restaurant
