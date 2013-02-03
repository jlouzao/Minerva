// RuTran.h: implementaci�n de la clase CRuTran



// Implementaci�n de CRuTran

// c�digo generado el lunes, 11 de julio de 2005, 15:19

#include "stdafx.h"
#include "RuTran.h"
IMPLEMENT_DYNAMIC(CRuTran, CRecordset)

CRuTran::CRuTran(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CRUTRAN = "";
	m_DRUTRAN = "";
	m_MATRICULA = "";
	m_MODELO = "";
	m_TARA = 0.0;
	m_PESOMAXIMO = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CRuTran::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CRuTran::GetDefaultSQL()
{
	return _T("[dbo].[RUTRAN]");
}

void CRuTran::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CRUTRAN]"), m_CRUTRAN);
	RFX_Text(pFX, _T("[DRUTRAN]"), m_DRUTRAN);
	RFX_Text(pFX, _T("[MATRICULA]"), m_MATRICULA);
	RFX_Text(pFX, _T("[MODELO]"), m_MODELO);
	RFX_Double(pFX, _T("[TARA]"), m_TARA);
	RFX_Double(pFX, _T("[PESOMAXIMO]"), m_PESOMAXIMO);

}
/////////////////////////////////////////////////////////////////////////////
// CRuTran diagn�sticos

#ifdef _DEBUG
void CRuTran::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRuTran::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla RUTRAN                                  */
/****************************************************************************/
HRESULT CRuTran::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO RUTRAN (CRUTRAN, DRUTRAN, MATRICULA, MODELO,"\
		"TARA, PESOMAXIMO) VALUES ('%s', '%s', '%s', '%s', %f, %f)", m_CRUTRAN,
		m_DRUTRAN, m_MATRICULA, m_MODELO ,m_TARA, m_PESOMAXIMO);

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
/* Modifica un registro en la tabla RUTRAN                                  */
/****************************************************************************/
HRESULT CRuTran::UpdateRutran()
{
	HRESULT hErr = S_OK;

	// Se prepara la instrucci�n 
	CString strSql;

	strSql.Format("UPDATE RUTRAN SET DRUTRAN = '%s', MATRICULA = '%s',"\
		"MODELO = '%s', TARA = %f, PESOMAXIMO = %f WHERE CRUTRAN LIKE '%s'", 
		m_DRUTRAN, m_MATRICULA, m_MODELO, m_TARA, m_PESOMAXIMO, m_CRUTRAN);

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

