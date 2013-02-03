// DirEnv.h: implementación de la clase CDirEnv



// Implementación de CDirEnv

// código generado el viernes, 08 de julio de 2005, 10:17

#include "stdafx.h"
#include "DirEnv.h"
IMPLEMENT_DYNAMIC(CDirEnv, CRecordset)

CDirEnv::CDirEnv(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CLIENTE = "";
	m_DIRENV = "";
	m_DDIRENV = "";
	m_POBL = "";
	m_CP = "";
	m_PROV = "";
	m_CONTACTO = "";
	m_TELEFONO = "";
	m_DISTANCIA = 0.0;
	m_DIVISA = "";
	m_FCOBRO = "";
	m_NCOBROS = 0.0;
	m_VTO1 = 0.0;
	m_DVTO = 0.0;
	m_DIA1 = 0.0;
	m_DIA2 = 0.0;
	m_DIA3 = 0.0;
	m_DIVAC = 0.0;
	m_DFVAC = 0.0;
	m_MIVAC = 0.0;
	m_MFVAC = 0.0;
	m_NUMCOMPA = "";
	m_SEGURO = "";
	m_RIESCLI = 0.0;
	m_ERIESCLI = 0.0;
	m_RIACCLI = 0.0;
	m_ERIACCLI = 0.0;
	m_CC1 = "";
	m_CC2 = "";
	m_DC = "";
	m_CTACORR = "";
	m_NOMBCO = "";
	m_AGE = "";
	m_DIRBCO = "";
	m_CPBCO = "";
	m_POBCO = "";
	m_TARIFA = "";
	m_DCTOS2 = 0.0;
	m_DCTOS3 = 0.0;
	m_DCTOS = 0.0;
	m_PP = 0.0;
	m_CTRCTA = "";
	m_GRUFAC = "";
	m_COPFAC = 0.0;
	m_ABFAC = 0.0;
	m_AABONAR = 0.0;
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
	m_TIEMPOTRAN = 0.0;
	m_TIEMPOOBRA = 0.0;
	m_ESTAOBRA = "";
	m_ZONA = "";
	m_NOMDIRENV = "";
	m_FECINIALQ;
	m_FECFINALQ;
	m_FECFINOBRA;
	m_OBRACERRA = "";
	m_FINOBRA = "";
	m_nFields = 67;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CDirEnv::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CDirEnv::GetDefaultSQL()
{
	return _T("[dbo].[DIRENV]");
}

void CDirEnv::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CLIENTE]"), m_CLIENTE);
	RFX_Text(pFX, _T("[DIRENV]"), m_DIRENV);
	RFX_Text(pFX, _T("[DDIRENV]"), m_DDIRENV);
	RFX_Text(pFX, _T("[POBL]"), m_POBL);
	RFX_Text(pFX, _T("[CP]"), m_CP);
	RFX_Text(pFX, _T("[PROV]"), m_PROV);
	RFX_Text(pFX, _T("[CONTACTO]"), m_CONTACTO);
	RFX_Text(pFX, _T("[TELEFONO]"), m_TELEFONO);
	RFX_Double(pFX, _T("[DISTANCIA]"), m_DISTANCIA);
	RFX_Text(pFX, _T("[DIVISA]"), m_DIVISA);
	RFX_Text(pFX, _T("[FCOBRO]"), m_FCOBRO);
	RFX_Double(pFX, _T("[NCOBROS]"), m_NCOBROS);
	RFX_Double(pFX, _T("[VTO1]"), m_VTO1);
	RFX_Double(pFX, _T("[DVTO]"), m_DVTO);
	RFX_Double(pFX, _T("[DIA1]"), m_DIA1);
	RFX_Double(pFX, _T("[DIA2]"), m_DIA2);
	RFX_Double(pFX, _T("[DIA3]"), m_DIA3);
	RFX_Double(pFX, _T("[DIVAC]"), m_DIVAC);
	RFX_Double(pFX, _T("[DFVAC]"), m_DFVAC);
	RFX_Double(pFX, _T("[MIVAC]"), m_MIVAC);
	RFX_Double(pFX, _T("[MFVAC]"), m_MFVAC);
	RFX_Text(pFX, _T("[NUMCOMPA]"), m_NUMCOMPA);
	RFX_Text(pFX, _T("[SEGURO]"), m_SEGURO);
	RFX_Double(pFX, _T("[RIESCLI]"), m_RIESCLI);
	RFX_Double(pFX, _T("[ERIESCLI]"), m_ERIESCLI);
	RFX_Double(pFX, _T("[RIACCLI]"), m_RIACCLI);
	RFX_Double(pFX, _T("[ERIACCLI]"), m_ERIACCLI);
	RFX_Text(pFX, _T("[CC1]"), m_CC1);
	RFX_Text(pFX, _T("[CC2]"), m_CC2);
	RFX_Text(pFX, _T("[DC]"), m_DC);
	RFX_Text(pFX, _T("[CTACORR]"), m_CTACORR);
	RFX_Text(pFX, _T("[NOMBCO]"), m_NOMBCO);
	RFX_Text(pFX, _T("[AGE]"), m_AGE);
	RFX_Text(pFX, _T("[DIRBCO]"), m_DIRBCO);
	RFX_Text(pFX, _T("[CPBCO]"), m_CPBCO);
	RFX_Text(pFX, _T("[POBCO]"), m_POBCO);
	RFX_Text(pFX, _T("[TARIFA]"), m_TARIFA);
	RFX_Double(pFX, _T("[DCTOS2]"), m_DCTOS2);
	RFX_Double(pFX, _T("[DCTOS3]"), m_DCTOS3);
	RFX_Double(pFX, _T("[DCTOS]"), m_DCTOS);
	RFX_Double(pFX, _T("[PP]"), m_PP);
	RFX_Text(pFX, _T("[CTRCTA]"), m_CTRCTA);
	RFX_Text(pFX, _T("[GRUFAC]"), m_GRUFAC);
	RFX_Double(pFX, _T("[COPFAC]"), m_COPFAC);
	RFX_Double(pFX, _T("[ABFAC]"), m_ABFAC);
	RFX_Double(pFX, _T("[AABONAR]"), m_AABONAR);
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
	RFX_Double(pFX, _T("[TIEMPOTRAN]"), m_TIEMPOTRAN);
	RFX_Double(pFX, _T("[TIEMPOOBRA]"), m_TIEMPOOBRA);
	RFX_Text(pFX, _T("[ESTAOBRA]"), m_ESTAOBRA);
	RFX_Text(pFX, _T("[ZONA]"), m_ZONA);
	RFX_Text(pFX, _T("[NOMDIRENV]"), m_NOMDIRENV);
	RFX_Date(pFX, _T("[FECINIALQ]"), m_FECINIALQ);
	RFX_Date(pFX, _T("[FECFINALQ]"), m_FECFINALQ);
	RFX_Date(pFX, _T("[FECFINOBRA]"), m_FECFINOBRA);
	RFX_Text(pFX, _T("[OBRACERRA]"), m_OBRACERRA);
	RFX_Text(pFX, _T("[FINOBRA]"), m_FINOBRA);

}
/////////////////////////////////////////////////////////////////////////////
// CDirEnv diagnósticos

