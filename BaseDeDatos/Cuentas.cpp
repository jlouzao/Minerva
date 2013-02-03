// Cuentas.h: implementación de la clase CCuentas



// Implementación de CCuentas

// código generado el miércoles, 15 de junio de 2005, 15:59

#include "stdafx.h"
#include "Cuentas.h"
IMPLEMENT_DYNAMIC(CCuentas, CRecordset)

CCuentas::CCuentas(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DEBE = 0.0;
	m_CUENTA = "";
	m_NOMBRE = "";
	m_HABER = 0.0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CCuentas::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-004;Trusted_Connection=Yes");
}

CString CCuentas::GetDefaultSQL()
{
	return _T("[dbo].[CUENTAS]");
}

void CCuentas::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Single(pFX, _T("[DEBE]"), m_DEBE);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[NOMBRE]"), m_NOMBRE);
	RFX_Single(pFX, _T("[HABER]"), m_HABER);

}
/////////////////////////////////////////////////////////////////////////////
// CCuentas diagnósticos

#ifdef _DEBUG
void CCuentas::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCuentas::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla ARTICULO                                 */
/****************************************************************************/
HRESULT CCuentas::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO CUENTAS (CUENTA, NOMBRE) VALUES ('%s', '%s')",m_CUENTA, m_NOMBRE);

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
/* Actualiza un registro en la tabla FAMILIA                                */
/****************************************************************************/
HRESULT CCuentas::UpdateRegistro()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE CUENTAS SET NOMBRE = '%s' WHERE CUENTA LIKE '%s'", m_NOMBRE, m_CUENTA);

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


