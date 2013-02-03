// AlbCompra.h: implementación de la clase CAlbCompra



// Implementación de CAlbCompra

// código generado el miércoles, 31 de agosto de 2005, 12:17

#include "stdafx.h"
#include "AlbCompra.h"
IMPLEMENT_DYNAMIC(CAlbCompra, CRecordset)

CAlbCompra::CAlbCompra(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NALBCOM = "";
	m_NPEDCOM = "";
	m_FECHALB;
	m_CUENTA = "";
	m_ALMACEN = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_SREF = "";
	m_OBSALB = "";
	m_DCTOS = 0.0;
	m_PP = 0.0;
	m_EXPORTA = "";
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_CENTRO = "";
	m_DCTO2 = 0.0;
	m_DCTO3 = 0.0;

	m_nFields = 20;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CAlbCompra::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CAlbCompra::GetDefaultSQL()
{
	return _T("[dbo].[ALBCOMPRA]");
}

void CAlbCompra::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NALBCOM]"), m_NALBCOM);
	RFX_Text(pFX, _T("[NPEDCOM]"), m_NPEDCOM);
	RFX_Date(pFX, _T("[FECHALB]"), m_FECHALB);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[ALMACEN]"), m_ALMACEN);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Text(pFX, _T("[SREF]"), m_SREF);
	RFX_Text(pFX, _T("[OBSALB]"), m_OBSALB);
	RFX_Double(pFX, _T("[DCTOS]"), m_DCTOS);
	RFX_Double(pFX, _T("[PP]"), m_PP);
	RFX_Text(pFX, _T("[EXPORTA]"), m_EXPORTA);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Double(pFX, _T("[DCTO2]"), m_DCTO2);
	RFX_Double(pFX, _T("[DCTO3]"), m_DCTO3);

}
/////////////////////////////////////////////////////////////////////////////
// CAlbCompra diagnósticos

#ifdef _DEBUG
void CAlbCompra::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAlbCompra::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////


/****************************************************************************/
/* Inserta un registro en la tabla ALBCOMPRA                                */
/****************************************************************************/
HRESULT CAlbCompra::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaAlbCompra;

	if (m_FECHALB == 0)
		strFechaAlbCompra = "NULL";
	else
		strFechaAlbCompra = "'" + m_FECHALB.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ALBCOMPRA (NALBCOM, NPEDCOM, EXPORTA, CUENTA, ALMACEN, FCOBRO, NCOBROS, VTO1, DVTO, " \
		"DIA1, DIA2, DIA3, DCTOS, DCTO2, DCTO3, PP, FECHALB, CENTRO, SREF, OBSALB) " \
		"VALUES ('%s','%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %s, '%s', '%s', '%s')", 
		m_NALBCOM, m_NPEDCOM, m_EXPORTA, m_CUENTA, m_ALMACEN, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, m_DIA1, m_DIA2,
		m_DIA3,	m_DCTOS, m_DCTO2, m_DCTO3, m_PP, strFechaAlbCompra, m_CENTRO, m_SREF, m_OBSALB);
		

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
/* Modifica un registro en la tabla ALBCOMPRA                               */
/****************************************************************************/
HRESULT CAlbCompra::UpdateAlbCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaAlbCompra;

	if (m_FECHALB == 0)
		strFechaAlbCompra = "NULL";
	else
		strFechaAlbCompra = "'" + m_FECHALB.Format("%d/%m/%Y") + "'";


	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ALBCOMPRA SET NPEDCOM ='%s', EXPORTA = '%s', CUENTA = '%s', ALMACEN = '%s',"\
		"FCOBRO = '%s',NCOBROS = %f, VTO1 = %f, DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, DCTOS = %f," \
		"DCTO2 = %f, DCTO3 = %f, PP = %f, FECHALB = %s, CENTRO = '%s', SREF = '%s', " \
		"OBSALB = '%s' WHERE NALBCOM = '%s'", m_NPEDCOM, m_EXPORTA, m_CUENTA, m_ALMACEN, m_FCOBRO, m_NCOBROS, 
		m_VTO1, m_DVTO, m_DIA1, m_DIA2, m_DIA3, m_DCTOS, m_DCTO2, m_DCTO3, m_PP, 
		strFechaAlbCompra, m_CENTRO, m_SREF, m_OBSALB, m_NALBCOM);

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
/* Elimina un albarán de la tabla                                           */
/****************************************************************************/
HRESULT CAlbCompra::DeleteAlbCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ALBCOMPRA WHERE NALBCOM = '%s'", m_NALBCOM);

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



