#pragma once


// CReferenciasMngr

class  __declspec(dllexport)CGestionCuentasMng : public CWnd
{
	DECLARE_DYNAMIC(CGestionCuentasMng)

public:
	CGestionCuentasMng();
	virtual ~CGestionCuentasMng();

	void Init(CDatabase *db, CWnd *pParent);
	HRESULT GestionCuentas();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;
};
