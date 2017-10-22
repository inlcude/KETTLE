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
		union common_value
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
		VarList();
		virtual ~VarList();

		virtual KETTLE::int8           GetInt8(KETTLE::int32 nPos);
		virtual void                   SetInt8(KETTLE::int32 nPos, KETTLE::int8 nValue);
		virtual KETTLE::uint8          GetUInt8(KETTLE::int32 nPos);
		virtual void                   SetUInt8(KETTLE::int32 nPos, KETTLE::uint8 nValue);
		virtual KETTLE::int16          GetInt16(KETTLE::int32 nPos);
		virtual void                   SetInt16(KETTLE::int32 nPos, KETTLE::int16 nValue);
		virtual KETTLE::uint16         GetUInt16(KETTLE::int32 nPos);
		virtual void                   SetUInt16(KETTLE::int32 nPos, KETTLE::uint16 nValue);
		virtual KETTLE::int32          GetInt32(KETTLE::int32 nPos);
		virtual void                   SetInt32(KETTLE::int32 nPos, KETTLE::int32 nValue);
		virtual KETTLE::uint32         GetUInt32(KETTLE::int32 nPos);
		virtual void                   SetUInt32(KETTLE::int32 nPos, KETTLE::uint32 nValue);
		virtual KETTLE::int64          GetInt64(KETTLE::int32 nPos);
		virtual void                   SetInt64(KETTLE::int32 nPos, KETTLE::int64 nValue);
		virtual KETTLE::uint64         GetUInt64(KETTLE::int32 nPos);
		virtual void                   SetUInt64(KETTLE::int32 nPos, KETTLE::uint64 nValue);
		virtual KETTLE::float32        GetFloat32(KETTLE::int32 nPos);
		virtual void                   SetFloat32(KETTLE::int32 nPos, KETTLE::float32 nValue);
		virtual KETTLE::double64       GetDouble64(KETTLE::int32 nPos);
		virtual void                   SetDouble64(KETTLE::int32 nPos, KETTLE::double64 nValue);
		virtual KETTLE::int8*          GetString(KETTLE::int32 nPos);
		virtual void                   SetString(KETTLE::int32 nPos, KETTLE::int8* nValue);

		VarList& operator=(const VarList& var);
		VarList& operator<<(const VarList& var);
		VarList& operator<<(KETTLE::int8 var);
		VarList& operator<<(KETTLE::uint8 var);
		VarList& operator<<(KETTLE::int16 var);
		VarList& operator<<(KETTLE::uint16 var);
		VarList& operator<<(KETTLE::int32 var);
		VarList& operator<<(KETTLE::uint32 var);
		VarList& operator<<(KETTLE::int64 var);
		VarList& operator<<(KETTLE::uint64 var);
		VarList& operator<<(KETTLE::float32 var);
		VarList& operator<<(KETTLE::double64 var);
		VarList& operator<<(KETTLE::int8* var);
		VarList& operator<<(const KETTLE::int8* var);

		KETTLE::int8* Serialize();
		void Serialize(const VarList& var);
	protected:
		void                                   Init();
		void                                   CleanUp();
		void                                   Resize();
	private:
		common_data                            m_InitData[InitSize];
		common_data*                           m_pData;
		KETTLE::int32                          m_nVarListSize;
		KETTLE::int32                          m_nCurPos;
	};
	typedef VarList<8>        CVarList;
}
#endif