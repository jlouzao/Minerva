// Ejercicios.h: implementaci�n de la clase CEjercicios



// Implementaci�n de CEjercicios

// c�digo generado el jueves, 02 de junio de 2005, 11:37

#include "stdafx.h"
#include "Ejercicios.h"
IMPLEMENT_DYNAMIC(CEjercicios, CRecordset)

CEjercicios::CEjercicios(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_DESCRIPCION = "";
	m_IDEMPR = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CEjercicios::GetDefaultConnect()
{
	return _T("DSN=General;Description=Empresas y ejercicios;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-004;DATABASE=General;Trusted_Connection=Yes");
}

CString CEjercicios::GetDefaultSQL()
{
	return _T("[dbo].[EJERCICIOS]");
}

void CEjercicios::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[DESCRIPCION]"), m_DESCRIPCION);
	RFX_Text(pFX, _T("[IDEMPR]"), m_IDEMPR);

}
/////////////////////////////////////////////////////////////////////////////
// CEjercicios diagn�sticos

#ifdef _DEBUG
void CEjercicios::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEjercicios::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


