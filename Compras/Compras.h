#pragma once

// CComprasMngr

class __declspec(dllexport) CComprasMngr : public CWnd
{
	DECLARE_DYNAMIC(CComprasMngr)

public:
	CComprasMngr();
	virtual ~CComprasMngr();
	void Init(CDatabase *db, CWnd* pParent);
	void GestionCompras();
	void GestionAlbaranes();
	void GestionPedidos();
	void GestionFacturas();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;

};
