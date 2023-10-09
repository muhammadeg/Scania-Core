void GetNPCList()
{
	NPCIDs.clear();
	for (int i = 0; i < 100000; i++) {
		int NPC = CNPC::FindNPC(i);
		if (NPC) {
			int Index = (*(DWORD*)(NPC + 448));

			if (Index == 729)
				TriangularBattle::HumanNPCID = i;
			if (Index == 730)
				TriangularBattle::DoggebiNPCID = i;
			if (Index == 731)
				TriangularBattle::DemonNPCID = i;

			NPCIDs[Index] = NPC;
			CIOObject::Release((void*)NPC);
		}
	}
}