#ifdef _DEBUG
void CDirEnv::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDirEnv::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla DIRENV                                   */
/****************************************************************************/
HRESULT CDirEnv::Insert()
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

	strSql.Format("INSERT INTO DIRENV (CLIENTE, DIRENV, DDIRENV, NOMDIRENV, CP, POBL, " \
		"PROV, CONTACTO, TELEFONO, DISTANCIA, FECHALTA, FECHBAJA, OBRACERRA) " \
        "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %f, %s, %s, '%s')", 
		m_CLIENTE, m_DIRENV, m_DDIRENV, m_NOMDIRENV, m_CP, m_POBL, m_PROV, m_CONTACTO,
		m_TELEFONO, m_DISTANCIA, strFechaAlta, strFechaBaja, m_OBRACERRA);

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
/* Modifica un registro en la tabla DIRENV                                  */
/****************************************************************************/
HRESULT CDirEnv::UpdateDirEnv()
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

	strSql.Format("UPDATE DIRENV SET DDIRENV = '%s', NOMDIRENV = '%s', CP = '%s', POBL = '%s', " \
		"PROV = '%s', CONTACTO = '%s', TELEFONO = '%s', DISTANCIA = %f, FECHALTA = %s, " \
		"FECHBAJA = %s, OBRACERRA = '%s' WHERE CLIENTE LIKE '%s' AND DIRENV LIKE '%s'", 
		m_DDIRENV, m_NOMDIRENV, m_CP, m_POBL, m_PROV, m_CONTACTO, m_TELEFONO, m_DISTANCIA, 
		strFechaAlta, strFechaBaja, m_OBRACERRA, m_CLIENTE, m_DIRENV);

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
/* Elimina un registro en la tabla DIRENV                                   */
/****************************************************************************/
HRESULT CDirEnv::DeleteDirEnv()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM DIRENV WHERE CLIENTE LIKE '%s'",m_CLIENTE);

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
/* Actualiza el campo de obra cerrada                                       */                               
/****************************************************************************/
HRESULT CDirEnv::UpdateCierreObra()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE DIRENV SET OBRACERRA = '%s' WHERE DIRENV LIKE '%s'", 
		m_OBRACERRA, m_DIRENV);

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
