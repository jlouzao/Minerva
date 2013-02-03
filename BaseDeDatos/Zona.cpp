// Zona.h: implementación de la clase CZona



// Implementación de CZona

// código generado el lunes, 11 de julio de 2005, 15:18

#include "stdafx.h"
#include "Zona.h"
IMPLEMENT_DYNAMIC(CZona, CRecordset)

CZona::CZona(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ZONA = "";
	m_DZONA = "";
	m_CUENTA = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CZona::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CZona::GetDefaultSQL()
{
	return _T("[dbo].[ZONA]");
}

void CZona::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ZONA]"), m_ZONA);
	RFX_Text(pFX, _T("[DZONA]"), m_DZONA);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);

}
/////////////////////////////////////////////////////////////////////////////
// CZona diagnósticos

#ifdef _DEBUG
void CZona::AssertValid() const
{
	CRecordset::AssertValid();
}

void CZona::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/****************************************************************************/
/* Inserta un registro en la tabla ZONA                                     */
/****************************************************************************/
HRESULT CZona::Insert()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("INSERT INTO ZONA (ZONA, DZONA, CUENTA) VALUES ('%s', '%s', '%s')",
		m_ZONA, m_DZONA, m_CUENTA);

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
/* Actualiza un registro en la tabla ZONA                                   */
/****************************************************************************/
HRESULT CZona::UpdateZona()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ZONA SET DZONA = '%s', CUENTA = '%s' WHERE ZONA"\
		" LIKE '%s'", m_DZONA, m_CUENTA, m_ZONA);

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