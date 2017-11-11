#ifndef __VAR_LIST_H__
#define __VAR_LIST_H__

#include "Platform.h"

using namespace KETTLE;
namespace	KETTLE
{
	typedef struct common_data
	{
		enum  VALUETYPE
		{
			VT_DEFAULT   = 0Xffffffff,
			VT_UNKNOW    = 0,
			VT_INT8      = 1,
			VT_UINT8,
			VT_INT16,
			VT_UINT16,
			VT_INT32,
			VT_UINT32,
			VT_INT64,
			VT_UINT64,
			VT_FLOAT32,
			VT_DOUBLE64,
			VT_STRING,
		};

		VALUETYPE    m_Type;
		union
		{
			KETTLE::int8         m_nValue8;
			KETTLE::uint8        m_nValueU8;
			KETTLE::int16        m_nValue16;
			KETTLE::uint16       m_nValueU16;
			KETTLE::int32        m_nValue32;
			KETTLE::uint32       m_nValueU32;
			KETTLE::int64        m_nValue64;
			KETTLE::uint64       m_nValueU64;
			KETTLE::float32      m_fValue;
			KETTLE::int8*        m_strValue;
			KETTLE::double64     m_dValue;
		}CommonValue;

		void            CleanUp()
		{
			m_Type = VT_DEFAULT;
		}
	}common_data;

	class IVarList
	{
	public:
		virtual KETTLE::int8           GetInt8(KETTLE::int32 nPos) = 0;
		virtual void                   SetInt8(KETTLE::int32 nPos,KETTLE::int8 nValue) = 0;
		virtual KETTLE::uint8          GetUInt8(KETTLE::int32 nPos) = 0;
		virtual void                   SetUInt8(KETTLE::int32 nPos, KETTLE::uint8 nValue) = 0;
		virtual KETTLE::int16          GetInt16(KETTLE::int32 nPos) = 0;
		virtual void                   SetInt16(KETTLE::int32 nPos, KETTLE::int16 nValue) = 0;
		virtual KETTLE::uint16         GetUInt16(KETTLE::int32 nPos) = 0;
		virtual void                   SetUInt16(KETTLE::int32 nPos, KETTLE::uint16 nValue) = 0;
		virtual KETTLE::int32          GetInt32(KETTLE::int32 nPos) = 0;
		virtual void                   SetInt32(KETTLE::int32 nPos, KETTLE::int32 nValue) = 0;
		virtual KETTLE::uint32         GetUInt32(KETTLE::int32 nPos) = 0;
		virtual void                   SetUInt32(KETTLE::int32 nPos, KETTLE::uint32 nValue) = 0;
		virtual KETTLE::int64          GetInt64(KETTLE::int32 nPos) = 0;
		virtual void                   SetInt64(KETTLE::int32 nPos, KETTLE::int64 nValue) = 0;
		virtual KETTLE::uint64         GetUInt64(KETTLE::int32 nPos) = 0;
		virtual void                   SetUInt64(KETTLE::int32 nPos, KETTLE::uint64 nValue) = 0;
		virtual KETTLE::float32        GetFloat32(KETTLE::int32 nPos) = 0;
		virtual void                   SetFloat32(KETTLE::int32 nPos, KETTLE::float32 nValue) = 0;
		virtual KETTLE::double64       GetDouble64(KETTLE::int32 nPos) = 0;
		virtual void                   SetDouble64(KETTLE::int32 nPos, KETTLE::double64 nValue) = 0;
		virtual KETTLE::int8*          GetString(KETTLE::int32 nPos) = 0;
		virtual void                   SetString(KETTLE::int32 nPos, KETTLE::int8* nValue) = 0;

		virtual KETTLE::int32          GetSize() = 0;
		virtual KETTLE::int32          GetMaxSize() = 0;
	};

	template<int32 InitSize>
	class VarList:public IVarList
	{
	public:
		VarList()
		{
			Init();
		}
		virtual ~VarList()
		{
			CleanUp();
		}

