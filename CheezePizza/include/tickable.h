#ifndef Tickable_H_
#define Tickable_H_

enum EEngineTickType
{
	ETT_Tick		= 0,
	ETT_PreTick		= 1,
	ETT_PostTick	= 2,
};

class Tickable
{
public:
	Tickable();
	virtual ~Tickable();

	virtual void Tick(float DeltaTime) {}

	EEngineTickType GetTickType() const { return TickType; }
	void SetTickType(EEngineTickType NewTickType) { TickType = NewTickType; }

	bool WillTick() const;
	void StopTicking();

private:
	EEngineTickType TickType;

	Tickable* ListPrevous;
	Tickable* ListNext;
};

#endif