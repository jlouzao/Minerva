// Centros.h: implementaci�n de la clase CCentros



// Implementaci�n de CCentros

// c�digo generado el martes, 26 de julio de 2005, 9:29

#include "stdafx.h"
#include "Centros.h"
IMPLEMENT_DYNAMIC(CCentros, CRecordset)

CCentros::CCentros(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CCENTRO = "";
	m_DCENTRO = "";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CCentros::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CCentros::GetDefaultSQL()
{
	return _T("[dbo].[CENTROS]");
}

void CCentros::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CCENTRO]"), m_CCENTRO);
	RFX_Text(pFX, _T("[DCENTRO]"), m_DCENTRO);

}
/////////////////////////////////////////////////////////////////////////////
// CCentros diagn�sticos

#ifdef _DEBUG
void CCentros::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCentros::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla CENTROS                                  */
/****************************************************************************/
HRESULT CCentros::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO CENTROS (CCENTRO, DCENTRO)VALUES ('%s', '%s')",m_CCENTRO, m_DCENTRO);

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
/* Modifica un registro en la tabla DIRENV                                  */
/****************************************************************************/
HRESULT CCentros::UpdateCentros()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE CENTROS SET DCENTRO = '%s' WHERE CCENTRO LIKE '%s'", m_DCENTRO, m_CCENTRO);

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
