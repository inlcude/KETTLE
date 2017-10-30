#ifndef __VAR_LIST_H__
#define __VAR_LIST_H__

#include "Platform.h"
namespace	KETTLE
{
	typedef struct common_data
	{
		enum  VALUETYPE
		{
			VT_DEFAULT   = 0Xffffffff,
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
		};

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
	};

	template<int32 InitSize>
	class VarList:public IVarList
	{
	public:
		VarList()
		{
			Init();
		}
		virtual ~VarList(){}

		virtual KETTLE::int8           GetInt8(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT8) return 0;
			return m_pData[nPos].m_nValue8;
		}
		virtual void                   SetInt8(KETTLE::int32 nPos, KETTLE::int8 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValue8 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT8;
		}
		virtual KETTLE::uint8          GetUInt8(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT8) return 0;
			return m_pData[nPos].m_nValueU8;
		}
		virtual void                   SetUInt8(KETTLE::int32 nPos, KETTLE::uint8 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValueU8 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT8;
		}
		virtual KETTLE::int16          GetInt16(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT16) return 0;
			return m_pData[nPos].m_nValue16;
		}
		virtual void                   SetInt16(KETTLE::int32 nPos, KETTLE::int16 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValue16 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT16;
		}
		virtual KETTLE::uint16         GetUInt16(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT16) return 0;
			return m_pData[nPos].m_nValueU16;
		}
		virtual void                   SetUInt16(KETTLE::int32 nPos, KETTLE::uint16 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValue16 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT16;
		}
		virtual KETTLE::int32          GetInt32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT32) return 0;
			return m_pData[nPos].m_nValue32;
		}
		virtual void                   SetInt32(KETTLE::int32 nPos, KETTLE::int32 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValue32 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT32;
		}
		virtual KETTLE::uint32         GetUInt32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT32) return 0;
			return m_pData[nPos].m_nValueU32;
		}
		virtual void                   SetUInt32(KETTLE::int32 nPos, KETTLE::uint32 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValueU32 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT32;
		}
		virtual KETTLE::int64          GetInt64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_INT64) return 0;
			return m_pData[nPos].m_nValue64;
		}
		virtual void                   SetInt64(KETTLE::int32 nPos, KETTLE::int64 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValue64 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_INT64;
		}
		virtual KETTLE::uint64         GetUInt64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0;
			if (m_pData[nPos].m_Type != common_data::VT_UINT64) return 0;
			return m_pData[nPos].m_nValueU64;
		}
		virtual void                   SetUInt64(KETTLE::int32 nPos, KETTLE::uint64 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_nValueU64 = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_UINT64;
		}
		virtual KETTLE::float32        GetFloat32(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0.0f;
			if (m_pData[nPos].m_Type != common_data::VT_FLOAT32) return 0.0f;
			return m_pData[nPos].m_fValue;
		}
		virtual void                   SetFloat32(KETTLE::int32 nPos, KETTLE::float32 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_fValue = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_FLOAT32;
		}
		virtual KETTLE::double64       GetDouble64(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return 0.0f;
			if (m_pData[nPos].m_Type != common_data::VT_DOUBLE64) return 0.0f;
			return m_pData[nPos].m_dValue;
		}
		virtual void                   SetDouble64(KETTLE::int32 nPos, KETTLE::double64 nValue)
		{
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			m_pData[m_nCurPos].m_dValue = nValue;
			m_pData[m_nCurPos].m_Type = common_data::VT_DOUBLE64;
		}
		virtual KETTLE::int8*          GetString(KETTLE::int32 nPos)
		{
			if (nPos >= m_nVarListSize || nPos < 0) return "";
			if (m_pData[nPos].m_Type != common_data::VT_STRING) return "";
			return m_pData[nPos].m_strValue;
		}
		virtual void                   SetString(KETTLE::int32 nPos, KETTLE::int8* nValue)
		{
			if (!nValue) return;
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == common_data::VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			int32 nStrlen = strlen(nValue);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, nValue);
			m_pData[nPos].m_strValue = pStr;
			m_pData[nPos].m_Type = common_data::VT_STRING;
		}

		VarList& operator= (const VarList& var)
		{
			return *this;
		}
		VarList& operator<< (const VarList& var)
		{
			return *this;
		}
		VarList& operator<< (KETTLE::int8 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValue8 = var;
			m_pData[m_nCurPos].m_Type = VT_INT8;
			m_nCurPos++;
			return *this;		
		}

		VarList& operator<< (KETTLE::uint8 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValueU8 = var;
			m_pData[m_nCurPos].m_Type = VT_UINT8;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int16 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValue16 = var;
			m_pData[m_nCurPos].m_Type = VT_INT16;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint16 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValueU16 = var;
			m_pData[m_nCurPos].m_Type = VT_UINT16;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int32 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValue32 = var;
			m_pData[m_nCurPos].m_Type = VT_INT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint32 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValueU32 = var;
			m_pData[m_nCurPos].m_Type = VT_UINT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int64 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValue64 = var;
			m_pData[m_nCurPos].m_Type = VT_INT64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::uint64 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_nValueU64 = var;
			m_pData[m_nCurPos].m_Type = VT_UINT64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::float32 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_fValue = var;
			m_pData[m_nCurPos].m_Type = VT_FLOAT32;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::double64 var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_dValue = var;
			m_pData[m_nCurPos].m_Type = VT_DOUBLE64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (KETTLE::int8* var)
		{
			if (m_nCurPos <= m_nVarListSize)
				Resize(2 * m_nVarListSize);
			m_pData[m_nCurPos].m_dValue = var;
			m_pData[m_nCurPos].m_Type = VT_DOUBLE64;
			m_nCurPos++;
			return *this;
		}
		VarList& operator<< (const KETTLE::int8* var)
		{
			if (!nValue) return;
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			int32 nStrlen = strlen(nValue);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, nValue);
			m_pData[m_nCurPos].m_strValue = pStr;
			m_pData[m_nCurPos].m_Type = VT_STRING;
			m_nCurPos++;
			return *this;
		}

		KETTLE::int8* Serialize()
		{
			if (!nValue) return;
			if (m_nCurPos >= m_nVarListSize) return;
			if (m_pData[nPos].m_Type == VT_STRING)
				SAFE_DELETE_ARRAY(m_pData[nPos].m_strValue);
			int32 nStrlen = strlen(nValue);
			char* pStr = new char[nStrlen + 1];
			memset(pStr, 0, nStrlen + 1);
			strcpy(pStr, nValue);
			m_pData[m_nCurPos].m_strValue = pStr;
			m_pData[m_nCurPos].m_Type = VT_STRING;
			m_nCurPos++;
			return *this;
		}
		void Serialize(const KETTLE::int8* pStr)
		{

		}
		void Serialize(KETTLE::int8* pStr)
		{
			
		}

	protected:
		void                                   Init()
		{
			m_nCurPos = 0;
			m_nVarListSize = InitSize;
			memset((&m_InitData[0]), 0, sizeof(m_InitData));
			m_pData = &(m_InitData[0]);
		}
		void                                   CleanUp()
		{
			for (int32 i = 0; i < m_nVarListSize; i++)
			{
				if (m_pData[i].m_Type == VT_STRING && m_pData[i].m_strValue)
					SAFE_DELETE_ARRAY(m_pData[i].m_strValue);
			}

			if (m_nVarListSize <= InitSize) return;
			SAFE_DELETE_ARRAY(m_pData[i].m_strValue);
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
	private:
		struct common_data                            m_InitData[InitSize];
		struct common_data*                           m_pData;
		KETTLE::int32                          m_nVarListSize;
		KETTLE::int32                          m_nCurPos;
	};
	typedef VarList<8>        CVarList;
}



#endif