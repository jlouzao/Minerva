// Clientes.h: implementación de la clase CClientes



// Implementación de CClientes

// código generado el lunes, 11 de julio de 2005, 16:00

#include "stdafx.h"
#include "Clientes.h"
IMPLEMENT_DYNAMIC(CClientes, CRecordset)

CClientes::CClientes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CIF = "";
	m_CUENTA = "";
	m_NOMBRE = "";
	m_PP = 0.0;
	m_DCTOS = 0.0;
	m_NOMFICHA = "";
	m_DIRECCION = "";
	m_POBLACION = "";
	m_PROVINCIA = "";
	m_CP = "";
	m_TELEFONO = "";
	m_FAX = "";
	m_IVA = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_DIVAC = 0.0;
	m_MFVAC = 0.0;
	m_DFVAC = 0.0;
	m_MIVAC = 0.0;
	m_AGE = "";
	m_NOMBCO = "";
	m_DIRBCO = "";
	m_POBCO = "";
	m_CTACORR = "";
	m_DIR1 = "";
	m_POB1 = "";
	m_CP1 = "";
	m_PROV1 = "";
	m_DIR2 = "";
	m_POB2 = "";
	m_CP2 = "";
	m_PROV2 = "";
	m_CONTACTO = "";
	m_CARGO = "";
	m_TEL2 = "";
	m_REPRE = "";
	m_REPRE2 = "";
	m_DCTOS2 = 0.0;
	m_DCTOS3 = 0.0;
	m_OBSER1 = "";
	m_OBSER2 = "";
	m_OBSER3 = "";
	m_RIACCLI = 0.0;
	m_RIESCLI = 0.0;
	m_COMISION = 0.0;
	m_COMISION2 = 0.0;
	m_IDIOMA = "";
	m_DIVISA = "";
	m_TRANSPOR = "";
	m_MATRICULA = "";
	m_DNI = "";
	m_TELTRAN = "";
	m_TARIFA = "";
	m_ZONA = "";
	m_COPFAC = 0.0;
	m_CPAIS = "";
	m_PAIS = "";
	m_IVAIDEN = "";
	m_SEGURO = "";
	m_AABONAR = 0.0;
	m_ABOPFAC = "";
	m_NUMCOMPA = "";
	m_NUMEXP = 0.0;
	m_SG = "";
	m_DIRHACIEN = "";
	m_NUMERO = "";
	m_CTRCTA = "";
	m_DC = "";
	m_CC1 = "";
	m_CC2 = "";
	m_CC3 = "";
	m_CPBCO = "";
	m_TIPO = "";
	m_CAMCLI = "";
	m_GRUFAC = "";
	m_EMAIL = "";
	m_CTRANS = "";
	m_DCTOS4 = 0.0;
	m_ERIESCLI = 0.0;
	m_ERIACCLI = 0.0;
	m_IVACLIENTE = 0.0;
	m_NOMFAC = "";
	m_DIREFAC = "";
	m_SGFAC = "";
	m_NUMEFAC = "";
	m_CPFAC = "";
	m_POBFAC = "";
	m_PROVFAC = "";
	m_CPAISFAC = "";
	m_DPAISFAC = "";
	m_FECHALTA;
	m_FECHBAJA;
	m_BLOQUEOCLI = 0;
	m_OBSCOBCLI = "";
	m_PORRETE = 0.0;
	m_CTARETE = "";
	m_RETFISCAL = "";
	m_RETCOMER = "";
	m_IBAN = "";
	m_nFields = 104;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CClientes::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CClientes::GetDefaultSQL()
{
	return _T("[dbo].[CLIENTES]");
}

