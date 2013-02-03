// ArtiFactura.h: implementación de la clase CArtiFactura



// Implementación de CArtiFactura

// código generado el lunes, 19 de septiembre de 2005, 15:51

#include "stdafx.h"
#include "ArtiFactura.h"
IMPLEMENT_DYNAMIC(CArtiFactura, CRecordset)

CArtiFactura::CArtiFactura(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMFAC = "";
	m_NUMALB = "";
	m_NUMPED = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_PESO = 0.0;
	m_ALQUILER = "";
	m_TIPOALQ = "";
	m_CANTI = 0.0;
	m_FECINIALQ;
	m_FECFINALQ;
	m_NDIASALQ = 0;
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_IVARTI = 0.0;
	m_DESARMEMO = "";
	m_CLAVE = 0.0;
	m_nFields = 17;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiFactura::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiFactura::GetDefaultSQL()
{
	return _T("[dbo].[ARTIFACTURA]");
}

void CArtiFactura::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMPED]"), m_NUMPED);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Double(pFX, _T("[PESO]"), m_PESO);
	RFX_Text(pFX, _T("[ALQUILER]"), m_ALQUILER);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Date(pFX, _T("[FECINIALQ]"), m_FECINIALQ);
	RFX_Date(pFX, _T("[FECFINALQ]"), m_FECFINALQ);
	RFX_Long(pFX, _T("[NDIASALQ]"), m_NDIASALQ);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);
	RFX_Double(pFX, _T("[CLAVE]"), m_CLAVE);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiFactura diagnósticos

#ifdef _DEBUG
void CArtiFactura::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiFactura::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla ARTIFACTURA                              */
/****************************************************************************/
HRESULT CArtiFactura::Insert()
{
	HRESULT hErr = S_OK;
	CString strFechaIniAlq, strFechaFinAlq;

	if (m_FECINIALQ == 0)
		strFechaIniAlq = "NULL";
	else
		strFechaIniAlq = "'" + m_FECINIALQ.Format("%d/%m/%Y") + "'";

	if (m_FECFINALQ == 0)
		strFechaFinAlq = "NULL";
	else
		strFechaFinAlq = "'" + m_FECFINALQ.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTIFACTURA (NUMFAC, NUMALB, NUMPED, ARTI, DESARTI, PESO, ALQUILER, TIPOALQ, " \
		"FECINIALQ, FECFINALQ, NDIASALQ, CANTI, IMPOARTI, DTOARTI, IVARTI, DESARMEMO) " \
		"VALUES ('%s', '%s', '%s', '%s', '%s', %f, '%s', '%s', %s, %s, %d, %f, %f, %f, %f, '%s')", 
		m_NUMFAC, m_NUMALB, m_NUMPED, m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, strFechaIniAlq,
		strFechaFinAlq, m_NDIASALQ, m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO);

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
/* Modifica un registro en la tabla ARTIFACTURA                             */
/****************************************************************************/
HRESULT CArtiFactura::UpdateArtiFactura()
{
	HRESULT hErr = S_OK;

	CString strFechaIniAlq, strFechaFinAlq;

	if (m_FECINIALQ == 0)
		strFechaIniAlq = "NULL";
	else
		strFechaIniAlq = "'" + m_FECINIALQ.Format("%d/%m/%Y") + "'";

	if (m_FECFINALQ == 0)
		strFechaFinAlq = "NULL";
	else
		strFechaFinAlq = "'" + m_FECFINALQ.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIFACTURA SET ARTI = '%s', DESARTI = '%s', PESO = %f, ALQUILER = '%s', " \
		"TIPOALQ = '%s', FECINIALQ = %s, FECFINALQ = %s, NDIASALQ = %d, CANTI = %f, IMPOARTI = %f, DTOARTI = %f, IVARTI = %f, DESARMEMO = '%s' WHERE " \
		"CLAVE = %f", m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, strFechaIniAlq,
		strFechaFinAlq, m_NDIASALQ,	m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_CLAVE);

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
/* Elimina todos los Artículos de una factura                               */
/****************************************************************************/
HRESULT CArtiFactura::DeleteArtiFactura()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ARTIFACTURA WHERE NUMFAC = '%s'", m_NUMFAC);

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

