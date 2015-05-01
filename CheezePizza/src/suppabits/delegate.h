#ifndef Delegate_H_
#define Delegate_H_

struct DelegateVoid
{
	virtual void Invoke() {}
};

struct DelegateInt
{
	virtual void Invoke(int Data) {}
};

struct DelegateFloat
{
	virtual void Invoke(float Data) {}
};

struct DelegateBool
{
	virtual void Invoke(bool Data) {}
};

struct DelegatePointer
{
	virtual void Invoke(void* Data) {}
};

#endif