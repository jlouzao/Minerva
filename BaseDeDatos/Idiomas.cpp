// Idiomas.h: implementación de la clase CIdiomas



// Implementación de CIdiomas

// código generado el miércoles, 22 de junio de 2005, 15:36

#include "stdafx.h"
#include "Idiomas.h"
IMPLEMENT_DYNAMIC(CIdiomas, CRecordset)

CIdiomas::CIdiomas(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_IDIOMA = "";
	m_DIDIOMA = "";
	m_IDFAC = "";
	m_IDLIT = "";
	m_IDREP = "";
	m_IDCLI = "";
	m_IDCIF = "";
	m_IDFEC = "";
	m_IDSR = "";
	m_IDPED = "";
	m_IDALB = "";
	m_IDCOD = "";
	m_IDDES = "";
	m_IDPIE = "";
	m_IDCAJ = "";
	m_IDPRE = "";
	m_IDDTO = "";
	m_IDIMP = "";
	m_IDTOT = "";
	m_IDDIS = "";
	m_IDPEB = "";
	m_IDPEN = "";
	m_IDPAL = "";
	m_IDFOR = "";
	m_nFields = 24;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CIdiomas::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CIdiomas::GetDefaultSQL()
{
	return _T("[dbo].[IDIOMAS]");
}

void CIdiomas::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[IDIOMA]"), m_IDIOMA);
	RFX_Text(pFX, _T("[DIDIOMA]"), m_DIDIOMA);
	RFX_Text(pFX, _T("[IDFAC]"), m_IDFAC);
	RFX_Text(pFX, _T("[IDLIT]"), m_IDLIT);
	RFX_Text(pFX, _T("[IDREP]"), m_IDREP);
	RFX_Text(pFX, _T("[IDCLI]"), m_IDCLI);
	RFX_Text(pFX, _T("[IDCIF]"), m_IDCIF);
	RFX_Text(pFX, _T("[IDFEC]"), m_IDFEC);
	RFX_Text(pFX, _T("[IDSR]"), m_IDSR);
	RFX_Text(pFX, _T("[IDPED]"), m_IDPED);
	RFX_Text(pFX, _T("[IDALB]"), m_IDALB);
	RFX_Text(pFX, _T("[IDCOD]"), m_IDCOD);
	RFX_Text(pFX, _T("[IDDES]"), m_IDDES);
	RFX_Text(pFX, _T("[IDPIE]"), m_IDPIE);
	RFX_Text(pFX, _T("[IDCAJ]"), m_IDCAJ);
	RFX_Text(pFX, _T("[IDPRE]"), m_IDPRE);
	RFX_Text(pFX, _T("[IDDTO]"), m_IDDTO);
	RFX_Text(pFX, _T("[IDIMP]"), m_IDIMP);
	RFX_Text(pFX, _T("[IDTOT]"), m_IDTOT);
	RFX_Text(pFX, _T("[IDDIS]"), m_IDDIS);
	RFX_Text(pFX, _T("[IDPEB]"), m_IDPEB);
	RFX_Text(pFX, _T("[IDPEN]"), m_IDPEN);
	RFX_Text(pFX, _T("[IDPAL]"), m_IDPAL);
	RFX_Text(pFX, _T("[IDFOR]"), m_IDFOR);

}
/////////////////////////////////////////////////////////////////////////////
// CIdiomas diagnósticos

#ifdef _DEBUG
void CIdiomas::AssertValid() const
{
	CRecordset::AssertValid();
}

void CIdiomas::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla IDIOMA                                   */
/****************************************************************************/
HRESULT CIdiomas::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO IDIOMAS (IDIOMA, DIDIOMA)VALUES ('%s', '%s')",m_IDIOMA, m_DIDIOMA);

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
/* Modifica un registro en la tabla IDIOMAS                                 */
/****************************************************************************/
HRESULT CIdiomas::UpdateIdioma()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE IDIOMAS SET DIDIOMA = '%s' WHERE IDIOMA LIKE '%s'", m_DIDIOMA, m_IDIOMA );

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

