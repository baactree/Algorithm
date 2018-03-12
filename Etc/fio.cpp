namespace fio {
	const int BSIZE = 524288;
	unsigned char buffer[BSIZE];
	auto p = buffer + BSIZE;
	inline unsigned char readChar() {
		if (p == buffer + BSIZE) {
            fread(buffer,1,BSIZE,stdin);
			p = buffer;
		}
		return *p++;
	}
	int readInt() {
		unsigned char c = readChar();
		while (c < '-') {
			c = readChar();
		}
		int ret = 0;
		while (c >= '-') {
			ret = ret * 10 + c - '0';
			c = readChar();
		}
        return ret;
	}
}