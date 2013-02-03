// Pedidos.h: implementación de la clase CPedidos



// Implementación de CPedidos

// código generado el miércoles, 10 de agosto de 2005, 11:28

#include "stdafx.h"
#include "Pedidos.h"
IMPLEMENT_DYNAMIC(CPedidos, CRecordset)

CPedidos::CPedidos(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMPEDIDO = "";
	m_NUMFAC = "";
	m_NUMALB = "";
	m_FECHPED;
	m_FECHPRE;
	m_FECHALB;
	m_FECHFAC;
	m_FECHENT;
	m_CUENTA = "";
	m_ALMACEN = "";
	m_REVISADO = 0;
	m_REPRE = "";
	m_SUBREP = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_DIRENV = "";
	m_DIRFAC = "";
	m_SREF = "";
	m_OBSPED = "";
	m_OBSALB = "";
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
	//m_IVA = "";
	m_IVA = 0.0;
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
	m_CERTIF = "";
	m_COMER = "";
	m_ADUAN = "";
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
	m_FLETES = 0.0;
	m_CENTRO = "";
	m_DESARTI2 = "";
	m_DESARTI3 = "";
	m_IMPODIVI = 0.0;
	m_RECARGO = 0.0;
	m_CAMVEN = "";
	m_GRUFAC = "";
	m_RUTRAN = "";
	m_SUPLEM = 0.0;
	m_DSUPLEM = "";
	m_DCTOS2 = 0.0;
	m_DCTOS3 = 0.0;
	m_DCTOS4 = 0.0;
	m_CAMCVEN = "";
	m_CAMNVEN = 0.0;
	m_EUROS = 0.0;
	m_DTOARTI2 = 0.0;
	m_DTOARTI3 = 0.0;
	m_DESARMEMO = "";
	m_NOMCONTA = "";
	m_CIFCONTA = "";
	m_DIRCONTA = "";
	m_POBCONTA = "";
	m_PROVCONTA = "";
	m_CPCONTA = "";
	m_TELEF1 = "";
	m_TELEF2 = "";
	m_IMPORI = 0.0;
	m_CONTRATO = "";
	m_ALQUILER = "";
	m_TIPOALQ = "";
	m_OBSERV = "";
	m_FECINIALQ;
	m_FECFINALQ;
	m_DIASFAC = 0.0;
	m_PREPMATE = "";
	m_FECALB2;
	m_MARCA = "";
	m_DIASOLD = 0.0;
	m_PREFAC = FALSE;
	m_FECPREF;
	m_IMPOPREF = 0.0;
	m_DIAFACPREF = 0.0;
	m_MODIPREF = "";
	m_LINPTEPRE = "";
	m_EIMPOPREF = 0.0;
	m_ATENCLI = "";
	m_CCOMPET = "";
	m_FECHADU;
	m_CLAVE = 0.0;
	m_RETENCOM = 0.0;
	m_RETENFIS = 0.0;
	m_EUROSUV = 0.0;
	m_nFields = 129;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CPedidos::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CPedidos::GetDefaultSQL()
{
	return _T("[dbo].[pedidos]");
}

void CPedidos::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado

	// ORDEN ORIGINAL
/*	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Date(pFX, _T("[FECHPED]"), m_FECHPED);
	RFX_Date(pFX, _T("[FECHPRE]"), m_FECHPRE);
	RFX_Date(pFX, _T("[FECHALB]"), m_FECHALB);
	RFX_Date(pFX, _T("[FECHFAC]"), m_FECHFAC);
	RFX_Date(pFX, _T("[FECHENT]"), m_FECHENT);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);*/

	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[NUMFAC]"), m_NUMFAC);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Date(pFX, _T("[FECHPED]"), m_FECHPED);
	RFX_Date(pFX, _T("[FECHPRE]"), m_FECHPRE);
	RFX_Date(pFX, _T("[FECHALB]"), m_FECHALB);
	RFX_Date(pFX, _T("[FECHFAC]"), m_FECHFAC);
	RFX_Date(pFX, _T("[FECHENT]"), m_FECHENT);

	RFX_Text(pFX, _T("[ALMACEN]"), m_ALMACEN);
	RFX_Long(pFX, _T("[REVISADO]"), m_REVISADO);
	RFX_Text(pFX, _T("[REPRE]"), m_REPRE);
	RFX_Text(pFX, _T("[SUBREP]"), m_SUBREP);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Text(pFX, _T("[DIRENV]"), m_DIRENV);
	RFX_Text(pFX, _T("[DIRFAC]"), m_DIRFAC);
	RFX_Text(pFX, _T("[SREF]"), m_SREF);
	RFX_Text(pFX, _T("[OBSPED]"), m_OBSPED);
	RFX_Text(pFX, _T("[OBSALB]"), m_OBSALB);
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
	//RFX_Text(pFX, _T("[IVA]"), m_IVA);
	RFX_Double(pFX, _T("[IVA]"), m_IVA);
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
	RFX_Text(pFX, _T("[CERTIF]"), m_CERTIF);
	RFX_Text(pFX, _T("[COMER]"), m_COMER);
	RFX_Text(pFX, _T("[ADUAN]"), m_ADUAN);
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
	RFX_Double(pFX, _T("[FLETES]"), m_FLETES);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Text(pFX, _T("[DESARTI2]"), m_DESARTI2);
	RFX_Text(pFX, _T("[DESARTI3]"), m_DESARTI3);
	RFX_Double(pFX, _T("[IMPODIVI]"), m_IMPODIVI);
	RFX_Double(pFX, _T("[RECARGO]"), m_RECARGO);
	RFX_Text(pFX, _T("[CAMVEN]"), m_CAMVEN);
	RFX_Text(pFX, _T("[GRUFAC]"), m_GRUFAC);
	RFX_Text(pFX, _T("[RUTRAN]"), m_RUTRAN);
	RFX_Double(pFX, _T("[SUPLEM]"), m_SUPLEM);
	RFX_Text(pFX, _T("[DSUPLEM]"), m_DSUPLEM);
	RFX_Double(pFX, _T("[DCTOS2]"), m_DCTOS2);
	RFX_Double(pFX, _T("[DCTOS3]"), m_DCTOS3);
	RFX_Double(pFX, _T("[DCTOS4]"), m_DCTOS4);
	RFX_Text(pFX, _T("[CAMCVEN]"), m_CAMCVEN);
	RFX_Double(pFX, _T("[CAMNVEN]"), m_CAMNVEN);
	RFX_Double(pFX, _T("[EUROS]"), m_EUROS);
	RFX_Double(pFX, _T("[DTOARTI2]"), m_DTOARTI2);
	RFX_Double(pFX, _T("[DTOARTI3]"), m_DTOARTI3);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);
	RFX_Text(pFX, _T("[NOMCONTA]"), m_NOMCONTA);
	RFX_Text(pFX, _T("[CIFCONTA]"), m_CIFCONTA);
	RFX_Text(pFX, _T("[DIRCONTA]"), m_DIRCONTA);
	RFX_Text(pFX, _T("[POBCONTA]"), m_POBCONTA);
	RFX_Text(pFX, _T("[PROVCONTA]"), m_PROVCONTA);
	RFX_Text(pFX, _T("[CPCONTA]"), m_CPCONTA);
	RFX_Text(pFX, _T("[TELEF1]"), m_TELEF1);
	RFX_Text(pFX, _T("[TELEF2]"), m_TELEF2);
	RFX_Double(pFX, _T("[IMPORI]"), m_IMPORI);
	RFX_Text(pFX, _T("[CONTRATO]"), m_CONTRATO);
	RFX_Text(pFX, _T("[ALQUILER]"), m_ALQUILER);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Text(pFX, _T("[OBSERV]"), m_OBSERV);
	RFX_Date(pFX, _T("[FECINIALQ]"), m_FECINIALQ);
	RFX_Date(pFX, _T("[FECFINALQ]"), m_FECFINALQ);
	RFX_Double(pFX, _T("[DIASFAC]"), m_DIASFAC);
	RFX_Text(pFX, _T("[PREPMATE]"), m_PREPMATE);
	RFX_Date(pFX, _T("[FECALB2]"), m_FECALB2);
	RFX_Text(pFX, _T("[MARCA]"), m_MARCA);
	RFX_Double(pFX, _T("[DIASOLD]"), m_DIASOLD);
	RFX_Bool(pFX, _T("[PREFAC]"), m_PREFAC);
	RFX_Date(pFX, _T("[FECPREF]"), m_FECPREF);
	RFX_Double(pFX, _T("[IMPOPREF]"), m_IMPOPREF);
	RFX_Double(pFX, _T("[DIAFACPREF]"), m_DIAFACPREF);
	RFX_Text(pFX, _T("[MODIPREF]"), m_MODIPREF);
	RFX_Text(pFX, _T("[LINPTEPRE]"), m_LINPTEPRE);
	RFX_Double(pFX, _T("[EIMPOPREF]"), m_EIMPOPREF);
	RFX_Text(pFX, _T("[ATENCLI]"), m_ATENCLI);
	RFX_Text(pFX, _T("[CCOMPET]"), m_CCOMPET);
	RFX_Date(pFX, _T("[FECHADU]"), m_FECHADU);
	RFX_Double(pFX, _T("[CLAVE]"), m_CLAVE);
	RFX_Double(pFX, _T("[RETENCOM]"), m_RETENCOM);
	RFX_Double(pFX, _T("[RETENFIS]"), m_RETENFIS);
	RFX_Double(pFX, _T("[EUROSUV]"), m_EUROSUV);

}
/////////////////////////////////////////////////////////////////////////////
// CPedidos diagnósticos

