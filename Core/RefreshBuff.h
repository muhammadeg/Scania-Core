int __fastcall CheckBuff(void *Argument, void *edx, int Value, int Player)
{
	TargetFind myTarget(0, 0, Player);
	void *Check = myTarget.getTarget();

	if (!Check)
		return 0;

	return 1;
}
