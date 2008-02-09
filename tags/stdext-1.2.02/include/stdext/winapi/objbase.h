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
// Module: stdext/winapi/objbase.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-8-26 0:45:33
// 
// $Id: objbase.h,v 1.1 2006/10/18 12:13:39 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __STDEXT_WINAPI_OBJBASE_H__
#define __STDEXT_WINAPI_OBJBASE_H__

#ifndef __STDEXT_WINAPI_WTYPES_H__
#include "wtypes.h"
#endif

#ifndef __STDEXT_WINAPI_WINERROR_H__
#include "winerror.h"
#endif

#ifndef interface
#define interface struct
#endif

// -------------------------------------------------------------------------

#ifndef __STDEXT_MSVC_OBJIDL_H__
#include "objidl.h"
#endif

#ifndef __STDEXT_MSVC_OLEAUTO_H__
#include "oleauto.h"
#endif

// -------------------------------------------------------------------------

/* Storage instantiation modes */
#define STGM_DIRECT             0x00000000L
#define STGM_TRANSACTED         0x00010000L
#define STGM_SIMPLE             0x08000000L

#define STGM_READ               0x00000000L
#define STGM_WRITE              0x00000001L
#define STGM_READWRITE          0x00000002L

#define STGM_SHARE_DENY_NONE    0x00000040L
#define STGM_SHARE_DENY_READ    0x00000030L
#define STGM_SHARE_DENY_WRITE   0x00000020L
#define STGM_SHARE_EXCLUSIVE    0x00000010L

#define STGM_PRIORITY           0x00040000L
#define STGM_DELETEONRELEASE    0x04000000L
#define STGM_NOSCRATCH          0x00100000L

#define STGM_CREATE             0x00001000L
#define STGM_CONVERT            0x00020000L
#define STGM_FAILIFTHERE        0x00000000L

#define STGM_NOSNAPSHOT         0x00200000L

/*  flags for internet asyncronous and layout docfile */
#define ASYNC_MODE_COMPATIBILITY    0x00000001L
#define ASYNC_MODE_DEFAULT          0x00000000L

#define STGTY_REPEAT                0x00000100L
#define STG_TOEND                   0xFFFFFFFFL

#define STG_LAYOUT_SEQUENTIAL       0x00000000L
#define STG_LAYOUT_INTERLEAVED      0x00000001L

#define STGFMT_STORAGE          0
#define STGFMT_NATIVE           1
#define STGFMT_FILE             3
#define STGFMT_ANY              4
#define STGFMT_DOCFILE          5

// This is a legacy define to allow old component to builds
#define STGFMT_DOCUMENT         0

// -------------------------------------------------------------------------
// $Log: objbase.h,v $
//

#endif /* __STDEXT_WINAPI_OBJBASE_H__ */
