// Conta.h: implementación de la clase CConta



// Implementación de CConta

// código generado el martes, 02 de agosto de 2005, 13:11

#include "stdafx.h"
#include "Conta.h"
IMPLEMENT_DYNAMIC(CConta, CRecordset)

CConta::CConta(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMPEDIDO = "";
	m_C_ASIENTO = 0.0;
	m_C_REAL = 0.0;
	m_NUMALBA = "";
	m_NUMALBB = "";
	m_NUMALBC = "";
	m_NUMALBD = "";
	m_NUMALBE = "";
	m_DNUMALBA = "";
	m_DNUMALBB = "";
	m_DNUMALBC = "";
	m_DNUMALBD = "";
	m_DNUMALBE = "";
	m_NUMFACA = "";
	m_NUMFACB = "";
	m_NUMFACC = "";
	m_NUMFACD = "";
	m_NUMFACE = "";
	m_DNUMFACA = "";
	m_DNUMFACB = "";
	m_DNUMFACC = "";
	m_DNUMFACD = "";
	m_DNUMFACE = "";
	m_NPEDCOM = "";
	m_NABONO = "";
	m_NREMESA = "";
	m_C1 = "";
	m_NIMPAGADO = "";
	m_NDECLARADO = "";
	m_NPAGO = "";
	m_NFACCOM = "";
	m_NFACCOMINV = "";
	m_CARGO = "";
	m_ABONO = "";
	m_NTALON = "";
	m_NENTREGA = "";
	m_NUMOP = "";
	m_NUM = "";
	m_ORDEN = "";
	m_NUMPROFOR = "";
	m_EJERCICIO = "";
	m_DEJER = "";
	m_nFields = 42;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CConta::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CConta::GetDefaultSQL()
{
	return _T("[dbo].[CONTA]");
}

void CConta::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Single(pFX, _T("[C_ASIENTO]"), m_C_ASIENTO);
	RFX_Single(pFX, _T("[C_REAL]"), m_C_REAL);
	RFX_Text(pFX, _T("[NUMALBA]"), m_NUMALBA);
	RFX_Text(pFX, _T("[NUMALBB]"), m_NUMALBB);
	RFX_Text(pFX, _T("[NUMALBC]"), m_NUMALBC);
	RFX_Text(pFX, _T("[NUMALBD]"), m_NUMALBD);
	RFX_Text(pFX, _T("[NUMALBE]"), m_NUMALBE);
	RFX_Text(pFX, _T("[DNUMALBA]"), m_DNUMALBA);
	RFX_Text(pFX, _T("[DNUMALBB]"), m_DNUMALBB);
	RFX_Text(pFX, _T("[DNUMALBC]"), m_DNUMALBC);
	RFX_Text(pFX, _T("[DNUMALBD]"), m_DNUMALBD);
	RFX_Text(pFX, _T("[DNUMALBE]"), m_DNUMALBE);
	RFX_Text(pFX, _T("[NUMFACA]"), m_NUMFACA);
	RFX_Text(pFX, _T("[NUMFACB]"), m_NUMFACB);
	RFX_Text(pFX, _T("[NUMFACC]"), m_NUMFACC);
	RFX_Text(pFX, _T("[NUMFACD]"), m_NUMFACD);
	RFX_Text(pFX, _T("[NUMFACE]"), m_NUMFACE);
	RFX_Text(pFX, _T("[DNUMFACA]"), m_DNUMFACA);
	RFX_Text(pFX, _T("[DNUMFACB]"), m_DNUMFACB);
	RFX_Text(pFX, _T("[DNUMFACC]"), m_DNUMFACC);
	RFX_Text(pFX, _T("[DNUMFACD]"), m_DNUMFACD);
	RFX_Text(pFX, _T("[DNUMFACE]"), m_DNUMFACE);
	RFX_Text(pFX, _T("[NPEDCOM]"), m_NPEDCOM);
	RFX_Text(pFX, _T("[NABONO]"), m_NABONO);
	RFX_Text(pFX, _T("[NREMESA]"), m_NREMESA);
	RFX_Text(pFX, _T("[C1]"), m_C1);
	RFX_Text(pFX, _T("[NIMPAGADO]"), m_NIMPAGADO);
	RFX_Text(pFX, _T("[NDECLARADO]"), m_NDECLARADO);
	RFX_Text(pFX, _T("[NPAGO]"), m_NPAGO);
	RFX_Text(pFX, _T("[NFACCOM]"), m_NFACCOM);
	RFX_Text(pFX, _T("[NFACCOMINV]"), m_NFACCOMINV);
	RFX_Text(pFX, _T("[CARGO]"), m_CARGO);
	RFX_Text(pFX, _T("[ABONO]"), m_ABONO);
	RFX_Text(pFX, _T("[NTALON]"), m_NTALON);
	RFX_Text(pFX, _T("[NENTREGA]"), m_NENTREGA);
	RFX_Text(pFX, _T("[NUMOP]"), m_NUMOP);
	RFX_Text(pFX, _T("[NUM]"), m_NUM);
	RFX_Text(pFX, _T("[ORDEN]"), m_ORDEN);
	RFX_Text(pFX, _T("[NUMPROFOR]"), m_NUMPROFOR);
	RFX_Text(pFX, _T("[EJERCICIO]"), m_EJERCICIO);
	RFX_Text(pFX, _T("[DEJER]"), m_DEJER);

}
/////////////////////////////////////////////////////////////////////////////
// CConta diagnósticos

