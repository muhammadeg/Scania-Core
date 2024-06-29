
struct ChanceItem {
	int Index;
	int Amount;
	int Chance;
};

struct SwapItem {
	int Index;
	int Chance;
	SwapItem(int nIndex, int nChance) {
		Index = nIndex;
		Chance = nChance;
	}
};
