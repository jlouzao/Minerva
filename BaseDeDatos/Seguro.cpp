// Seguro.h: implementaci�n de la clase CSeguro



// Implementaci�n de CSeguro

// c�digo generado el lunes, 11 de julio de 2005, 15:19

#include "stdafx.h"
#include "Seguro.h"
IMPLEMENT_DYNAMIC(CSeguro, CRecordset)

CSeguro::CSeguro(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SEGURO = "";
	m_DSEGURO = "";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CSeguro::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CSeguro::GetDefaultSQL()
{
	return _T("[dbo].[SEGURO]");
}

void CSeguro::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[SEGURO]"), m_SEGURO);
	RFX_Text(pFX, _T("[DSEGURO]"), m_DSEGURO);

}
/////////////////////////////////////////////////////////////////////////////
// CSeguro diagn�sticos

#ifdef _DEBUG
void CSeguro::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSeguro::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla SEGURO                                   */
/****************************************************************************/
HRESULT CSeguro::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO SEGURO (SEGURO, DSEGURO)VALUES ('%s', '%s')",m_SEGURO, m_DSEGURO);

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
/* Modifica un registro en la tabla SEGURO                                  */
/****************************************************************************/
HRESULT CSeguro::UpdateSeguro()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE SEGURO SET DSEGURO = '%s' WHERE SEGURO LIKE '%s'", m_DSEGURO, m_SEGURO);

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



