#pragma once
class IWindow
{
public:
	//	TODO 窗口应该有哪些基本的行为？

	// 创建窗口
	virtual int Create() = 0;

	virtual void Show() = 0;

	virtual void ProcessEvent() = 0;


};