#pragma once
class IWindow
{
public:
	//	TODO ����Ӧ������Щ��������Ϊ��

	// ��������
	virtual int Create() = 0;

	virtual void Show() = 0;

	virtual void ProcessEvent() = 0;


};