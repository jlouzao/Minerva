// Festivos.h: implementaci�n de la clase CFestivos



// Implementaci�n de CFestivos

// c�digo generado el mi�rcoles, 05 de octubre de 2005, 10:57

#include "stdafx.h"
#include "Festivos.h"
IMPLEMENT_DYNAMIC(CFestivos, CRecordset)

CFestivos::CFestivos(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DIA;
	m_nFields = 1;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexi�n puede contener una contrase�a
// La cadena de conexi�n siguiente puede contener contrase�as de texto sin formato/u
// otro tipo de informaci�n reservada. Quite #error despu�s de revisar
// la cadena de conexi�n relacionada con los problemas de seguridad. Puede que desee
// almacenar la contrase�a en otro formulario o utilizar una autenticaci�n de usuario diferente.
CString CFestivos::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CFestivos::GetDefaultSQL()
{
	return _T("[dbo].[FESTIVOS]");
}

void CFestivos::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentar� convertir autom�ticamente el valor de columna en el tipo solicitado
	RFX_Date(pFX, _T("[DIA]"), m_DIA);

}
/////////////////////////////////////////////////////////////////////////////
// CFestivos diagn�sticos

#ifdef _DEBUG
void CFestivos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFestivos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla FESTIVOS                                 */
/****************************************************************************/
HRESULT CFestivos::Insert()
{
	HRESULT hErr = S_OK;
	CString strFecha;

	if (m_DIA == 0)
		strFecha = "NULL";
	else
		strFecha = "'" + m_DIA.Format("%d/%m/%Y") + "'";

	CString strSql;
	strSql.Format("INSERT INTO FESTIVOS (DIA) VALUES (%s)",
		strFecha);

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
/* Elimina un registro en la tabla FESTIVOS                                 */
/****************************************************************************/
HRESULT CFestivos::DeleteFestivo()
{
	HRESULT hErr = S_OK;
	CString strFecha;

	if (m_DIA == 0)
		strFecha = "NULL";
	else
		strFecha = "'" + m_DIA.Format("%d/%m/%Y") + "'";

	CString strSql;
	strSql.Format("DELETE FROM FESTIVOS WHERE DIA = %s", strFecha);

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