#ifdef _DEBUG
void CPedidos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPedidos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
CPedidos& CPedidos::operator =(CPedidos& Other)
{
	m_pDatabase = Other.m_pDatabase;
	m_CLAVE = Other.m_CLAVE;
	m_NUMPEDIDO = Other.m_NUMPEDIDO;
	m_NUMALB = Other.m_NUMALB; 
	m_EXPORTA = Other.m_EXPORTA;
	m_CUENTA = Other.m_CUENTA;
	m_ALMACEN = Other.m_ALMACEN;
	m_ESTADO = Other.m_ESTADO;
	m_REVISADO = Other.m_REVISADO;
	m_TARIFA = Other.m_TARIFA;
	m_DCTOS = Other.m_DCTOS;
	m_DCTOS2 = Other.m_DCTOS2;
	m_DCTOS3 = Other.m_DCTOS3;
	m_PP = Other. m_PP;
	m_IVA = Other. m_IVA;
	m_GRUFAC = Other.m_GRUFAC;
	m_DIRENV = Other.m_DIRENV;
	m_REPRE = Other.m_REPRE;
	m_SUBREP = Other.m_SUBREP;
	m_COMISION = Other.m_COMISION;
	m_COMISION2 = Other.m_COMISION2;
	m_FECHPED = Other.m_FECHPED;
	m_CENTRO = Other.m_CENTRO;
	m_SREF = Other.m_SREF;
	m_ATENCLI = Other.m_ATENCLI;
	m_TELEF1 = Other.m_TELEF1;
	m_TELEF2 = Other.m_TELEF2;
	m_OBSPED = Other.m_OBSPED;
	m_FCOBRO = Other.m_FCOBRO; 
	m_NCOBROS = Other.m_NCOBROS;
	m_VTO1 = Other.m_VTO1;
	m_DVTO = Other.m_DVTO;
	m_DIA1 = Other.m_DIA1;
	m_DIA2 = Other.m_DIA2;
	m_DIA3 = Other.m_DIA3;
	m_RETENCOM = Other.m_RETENCOM;
	m_RETENFIS = Other.m_RETENFIS;

	return(*this);
}

