// ArtiCompra.h: implementación de la clase CArtiCompra



// Implementación de CArtiCompra

// código generado el miércoles, 10 de agosto de 2005, 13:26

#include "stdafx.h"
#include "ArtiCompra.h"
IMPLEMENT_DYNAMIC(CArtiCompra, CRecordset)

CArtiCompra::CArtiCompra(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NPEDCOM = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_CANTI = 0.0;
	m_RECIBIDOS = 0.0;
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_IVARTI = 0.0;
	m_DESARMEMO = "";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiCompra::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiCompra::GetDefaultSQL()
{
	return _T("[dbo].[ARTICOMPRA]");
}

void CArtiCompra::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NPEDCOM]"), m_NPEDCOM);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Double(pFX, _T("[RECIBIDOS]"), m_RECIBIDOS);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiCompra diagnósticos

#ifdef _DEBUG
void CArtiCompra::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiCompra::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ARTICOMPRA                               */
/****************************************************************************/
HRESULT CArtiCompra::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTICOMPRA (NPEDCOM, ARTI, DESARTI, CANTI, RECIBIDOS, IMPOARTI, " \
		"DTOARTI, IVARTI, DESARMEMO) VALUES ('%s', '%s', '%s', %f, %f, %f, %f, %f, '%s')",
		m_NPEDCOM, m_ARTI, m_DESARTI, m_CANTI, m_RECIBIDOS, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO);

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
/* Modifica un registro en la tabla ARTICOMPRA                              */
/****************************************************************************/
HRESULT CArtiCompra::UpdateArtiCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTICOMPRA SET ARTI = '%s', DESARTI = '%s', CANTI = %f, " \
		"RECIBIDOS = %f, IMPOARTI = %f, DTOARTI = %f, IVARTI = %f, DESARMEMO = '%s'  WHERE NPEDCOM = '%s'",
		m_ARTI, m_DESARTI, m_CANTI, m_RECIBIDOS, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_NPEDCOM);

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
/* Elimina todos los Artículos de una Compra                                */
/****************************************************************************/
HRESULT CArtiCompra::DeleteArtiCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ARTICOMPRA WHERE NPEDCOM = '%s'", m_NPEDCOM);

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
/* Actualiza el número de unidades recibidas del artículo                   */                               
/****************************************************************************/
HRESULT CArtiCompra::UpdateRecibidos()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTICOMPRA SET RECIBIDOS = %f WHERE NPEDCOM LIKE '%s' AND ARTI LIKE '%s'", 
		m_RECIBIDOS, m_NPEDCOM, m_ARTI);

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
