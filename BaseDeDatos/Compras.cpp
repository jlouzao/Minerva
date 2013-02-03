// Compras.h: implementación de la clase CCompras



// Implementación de CCompras

// código generado el miércoles, 10 de agosto de 2005, 12:52

#include "stdafx.h"
#include "Compras.h"
IMPLEMENT_DYNAMIC(CCompras, CRecordset)

CCompras::CCompras(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NPEDCOM = "";
	m_NUMFAC = "";
	m_NUMALBCO = "";
	m_FECHPED;
	m_FECHALBCO;
	m_FECHFAC;
	m_CUENTA = "";
	m_ALMACEN = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_DIRENV = "";
	m_DIRFAC = "";
	m_SREF = "";
	m_OBSPED = "";
	m_OBSALBCO = "";
	m_OBSFAC = "";
	m_DCTOS = 0.0;
	m_PP = 0.0;
	m_DIVISA = "";
	m_IDIOMA = "";
	m_PUERTO = "";
	m_TIPO = "";
	m_PARTIDA = "";
	m_TRANS = "";
	m_MERCAN = "";
	m_EXPORTA = "";
	m_ARTI = "";
	m_DESARTI = "";
	m_CAM1 = "";
	m_CAM2 = "";
	m_CAM3 = "";
	m_CANTI = 0.0;
	m_UNIDAD = "";
	m_TARIFA = "";
	m_IMPOARTI = 0.0;
	m_DTOARTI = 0.0;
	m_COMARTI = 0.0;
	m_IVARTI = 0.0;
	m_IVA = "";
	m_CANTIFAC = 0.0;
	m_COMISION = 0.0;
	m_COMISION2 = 0.0;
	m_TRANSPOR = "";
	m_DNI = "";
	m_MATRICULA = "";
	m_BULTOS = "";
	m_MUESTRAS = FALSE;
	m_CAMBIO = 0.0;
	m_INCOTERM = "";
	m_EMBALAJE = "";
	m_CONTAINERS = "";
	m_CAJAS = 0.0;
	m_PORTES = "";
	m_PESNETO = 0.0;
	m_PESBRUTO = 0.0;
	m_ESTADO = "";
	m_SUPFAC = FALSE;
	m_IMPABO = 0.0;
	m_LCACE = "";
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_TOTALPAL = 0.0;
	m_CANTRANS = 0.0;
	m_TRANSEMP = "";
	m_CENTRO = "";
	m_DESARTI2 = "";
	m_DESARTI3 = "";
	m_IMPODIVI = 0.0;
	m_SUPLEM = 0.0;
	m_DSUPLEM = "";
	m_CAMCOMPRA = "";
	m_DCTO2 = 0.0;
	m_DCTO3 = 0.0;
	m_CAMCOM2 = "";
	m_FECHENT;
	m_EUROS = 0.0;
	m_DTOARTI2 = 0.0;
	m_DTOARTI3 = 0.0;
	m_DESARMEMO = "";
	m_CLAVE = 0.0;
	m_nFields = 83;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CCompras::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CCompras::GetDefaultSQL()
{
	return _T("[dbo].[COMPRAS]");
}

void CCompras::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado

	// ORDEN ORIGINAL
	/*RFX_Text(pFX, _T("[NPEDCOM]"), m_NPEDCOM);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALBCO]"), m_NUMALBCO);
	RFX_Date(pFX, _T("[FECHPED]"), m_FECHPED);
	RFX_Date(pFX, _T("[FECHALBCO]"), m_FECHALBCO);
	RFX_Date(pFX, _T("[FECHFAC]"), m_FECHFAC);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);*/

	RFX_Text(pFX, _T("[NPEDCOM]"), m_NPEDCOM);
	//RFX_Double(pFX, _T("[DCTOGEN]"), m_DCTOGEN);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALBCO]"), m_NUMALBCO);
	RFX_Date(pFX, _T("[FECHPED]"), m_FECHPED);
	RFX_Date(pFX, _T("[FECHALBCO]"), m_FECHALBCO);
	RFX_Date(pFX, _T("[FECHFAC]"), m_FECHFAC);
	RFX_Text(pFX, _T("[ALMACEN]"), m_ALMACEN);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Text(pFX, _T("[DIRENV]"), m_DIRENV);
	RFX_Text(pFX, _T("[DIRFAC]"), m_DIRFAC);
	RFX_Text(pFX, _T("[SREF]"), m_SREF);
	RFX_Text(pFX, _T("[OBSPED]"), m_OBSPED);
	RFX_Text(pFX, _T("[OBSALBCO]"), m_OBSALBCO);
	RFX_Text(pFX, _T("[OBSFAC]"), m_OBSFAC);
	RFX_Double(pFX, _T("[DCTOS]"), m_DCTOS);
	RFX_Double(pFX, _T("[PP]"), m_PP);
	RFX_Text(pFX, _T("[DIVISA]"), m_DIVISA);
	RFX_Text(pFX, _T("[IDIOMA]"), m_IDIOMA);
	RFX_Text(pFX, _T("[PUERTO]"), m_PUERTO);
	RFX_Text(pFX, _T("[TIPO]"), m_TIPO);
	RFX_Text(pFX, _T("[PARTIDA]"), m_PARTIDA);
	RFX_Text(pFX, _T("[TRANS]"), m_TRANS);
	RFX_Text(pFX, _T("[MERCAN]"), m_MERCAN);
	RFX_Text(pFX, _T("[EXPORTA]"), m_EXPORTA);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Text(pFX, _T("[CAM1]"), m_CAM1);
	RFX_Text(pFX, _T("[CAM2]"), m_CAM2);
	RFX_Text(pFX, _T("[CAM3]"), m_CAM3);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Text(pFX, _T("[UNIDAD]"), m_UNIDAD);
	RFX_Text(pFX, _T("[TARIFA]"), m_TARIFA);
	RFX_Double(pFX, _T("[IMPOARTI]"), m_IMPOARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Double(pFX, _T("[COMARTI]"), m_COMARTI);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Text(pFX, _T("[IVA]"), m_IVA);
	RFX_Double(pFX, _T("[CANTIFAC]"), m_CANTIFAC);
	RFX_Double(pFX, _T("[COMISION]"), m_COMISION);
	RFX_Double(pFX, _T("[COMISION2]"), m_COMISION2);
	RFX_Text(pFX, _T("[TRANSPOR]"), m_TRANSPOR);
	RFX_Text(pFX, _T("[DNI]"), m_DNI);
	RFX_Text(pFX, _T("[MATRICULA]"), m_MATRICULA);
	RFX_Text(pFX, _T("[BULTOS]"), m_BULTOS);
	RFX_Bool(pFX, _T("[MUESTRAS]"), m_MUESTRAS);
	RFX_Double(pFX, _T("[CAMBIO]"), m_CAMBIO);
	RFX_Text(pFX, _T("[INCOTERM]"), m_INCOTERM);
	RFX_Text(pFX, _T("[EMBALAJE]"), m_EMBALAJE);
	RFX_Text(pFX, _T("[CONTAINERS]"), m_CONTAINERS);
	RFX_Double(pFX, _T("[CAJAS]"), m_CAJAS);
	RFX_Text(pFX, _T("[PORTES]"), m_PORTES);
	RFX_Double(pFX, _T("[PESNETO]"), m_PESNETO);
	RFX_Double(pFX, _T("[PESBRUTO]"), m_PESBRUTO);
	RFX_Text(pFX, _T("[ESTADO]"), m_ESTADO);
	RFX_Bool(pFX, _T("[SUPFAC]"), m_SUPFAC);
	RFX_Double(pFX, _T("[IMPABO]"), m_IMPABO);
	RFX_Text(pFX, _T("[LCACE]"), m_LCACE);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Double(pFX, _T("[TOTALPAL]"), m_TOTALPAL);
	RFX_Double(pFX, _T("[CANTRANS]"), m_CANTRANS);
	RFX_Text(pFX, _T("[TRANSEMP]"), m_TRANSEMP);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Text(pFX, _T("[DESARTI2]"), m_DESARTI2);
	RFX_Text(pFX, _T("[DESARTI3]"), m_DESARTI3);
	RFX_Double(pFX, _T("[IMPODIVI]"), m_IMPODIVI);
	RFX_Double(pFX, _T("[SUPLEM]"), m_SUPLEM);
	RFX_Text(pFX, _T("[DSUPLEM]"), m_DSUPLEM);
	RFX_Text(pFX, _T("[CAMCOMPRA]"), m_CAMCOMPRA);
	RFX_Double(pFX, _T("[DCTO2]"), m_DCTO2);
	RFX_Double(pFX, _T("[DCTO3]"), m_DCTO3);
	RFX_Text(pFX, _T("[CAMCOM2]"), m_CAMCOM2);
	RFX_Date(pFX, _T("[FECHENT]"), m_FECHENT);
	RFX_Double(pFX, _T("[EUROS]"), m_EUROS);
	RFX_Double(pFX, _T("[DTOARTI2]"), m_DTOARTI2);
	RFX_Double(pFX, _T("[DTOARTI3]"), m_DTOARTI3);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);
	RFX_Double(pFX, _T("[CLAVE]"), m_CLAVE);

}
/////////////////////////////////////////////////////////////////////////////
// CCompras diagnósticos

