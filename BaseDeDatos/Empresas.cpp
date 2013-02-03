// Empresas.h: implementación de la clase CEmpresas



// Implementación de CEmpresas

// código generado el jueves, 02 de junio de 2005, 11:32

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
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
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
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[DESCRIPCION]"), m_DESCRIPCION);

}
/////////////////////////////////////////////////////////////////////////////
// CEmpresas diagnósticos

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


