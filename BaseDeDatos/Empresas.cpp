// Empresas.h: implementaci�n de la clase CEmpresas



// Implementaci�n de CEmpresas

// c�digo generado el jueves, 02 de junio de 2005, 11:32

#include "stdafx.h"
#include "Empresas.h"
IMPLEMENT_DYNAMIC(CEmpresas, CRecordset)

CEmpresas::CEmpresas(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = "";
	m_DESCRIPCION = "";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CEmpresas::GetDefaultConnect()
{
	return _T("DSN=General;Description=Empresas y ejercicios;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-004;DATABASE=General;Trusted_Connection=Yes");
}

CString CEmpresas::GetDefaultSQL()
{
	return _T("[dbo].[EMPRESAS]");
}

void CEmpresas::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[DESCRIPCION]"), m_DESCRIPCION);

}
/////////////////////////////////////////////////////////////////////////////
// CEmpresas diagn�sticos

#ifdef _DEBUG
void CEmpresas::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmpresas::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


