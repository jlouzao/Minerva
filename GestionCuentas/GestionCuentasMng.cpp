#include "stdafx.h"
#include "DlgGestionCuentas.h"
#include "GestionCuentasMng.h"


// CReferenciasMngr
IMPLEMENT_DYNAMIC(CGestionCuentasMng, CWnd)
CGestionCuentasMng::CGestionCuentasMng()
{
}

CGestionCuentasMng::~CGestionCuentasMng()
{
}


BEGIN_MESSAGE_MAP(CGestionCuentasMng, CWnd)
END_MESSAGE_MAP()

// Controladores de mensajes de CReferenciasMngr

void CGestionCuentasMng::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

HRESULT CGestionCuentasMng::GestionCuentas()
{
	HRESULT hErr = S_OK;

	CDlgGestionCuentas dlgGestionCuentas(m_pParent);
	dlgGestionCuentas.SetConexion(m_db);
	dlgGestionCuentas.DoModal();
	return hErr;
}
////////////////////////////////////////////////////////////////
