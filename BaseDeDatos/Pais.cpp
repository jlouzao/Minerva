// Pais.h: implementaci�n de la clase CPais



// Implementaci�n de CPais

// c�digo generado el mi�rcoles, 22 de junio de 2005, 15:37

#include "stdafx.h"
#include "Pais.h"
IMPLEMENT_DYNAMIC(CPais, CRecordset)

CPais::CPais(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CPAIS = "";
	m_DPAIS = "";
	m_EUROPA = "";
	m_INTRA = FALSE;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CPais::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CPais::GetDefaultSQL()
{
	return _T("[dbo].[PAIS]");
}

void CPais::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CPAIS]"), m_CPAIS);
	RFX_Text(pFX, _T("[DPAIS]"), m_DPAIS);
	RFX_Text(pFX, _T("[EUROPA]"), m_EUROPA);
	RFX_Bool(pFX, _T("[INTRA]"), m_INTRA);

}
/////////////////////////////////////////////////////////////////////////////
// CPais diagn�sticos

#ifdef _DEBUG
void CPais::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPais::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla PAIS                                     */
/****************************************************************************/
HRESULT CPais::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO PAIS (CPAIS, DPAIS)VALUES ('%s', '%s')",m_CPAIS, m_DPAIS);

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
/* Modifica un registro en la tabla PAIS                                    */
/****************************************************************************/
HRESULT CPais::UpdatePais()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE PAIS SET DPAIS = '%s' WHERE CPAIS LIKE '%s'", m_DPAIS, m_CPAIS );

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


