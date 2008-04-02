/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: stdext/archive/Stdio.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-11-29 21:07:06
// 
// $Id: Stdio.h,v 1.3 2007/01/10 09:36:12 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __STDEXT_ARCHIVE_STDIO_H__
#define __STDEXT_ARCHIVE_STDIO_H__

#ifndef __STDEXT_ARCHIVE_WRITER_H__
#include "Writer.h"
#endif

#ifndef __STDEXT_ARCHIVE_READER_H__
#include "Reader.h"
#endif

#ifndef __STDEXT_ARCHIVE_WRITEARCHIVE_H__
#include "WriteArchive.h"
#endif

#ifndef __STDEXT_ARCHIVE_READARCHIVE_H__
#include "ReadArchive.h"
#endif

#if !defined(STD_NO_MSVCRT)
	#ifndef _INC_IO
	#include <io.h>
	#endif
#else
	#ifndef __STDEXT_MSVCRT_H__
	#include "../msvcrt.h"
	#endif
#endif

__NS_STD_BEGIN

// -------------------------------------------------------------------------
// class StdioAdapter

class StdioAdapter
{
private:
	typedef char _E;

public:
	enum { endch = -1 };

	typedef _E				char_type;
	typedef int				int_type;
	typedef unsigned char	uchar_type;
	typedef unsigned long	pos_type;
	typedef signed long		off_type;
	typedef unsigned		size_type;

protected:
	FILE* m_pFile;
	
public:
	StdioAdapter() : m_pFile(NULL) {}
	~StdioAdapter()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
		}
	}
	
	void winx_call attach(FILE* pFile)
	{
		m_pFile = pFile;
	}

	FILE* winx_call detach()
	{
		FILE* pFile = m_pFile;
		m_pFile = NULL;
		return pFile;
	}

	void winx_call open_handle(FILE* pFile)
	{
		WINX_ASSERT(m_pFile == NULL);
		m_pFile = pFile;
	}

	HRESULT winx_call open_to_write(LPCWSTR szFile)
	{
		WINX_ASSERT(m_pFile == NULL);
		WINX_USES_CONVERSION;
		m_pFile = fopen(WINX_W2CA(szFile), "wb");
		return m_pFile ? S_OK : E_ACCESSDENIED;
	}

	HRESULT winx_call open_to_write(LPCSTR szFile)
	{
		WINX_ASSERT(m_pFile == NULL);
		m_pFile = fopen(szFile, "wb");
		return m_pFile ? S_OK : E_ACCESSDENIED;
	}

	HRESULT winx_call open_to_read(LPCWSTR szFile)
	{
		WINX_ASSERT(m_pFile == NULL);
		WINX_USES_CONVERSION;
		m_pFile = fopen(WINX_W2CA(szFile), "rb");
		return m_pFile ? S_OK : E_ACCESSDENIED;
	}

	HRESULT winx_call open_to_read(LPCSTR szFile)
	{
		WINX_ASSERT(m_pFile == NULL);
		m_pFile = fopen(szFile, "rb");
		return m_pFile ? S_OK : E_ACCESSDENIED;
	}

	void winx_call seek(const off_type& pos, int dir = SEEK_SET)
	{
		fseek(m_pFile, pos, dir);
	}
	
	pos_type winx_call tell() const
	{
		return ftell(m_pFile);
	}

	pos_type winx_call size() const
	{
		return _filelength(fileno(m_pFile));
	}
	
	size_type winx_call get(_E* buf, size_type cch)
	{	
		return fread(buf, sizeof(char_type), cch, m_pFile);
	}

	size_type winx_call put(const _E* s, size_type cch)
	{
		return fwrite(s, sizeof(char_type), cch, m_pFile);
	}

	void winx_call flush()
	{
		fflush(m_pFile);
	}

	void winx_call close()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
		}
	}

	operator FILE*() const
	{
		return m_pFile;
	}

	int winx_call operator!() const
	{
		return m_pFile == NULL;
	}

	int winx_call good() const
	{
		return m_pFile != NULL;
	}

	int winx_call bad() const
	{
		return m_pFile == NULL;
	}
};

