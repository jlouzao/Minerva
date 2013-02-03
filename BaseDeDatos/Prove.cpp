// Prove.h: implementación de la clase CProve



// Implementación de CProve

// código generado el viernes, 08 de julio de 2005, 10:07

#include "stdafx.h"
#include "Prove.h"
IMPLEMENT_DYNAMIC(CProve, CRecordset)

CProve::CProve(CDatabase* pdb)
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
	m_POBCO = "";
	m_NOMBCO = "";
	m_AGE = "";
	m_DIRBCO = "";
	m_RETENCION = "";
	m_CONTACTO = "";
	m_CARGO = "";
	m_TEL2 = "";
	m_COMISION = 0.0;
	m_OBSER1 = "";
	m_OBSER2 = "";
	m_OBSER3 = "";
	m_IDIOMA = "";
	m_DIVISA = "";
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_IVAIDEN = "";
	m_AABONAR = 0.0;
	m_DIVAC = 0.0;
	m_MIVAC = 0.0;
	m_DFVAC = 0.0;
	m_MFVAC = 0.0;
	m_SG = "";
	m_DIRHACIEN = "";
	m_NUMERO = "";
	m_CTACORR = "";
	m_DC = "";
	m_CC1 = "";
	m_CC2 = "";
	m_CC3 = "";
	m_CPBCO = "";
	m_CPAIS = "";
	m_TIPO = "";
	m_EMAIL = "";
	m_DCTO2 = 0.0;/////////////////////////////
	m_DCTO3 = 0.0;/////////////////////////////
	m_CTABANCO = "";
	m_CAMPROVE1 = "";
	m_CAMPROVE2 = "";
	m_PLAZOENT = 0.0;
	m_FECHALTA;
	m_FECHBAJA;
	m_PORRETE = 0.0;
	m_CTARETE = "";
	m_CTACOM = "";
	m_IBAN = "";
	m_nFields = 64;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CProve::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CProve::GetDefaultSQL()
{
	return _T("[dbo].[PROVE]");
}

void CProve::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[POBCO]"), m_POBCO);
	RFX_Text(pFX, _T("[NOMBCO]"), m_NOMBCO);
	RFX_Text(pFX, _T("[AGE]"), m_AGE);
	RFX_Text(pFX, _T("[DIRBCO]"), m_DIRBCO);
	RFX_Text(pFX, _T("[RETENCION]"), m_RETENCION);
	RFX_Text(pFX, _T("[CONTACTO]"), m_CONTACTO);
	RFX_Text(pFX, _T("[CARGO]"), m_CARGO);
	RFX_Text(pFX, _T("[TEL2]"), m_TEL2);
	RFX_Double(pFX, _T("[COMISION]"), m_COMISION);
	RFX_Text(pFX, _T("[OBSER1]"), m_OBSER1);
	RFX_Text(pFX, _T("[OBSER2]"), m_OBSER2);
	RFX_Text(pFX, _T("[OBSER3]"), m_OBSER3);
	RFX_Text(pFX, _T("[IDIOMA]"), m_IDIOMA);
	RFX_Text(pFX, _T("[DIVISA]"), m_DIVISA);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Text(pFX, _T("[IVAIDEN]"), m_IVAIDEN);
	RFX_Double(pFX, _T("[AABONAR]"), m_AABONAR);
	RFX_Double(pFX, _T("[DIVAC]"), m_DIVAC);
	RFX_Double(pFX, _T("[MIVAC]"), m_MIVAC);
	RFX_Double(pFX, _T("[DFVAC]"), m_DFVAC);
	RFX_Double(pFX, _T("[MFVAC]"), m_MFVAC);
	RFX_Text(pFX, _T("[SG]"), m_SG);
	RFX_Text(pFX, _T("[DIRHACIEN]"), m_DIRHACIEN);
	RFX_Text(pFX, _T("[NUMERO]"), m_NUMERO);
	RFX_Text(pFX, _T("[CTACORR]"), m_CTACORR);
	RFX_Text(pFX, _T("[DC]"), m_DC);
	RFX_Text(pFX, _T("[CC1]"), m_CC1);
	RFX_Text(pFX, _T("[CC2]"), m_CC2);
	RFX_Text(pFX, _T("[CC3]"), m_CC3);
	RFX_Text(pFX, _T("[CPBCO]"), m_CPBCO);
	RFX_Text(pFX, _T("[CPAIS]"), m_CPAIS);
	RFX_Text(pFX, _T("[TIPO]"), m_TIPO);
	RFX_Text(pFX, _T("[EMAIL]"), m_EMAIL);
	RFX_Double(pFX, _T("[DCTO2]"), m_DCTO2);///////////////////////////////////////////
	RFX_Double(pFX, _T("[DCTO3]"), m_DCTO3);///////////////////////////////////////////
	RFX_Text(pFX, _T("[CTABANCO]"), m_CTABANCO);
	RFX_Text(pFX, _T("[CAMPROVE1]"), m_CAMPROVE1);
	RFX_Text(pFX, _T("[CAMPROVE2]"), m_CAMPROVE2);
	RFX_Double(pFX, _T("[PLAZOENT]"), m_PLAZOENT);
	RFX_Date(pFX, _T("[FECHALTA]"), m_FECHALTA);
	RFX_Date(pFX, _T("[FECHBAJA]"), m_FECHBAJA);
	RFX_Double(pFX, _T("[PORRETE]"), m_PORRETE);
	RFX_Text(pFX, _T("[CTARETE]"), m_CTARETE);
	RFX_Text(pFX, _T("[CTACOM]"), m_CTACOM);
	RFX_Text(pFX, _T("[IBAN]"), m_IBAN);

}
/////////////////////////////////////////////////////////////////////////////
// CProve diagnósticos

