// Inventario.h: implementación de la clase CInventario



// Implementación de CInventario

// código generado el jueves, 23 de junio de 2005, 13:51

#include "stdafx.h"
#include "Inventario.h"
IMPLEMENT_DYNAMIC(CInventario, CRecordset)

CInventario::CInventario(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ARTI = "";
	m_ALMACEN = "";
	m_UNITOTAL = 0;
	m_UNIDISPONIBLE = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CInventario::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CInventario::GetDefaultSQL()
{
	return _T("[dbo].[INVENTARIO]");
}

void CInventario::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[ALMACEN]"), m_ALMACEN);
	RFX_Long(pFX, _T("[UNITOTAL]"), m_UNITOTAL);
	RFX_Long(pFX, _T("[UNIDISPONIBLE]"), m_UNIDISPONIBLE);

}
/////////////////////////////////////////////////////////////////////////////
// CInventario diagnósticos

#ifdef _DEBUG
void CInventario::AssertValid() const
{
	CRecordset::AssertValid();
}

void CInventario::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla INVENTARIO                               */
/****************************************************************************/
HRESULT CInventario::Insert()
{
	HRESULT hErr = S_OK;

	CString strSql;
	strSql.Format("INSERT INTO INVENTARIO (ARTI, ALMACEN, UNITOTAL, UNIDISPONIBLE) " \
		"VALUES ('%s', '%s', %d, %d)",	m_ARTI, m_ALMACEN, m_UNITOTAL, m_UNIDISPONIBLE);

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
/* Actualiza la cantidad de unidades totales de un articulo                 */                               
/****************************************************************************/
HRESULT CInventario::UpdateUniTotal()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE INVENTARIO SET UNITOTAL = %d WHERE ARTI LIKE '%s' AND ALMACEN LIKE '%s'", 
		m_UNITOTAL, m_ARTI, m_ALMACEN);

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
/* Actualiza la cantidad de unidades totales de un articulo                 */                               
/****************************************************************************/
HRESULT CInventario::UpdateUniDisponible()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE INVENTARIO SET UNIDISPONIBLE = %d WHERE ARTI LIKE '%s' AND ALMACEN LIKE '%s'", 
		m_UNIDISPONIBLE, m_ARTI, m_ALMACEN);

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


