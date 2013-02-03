// Cobros.h: implementación de la clase CCobros

// Implementación de CCobros

// código generado el jueves, 03 de noviembre de 2005, 9:51

#include "stdafx.h"
#include "Cobros.h"
IMPLEMENT_DYNAMIC(CCobros, CRecordset)

CCobros::CCobros(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_FCOBRO = "";
	m_NUMFAC = "";
	m_FECHA;
	m_IMPORTE = 0.0;
	m_CUENTA = "";
	m_GASTOS = 0.0;
	m_NREMESA = "";
	m_ESTADREM = "";
	m_ESTADO = "";
	m_BANCO = "";
	m_FECHLIBRA;
	m_FECHDOC;
	m_REPRE = "";
	m_NUMEFEC = "";
	m_FESTADO;
	m_FRECEP;
	m_CENTRO = "";
	m_CAMBIO = 0.0;
	m_IMPODIVI = 0.0;
	m_TIPOREM = 0.0;
	m_CLICON = "";
	m_OBSCOBRO = "";
	m_EMITIDO = FALSE;
	m_FECHCONTA;
	m_EUROS = 0.0;
	m_VENCIDO = FALSE;
	m_EGASTOS = 0.0;
	m_NPAGARE = 0.0;
	m_nFields = 28;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CCobros::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CCobros::GetDefaultSQL()
{
	return _T("[dbo].[cobros]");
}

void CCobros::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Date(pFX, _T("[FECHA]"), m_FECHA);
	RFX_Double(pFX, _T("[IMPORTE]"), m_IMPORTE);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Double(pFX, _T("[GASTOS]"), m_GASTOS);
	RFX_Text(pFX, _T("[NREMESA]"), m_NREMESA);
	RFX_Text(pFX, _T("[ESTADREM]"), m_ESTADREM);
	RFX_Text(pFX, _T("[ESTADO]"), m_ESTADO);
	RFX_Text(pFX, _T("[BANCO]"), m_BANCO);
	RFX_Date(pFX, _T("[FECHLIBRA]"), m_FECHLIBRA);
	RFX_Date(pFX, _T("[FECHDOC]"), m_FECHDOC);
	RFX_Text(pFX, _T("[REPRE]"), m_REPRE);
	RFX_Text(pFX, _T("[NUMEFEC]"), m_NUMEFEC);
	RFX_Date(pFX, _T("[FESTADO]"), m_FESTADO);
	RFX_Date(pFX, _T("[FRECEP]"), m_FRECEP);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Double(pFX, _T("[CAMBIO]"), m_CAMBIO);
	RFX_Double(pFX, _T("[IMPODIVI]"), m_IMPODIVI);
	RFX_Double(pFX, _T("[TIPOREM]"), m_TIPOREM);
	RFX_Text(pFX, _T("[CLICON]"), m_CLICON);
	RFX_Text(pFX, _T("[OBSCOBRO]"), m_OBSCOBRO);
	RFX_Bool(pFX, _T("[EMITIDO]"), m_EMITIDO);
	RFX_Date(pFX, _T("[FECHCONTA]"), m_FECHCONTA);
	RFX_Double(pFX, _T("[EUROS]"), m_EUROS);
	RFX_Bool(pFX, _T("[VENCIDO]"), m_VENCIDO);
	RFX_Double(pFX, _T("[EGASTOS]"), m_EGASTOS);
	RFX_Double(pFX, _T("[NPAGARE]"), m_NPAGARE);

}
/////////////////////////////////////////////////////////////////////////////
// CCobros diagnósticos

#ifdef _DEBUG
void CCobros::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCobros::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla COBROS                                   */
/****************************************************************************/
HRESULT CCobros::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara las cadenas con las fechas */
	CString strFechaVencimiento, strFechaLibramiento, strFechaRecep;

	if (m_FECHA == 0)
		strFechaVencimiento = "NULL";
	else
		strFechaVencimiento = "'" + m_FECHA.Format("%d/%m/%Y") + "'";

	if (m_FECHLIBRA == 0)
		strFechaLibramiento = "NULL";
	else
		strFechaLibramiento = "'" + m_FECHLIBRA.Format("%d/%m/%Y") + "'";

	if (m_FRECEP == 0)
		strFechaRecep = "NULL";
	else
		strFechaRecep = "'" + m_FRECEP.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO COBROS (NUMEFEC, NUMFAC, FCOBRO, CUENTA, EUROS, FECHA, FECHLIBRA, " \
		"FRECEP, NREMESA, ESTADO, OBSCOBRO, BANCO, CENTRO) VALUES ('%s', '%s', '%s', '%s', %f, %s, %s, " \
		"%s, '%s', '%s', '%s', '%s', '%s')", m_NUMEFEC, m_NUMFAC, m_FCOBRO, m_CUENTA, m_EUROS, strFechaVencimiento,
		strFechaLibramiento, strFechaRecep, m_NREMESA, m_ESTADO, m_OBSCOBRO, m_BANCO, m_CENTRO);
		
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
/* Modifica un registro en la tabla COBROS                                  */
/****************************************************************************/
HRESULT CCobros::UpdateCobros()
{
	HRESULT hErr = S_OK;

	/* Se prepara las cadenas con las fechas */
	CString strFechaVencimiento, strFechaLibramiento, strFechaRecep;

	if (m_FECHA == 0)
		strFechaVencimiento = "NULL";
	else
		strFechaVencimiento = "'" + m_FECHA.Format("%d/%m/%Y") + "'";
	
	if (m_FECHLIBRA == 0)
		strFechaLibramiento = "NULL";
	else
		strFechaLibramiento = "'" + m_FECHLIBRA.Format("%d/%m/%Y") + "'";

	if (m_FRECEP == 0)
		strFechaRecep = "NULL";
	else
		strFechaRecep = "'" + m_FRECEP.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE COBROS SET CUENTA = '%s', FCOBRO = '%s', EUROS = %f, FECHA = %s, " \
		"FECHLIBRA = %s, FRECEP = %s, NREMESA = '%s', ESTADO = '%s', OBSCOBRO = '%s', BANCO = '%s', " \
		"CENTRO = '%s' WHERE NUMEFEC = '%s'", m_CUENTA, m_FCOBRO, m_EUROS, strFechaVencimiento, strFechaLibramiento, strFechaRecep, m_NREMESA, m_ESTADO, 
		m_OBSCOBRO, m_BANCO, m_CENTRO, m_NUMEFEC.Trim());

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
/* Modifica el importe de un cobro                                          */
/****************************************************************************/
HRESULT CCobros::UpdateImporteCobro()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE COBROS SET EUROS = %f WHERE NUMEFEC = '%s'",m_EUROS, m_NUMEFEC);

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
/* Elimina todos los cobros de una factura                                  */
/****************************************************************************/
HRESULT CCobros::DeleteCobros()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM COBROS WHERE NUMFAC = '%s'", m_NUMFAC);

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

