#pragma once


// CReferenciasMngr

class  __declspec(dllexport)CReferenciasMngr : public CWnd
{
	DECLARE_DYNAMIC(CReferenciasMngr)

public:
	CReferenciasMngr();
	virtual ~CReferenciasMngr();

	void Init(CDatabase *db, CWnd *pParent);
	HRESULT GestionReferencia();
	HRESULT GestionFamilia();
	HRESULT GestionSubFamilia();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;
};


