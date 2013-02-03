// ArtiAlbaran.h: implementaci�n de la clase CArtiAlbaran



// Implementaci�n de CArtiAlbaran

// c�digo generado el viernes, 19 de agosto de 2005, 9:19

#include "stdafx.h"
#include "ArtiAlbaran.h"
IMPLEMENT_DYNAMIC(CArtiAlbaran, CRecordset)

CArtiAlbaran::CArtiAlbaran(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMALB = "";
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
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CArtiAlbaran::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiAlbaran::GetDefaultSQL()
{
	return _T("[dbo].[ARTIALBARAN]");
}

void CArtiAlbaran::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
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
// CArtiAlbaran diagn�sticos

#ifdef _DEBUG
void CArtiAlbaran::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiAlbaran::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ARTIALBARAN                              */
/****************************************************************************/
HRESULT CArtiAlbaran::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("INSERT INTO ARTIALBARAN (NUMALB, ARTI, DESARTI, PESO, ALQUILER, TIPOALQ, " \
		"CANTI, IMPOARTI, DTOARTI, IVARTI, DESARMEMO) VALUES ('%s', '%s', '%s', %f, '%s', '%s', " \
		"%f, %f, %f, %f, '%s')", m_NUMALB, m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
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
/* Modifica un registro en la tabla ARTIALBARAN                             */
/****************************************************************************/
HRESULT CArtiAlbaran::UpdateArtiAlbaran()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("UPDATE ARTIALBARAN SET ARTI = '%s', DESARTI = '%s', PESO = %f, ALQUILER = '%s', " \
		"TIPOAQL = '%s', CANTI = %f, IMPOARTI = %f, DTOARTI = %f, IVATI = %f, DESARMEMO = '%s' WHERE " \
		"NUMALB = '%s'", m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
		m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_NUMALB);

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
/* Elimina todos los Art�culos de un Albaran                                */
/****************************************************************************/
HRESULT CArtiAlbaran::DeleteArtiAlbaran()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucci�n */
	CString strSql;

	strSql.Format("DELETE FROM ARTIALBARAN WHERE NUMALB = '%s'", m_NUMALB);

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

