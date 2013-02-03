#pragma once


#define LONG_USUARIO   8
#define LONG_PASSWORD  8


// CEncriptar

class CEncriptar : public CWnd
{
	DECLARE_DYNAMIC(CEncriptar)

public:
	CEncriptar();
	virtual ~CEncriptar();
	void Encriptar(CString &strPassw);
	void Desencriptar(CString &strPassw);

protected:
	DECLARE_MESSAGE_MAP()
};


