// ReferenciasMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgGestionReferencias.h"
#include "DlgGestionFamilias.h"
#include "DlgGestionSubFamilia.h"
#include "ReferenciasMngr.h"


// CReferenciasMngr

IMPLEMENT_DYNAMIC(CReferenciasMngr, CWnd)
CReferenciasMngr::CReferenciasMngr()
{
}

CReferenciasMngr::~CReferenciasMngr()
{
}


BEGIN_MESSAGE_MAP(CReferenciasMngr, CWnd)
END_MESSAGE_MAP()

// Controladores de mensajes de CReferenciasMngr

void CReferenciasMngr::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

HRESULT CReferenciasMngr::GestionReferencia()
{
	HRESULT hErr = S_OK;

	CDlgGestionReferencias dlgGestionReferencia(m_pParent);
	dlgGestionReferencia.SetConexion(m_db);
	dlgGestionReferencia.DoModal();
	return hErr;
}
////////////////////////////////////////////////////////////////
HRESULT CReferenciasMngr::GestionFamilia()
{
	HRESULT hErr = S_OK;

	CDlgGestionFamilias dlgGestionFamilia(m_pParent);
	dlgGestionFamilia.SetConexion(m_db);
	dlgGestionFamilia.DoModal();
	return hErr;
}
////////////////////////////////////////////////////////////////
HRESULT CReferenciasMngr::GestionSubFamilia()
{
	HRESULT hErr = S_OK;

	CDlgGestionSubFamilia dlgGestionSubFamilia(m_pParent);
	dlgGestionSubFamilia.SetConexion(m_db);
	dlgGestionSubFamilia.DoModal();
	return hErr;
}