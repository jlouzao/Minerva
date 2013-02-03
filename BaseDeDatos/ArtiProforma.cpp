// ArtiProforma.h: implementación de la clase CArtiProforma



// Implementación de CArtiProforma

// código generado el martes, 26 de julio de 2005, 9:31

#include "stdafx.h"
#include "ArtiProforma.h"
IMPLEMENT_DYNAMIC(CArtiProforma, CRecordset)

CArtiProforma::CArtiProforma(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMPROFOR = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_PESO = 0.0;
	m_ALQUILER = "";
	m_TIPOALQ = "";
	m_CANTI = 0.0;
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_IVARTI = 0.0;
	m_DESARMEMO = "";
	m_nFields = 11;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiProforma::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiProforma::GetDefaultSQL()
{
	return _T("[dbo].[ARTIPROFORMA]");
}

void CArtiProforma::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMPROFOR]"), m_NUMPROFOR);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Double(pFX, _T("[PESO]"), m_PESO);
	RFX_Text(pFX, _T("[ALQUILER]"), m_ALQUILER);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiProforma diagnósticos

#ifdef _DEBUG
void CArtiProforma::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiProforma::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ARTIPROFORMA                             */
/****************************************************************************/
HRESULT CArtiProforma::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTIPROFORMA (NUMPROFOR, ARTI, DESARTI, PESO, ALQUILER, TIPOALQ, " \
		"CANTI, IMPOARTI, DTOARTI, IVARTI, DESARMEMO) VALUES ('%s', '%s', '%s', %f, '%s', '%s', " \
		"%f, %f, %f, %f, '%s')", m_NUMPROFOR, m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
		m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO);

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
/* Modifica un registro en la tabla ARTIPROFORMA                            */
/****************************************************************************/
HRESULT CArtiProforma::UpdateArtiProforma()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIPROFORMA SET ARTI = '%s', DESARTI = '%s', PESO = %f, ALQUILER = '%s', " \
		"TIPOAQL = '%s', CANTI = %f, IMPOARTI = %f, DTOARTI = %f, IVATI = %f, DESARMEMO = '%s' WHERE " \
		"NUMPROFOR = '%s'", m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
		m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_NUMPROFOR);

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
/* Elimina todos los Artículos de una Proforma                              */
/****************************************************************************/
HRESULT CArtiProforma::DeleteArtiProforma()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ARTIPROFORMA WHERE NUMPROFOR = '%s'", m_NUMPROFOR);

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


