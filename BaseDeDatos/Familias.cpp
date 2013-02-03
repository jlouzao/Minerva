// Familias.h: implementación de la clase CFamilias



// Implementación de CFamilias

// código generado el miércoles, 15 de junio de 2005, 15:02

#include "stdafx.h"
#include "Familias.h"
IMPLEMENT_DYNAMIC(CFamilias, CRecordset)

CFamilias::CFamilias(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CFAMILIA = "";
	m_DFAMILIA = "";
	m_ARTI = "";
	m_CLAVE = 0.0;
	m_DTOVFAM = 0.0;
	m_DTOCFAM = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CFamilias::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-004;Trusted_Connection=Yes");
}

CString CFamilias::GetDefaultSQL()
{
	return _T("[dbo].[FAMILIAS]");
}

void CFamilias::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[CFAMILIA]"), m_CFAMILIA);
	RFX_Text(pFX, _T("[DFAMILIA]"), m_DFAMILIA);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Double(pFX, _T("[CLAVE]"), m_CLAVE);
	RFX_Double(pFX, _T("[DTOVFAM]"), m_DTOVFAM);
	RFX_Double(pFX, _T("[DTOCFAM]"), m_DTOCFAM);

}
/////////////////////////////////////////////////////////////////////////////
// CFamilias diagnósticos

#ifdef _DEBUG
void CFamilias::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFamilias::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla FAMILIAS                                */
/****************************************************************************/
HRESULT CFamilias::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO FAMILIAS (CFAMILIA, DFAMILIA, DTOVFAM, DTOCFAM)"\
		" VALUES ('%s', '%s', '%f','%f')",m_CFAMILIA, m_DFAMILIA, m_DTOVFAM, m_DTOCFAM);

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
/* Actualiza un registro en la tabla FAMILIAS                               */
/****************************************************************************/
HRESULT CFamilias::UpdateRegistro()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE FAMILIAS SET DFAMILIA = '%s', DTOVFAM = %f, DTOCFAM = %f "\
		"WHERE CFAMILIA LIKE '%s'", m_DFAMILIA, m_DTOVFAM, m_DTOCFAM, m_CFAMILIA);

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