void CClientes::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CIF]"), m_CIF);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[NOMBRE]"), m_NOMBRE);
	RFX_Double(pFX, _T("[PP]"), m_PP);
	RFX_Double(pFX, _T("[DCTOS]"), m_DCTOS);
	RFX_Text(pFX, _T("[NOMFICHA]"), m_NOMFICHA);
	RFX_Text(pFX, _T("[DIRECCION]"), m_DIRECCION);
	RFX_Text(pFX, _T("[POBLACION]"), m_POBLACION);
	RFX_Text(pFX, _T("[PROVINCIA]"), m_PROVINCIA);
	RFX_Text(pFX, _T("[CP]"), m_CP);
	RFX_Text(pFX, _T("[TELEFONO]"), m_TELEFONO);
	RFX_Text(pFX, _T("[FAX]"), m_FAX);
	RFX_Text(pFX, _T("[IVA]"), m_IVA);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Double(pFX, _T("[DIVAC]"), m_DIVAC);
	RFX_Double(pFX, _T("[MFVAC]"), m_MFVAC);
	RFX_Double(pFX, _T("[DFVAC]"), m_DFVAC);
	RFX_Double(pFX, _T("[MIVAC]"), m_MIVAC);
	RFX_Text(pFX, _T("[AGE]"), m_AGE);
	RFX_Text(pFX, _T("[NOMBCO]"), m_NOMBCO);
	RFX_Text(pFX, _T("[DIRBCO]"), m_DIRBCO);
	RFX_Text(pFX, _T("[POBCO]"), m_POBCO);
	RFX_Text(pFX, _T("[CTACORR]"), m_CTACORR);
	RFX_Text(pFX, _T("[DIR1]"), m_DIR1);
	RFX_Text(pFX, _T("[POB1]"), m_POB1);
	RFX_Text(pFX, _T("[CP1]"), m_CP1);
	RFX_Text(pFX, _T("[PROV1]"), m_PROV1);
	RFX_Text(pFX, _T("[DIR2]"), m_DIR2);
	RFX_Text(pFX, _T("[POB2]"), m_POB2);
	RFX_Text(pFX, _T("[CP2]"), m_CP2);
	RFX_Text(pFX, _T("[PROV2]"), m_PROV2);
	RFX_Text(pFX, _T("[CONTACTO]"), m_CONTACTO);
	RFX_Text(pFX, _T("[CARGO]"), m_CARGO);
	RFX_Text(pFX, _T("[TEL2]"), m_TEL2);
	RFX_Text(pFX, _T("[REPRE]"), m_REPRE);
	RFX_Text(pFX, _T("[REPRE2]"), m_REPRE2);
	RFX_Double(pFX, _T("[DCTOS2]"), m_DCTOS2);
	RFX_Double(pFX, _T("[DCTOS3]"), m_DCTOS3);
	RFX_Text(pFX, _T("[OBSER1]"), m_OBSER1);
	RFX_Text(pFX, _T("[OBSER2]"), m_OBSER2);
	RFX_Text(pFX, _T("[OBSER3]"), m_OBSER3);
	RFX_Double(pFX, _T("[RIACCLI]"), m_RIACCLI);
	RFX_Double(pFX, _T("[RIESCLI]"), m_RIESCLI);
	RFX_Double(pFX, _T("[COMISION]"), m_COMISION);
	RFX_Double(pFX, _T("[COMISION2]"), m_COMISION2);
	RFX_Text(pFX, _T("[IDIOMA]"), m_IDIOMA);
	RFX_Text(pFX, _T("[DIVISA]"), m_DIVISA);
	RFX_Text(pFX, _T("[TRANSPOR]"), m_TRANSPOR);
	RFX_Text(pFX, _T("[MATRICULA]"), m_MATRICULA);
	RFX_Text(pFX, _T("[DNI]"), m_DNI);
	RFX_Text(pFX, _T("[TELTRAN]"), m_TELTRAN);
	RFX_Text(pFX, _T("[TARIFA]"), m_TARIFA);
	RFX_Text(pFX, _T("[ZONA]"), m_ZONA);
	RFX_Double(pFX, _T("[COPFAC]"), m_COPFAC);
	RFX_Text(pFX, _T("[CPAIS]"), m_CPAIS);
	RFX_Text(pFX, _T("[PAIS]"), m_PAIS);
	RFX_Text(pFX, _T("[IVAIDEN]"), m_IVAIDEN);
	RFX_Text(pFX, _T("[SEGURO]"), m_SEGURO);
	RFX_Double(pFX, _T("[AABONAR]"), m_AABONAR);
	RFX_Text(pFX, _T("[ABOPFAC]"), m_ABOPFAC);
	RFX_Text(pFX, _T("[NUMCOMPA]"), m_NUMCOMPA);
	RFX_Double(pFX, _T("[NUMEXP]"), m_NUMEXP);
	RFX_Text(pFX, _T("[SG]"), m_SG);
	RFX_Text(pFX, _T("[DIRHACIEN]"), m_DIRHACIEN);
	RFX_Text(pFX, _T("[NUMERO]"), m_NUMERO);
	RFX_Text(pFX, _T("[CTRCTA]"), m_CTRCTA);
	RFX_Text(pFX, _T("[DC]"), m_DC);
	RFX_Text(pFX, _T("[CC1]"), m_CC1);
	RFX_Text(pFX, _T("[CC2]"), m_CC2);
	RFX_Text(pFX, _T("[CC3]"), m_CC3);
	RFX_Text(pFX, _T("[CPBCO]"), m_CPBCO);
	RFX_Text(pFX, _T("[TIPO]"), m_TIPO);
	RFX_Text(pFX, _T("[CAMCLI]"), m_CAMCLI);
	RFX_Text(pFX, _T("[GRUFAC]"), m_GRUFAC);
	RFX_Text(pFX, _T("[EMAIL]"), m_EMAIL);
	RFX_Text(pFX, _T("[CTRANS]"), m_CTRANS);
	RFX_Double(pFX, _T("[DCTOS4]"), m_DCTOS4);
	RFX_Double(pFX, _T("[ERIESCLI]"), m_ERIESCLI);
	RFX_Double(pFX, _T("[ERIACCLI]"), m_ERIACCLI);
	RFX_Double(pFX, _T("[IVACLIENTE]"), m_IVACLIENTE);
	RFX_Text(pFX, _T("[NOMFAC]"), m_NOMFAC);
	RFX_Text(pFX, _T("[DIREFAC]"), m_DIREFAC);
	RFX_Text(pFX, _T("[SGFAC]"), m_SGFAC);
	RFX_Text(pFX, _T("[NUMEFAC]"), m_NUMEFAC);
	RFX_Text(pFX, _T("[CPFAC]"), m_CPFAC);
	RFX_Text(pFX, _T("[POBFAC]"), m_POBFAC);
	RFX_Text(pFX, _T("[PROVFAC]"), m_PROVFAC);
	RFX_Text(pFX, _T("[CPAISFAC]"), m_CPAISFAC);
	RFX_Text(pFX, _T("[DPAISFAC]"), m_DPAISFAC);
	RFX_Date(pFX, _T("[FECHALTA]"), m_FECHALTA);
	RFX_Date(pFX, _T("[FECHBAJA]"), m_FECHBAJA);
	RFX_Long(pFX, _T("[BLOQUEOCLI]"), m_BLOQUEOCLI);
	RFX_Text(pFX, _T("[OBSCOBCLI]"), m_OBSCOBCLI);
	RFX_Double(pFX, _T("[PORRETE]"), m_PORRETE);
	RFX_Text(pFX, _T("[CTARETE]"), m_CTARETE);
	RFX_Text(pFX, _T("[RETFISCAL]"), m_RETFISCAL);
	RFX_Text(pFX, _T("[RETCOMER]"), m_RETCOMER);
	RFX_Text(pFX, _T("[IBAN]"), m_IBAN);

}
/////////////////////////////////////////////////////////////////////////////
// CClientes diagnósticos

