// Subfami.h: implementaci�n de la clase CSubfami



// Implementaci�n de CSubfami

// c�digo generado el mi�rcoles, 15 de junio de 2005, 15:57

#include "stdafx.h"
#include "Subfami.h"
IMPLEMENT_DYNAMIC(CSubfami, CRecordset)

CSubfami::CSubfami(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CSUBFAM = "";
	m_DSUBFAM = "";
	m_ARTI = "";
	m_DTOVSFAM = 0.0;
	m_DTOCSFAM = 0.0;
	m_CFAMILIA = "";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CSubfami::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-004;Trusted_Connection=Yes");
}

CString CSubfami::GetDefaultSQL()
{
	return _T("[dbo].[subfami]");
}

void CSubfami::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CSUBFAM]"), m_CSUBFAM);
	RFX_Text(pFX, _T("[DSUBFAM]"), m_DSUBFAM);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Double(pFX, _T("[DTOVSFAM]"), m_DTOVSFAM);
	RFX_Double(pFX, _T("[DTOCSFAM]"), m_DTOCSFAM);
	RFX_Text(pFX, _T("[CFAMILIA]"), m_CFAMILIA);

}
/////////////////////////////////////////////////////////////////////////////
// CSubfami diagn�sticos

#ifdef _DEBUG
void CSubfami::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubfami::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla SUBFAMI                                  */
/****************************************************************************/
HRESULT CSubfami::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO SUBFAMI (CSUBFAM, DSUBFAM, CFAMILIA, DTOVSFAM, DTOCSFAM)"\
		" VALUES ('%s', '%s','%s', '%f','%f')",m_CSUBFAM, m_DSUBFAM,m_CFAMILIA, m_DTOVSFAM, m_DTOCSFAM);

	TRY
	{
		m_pDatabase->ExecuteSQL(strSql);		
	}

	CATCH(CDBException, exp)
	{
		AfxMessageBox(exp->m_strError);
		hErr = exp->m_nRetCode;
	}

	END_CATCH

	return (hErr);
}

/****************************************************************************/
/* Actualiza un registro en la tabla SUBFAMILIA                             */
/****************************************************************************/
HRESULT CSubfami::UpdateRegistro()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE SUBFAMI SET DSUBFAM = '%s', CFAMILIA = '%s', DTOVSFAM = %f, DTOCSFAM = %f "\
		"WHERE CSUBFAM LIKE '%s'", m_DSUBFAM, m_CFAMILIA, m_DTOVSFAM, m_DTOCSFAM, m_CSUBFAM);

	TRY
	{
		m_pDatabase->ExecuteSQL(strSql);		
	}

	CATCH(CDBException, exp)
	{
		AfxMessageBox(exp->m_strError);
		hErr = exp->m_nRetCode;
	}

	END_CATCH

	return (hErr);
}


