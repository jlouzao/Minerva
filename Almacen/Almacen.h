#pragma once


// CAlmacenMngr

class __declspec(dllexport) CAlmacenMngr : public CWnd
{
	DECLARE_DYNAMIC(CAlmacenMngr)

public:
	CAlmacenMngr();
	virtual ~CAlmacenMngr();
	void Init(CDatabase *db, CWnd* pParent);
	void ExistenciasPorArticulo();
	void Regularizaciones();
	void Transferencias();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;
};


