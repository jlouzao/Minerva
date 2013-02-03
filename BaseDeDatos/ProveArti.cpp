// ProveArti.h: implementación de la clase CProveArti



// Implementación de CProveArti

// código generado el miércoles, 13 de julio de 2005, 15:38

#include "stdafx.h"
#include "ProveArti.h"
IMPLEMENT_DYNAMIC(CProveArti, CRecordset)

CProveArti::CProveArti(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ARTI = "";
	m_CUENTA = "";
	m_SREF = "";
	m_NOMPROVE = "";
	m_TARIFA = 0.0;
	m_DESCUENTO = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CProveArti::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CProveArti::GetDefaultSQL()
{
	return _T("[dbo].[PROVEARTI]");
}

void CProveArti::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[SREF]"), m_SREF);
	RFX_Text(pFX, _T("[NOMPROVE]"), m_NOMPROVE);
	RFX_Double(pFX, _T("[TARIFA]"), m_TARIFA);
	RFX_Double(pFX, _T("[DESCUENTO]"), m_DESCUENTO);

}
/////////////////////////////////////////////////////////////////////////////
// CProveArti diagnósticos

#ifdef _DEBUG
void CProveArti::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProveArti::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/****************************************************************************/
CProveArti& CProveArti::operator =(CProveArti& Other)
{
	m_ARTI = Other.m_ARTI;;
	m_CUENTA = Other.m_CUENTA;
	m_SREF = Other.m_SREF;
	m_NOMPROVE = Other.m_NOMPROVE;
	m_TARIFA = Other.m_TARIFA;
	m_DESCUENTO = Other.m_DESCUENTO;

	return(*this);
}

/****************************************************************************/
/* Inserta un registro en la tabla PROVEARTI                                */
/****************************************************************************/
HRESULT CProveArti::Insert()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO PROVEARTI (ARTI, CUENTA, SREF, NOMPROVE, TARIFA, DESCUENTO)" \
		" VALUES ('%s', '%s', '%s', '%s', %f, %f)", m_ARTI, m_CUENTA, m_SREF, m_NOMPROVE, m_TARIFA,
		m_DESCUENTO);

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
/* Modifica un registro en la tabla PROVEARTI                               */
/****************************************************************************/
HRESULT CProveArti::UpdateProveArti()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE PROVEARTI SET CUENTA = '%s', SREF = '%s', NOMPROVE = '%s', TARIFA = %f, " \
		"DESCUENTO = %f	WHERE ARTI = '%s'", m_CUENTA, m_SREF, m_NOMPROVE, m_TARIFA, m_DESCUENTO, 
		m_ARTI);

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
/* Elimina todos los Proveedores de un Artículo                             */
/****************************************************************************/
HRESULT CProveArti::DeleteProveArti()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM PROVEARTI WHERE ARTI = '%s'", m_ARTI);

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
