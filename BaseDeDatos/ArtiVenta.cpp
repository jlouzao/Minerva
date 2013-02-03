// ArtiVenta.h: implementación de la clase CArtiVenta



// Implementación de CArtiVenta

// código generado el miércoles, 10 de agosto de 2005, 12:18

#include "stdafx.h"
#include "ArtiVenta.h"
IMPLEMENT_DYNAMIC(CArtiVenta, CRecordset)

CArtiVenta::CArtiVenta(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMPEDIDO = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_PESO = 0.0;
	m_ALQUILER = "";
	m_TIPOALQ = "";
	m_CANTI = 0.0;
	m_ENVIADOS = 0.0;
	m_RECOGIDOS = 0.0;
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_IVARTI = 0.0;
	m_DESARMEMO = "";
	m_nFields = 13;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiVenta::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiVenta::GetDefaultSQL()
{
	return _T("[dbo].[ARTIVENTA]");
}

void CArtiVenta::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Double(pFX, _T("[PESO]"), m_PESO);
	RFX_Text(pFX, _T("[ALQUILER]"), m_ALQUILER);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Double(pFX, _T("[ENVIADOS]"), m_ENVIADOS);
	RFX_Double(pFX, _T("[RECOGIDOS]"), m_RECOGIDOS);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiVenta diagnósticos

#ifdef _DEBUG
void CArtiVenta::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiVenta::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ARTIVENTA                                */
/****************************************************************************/
HRESULT CArtiVenta::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTIVENTA (NUMPEDIDO, ARTI, DESARTI, PESO, ALQUILER, TIPOALQ, " \
		"CANTI, ENVIADOS, RECOGIDOS, IMPOARTI, DTOARTI, IVARTI, DESARMEMO) VALUES ('%s', '%s', '%s', %f, '%s', '%s', " \
		"%f, %f, %f, %f, %f, %f, '%s')", m_NUMPEDIDO, m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
		m_CANTI, m_ENVIADOS, m_RECOGIDOS, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO);

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
/* Modifica un registro en la tabla ARTIVENTA                               */
/****************************************************************************/
HRESULT CArtiVenta::UpdateArtiVenta()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIVENTA SET ARTI = '%s', DESARTI = '%s', PESO = %f, ALQUILER = '%s', " \
		"TIPOAQL = '%s', CANTI = %f, ENVIADOS = %f, RECOGIDOS = %f, IMPOARTI = %f, DTOARTI = %f, IVATI = %f, DESARMEMO = '%s' WHERE " \
		"NUMPEDIDO = '%s'", m_ARTI, m_DESARTI, m_PESO, m_ALQUILER, m_TIPOALQ, 
		m_CANTI, m_ENVIADOS, m_RECOGIDOS, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_NUMPEDIDO);

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
/* Elimina todos los Artículos de una Venta                                 */
/****************************************************************************/
HRESULT CArtiVenta::DeleteArtiVenta()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ARTIVENTA WHERE NUMPEDIDO = '%s'", m_NUMPEDIDO);

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
/* Actualiza el número de unidades enviadas del artículo                    */                               
/****************************************************************************/
HRESULT CArtiVenta::UpdateEnviados()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIVENTA SET ENVIADOS = %f WHERE NUMPEDIDO LIKE '%s' AND ARTI LIKE '%s'", 
		m_ENVIADOS, m_NUMPEDIDO, m_ARTI);

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
/* Actualiza el número de unidades recogidas del artículo                   */                               
/****************************************************************************/
HRESULT CArtiVenta::UpdateRecogidos()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIVENTA SET RECOGIDOS = %f WHERE NUMPEDIDO LIKE '%s' AND ARTI LIKE '%s'", 
		m_RECOGIDOS, m_NUMPEDIDO, m_ARTI);

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