#ifdef _DEBUG
void CCompras::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCompras::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla COMPRAS                                  */
/****************************************************************************/
HRESULT CCompras::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaCompra;

	if (m_FECHPED == 0)
		strFechaCompra = "NULL";
	else
		strFechaCompra = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO COMPRAS (NPEDCOM, EXPORTA, CUENTA, ALMACEN, FCOBRO, NCOBROS, VTO1, DVTO, " \
		"DIA1, DIA2, DIA3, DCTOS, DCTO2, DCTO3, PP, FECHPED, CENTRO, SREF, OBSPED)" \
		"VALUES ('%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %s, '%s', '%s', '%s')",
		m_NPEDCOM, m_EXPORTA, m_CUENTA, m_ALMACEN, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, m_DIA1, m_DIA2,
		m_DIA3,	m_DCTOS, m_DCTO2, m_DCTO3, m_PP, strFechaCompra, m_CENTRO, m_SREF, m_OBSPED);
		

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
/* Modifica un registro en la tabla COMPRAS                              */
/****************************************************************************/
HRESULT CCompras::UpdateCompra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaCompra;

	if (m_FECHPED == 0)
		strFechaCompra = "NULL";
	else
		strFechaCompra = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";


	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE COMPRAS SET EXPORTA = '%s', CUENTA = '%s', ALMACEN = '%s', FCOBRO = '%s', " \
		"NCOBROS = %f, VTO1 = %f, DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, DCTOS = %f," \
		"DCTO2 = %f, DCTO3 = %f, PP = %f, FECHPED = %s, CENTRO = '%s', SREF = '%s', " \
		"OBSPED = '%s' WHERE NPEDCOM = '%s'", m_EXPORTA, m_CUENTA, m_ALMACEN, m_FCOBRO, m_NCOBROS, 
		m_VTO1, m_DVTO, m_DIA1, m_DIA2, m_DIA3, m_DCTOS, m_DCTO2, m_DCTO3, m_PP, 
		strFechaCompra, m_CENTRO, m_SREF, m_OBSPED, m_NPEDCOM);

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