#ifdef _DEBUG
void CClientes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla CLIENTES                                 */
/****************************************************************************/
HRESULT CClientes::Insert()
{
	HRESULT hErr = S_OK;

	/* Se preparan las cadenas con las fechas */
	CString strFechaAlta;
	CString strFechaBaja;

	if (m_FECHALTA == 0)
		strFechaAlta = "NULL";
	else
		strFechaAlta = "'" + m_FECHALTA.Format("%d/%m/%Y") + "'";

	if (m_FECHBAJA == 0)
		strFechaBaja = "NULL";
	else
		strFechaBaja = "'" + m_FECHBAJA.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO CLIENTES (CUENTA, NOMBRE, NOMFICHA, DIRECCION, SG, NUMERO, CP, " \
		"POBLACION, PROVINCIA, CPAIS, PAIS, CIF, TIPO, IVAIDEN, IVA, TELEFONO, TEL2, FAX, " \
		"EMAIL, CONTACTO, IDIOMA, ZONA, OBSER1, REPRE, REPRE2, CTRANS, TELTRAN, " \
		"MATRICULA, DNI, COMISION, COMISION2, FECHALTA, FECHBAJA, DIVISA, FCOBRO, NCOBROS, " \
		"VTO1, DVTO, DIA1, DIA2, DIA3, DIVAC, MIVAC, DFVAC, MFVAC, NUMCOMPA, SEGURO, ERIESCLI, " \
		"ERIACCLI, CC1, CC2, DC, CTACORR, NOMBCO, IBAN, TARIFA, DCTOS2, DCTOS3, DCTOS, PP, " \
		"RETFISCAL, PORRETE, CTARETE, RETCOMER, CTRCTA, GRUFAC, COPFAC, ABOPFAC, AABONAR, " \
		"NOMFAC, DIREFAC, SGFAC, NUMEFAC, CPFAC, POBFAC, PROVFAC, CPAISFAC) " \
        "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', " \
				"'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', " \
				"'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'," \
				"%f, %f, %s, %s, '%s', '%s', %f, %f, %f, %f, " \
				"%f, %f, %f, %f, %f, %f, '%s', '%s', %f, %f, " \
				"'%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %f, %f, " \
				"%f, '%s', %f, '%s', '%s', '%s', '%s', %f, '%s', %f, " \
				"'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", 
		m_CUENTA, m_NOMBRE, m_NOMFICHA, m_DIRECCION, m_SG, m_NUMERO, m_CP, 
		m_POBLACION, m_PROVINCIA, m_CPAIS, m_PAIS, m_CIF, m_TIPO, m_IVAIDEN, m_IVA, m_TELEFONO, m_TEL2, m_FAX, 
		m_EMAIL, m_CONTACTO, m_IDIOMA, m_ZONA, m_OBSER1, m_REPRE, m_REPRE2, m_CTRANS, m_TELTRAN, 
		m_MATRICULA, m_DNI, m_COMISION, m_COMISION2, strFechaAlta, strFechaBaja, m_DIVISA, m_FCOBRO, m_NCOBROS, 
		m_VTO1, m_DVTO, m_DIA1, m_DIA2, m_DIA3, m_DIVAC, m_MIVAC, m_DFVAC, m_MFVAC, m_NUMCOMPA, m_SEGURO, m_ERIESCLI,
		m_ERIACCLI, m_CC1, m_CC2, m_DC, m_CTACORR, m_NOMBCO, m_IBAN, m_TARIFA, m_DCTOS2, m_DCTOS3, m_DCTOS, m_PP, 
		m_RETFISCAL, m_PORRETE, m_CTARETE, m_RETCOMER, m_CTRCTA, m_GRUFAC, m_COPFAC, m_ABOPFAC, m_AABONAR, 
		m_NOMFAC, m_DIREFAC, m_SGFAC, m_NUMEFAC, m_CPFAC, m_POBFAC, m_PROVFAC, m_CPAISFAC);

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
/* Modifica un registro en la tabla CLIENTES                                */
/****************************************************************************/
HRESULT CClientes::UpdateClientes()
{
	HRESULT hErr = S_OK;

	/* Se preparan las cadenas con las fechas */
	CString strFechaAlta;
	CString strFechaBaja;

	if (m_FECHALTA == 0)
		strFechaAlta = "NULL";
	else
		strFechaAlta = "'" + m_FECHALTA.Format("%d/%m/%Y") + "'";

	if (m_FECHBAJA == 0)
		strFechaBaja = "NULL";
	else
		strFechaBaja = "'" + m_FECHBAJA.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE CLIENTES SET NOMBRE = '%s', NOMFICHA = '%s', DIRECCION = '%s', SG = '%s', " \
		"NUMERO = '%s', CP = '%s', POBLACION = '%s', PROVINCIA  = '%s', CPAIS = '%s', PAIS = '%s', " \
		"CIF = '%s', TIPO = '%s', IVAIDEN = '%s', IVA = '%s', TELEFONO = '%s', TEL2 = '%s', FAX = '%s', " \
		"EMAIL = '%s', CONTACTO = '%s', IDIOMA = '%s', ZONA = '%s', OBSER1 = '%s', REPRE = '%s', " \
		"REPRE2 = '%s', CTRANS = '%s', TELTRAN = '%s', MATRICULA = '%s', DNI = '%s', COMISION = %f, " \
		"COMISION2 = %f, FECHALTA = %s, FECHBAJA = %s, DIVISA  = '%s', FCOBRO = '%s', NCOBROS = %f, " \
		"VTO1 = %f, DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, DIVAC = %f, MIVAC = %f, DFVAC = %f, " \
		"MFVAC = %f, NUMCOMPA = '%s', SEGURO = '%s', ERIESCLI = %f, ERIACCLI = %f, CC1 = '%s', " \
		"CC2 = '%s', DC = '%s', CTACORR = '%s', NOMBCO = '%s', IBAN = '%s', TARIFA = '%s', " \
		"DCTOS2 = %f, DCTOS3 = %f, DCTOS = %f, PP = %f, RETFISCAL = '%s', PORRETE = %f, " \
		"CTARETE = '%s', RETCOMER = '%s', CTRCTA = '%s', GRUFAC = '%s', COPFAC = %f, ABOPFAC = '%s', " \
		"AABONAR = %f, NOMFAC = '%s', DIREFAC = '%s', SGFAC = '%s', NUMEFAC = '%s', CPFAC = '%s', " \
		"POBFAC = '%s', PROVFAC = '%s', CPAISFAC = '%s' WHERE CUENTA LIKE '%s'",
		m_NOMBRE, m_NOMFICHA, m_DIRECCION, m_SG, m_NUMERO, m_CP, 
		m_POBLACION, m_PROVINCIA, m_CPAIS, m_PAIS, m_CIF, m_TIPO, m_IVAIDEN, m_IVA, m_TELEFONO, m_TEL2, m_FAX, 
		m_EMAIL, m_CONTACTO, m_IDIOMA, m_ZONA, m_OBSER1, m_REPRE, m_REPRE2, m_CTRANS, m_TELTRAN, 
		m_MATRICULA, m_DNI, m_COMISION, m_COMISION2, strFechaAlta, strFechaBaja, m_DIVISA, m_FCOBRO, m_NCOBROS, 
		m_VTO1, m_DVTO, m_DIA1, m_DIA2, m_DIA3, m_DIVAC, m_MIVAC, m_DFVAC, m_MFVAC, m_NUMCOMPA, m_SEGURO, m_ERIESCLI,
		m_ERIACCLI, m_CC1, m_CC2, m_DC, m_CTACORR, m_NOMBCO, m_IBAN, m_TARIFA, m_DCTOS2, m_DCTOS3, m_DCTOS, m_PP, 
		m_RETFISCAL, m_PORRETE, m_CTARETE, m_RETCOMER, m_CTRCTA, m_GRUFAC, m_COPFAC, m_ABOPFAC, m_AABONAR, 
		m_NOMFAC, m_DIREFAC, m_SGFAC, m_NUMEFAC, m_CPFAC, m_POBFAC, m_PROVFAC, m_CPAISFAC, m_CUENTA);

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


