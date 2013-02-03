// Perfiles.h: implementación de la clase CPerfiles



// Implementación de CPerfiles

// código generado el miércoles, 08 de junio de 2005, 15:37

#include "stdafx.h"
#include "Perfiles.h"
IMPLEMENT_DYNAMIC(CPerfiles, CRecordset)

CPerfiles::CPerfiles(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_DESCRIPCION = "";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CPerfiles::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CPerfiles::GetDefaultSQL()
{
	return _T("[dbo].[PERFILES]");
}

void CPerfiles::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[DESCRIPCION]"), m_DESCRIPCION);

}
/////////////////////////////////////////////////////////////////////////////
// CPerfiles diagnósticos

#ifdef _DEBUG
void CPerfiles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPerfiles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


