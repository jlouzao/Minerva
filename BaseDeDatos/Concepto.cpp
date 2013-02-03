// Concepto.h: implementaci�n de la clase CConcepto



// Implementaci�n de CConcepto

// c�digo generado el mi�rcoles, 22 de junio de 2005, 15:39

#include "stdafx.h"
#include "Concepto.h"
IMPLEMENT_DYNAMIC(CConcepto, CRecordset)

CConcepto::CConcepto(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CONCEPTO = "";
	m_DCONCEPTO = "";
	m_CONTA = 0.0;
	m_EJERCICIO = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CConcepto::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CConcepto::GetDefaultSQL()
{
	return _T("[dbo].[CONCEPCO]");
}

void CConcepto::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CONCEPTO]"), m_CONCEPTO);
	RFX_Text(pFX, _T("[DCONCEPTO]"), m_DCONCEPTO);
	RFX_Double(pFX, _T("[CONTA]"), m_CONTA);
	RFX_Text(pFX, _T("[EJERCICIO]"), m_EJERCICIO);

}
/////////////////////////////////////////////////////////////////////////////
// CConcepto diagn�sticos

#ifdef _DEBUG
void CConcepto::AssertValid() const
{
	CRecordset::AssertValid();
}

void CConcepto::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla CONCEPCO                                 */
/****************************************************************************/
HRESULT CConcepto::Insert()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("INSERT INTO CONCEPCO (CONCEPTO, DCONCEPTO, CONTA, EJERCICIO)"\
		"VALUES ('%s', '%s', %f, '%s')",m_CONCEPTO, m_DCONCEPTO, m_CONTA, m_EJERCICIO);

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
/* Actualiza un registro en la tabla CONCEPCO                               */
/****************************************************************************/
HRESULT CConcepto::UpdateConcepto()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE CONCEPCO SET DCONCEPTO = '%s', CONTA = %f, "\
	"EJERCICIO = '%s' WHERE CONCEPTO LIKE '%s'", m_DCONCEPTO, m_CONTA,m_EJERCICIO, m_CONCEPTO);

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