#ifdef _DEBUG
void CProve::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProve::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla de proveedores                           */
/****************************************************************************/
HRESULT CProve::Insert()
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

	strSql.Format("INSERT INTO PROVE (CUENTA, NOMBRE, NOMFICHA, DIRECCION, SG, NUMERO, " \
		"CP, POBLACION, PROVINCIA, CPAIS, CIF, TIPO, IVAIDEN, TELEFONO, TEL2, FAX, EMAIL, " \
		"CONTACTO, CARGO, IDIOMA, PLAZOENT, OBSER1, FECHALTA, FECHBAJA, DIVISA, FCOBRO, "\
		"NCOBROS, VTO1, DVTO, DIA1, DIA2, DIA3, CTABANCO, CC1, CC2, DC, CTACORR, NOMBCO, " \
		"IBAN, DCTOS, PP, RETENCION, PORRETE, CTARETE, CTACOM, DCTO2, DCTO3) " \
        "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', "\
		"'%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, '%s', %s, %s, '%s', '%s', %f, %f, %f, " \
		"%f, %f, %f, '%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %f, '%s', %f, '%s', '%s', %f, %f )", 
		m_CUENTA, m_NOMBRE, m_NOMFICHA, m_DIRECCION, m_SG, m_NUMERO,
		m_CP, m_POBLACION, m_PROVINCIA, m_CPAIS, m_CIF, m_TIPO, m_IVAIDEN, m_TELEFONO, 
		m_TEL2, m_FAX, m_EMAIL, m_CONTACTO, m_CARGO, m_IDIOMA, m_PLAZOENT, m_OBSER1, 
		strFechaAlta, strFechaBaja, m_DIVISA, m_FCOBRO, m_NCOBROS, m_VTO1, m_DVTO, m_DIA1, 
		m_DIA2, m_DIA3, m_CTABANCO, m_CC1, m_CC2, m_DC, m_CTACORR, m_NOMBCO, m_IBAN, 
		m_DCTOS, m_PP, m_RETENCION, m_PORRETE, m_CTARETE, m_CTACOM, m_DCTO2, m_DCTO3);

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
/* Modifica un registro en la tabla de proveedores                          */
/****************************************************************************/
HRESULT CProve::UpdateProve()
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

	strSql.Format("UPDATE PROVE SET NOMBRE= '%s', NOMFICHA= '%s', DIRECCION= '%s'," \
		"SG= '%s', NUMERO= '%s', CP = '%s', POBLACION = '%s', PROVINCIA = '%s', CPAIS = '%s', " \
		"CIF = '%s', TIPO = '%s', IVAIDEN = '%s', TELEFONO = '%s', TEL2 = '%s', FAX = '%s', " \
		"EMAIL = '%s', CONTACTO = '%s', CARGO = '%s', IDIOMA = '%s', PLAZOENT = %f, OBSER1 = '%s', " \
		"FECHALTA = %s, FECHBAJA = %s, DIVISA = '%s', FCOBRO = '%s', NCOBROS = %f, VTO1 = %f, " \
		"DVTO = %f, DIA1 = %f, DIA2 = %f, DIA3 = %f, CTABANCO = '%s', CC1 = '%s', CC2 = '%s', " \
		"DC = '%s', CTACORR = '%s', NOMBCO = '%s', IBAN = '%s', DCTOS = %f, PP = %f, " \
		"RETENCION = '%s', PORRETE = %f, CTARETE = '%s', CTACOM = '%s', DCTO2 = %f, DCTO3 = %f "\
		"WHERE CUENTA LIKE '%s' ", 
		m_NOMBRE, m_NOMFICHA, m_DIRECCION, m_SG, m_NUMERO,m_CP, m_POBLACION, m_PROVINCIA, m_CPAIS,
		m_CIF, m_TIPO, m_IVAIDEN, m_TELEFONO,m_TEL2, m_FAX, m_EMAIL, m_CONTACTO, m_CARGO, m_IDIOMA,
		m_PLAZOENT, m_OBSER1,strFechaAlta, strFechaBaja, m_DIVISA, m_FCOBRO, m_NCOBROS, m_VTO1,
		m_DVTO, m_DIA1,m_DIA2, m_DIA3, m_CTABANCO, m_CC1, m_CC2, m_DC, m_CTACORR, m_NOMBCO, m_IBAN, 
		m_DCTOS, m_PP, m_RETENCION, m_PORRETE, m_CTARETE, m_CTACOM, m_DCTO2, m_DCTO3, m_CUENTA);

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
CProve& CProve::operator =(CProve& Other)
{
	m_CIF = Other.m_CIF;
	m_CUENTA = Other.m_CUENTA;
	m_NOMBRE = Other.m_NOMBRE;
	m_PP = Other.m_PP;
	m_DCTOS = Other.m_DCTOS;
	m_NOMFICHA = Other.m_NOMFICHA;
	m_DIRECCION = Other.m_DIRECCION;
	m_POBLACION = Other.m_POBLACION;
	m_PROVINCIA = Other.m_PROVINCIA;
	m_CP = Other.m_CP;
	m_TELEFONO = Other.m_TELEFONO;
	m_FAX = Other.m_FAX;
	m_IVA = Other.m_IVA;
	m_FCOBRO = Other.m_FCOBRO;
	m_NCOBROS = Other.m_NCOBROS;
	m_VTO1 = Other.m_VTO1;
	m_DVTO = Other.m_DVTO;
	m_POBCO = Other.m_POBCO;
	m_NOMBCO = Other.m_NOMBCO;
	m_AGE =Other.m_AGE;
	m_DIRBCO = Other.m_DIRBCO;
	m_RETENCION = Other.m_RETENCION;
	m_CONTACTO = Other.m_CONTACTO;
	m_CARGO = Other.m_CARGO;
	m_TEL2 = Other.m_TEL2;
	m_COMISION = Other.m_COMISION;
	m_OBSER1 = Other.m_OBSER1;
	m_OBSER2 = Other.m_OBSER2;
	m_OBSER3 = Other.m_OBSER3;
	m_IDIOMA = Other.m_IDIOMA;
	m_DIVISA = Other.m_DIVISA;
	m_DIA1 = Other.m_DIA1;
	m_DIA2 = Other.m_DIA2;
	m_DIA3 = Other.m_DIA3;
	m_IVAIDEN = Other.m_IVAIDEN;
	m_AABONAR = Other.m_AABONAR;
	m_DIVAC = Other.m_DIVAC;
	m_MIVAC = Other.m_MIVAC;
	m_DFVAC = Other.m_DFVAC;
	m_MFVAC = Other.m_MFVAC;
	m_SG = Other.m_SG;
	m_DIRHACIEN = Other.m_DIRHACIEN;
	m_NUMERO = Other.m_NUMERO;
	m_CTACORR = Other.m_CTACORR;
	m_DC = Other.m_DC;
	m_CC1 = Other.m_CC1;
	m_CC2 = Other.m_CC2;
	m_CC3 = Other.m_CC3;
	m_CPBCO = Other.m_CPBCO;
	m_CPAIS = Other.m_CPAIS;
	m_TIPO = Other.m_TIPO;
	m_EMAIL = Other.m_EMAIL;
	m_DCTO2 = Other.m_DCTO2;
	m_DCTO3 = Other.m_DCTO3;
	m_CTABANCO = Other.m_CTABANCO;
	m_CAMPROVE1 = Other.m_CAMPROVE1;
	m_CAMPROVE2 = Other.m_CAMPROVE2;
	m_PLAZOENT = Other.m_PLAZOENT;
	m_FECHALTA = Other.m_FECHALTA;
	m_FECHBAJA = Other.m_FECHBAJA;
	m_PORRETE = Other.m_PORRETE;
	m_CTARETE = Other.m_CTARETE;
	m_CTACOM = Other.m_CTACOM;
	m_IBAN = Other.m_IBAN;

	return(*this);
}
