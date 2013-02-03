// ArtiPendiente.h: implementación de la clase CArtiPendiente



// Implementación de CArtiPendiente

// código generado el jueves, 15 de septiembre de 2005, 10:55

#include "stdafx.h"
#include "ArtiPendiente.h"
IMPLEMENT_DYNAMIC(CArtiPendiente, CRecordset)

CArtiPendiente::CArtiPendiente(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NUMPEDIDO = "";
	m_NUMALB = "";
	m_ARTI = "";
	m_CANTI = 0.0;
	m_FECINIALQ;
	m_TIPOALQ = "";
	m_ESTADO = "";
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArtiPendiente::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=998;Trusted_Connection=Yes");
}

CString CArtiPendiente::GetDefaultSQL()
{
	return _T("[dbo].[ARTIPENDIENTE]");
}

void CArtiPendiente::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[NUMPEDIDO]"), m_NUMPEDIDO);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Date(pFX, _T("[FECINIALQ]"), m_FECINIALQ);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Text(pFX, _T("[ESTADO]"), m_ESTADO);

}
/////////////////////////////////////////////////////////////////////////////
// CArtiPendiente diagnósticos

#ifdef _DEBUG
void CArtiPendiente::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArtiPendiente::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/****************************************************************************/
/* Inserta un registro en la tabla ARTIPENDIENTE                            */
/****************************************************************************/
HRESULT CArtiPendiente::Insert()
{
	HRESULT hErr = S_OK;
	CString strFechaIniAlq;

	if (m_FECINIALQ == 0)
		strFechaIniAlq = "NULL";
	else
		strFechaIniAlq = "'" + m_FECINIALQ.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTIPENDIENTE (NUMPEDIDO, NUMALB, ARTI, CANTI, FECINIALQ, " \
		"TIPOALQ, ESTADO) VALUES ('%s', '%s', '%s', %f, %s, '%s', '%s')",
		m_NUMPEDIDO, m_NUMALB, m_ARTI, m_CANTI, strFechaIniAlq, m_TIPOALQ, m_ESTADO);

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
/* Actualiza el estado del articulo                                         */                               
/****************************************************************************/
HRESULT CArtiPendiente::UpdateEstado()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTIPENDIENTE SET ESTADO = '%s' WHERE NUMPEDIDO LIKE '%s' " \
		" AND NUMALB LIKE '%s' AND ARTI LIKE '%s'", 
		m_ESTADO, m_NUMPEDIDO, m_NUMALB, m_ARTI);

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

