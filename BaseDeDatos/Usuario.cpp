// Usuario.h: implementaci�n de la clase CUsuario



// Implementaci�n de CUsuario

// c�digo generado el lunes, 06 de junio de 2005, 13:52

#include "stdafx.h"
#include "Usuario.h"
IMPLEMENT_DYNAMIC(CUsuario, CRecordset)

CUsuario::CUsuario(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_USUARIO = "";
	m_PASSWORD = "";
	m_IDPERFIL = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CUsuario::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CUsuario::GetDefaultSQL()
{
	return _T("[dbo].[USUARIO]");
}

void CUsuario::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[USUARIO]"), m_USUARIO);
	RFX_Text(pFX, _T("[PASSWORD]"), m_PASSWORD);
	RFX_Long(pFX, _T("[IDPERFIL]"), m_IDPERFIL);

}
/////////////////////////////////////////////////////////////////////////////
// CUsuario diagn�sticos

#ifdef _DEBUG
void CUsuario::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUsuario::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla USUARIO                                  */
/****************************************************************************/
HRESULT CUsuario::Insert()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("INSERT INTO USUARIO (USUARIO, PASSWORD, IDPERFIL) VALUES ('%s', '%s', %d)",
		m_USUARIO, m_PASSWORD, m_IDPERFIL);

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
/* Elimina un registro en la tabla USUARIO seg�n el nombre del usuario      */
/****************************************************************************/
HRESULT CUsuario::DeleteFromUser()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("DELETE FROM USUARIO WHERE USUARIO LIKE '%s'",	m_USUARIO);

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
/* Actualiza la contrase�a de un registro en la tabla USUARIO seg�n el      */
/* nombre del usuario                                                       */
/****************************************************************************/
HRESULT CUsuario::UpdatePassword()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("UPDATE USUARIO SET PASSWORD = '%s' WHERE USUARIO LIKE '%s'",	m_PASSWORD, m_USUARIO);

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