/****************************************************************************/
/* Inserta un registro en la tabla PEDIDOS                                  */
/****************************************************************************/
HRESULT CPedidos::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaPedido;

	if (m_FECHPED == 0)
		strFechaPedido = "NULL";
	else
		strFechaPedido = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO PEDIDOS (NUMPEDIDO, EXPORTA, TIPO, CUENTA, ALMACEN, ESTADO, TARIFA, DCTOS, DCTOS2, DCTOS3, " \
		"PP, IVA, GRUFAC, DIRENV, REPRE, SUBREP, COMISION, COMISION2, FECHPED, CENTRO, " \
		"SREF, ATENCLI, TELEF1, TELEF2, OBSPED, FCOBRO, NCOBROS, VTO1, DVTO, DIA1, DIA2, DIA3, RETENCOM, "\
		"RETENFIS) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, '%s', '%s', '%s', '%s'," \
		"%f, %f, %s, '%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f)", 
		m_NUMPEDIDO, m_EXPORTA, m_TIPO, m_CUENTA, m_ALMACEN, m_ESTADO, m_TARIFA, m_DCTOS, m_DCTOS2, m_DCTOS3, m_PP, m_IVA, m_GRUFAC, 
		m_DIRENV, m_REPRE, m_SUBREP, m_COMISION, m_COMISION2, strFechaPedido, m_CENTRO, m_SREF, 
		m_ATENCLI, m_TELEF1, m_TELEF2, m_OBSPED, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, m_DIA1, m_DIA2,
		m_DIA3, m_RETENCOM, m_RETENFIS);
		

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
/* Modifica un registro en la tabla PEDIDDOS                                */
/****************************************************************************/
HRESULT CPedidos::UpdatePedido()
{
	HRESULT hErr = S_OK;

	/* Se prepara la cadena con la fecha */
	CString strFechaPedido;

	if (m_FECHPED == 0)
		strFechaPedido = "NULL";
	else
		strFechaPedido = "'" + m_FECHPED.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE PEDIDOS SET EXPORTA = '%s', TIPO = '%s', CUENTA = '%s', ALMACEN = '%s', TARIFA = '%s', DCTOS = %f," \
		"DCTOS2 = %f, DCTOS3 = %f, PP = %f, IVA = %f, GRUFAC = '%s', DIRENV = '%s', REPRE = '%s', SUBREP = '%s', " \
		"COMISION = %f, COMISION2 = %f, FECHPED = %s, CENTRO = '%s', SREF = '%s', " \
		"ATENCLI = '%s', TELEF1 = '%s', TELEF2 = '%s', OBSPED = '%s', FCOBRO = '%s', NCOBROS = %f, VTO1 = %f, " \
		"DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, RETENCOM = %f, RETENFIS = %f " \
		"WHERE NUMPEDIDO = '%s'", m_EXPORTA, m_TIPO, m_CUENTA, m_ALMACEN, m_TARIFA, m_DCTOS, m_DCTOS2, m_DCTOS3, m_PP, m_IVA,
		m_GRUFAC, m_DIRENV, m_REPRE, m_SUBREP, m_COMISION, m_COMISION2, strFechaPedido, 
		m_CENTRO, m_SREF, m_ATENCLI, m_TELEF1, m_TELEF2, m_OBSPED, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, 
		m_DIA1, m_DIA2, m_DIA3, m_RETENCOM, m_RETENFIS, m_NUMPEDIDO);

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
/* Actualiza el número de albarán que sa creado a partir del pedido         */
/****************************************************************************/
HRESULT CPedidos::UpdateNumAlbaran()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE PEDIDOS SET NUMALB = '%s' WHERE NUMPEDIDO = '%s'", m_NUMALB, m_NUMPEDIDO);

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
/* Marca el pedido como revisado                                            */
/****************************************************************************/
HRESULT CPedidos::MarcaRevisado()
{	
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE PEDIDOS SET REVISADO = 1 WHERE NUMPEDIDO = '%s'", m_NUMPEDIDO);

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
/* Actualiza el estado del Pedido (Sin Facturar, Pendiente, Facturado       */                               
/****************************************************************************/
HRESULT CPedidos::UpdateEstado()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE PEDIDOS SET ESTADO = '%s' WHERE NUMPEDIDO LIKE '%s'", 
		m_ESTADO, m_NUMPEDIDO);

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

