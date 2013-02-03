#pragma once


// CAdministracion

class __declspec(dllexport) CAdministracion : public CWnd
{
	DECLARE_DYNAMIC(CAdministracion)

public:
	CAdministracion();
	virtual ~CAdministracion();
	void Init(CDatabase *db, CWnd *pParent);
	HRESULT GestionUsuarios();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;

};


