// Divisas.h: implementaci�n de la clase CDivisas



// Implementaci�n de CDivisas

// c�digo generado el viernes, 08 de julio de 2005, 9:53

#include "stdafx.h"
#include "Divisas.h"
IMPLEMENT_DYNAMIC(CDivisas, CRecordset)

CDivisas::CDivisas(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DIVISA = "";
	m_DDIVISA = "";
	m_CAMBIO = 0.0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CDivisas::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CDivisas::GetDefaultSQL()
{
	return _T("[dbo].[DIVISAS]");
}

void CDivisas::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[DIVISA]"), m_DIVISA);
	RFX_Text(pFX, _T("[DDIVISA]"), m_DDIVISA);
	RFX_Double(pFX, _T("[CAMBIO]"), m_CAMBIO);

}
/////////////////////////////////////////////////////////////////////////////
// CDivisas diagn�sticos

#ifdef _DEBUG
void CDivisas::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDivisas::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla DIVISAS                                  */
/****************************************************************************/
HRESULT CDivisas::Insert()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("INSERT INTO DIVISAS (DIVISA, DDIVISA, CAMBIO) VALUES ('%s', '%s', %f)",
		m_DIVISA, m_DDIVISA, m_CAMBIO);

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
/* Actualiza un registro en la tabla DIVISAS                                */
/****************************************************************************/
HRESULT CDivisas::UpdateDivisa()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE DIVISAS SET DDIVISA = '%s', CAMBIO = %f WHERE DIVISA"\
		" LIKE '%s'", m_DDIVISA, m_CAMBIO, m_DIVISA);

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
