#pragma once

#define NUEVO        0
#define MODIFICACION  1

// CCobrosMngr

class __declspec(dllexport) CCobrosMngr : public CWnd
{
	DECLARE_DYNAMIC(CCobrosMngr)

public:
	CCobrosMngr();
	virtual ~CCobrosMngr();
	void Init(CDatabase *db, CWnd* pParent);
	void NuevoCobro();
	void ModificacionCobro();
	void IntroCobros();
	void RecepAceptos();
	void InformeCobros();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;

};