// -------------------------------------------------------------------------

typedef WriteArchive<FILE*, StdioAdapter> StdioWriteArchive;
typedef Writer<StdioWriteArchive> StdioWriter;

typedef ReadArchive<FILE*, StdioAdapter> StdioReadArchive;
typedef Reader<StdioReadArchive> StdioReader;

// -------------------------------------------------------------------------
// class TestStdioArchive

template <class LogT>
class TestStdioArchive : public TestCase
{
	WINX_TEST_SUITE(TestStdioArchive);
		WINX_TEST(testBasic);
	WINX_TEST_SUITE_END();

public:
	void testBasic(LogT& log)
	{
		typedef std::StdioReader ReaderT;
		typedef std::StdioWriter WriterT;

		const char stg[] = "/__teststdio__.txt";

		std::BlockPool recycle;
		std::ScopeAlloc alloc(recycle);

		WINX_USES_CONVERSION;
		{
			WriterT ar(alloc, WINX_A2W(stg));
			ar.put("hello\n");
			ar.put('\n');
		}
		{
			char szBuf[100];
			ReaderT ar(alloc, stg);
			size_t cch = ar.get(szBuf, countof(szBuf));
			szBuf[cch] = '\0';
			AssertExp(strcmp(szBuf, "hello\n\n") == 0);
		}
		// ------------------------------------
		{
			WriterT ar(alloc);
			ar.open(stg);
			ar.put("you're welcome!\n");
		}
		{
			char szBuf[100];
			ReaderT ar(alloc);
			ar.open(WINX_A2W(stg));
			size_t cch = ar.get(szBuf, countof(szBuf));
			szBuf[cch] = '\0';
			AssertExp(strcmp(szBuf, "you're welcome!\n") == 0);
		}
		{
			ReaderT ar(alloc, stg);
			std::String sym;
			AssertExp(ar.get_csymbol(alloc, sym) == sym.size());
			AssertExp(sym == "you");
			AssertExp(ar.get() == '\'');
			AssertExp(ar.get_csymbol(alloc, sym) == sym.size());
			AssertExp(sym == "re");
			AssertExp(ar.scan_csymbol(alloc, sym) == S_OK);
			AssertExp(sym == "welcome");
		}
		// ------------------------------------
		{
			char szBuf[100];
			WriterT ar(alloc, stg);
			ar.put(_itoa(13242, szBuf, 10));
			ar.put(' ');
			ar.put(_itoa(1111, szBuf, 10));
		}
		{
			ReaderT ar(alloc, stg);
			unsigned val;
			ar.scan_uint(val);
			AssertExp(val == 13242);
			ar.scan_uint(val, 2);
			AssertExp(val == 15);
		}
		// ------------------------------------
		{
			WriterT ar(alloc, stg);
			ar.puts("Hello");
			ar.puts(std::string("World"));
			ar.puts(std::vector<char>(255, '!'));
			ar.puts(std::vector<char>(65538, '?'));
		}
		{
			ReaderT ar(alloc, stg);
			std::string s1;
			AssertExp(ar.gets(s1) == S_OK);
			AssertExp(s1 == "Hello");
			std::vector<char> s2;
			AssertExp(ar.gets(s2) == S_OK);
			AssertExp(std::compare(s2.begin(), s2.end(), "World") == 0);
			std::String s3;
			AssertExp(ar.gets(alloc, s3) == S_OK);
			AssertExp(s3 == std::String(alloc, 255, '!'));
			std::String s4;
			AssertExp(ar.gets(alloc, s4) == S_OK);
			AssertExp(s4 == std::String(alloc, 65538, '?'));
			std::String s5;
			AssertExp(ar.gets(alloc, s5) != S_OK);
		}
	}
};

// -------------------------------------------------------------------------
// $Log: Stdio.h,v $

__NS_STD_END

#endif /* __STDEXT_ARCHIVE_STDIO_H__ */