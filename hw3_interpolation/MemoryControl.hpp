unsigned char* MemAlloc(int total, unsigned char val) {
	unsigned char* rtn = new unsigned char[total];
	for (int i = 0; i < total; i++) {
		rtn[i] = val;
	}
	return rtn;
}

void MemFree(unsigned char* Mem) {
	delete[] Mem;
}