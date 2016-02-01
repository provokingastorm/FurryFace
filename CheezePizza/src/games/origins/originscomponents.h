#ifndef OriginsComponents_H_
#define OriginsComponents_H_


class LinkComponent : public HealthComponent
{
public:
	LinkComponent(class ComponentSystem& System);

	int ModifyHealth(int HealthChange);
	void SetHealthMax(int NewMaxHealth);
};


#endif

// EOF
