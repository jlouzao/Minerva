// Facturas.h: implementación de la clase CFacturas



// Implementación de CFacturas

// código generado el lunes, 19 de septiembre de 2005, 15:23

#include "stdafx.h"
#include "Facturas.h"
IMPLEMENT_DYNAMIC(CFacturas, CRecordset)

CFacturas::CFacturas(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMFAC = "";
	m_NUMALB = "";
	m_NUMPEDIDO = "";
	m_TIPO = "";
	m_FECHFAC;
	m_FECHALB;
	m_FECHPED;
	m_CUENTA = "";
	m_REPRE = "";
	m_SUBREP = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_DIRENV = "";
	m_SREF = "";
	m_OBSFAC = "";
	m_DCTOS = 0.0;
	m_PP = 0.0;
	m_IVA = 0.0;
	m_TARIFA = "";
	m_COMISION = 0.0;
	m_COMISION2 = 0.0;
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_CENTRO = "";
	m_GRUFAC = "";
	m_DCTOS2 = 0.0;
	m_DCTOS3 = 0.0;
	m_TELEF1 = "";
	m_TELEF2 = "";
	m_ATENCLI = "";
	m_RETENCOM = 0.0;
	m_RETENFIS = 0.0;
	m_nFields = 35;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CFacturas::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CFacturas::GetDefaultSQL()
{
	return _T("[dbo].[FACTURAS]");
}

void CFacturas::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Text(pFX, _T("[TIPO]"), m_TIPO);
	RFX_Date(pFX, _T("[FECHFAC]"), m_FECHFAC);
	RFX_Date(pFX, _T("[FECHALB]"), m_FECHALB);
	RFX_Date(pFX, _T("[FECHPED]"), m_FECHPED);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[REPRE]"), m_REPRE);
	RFX_Text(pFX, _T("[SUBREP]"), m_SUBREP);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Text(pFX, _T("[DIRENV]"), m_DIRENV);
	RFX_Text(pFX, _T("[SREF]"), m_SREF);
	RFX_Text(pFX, _T("[OBSFAC]"), m_OBSFAC);
	RFX_Double(pFX, _T("[DCTOS]"), m_DCTOS);
	RFX_Double(pFX, _T("[PP]"), m_PP);
	RFX_Double(pFX, _T("[IVA]"), m_IVA);
	RFX_Text(pFX, _T("[TARIFA]"), m_TARIFA);
	RFX_Double(pFX, _T("[COMISION]"), m_COMISION);
	RFX_Double(pFX, _T("[COMISION2]"), m_COMISION2);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Text(pFX, _T("[GRUFAC]"), m_GRUFAC);
	RFX_Double(pFX, _T("[DCTOS2]"), m_DCTOS2);
	RFX_Double(pFX, _T("[DCTOS3]"), m_DCTOS3);
	RFX_Text(pFX, _T("[TELEF1]"), m_TELEF1);
	RFX_Text(pFX, _T("[TELEF2]"), m_TELEF2);
	RFX_Text(pFX, _T("[ATENCLI]"), m_ATENCLI);
	RFX_Double(pFX, _T("[RETENCOM]"), m_RETENCOM);
	RFX_Double(pFX, _T("[RETENFIS]"), m_RETENFIS);

}
/////////////////////////////////////////////////////////////////////////////
// CFacturas diagnósticos

#ifdef _DEBUG
void CFacturas::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFacturas::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla FACTURAS                                 */
/****************************************************************************/
HRESULT CFacturas::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara las cadenas con las fechas */
	CString strFechaFactura, strFechaAlbaran, strFechaPedido;

	if (m_FECHFAC == 0)
		strFechaFactura = "NULL";
	else
		strFechaFactura = "'" + m_FECHFAC.Format("%d/%m/%Y") + "'";

	if (m_FECHALB == 0)
		strFechaAlbaran = "NULL";
	else
		strFechaAlbaran = "'" + m_FECHALB.Format("%d/%m/%Y") + "'";

	if (m_FECHPED == 0)
		strFechaPedido = "NULL";
	else
		strFechaPedido = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO FACTURAS (NUMFAC, NUMALB, NUMPEDIDO, TIPO, CUENTA, TARIFA, DCTOS, DCTOS2, DCTOS3, " \
		"PP, IVA, GRUFAC, DIRENV, REPRE, SUBREP, COMISION, COMISION2, FECHFAC, FECHALB, FECHPED, CENTRO, " \
		"SREF, ATENCLI, TELEF1, TELEF2, OBSFAC, FCOBRO, NCOBROS, VTO1, DVTO, DIA1, DIA2, DIA3, RETENCOM, "\
		"RETENFIS) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, '%s', '%s', '%s', '%s'," \
		"%f, %f, %s, %s, %s, '%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f)", 
		m_NUMFAC, m_NUMALB, m_NUMPEDIDO, m_TIPO, m_CUENTA, m_TARIFA, m_DCTOS, m_DCTOS2, m_DCTOS3, m_PP, m_IVA, m_GRUFAC, 
		m_DIRENV, m_REPRE, m_SUBREP, m_COMISION, m_COMISION2, strFechaFactura, strFechaAlbaran, strFechaPedido,
		m_CENTRO, m_SREF, m_ATENCLI, m_TELEF1, m_TELEF2, m_OBSFAC, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, 
		m_DIA1, m_DIA2,	m_DIA3, m_RETENCOM, m_RETENFIS);

	
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
/* Modifica un registro en la tabla FACTURAS                                */
/****************************************************************************/
HRESULT CFacturas::UpdateFactura()
{
	HRESULT hErr = S_OK;

	/* Se prepara las cadenas con las fechas */
	CString strFechaFactura, strFechaAlbaran, strFechaPedido;

	if (m_FECHFAC == 0)
		strFechaFactura = "NULL";
	else
		strFechaFactura = "'" + m_FECHFAC.Format("%d/%m/%Y") + "'";

	if (m_FECHALB == 0)
		strFechaAlbaran = "NULL";
	else
		strFechaAlbaran = "'" + m_FECHALB.Format("%d/%m/%Y") + "'";

	if (m_FECHPED == 0)
		strFechaPedido = "NULL";
	else
		strFechaPedido = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE FACTURAS SET CUENTA = '%s', TARIFA = '%s', DCTOS = %f," \
		"DCTOS2 = %f, DCTOS3 = %f, PP = %f, IVA = %f, GRUFAC = '%s', DIRENV = '%s', REPRE = '%s', SUBREP = '%s', " \
		"COMISION = %f, COMISION2 = %f, FECHFAC = %s, FECHALB = %s, FECHPED = %s, CENTRO = '%s', SREF = '%s', " \
		"ATENCLI = '%s', TELEF1 = '%s', TELEF2 = '%s', OBSFAC = '%s', FCOBRO = '%s', NCOBROS = %f, VTO1 = %f, " \
		"DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, RETENCOM = %f, RETENFIS = %f " \
		"WHERE NUMFAC = '%s'", m_CUENTA, m_TARIFA, m_DCTOS, m_DCTOS2, m_DCTOS3, m_PP, m_IVA,
		m_GRUFAC, m_DIRENV, m_REPRE, m_SUBREP, m_COMISION, m_COMISION2, strFechaFactura, strFechaAlbaran, 
		strFechaPedido, m_CENTRO, m_SREF, m_ATENCLI, m_TELEF1, m_TELEF2, m_OBSFAC, m_FCOBRO, 
		m_NCOBROS, m_VTO1, m_DVTO, m_DIA1, m_DIA2, m_DIA3, m_RETENCOM, m_RETENFIS, m_NUMFAC);

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




