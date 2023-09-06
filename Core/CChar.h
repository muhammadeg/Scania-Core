int __fastcall ObjectRelease(void* Object, void *edx, volatile LONG* lpAddend)
{
	if (Object)
		return CIOObject::_Release(Object, lpAddend);
	return 0;
}

LONG __fastcall CIOBufferRelease(void* Buffer, void* edx) {
	if (Buffer)
		return CIOBuffer::Release(Buffer);
	return 0;
}

LONG __fastcall ObjectRef(int Object, void *edx, volatile LONG *lpAddend)
{
	if (Object)
		return CIOObject::_AddRef(Object, lpAddend);
	return 0;
}

void __fastcall ObjectTick(int Object, void *edx)
{
	IChar IObject((void*)Object);

	if (IObject.GetType() == 1) {
		int Channel = IObject.GetChannel();

		int Tanker = IObject.GetMobTanker();
		if (Tanker) {
			IChar ITanker((void*)Tanker);
			if (ITanker.GetType() == 0 && ITanker.IsValid()) {
				int MobPet = ITanker.GetMobPet();

				if (MobPet) {
					IChar IPet((void*)MobPet);
					if (IPet.IsOnline() && !IPet.GetMobTanker())
						IPet.SetMobTarget((int)IObject.GetOffset());
				}
			}

			if (ITanker.GetChannel() != Channel)
				IObject.SetMobTarget(0);
		}

		if (Channel && !IObject.GetMobTanker() && (Channel > ChannelActivated || !ChannelMaps.count(IObject.GetMapIndex()))) {
			IObject.MobDelete();
			return;
		}

		/*	bool targetFound = false;
			int TargetSight = CMonsterReal::ScanSight(Object);
			if (TargetSight) {
				IChar ISight((void*)TargetSight);
				if (ISight.GetChannel() == Channel)
					targetFound = true;
				else {
					int Around = IObject.GetPlayerListAround(64);
					while (Around) {
						IChar PObject((void*)CBaseList::Offset((void*)Around));

						if (!targetFound && PObject.GetChannel() == Channel)
							targetFound = true;

						Around = CBaseList::Pop((void*)Around);
					}
				}
			}

			if (!targetFound) {
				IObject.MobDelete();
				return;
			}*/
	}


	return CChar::RefreshBuff(Object);
}