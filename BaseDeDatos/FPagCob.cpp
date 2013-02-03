// FPagCob.h: implementación de la clase CFPagCob



// Implementación de CFPagCob

// código generado el viernes, 08 de julio de 2005, 9:56

#include "stdafx.h"
#include "FPagCob.h"
IMPLEMENT_DYNAMIC(CFPagCob, CRecordset)

CFPagCob::CFPagCob(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_FCOBRO = "";
	m_DFCOBRO = "";
	m_ACEPTO = "";
	m_DESCONTA = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CFPagCob::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CFPagCob::GetDefaultSQL()
{
	return _T("[dbo].[FPAGCOB]");
}

void CFPagCob::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Text(pFX, _T("[DFCOBRO]"), m_DFCOBRO);
	RFX_Text(pFX, _T("[ACEPTO]"), m_ACEPTO);
	RFX_Text(pFX, _T("[DESCONTA]"), m_DESCONTA);

}
/////////////////////////////////////////////////////////////////////////////
// CFPagCob diagnósticos

#ifdef _DEBUG
void CFPagCob::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFPagCob::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla FPAGCOB                                  */
/****************************************************************************/
HRESULT CFPagCob::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO FPAGCOB (FCOBRO, DFCOBRO)VALUES ('%s', '%s')",m_FCOBRO, m_DFCOBRO);

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
/* Modifica un registro en la tabla FPAGCOB                                 */
/****************************************************************************/
HRESULT CFPagCob::UpdateFPagCob()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE FPAGCOB SET DFCOBRO = '%s' WHERE FCOBRO LIKE '%s'", m_DFCOBRO, m_FCOBRO);

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