// Almacen.h: implementación de la clase CAlmacen



// Implementación de CAlmacen

// código generado el miércoles, 22 de junio de 2005, 15:35

#include "stdafx.h"
#include "Almacen.h"
IMPLEMENT_DYNAMIC(CAlmacen, CRecordset)

CAlmacen::CAlmacen(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ARTI = "";
	m_CANTI = 0.0;
	m_CANTIENT = 0.0;
	m_CANTISAL = 0.0;
	m_ALMACEN = "";
	m_CAMPAN1 = "";
	m_CAMPAN2 = "";
	m_CAMPAN3 = "";
	m_NDOC = 0.0;
	m_FECHA;
	m_MOVEXI = 0.0;
	m_MOVENT = 0.0;
	m_MOVSAL = 0.0;
	m_TIPOMOV = "";
	m_CUENTA = "";
	m_OBSER = "";
	m_CENTRO = "";
	m_COSART1 = 0.0;
	m_COSART2 = 0.0;
	m_COSART3 = 0.0;
	m_CLAVE = 0.0;
	m_CANTITOTAL = 0.0;
	m_CANTIDISPONIBLE = 0.0;
	m_nFields = 23;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CAlmacen::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;DATABASE=999;Trusted_Connection=Yes");
}

CString CAlmacen::GetDefaultSQL()
{
	return _T("[dbo].[ALMACEN]");
}

void CAlmacen::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Double(pFX, _T("[CANTI]"), m_CANTI);
	RFX_Double(pFX, _T("[CANTIENT]"), m_CANTIENT);
	RFX_Double(pFX, _T("[CANTISAL]"), m_CANTISAL);
	RFX_Text(pFX, _T("[ALMACEN]"), m_ALMACEN);
	RFX_Text(pFX, _T("[CAMPAN1]"), m_CAMPAN1);
	RFX_Text(pFX, _T("[CAMPAN2]"), m_CAMPAN2);
	RFX_Text(pFX, _T("[CAMPAN3]"), m_CAMPAN3);
	RFX_Double(pFX, _T("[NDOC]"), m_NDOC);
	RFX_Date(pFX, _T("[FECHA]"), m_FECHA);
	RFX_Double(pFX, _T("[MOVEXI]"), m_MOVEXI);
	RFX_Double(pFX, _T("[MOVENT]"), m_MOVENT);
	RFX_Double(pFX, _T("[MOVSAL]"), m_MOVSAL);
	RFX_Text(pFX, _T("[TIPOMOV]"), m_TIPOMOV);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Text(pFX, _T("[OBSER]"), m_OBSER);
	RFX_Text(pFX, _T("[CENTRO]"), m_CENTRO);
	RFX_Double(pFX, _T("[COSART1]"), m_COSART1);
	RFX_Double(pFX, _T("[COSART2]"), m_COSART2);
	RFX_Double(pFX, _T("[COSART3]"), m_COSART3);
	RFX_Double(pFX, _T("[CLAVE]"), m_CLAVE);
	RFX_Double(pFX, _T("[CANTITOTAL]"), m_CANTITOTAL);
	RFX_Double(pFX, _T("[CANTIDISPONIBLE]"), m_CANTIDISPONIBLE);
}
/////////////////////////////////////////////////////////////////////////////
// CAlmacen diagnósticos

#ifdef _DEBUG
void CAlmacen::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAlmacen::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/* Inserta un registro en la tabla ALMACEN                                  */
/****************************************************************************/
HRESULT CAlmacen::Insert()
{
	HRESULT hErr = S_OK;

	/* Se preparan las cadenas con las fechas */
	CString strFecha;

	if (m_FECHA == 0)
		strFecha = "NULL";
	else
		strFecha = "'" + m_FECHA.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ALMACEN (ARTI, CANTI, ALMACEN, NDOC, FECHA, " \
		"TIPOMOV, CUENTA, OBSER, CANTITOTAL, CANTIDISPONIBLE) VALUES ('%s', %f, '%s', %f, %s, '%s', '%s', "\
		"'%s', %f, %f)", m_ARTI, m_CANTI, m_ALMACEN, m_NDOC, strFecha, m_TIPOMOV, m_CUENTA, 
		m_OBSER, m_CANTITOTAL, m_CANTIDISPONIBLE);

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
/* Elimina todos los movimientos de almacén del albarán                     */
/****************************************************************************/
HRESULT CAlmacen::DeleteMovientosAlbaran()
{
	HRESULT hErr = S_OK;

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("DELETE FROM ALMACEN WHERE NDOC = %f", m_NDOC);

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