		virtual KETTLE::int8           GetInt8(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT8) return 0;
			return m_pData[nPos].CommonValue.m_nValue8;
		}
		virtual void                   SetInt8(KETTLE::int32 nPos, KETTLE::int8 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValue8 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT8;
		}
		virtual KETTLE::uint8          GetUInt8(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT8) return 0;
			return m_pData[nPos].CommonValue.m_nValueU8;
		}
		virtual void                   SetUInt8(KETTLE::int32 nPos, KETTLE::uint8 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValueU8 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT8;
		}
		virtual KETTLE::int16          GetInt16(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT16) return 0;
			return m_pData[nPos].CommonValue.m_nValue16;
		}
		virtual void                   SetInt16(KETTLE::int32 nPos, KETTLE::int16 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValue16 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT16;
		}
		virtual KETTLE::uint16         GetUInt16(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT16) return 0;
			return m_pData[nPos].CommonValue.m_nValueU16;
		}
		virtual void                   SetUInt16(KETTLE::int32 nPos, KETTLE::uint16 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValue16 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT16;
		}
		virtual KETTLE::int32          GetInt32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT32) return 0;
			return m_pData[nPos].CommonValue.m_nValue32;
		}
		virtual void                   SetInt32(KETTLE::int32 nPos, KETTLE::int32 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValue32 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT32;
		}
		virtual KETTLE::uint32         GetUInt32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT32) return 0;
			return m_pData[nPos].CommonValue.m_nValueU32;
		}
		virtual void                   SetUInt32(KETTLE::int32 nPos, KETTLE::uint32 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValueU32 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT32;
		}
		virtual KETTLE::int64          GetInt64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT64) return 0;
			return m_pData[nPos].CommonValue.m_nValue64;
		}
		virtual void                   SetInt64(KETTLE::int32 nPos, KETTLE::int64 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValue64 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT64;
		}
		virtual KETTLE::uint64         GetUInt64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT64) return 0;
			return m_pData[nPos].CommonValue.m_nValueU64;
		}
		virtual void                   SetUInt64(KETTLE::int32 nPos, KETTLE::uint64 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_nValueU64 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT64;
		}
		virtual KETTLE::float32        GetFloat32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0.0f;
			if (m_pData[nPos].m_Type != common_data::VT_FLOAT32) return 0.0f;
			return m_pData[nPos].CommonValue.m_fValue;
		}
		virtual void                   SetFloat32(KETTLE::int32 nPos, KETTLE::float32 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_fValue = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_FLOAT32;
		}
		virtual KETTLE::double64       GetDouble64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0.0f;
			if (m_pData[nPos].m_Type != common_data::VT_DOUBLE64) return 0.0f;
			return m_pData[nPos].CommonValue.m_dValue;
		}
		virtual void                   SetDouble64(KETTLE::int32 nPos, KETTLE::double64 nValue)
		{
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			m_pData[m_nCurPos].CommonValue.m_dValue = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_DOUBLE64;
		}
		virtual KETTLE::int8*          GetString(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return "";
			if (m_pData[nPos].m_Type != common_data::VT_STRING) return "";
			return m_pData[nPos].CommonValue.m_strValue;
		}
		virtual void                   SetString(KETTLE::int32 nPos, KETTLE::int8* nValue)
		{
			if (!nValue) return;
			if (nPos >= m_nCurPos) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].CommonValue.m_strValue);
			int32 nStrlen = strlen(nValue);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, nValue);
			m_pData[nPos].CommonValue.m_strValue = pStr;
			m_pData[nPos].m_Type = common_data::VT_STRING;
		}

		VarList& operator= (const VarList& var)
		{
			if (m_nVarListSize < var.GetSize())
				Resize(var.GetMaxSize());
			InitializeList();

			for (int32 i = 0; i < var.GetSize(); i++)
			{
				int8 nType = var.GetType(i);
				switch (nType)
				{
				case common_data::VT_INT8:
					*this << var.GetInt8(i);
					break;
				case common_data::VT_UINT8:
					*this << var.GetUInt8(i);
					break;
				case common_data::VT_INT16:
					*this << var.GetInt16(i);
					break;
				case common_data::VT_UINT16:
					*this << var.GetUInt16(i);
					break;
				case common_data::VT_INT32:
					*this << var.GetInt32(i);
					break;
				case common_data::VT_UINT32:
					*this << var.GetUInt32(i);
					break;
				case common_data::VT_INT64:
					*this << var.GetInt64(i);
					break;
				case common_data::VT_UINT64:
					*this << var.GetUInt64(i);
					break;
				case common_data::VT_FLOAT32:
					*this << var.GetFloat32(i);
					break;
				case common_data::VT_DOUBLE64:
					*this << var.GetDouble64(i);
					break;
				case common_data::VT_STRING:
					*this << var.GetString(i);
					break;
				default:
					break;
				}
			}

			return *this;
		}
		VarList& operator<< (const VarList& var)
		{
			for (int32 i = 0; i < var.GetSize(); i++)
			{
				int8 nType = var.GetType(i);
				switch (nType)
				{
				case common_data::VT_INT8:
					*this << var.GetInt8(i);
					break;
				case common_data::VT_UINT8:
					*this << var.GetUInt8(i);
					break;
				case common_data::VT_INT16:
					*this << var.GetInt16(i);
					break;
				case common_data::VT_UINT16:
					*this << var.GetUInt16(i);
					break;
				case common_data::VT_INT32:
					*this << var.GetInt32(i);
					break;
				case common_data::VT_UINT32:
					*this << var.GetUInt32(i);
					break;
				case common_data::VT_INT64:
					*this << var.GetInt64(i);
					break;
				case common_data::VT_UINT64:
					*this << var.GetUInt64(i);
					break;
				case common_data::VT_FLOAT32:
					*this << var.GetFloat32(i);
					break;
				case common_data::VT_DOUBLE64:
					*this << var.GetDouble64(i);
					break;
				case common_data::VT_STRING:
					*this << var.GetString(i);
					break;
				default:
					break;
				}
			}

			return *this;
		}
		VarList& operator<< (KETTLE::int8 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValue8 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT8;
			m_nCurPos++;
			return *this;		
		}

		VarList& operator<< (KETTLE::uint8 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValueU8 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT8;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int16 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValue16 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT16;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint16 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValueU16 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT16;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int32 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValue32 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint32 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValueU32 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int64 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValue64 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint64 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_nValueU64 = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::float32 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_fValue = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_FLOAT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::double64 var)
		{
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].CommonValue.m_dValue = var;
			m_pData[m_nCurPos].m_Type = common_data::VT_DOUBLE64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int8* var)
		{
			if (!var) return *this;
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			int32 nStrlen = strlen(var);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, var);
			m_pData[m_nCurPos].CommonValue.m_strValue = pStr;
			m_pData[m_nCurPos].m_Type = common_data::VT_STRING;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (const KETTLE::int8* var)
		{
			if (!var) return *this;
			if (m_nCurPos >= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			int32 nStrlen = strlen(var);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, var);
			m_pData[m_nCurPos].CommonValue.m_strValue = pStr;
			m_pData[m_nCurPos].m_Type = common_data::VT_STRING;
			m_nCurPos++;
			return *this;
		}


		virtual KETTLE::int32          GetSize()
		{
			return m_nCurPos;
		}

		virtual KETTLE::int32          GetMaxSize()
		{
			return m_nVarListSize;
		}

		KETTLE::int8     GetType(const KETTLE::int32 nPos)
		{
			if (nPos >= m_nCurPos) return common_data::VT_UNKNOW;
			return m_pData[nPos].m_Type;
		}

		KETTLE::int8* Serialize()
		{
			int32 nSize = 0;
			for (int32 i = 0; i < GetSize(); ++i)
			{
				int8 nType = GetType(i);
				switch (nType)
				{
				case common_data::VT_INT8:
					nSize += sizeof(nType);
					nSize += sizeof(int8);
					break;
				case common_data::VT_UINT8:
					nSize += sizeof(nType);
					nSize += sizeof(uint8);
					break;
				case common_data::VT_INT16:
					nSize += sizeof(nType);
					nSize += sizeof(int16);
					break;
				case common_data::VT_UINT16:
					nSize += sizeof(nType);
					nSize += sizeof(uint16);
					break;
				case common_data::VT_INT32:
					nSize += sizeof(nType);
					nSize += sizeof(int32);
					break;
				case common_data::VT_UINT32:
					nSize += sizeof(nType);
					nSize += sizeof(uint32);
					break;
				case common_data::VT_INT64:
					nSize += sizeof(nType);
					nSize += sizeof(int64);
					break;
				case common_data::VT_UINT64:
					nSize += sizeof(nType);
					nSize += sizeof(uint64);
					break;
				case common_data::VT_FLOAT32:
					nSize += sizeof(nType);
					nSize += sizeof(float32);
					break;
				case common_data::VT_DOUBLE64:
					nSize += sizeof(nType);
					nSize += sizeof(double64);
					break;
				case common_data::VT_STRING:
					nSize += sizeof(nType);
					nSize += strlen(m_pData[i].CommonValue.m_strValue) + 1;
					nSize += sizeof(int32);
					break;
				default:
					break;
				}
			}

			nSize += sizeof(m_nCurPos);
			int8* pStr = new int8[nSize];
			int8* TempStr = pStr;
			memset(pStr, 0, nSize);
			memcpy(pStr, &m_nCurPos, sizeof(m_nCurPos));
			pStr += sizeof(m_nCurPos);

			for (int32 i = 0; i < m_nCurPos; ++i)
			{
				int8 nType = GetType(i);
				switch (nType)
				{
				case common_data::VT_INT8:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValue8, sizeof(m_pData[i].CommonValue.m_nValue8));
					pStr += sizeof(m_pData[i].CommonValue.m_nValue8);
					break;
				case common_data::VT_UINT8:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValueU8, sizeof(m_pData[i].CommonValue.m_nValueU8));
					pStr += sizeof(m_pData[i].CommonValue.m_nValueU8);
					break;
				case common_data::VT_INT16:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValue16, sizeof(m_pData[i].CommonValue.m_nValue16));
					pStr += sizeof(m_pData[i].CommonValue.m_nValue16);
					break;
				case common_data::VT_UINT16:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValueU16, sizeof(m_pData[i].CommonValue.m_nValueU16));
					pStr += sizeof(m_pData[i].CommonValue.m_nValueU16);
					break;
				case common_data::VT_INT32:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValue32, sizeof(m_pData[i].CommonValue.m_nValue32));
					pStr += sizeof(m_pData[i].CommonValue.m_nValue32);
					break;
				case common_data::VT_UINT32:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValueU32, sizeof(m_pData[i].CommonValue.m_nValueU32));
					pStr += sizeof(m_pData[i].CommonValue.m_nValueU32);
					break;
				case common_data::VT_INT64:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValue64, sizeof(m_pData[i].CommonValue.m_nValue64));
					pStr += sizeof(m_pData[i].CommonValue.m_nValue64);
					break;
				case common_data::VT_UINT64:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_nValueU64, sizeof(m_pData[i].CommonValue.m_nValueU64));
					pStr += sizeof(m_pData[i].CommonValue.m_nValueU64);
					break;
				case common_data::VT_FLOAT32:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_fValue, sizeof(m_pData[i].CommonValue.m_fValue));
					pStr += sizeof(m_pData[i].CommonValue.m_fValue);
					break;
				case common_data::VT_DOUBLE64:
					memcpy(pStr, &nType, sizeof(nType));
					pStr += sizeof(nType);
					memcpy(pStr, &m_pData[i].CommonValue.m_dValue, sizeof(m_pData[i].CommonValue.m_dValue));
					pStr += sizeof(m_pData[i].CommonValue.m_dValue);
					break;
					case common_data::VT_STRING:
					{
						memcpy(pStr, &nType, sizeof(nType));
						pStr += sizeof(nType);
						int32 nLen = strlen(m_pData[i].CommonValue.m_strValue) + 1;
						memcpy(pStr, &nLen, sizeof(nLen));
						pStr += sizeof(nLen);
						memcpy(pStr, &m_pData[i].CommonValue.m_strValue, nLen);
						pStr += nLen;
					}break;
				default:
					break;
				}
			}

			return TempStr;
		}
		void Serialize(const KETTLE::int8* pStr)
		{
		}
		void Serialize(KETTLE::int8* pStr)
		{
			InitializeList();
			int32 nSize = 0;
			memcpy(&nSize, pStr, sizeof(nSize));
			pStr += sizeof(nSize);
			if (nSize <= 0) return;
			for (int32 i = 0; i < nSize; ++i)
			{
				int8 nType = common_data::VT_UNKNOW;
				memcpy(&nType, pStr, sizeof(nType));
				pStr += sizeof(nType);
				switch (nType)
				{
					case common_data::VT_INT8:
					{
						int8 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_UINT8:
					{
						uint8 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_INT16:
					{
						int16 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_UINT16:
					{
						uint16 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_INT32:
					{
						int32 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_UINT32:
					{
						uint32 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_INT64:
					{
						int64 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_UINT64:
					{
						uint64 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_FLOAT32:
					{
						float32 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_DOUBLE64:
					{
						double64 nValue = 0;
						memcpy(&nValue, pStr, sizeof(nValue));
						pStr += sizeof(nValue);
						*this << nValue;
					}break;
					case common_data::VT_STRING:
					{
						int32 nStringSize = 0;
						memcpy(&nStringSize, pStr, sizeof(nStringSize));
						pStr += sizeof(nStringSize);
						int8* pString = new int8[nStringSize];
						memset(pString, 0, nStringSize);
						memcpy(pString, pStr, nStringSize);
						pStr += nStringSize;
						*this << pString;
						SAFE_DELETE_ARRAY(pString);
					}break;
					default:
						return;
				}
			}
		}



	protected:
		void                                   Init()
		{
			m_nCurPos = 0;
			m_nVarListSize = InitSize;
			memset((&m_InitData[0]), 0, sizeof(m_InitData));
			m_pData = &(m_InitData[0]);
			m_nSerializeSize = 0;
		}
		void                                   CleanUp()
		{
			for (int32 i = 0; i < m_nCurPos; i++)
			{
				if (m_pData[i].m_Type == common_data::VT_STRING && m_pData[i].CommonValue.m_strValue)
					SAFE_DELETE_ARRAY(m_pData[i].CommonValue.m_strValue);
			}

			if (m_nVarListSize <= InitSize) return;
			SAFE_DELETE_ARRAY(m_pData);
		}
		void                                   Resize(KETTLE::int32 nSize)
		{
			if (nSize <= m_nVarListSize) return;
			common_data* pData = new common_data[nSize];
			memset(pData, 0, sizeof(common_data) * nSize);
			memcpy(pData, m_pData, sizeof(common_data) * m_nVarListSize);
			if (m_nVarListSize > InitSize)
				SAFE_DELETE_ARRAY(m_pData);
			m_pData = pData;
			m_nVarListSize = nSize;
		}
		void                                   InitializeList()
		{
			for (int32 i = 0; i < m_nCurPos; ++i)
			{
				if (m_pData[i].m_Type == common_data::VT_STRING && m_pData[i].CommonValue.m_strValue){
					m_pData[i].m_Type = common_data::VT_DEFAULT;
					SAFE_DELETE_ARRAY(m_pData[i].CommonValue.m_strValue);
				}
				else {
					m_pData[i].m_Type = common_data::VT_DEFAULT;
					m_pData[i].CommonValue.m_dValue = 0;
				}
			}

			m_nCurPos = 0;
			m_nSerializeSize = 0;
		}
	private:
		struct common_data                            m_InitData[InitSize];
		struct common_data*                           m_pData;
		KETTLE::int32                                 m_nVarListSize;
		KETTLE::int32                                 m_nCurPos;
		KETTLE::int32                                 m_nSerializeSize;
	};
	typedef VarList<8>        CVarList;
}



#endif
