// ArtiAlbCompra.h: implementación de la clase CArtiAlbCompra



// Implementación de CArtiAlbCompra

// código generado el miércoles, 31 de agosto de 2005, 12:30

#include "stdafx.h"
#include "ArtiAlbCompra.h"
IMPLEMENT_DYNAMIC(CArtiAlbCompra, CRecordset)

CArtiAlbCompra::CArtiAlbCompra(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NALBCOM = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_CANTI = 0.0;
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_IVARTI = 0.0;
	m_DESARMEMO = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiAlbCompra::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiAlbCompra::GetDefaultSQL()
{
	return _T("[dbo].[ARTIALBCOMPRA]");
}

void CArtiAlbCompra::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NALBCOM]"), m_NALBCOM);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiAlbCompra diagnósticos

#ifdef _DEBUG
void CArtiAlbCompra::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiAlbCompra::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ARTIALBCOMPRA                            */
/****************************************************************************/
HRESULT CArtiAlbCompra::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTIALBCOMPRA (NALBCOM, ARTI, DESARTI, CANTI, IMPOARTI, " \
		"DTOARTI, IVARTI, DESARMEMO) VALUES ('%s', '%s', '%s', %f, %f, %f, %f, '%s')",
		m_NALBCOM, m_ARTI, m_DESARTI, m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO);

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
/* Modifica un registro en la tabla ARTIALBCOMPRA                           */
/****************************************************************************/
HRESULT CArtiAlbCompra::UpdateArtiAlbCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIALBCOMPRA SET ARTI = '%s', DESARTI = '%s', CANTI = %f, " \
		"IMPOARTI = %f, DTOARTI = %f, IVARTI = %f, DESARMEMO = '%s'  WHERE NALBCOM = '%s'",
		m_ARTI, m_DESARTI, m_CANTI, m_IMPOARTI, m_DTOARTI, m_IVARTI, m_DESARMEMO, m_NALBCOM);

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
/* Elimina todos los Artículos de un albarán de compra                      */
/****************************************************************************/
HRESULT CArtiAlbCompra::DeleteArtiAlbCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ARTIALBCOMPRA WHERE NALBCOM = '%s'", m_NALBCOM);

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