#ifdef _DEBUG
void CConta::AssertValid() const
{
	CRecordset::AssertValid();
}

void CConta::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/*******************************************************************************************/
// Se obtiene el siguiente número de Oferta y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumProfor(CString &strNextNumProfor)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Proforma
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMPROFOR.IsEmpty())
		strNextNumProfor = m_NUMPROFOR.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Proforma
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMPROFOR)+1);
	CString strSql = "UPDATE CONTA SET NUMPROFOR = '" + strNext + "'";

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

/*******************************************************************************************/
// Se obtiene el siguiente número de Pedido de venta y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumPedidoVenta(CString &strNextNumPedidoVenta)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Proforma
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMPEDIDO.IsEmpty())
		strNextNumPedidoVenta = m_NUMPEDIDO.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMPEDIDO)+1);
	CString strSql = "UPDATE CONTA SET NUMPEDIDO = '" + strNext + "'";

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

/*******************************************************************************************/
// Se obtiene el siguiente número de Pedido de compra y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumPedidoCompra(CString &strNextNumPedidoCompra)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Pedido
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NPEDCOM.IsEmpty())
		strNextNumPedidoCompra = m_NPEDCOM.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NPEDCOM)+1);
	CString strSql = "UPDATE CONTA SET NPEDCOM = '" + strNext + "'";

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


/*******************************************************************************************/
// Se obtiene el siguiente número de Albarán de venta y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumAlbaran(CString &strNextNumAlbaran)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Albarán
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMALBA.IsEmpty())
		strNextNumAlbaran = m_NUMALBA.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMALBA)+1);
	CString strSql = "UPDATE CONTA SET NUMALBA = '" + strNext + "'";

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

/*******************************************************************************************/
// Se obtiene el siguiente número de Albarán de compra y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumAlbCompra(CString &strNextNumAlbCompra)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Albarán
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMALBB.IsEmpty())
		strNextNumAlbCompra = m_NUMALBB.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMALBB)+1);
	CString strSql = "UPDATE CONTA SET NUMALBB = '" + strNext + "'";

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


/*******************************************************************************************/
// Se obtiene el siguiente número de factura y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumFacturaA(CString &strNextNumFactura)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Albarán
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMFACA.IsEmpty())
		strNextNumFactura = m_NUMFACA.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMFACA)+1);
	CString strSql = "UPDATE CONTA SET NUMFACA = '" + strNext + "'";

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


/*******************************************************************************************/
// Se obtiene el siguiente número de factura y se actualiza el contador al siguiente
/*******************************************************************************************/
HRESULT CConta::GetNextNumFacturaB(CString &strNextNumFactura)
{
	HRESULT hErr = S_OK;

	// Se obtiene el siguiente número de Albarán
	if (!Open(CRecordset::dynaset))
		return -1;

	if (!m_NUMFACB.IsEmpty())
		strNextNumFactura = m_NUMFACB.Trim();

	Close();

	// Se actualiza el contador al siguiente número de Pedido de venta
	CString strNext;
	strNext.Format("%.0f", atof(m_NUMFACB)+1);
	CString strSql = "UPDATE CONTA SET NUMFACB = '" + strNext + "'";

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
