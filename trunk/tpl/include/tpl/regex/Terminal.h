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
// Module: tpl/regex/Terminal.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-8-13 9:41:58
// 
// $Id$
// -----------------------------------------------------------------------*/
#ifndef TPL_REGEX_TERMINAL_H
#define TPL_REGEX_TERMINAL_H

#ifndef TPL_REGEX_BASIC_H
#include "Basic.h"
#endif

#ifndef STDEXT_CHARTYPE_H
#include "../../../../stdext/include/stdext/CharType.h"
#endif

NS_TPL_BEGIN

// -------------------------------------------------------------------------
// function ch_any

// Usage: ch_any()	--- means: matching any character.

class ChAny
{
public:
	enum { character = 0 };
	enum { endch = -1 };

	typedef ExplicitConvertible convertible_type;
	typedef TagAssigChar assig_tag;

	template <class SourceT, class ContextT>
	bool TPL_CALL match(SourceT& ar, ContextT& context) const
	{
		TPL_REQUIRE(endch == (int)SourceT::endch, ConstConsistent_);
		TPL_REQUIRE(sizeof(int) == sizeof(typename SourceT::int_type), SizeConsistent_);
		return ar.get() != SourceT::endch;
	}

	bool TPL_CALL operator()(int c) const {
		return c != endch;
	}
};

__forceinline Rule<ChAny> TPL_CALL ch_any() {
	return Rule<ChAny>();
}

// -------------------------------------------------------------------------
// class EqCh

template <class PredT>
class EqCh : public PredT // Match a Char
{
public:
	EqCh() {}
	
	template <class T1>
	EqCh(const T1& x) : PredT(x) {}

	template <class T1, class T2>
	EqCh(const T1& x, const T2& y) : PredT(x, y) {}

	template <class T1, class T2, class T3>
	EqCh(const T1& x, const T2& y, const T3& z) : PredT(x, y, z) {}

public:
	enum { character = 0 };

	typedef AutoConvertible convertible_type;
	typedef TagAssigChar assig_tag;

	template <class SourceT, class ContextT>
	bool TPL_CALL match(SourceT& ar, ContextT& context) const
	{
		typename SourceT::int_type c = ar.get();
		if (PredT::operator()(c))
			return true;
		ar.unget(c);
		return false;
	}
};

// -------------------------------------------------------------------------
// function ch_range

// Usage: ch_range<'0', '9'>()	--- means: [0-9]

template <int m_c1, int m_c2>
class ChRg_
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return c >= m_c1 && c <= m_c2;
	}
};

template <int m_c1, int m_c2>
class ChRange : public EqCh<ChRg_<m_c1, m_c2> > {
};

template <int m_c1, int m_c2> 
__forceinline Rule<ChRange<m_c1, m_c2> > TPL_CALL ch_range() {
	return Rule<ChRange<m_c1, m_c2> >();
}

// -------------------------------------------------------------------------
// function not_ch

// Usage: not_ch<'a'>()			--- means: ~ch('a')
// Usage: not_ch<'a', 'b'>()	--- means: ~(ch('a') | ~ch('b'))

template <int m_c1, int m_c2 = m_c1, int m_c3 = m_c2>
class N_
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c1 != c && m_c2 != c && m_c3 != c;
	}
};

template <int m_c1, int m_c2>
class N_<m_c1, m_c2, m_c2>
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c1 != c && m_c2 != c;
	}
};

template <int m_c>
class N_<m_c, m_c, m_c>
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c != c;
	}
};

template <int m_c1, int m_c2 = m_c1, int m_c3 = m_c2>
class NotCh : public EqCh<N_<m_c1, m_c2, m_c3> > {
};

template <int m_c>
__forceinline Rule<NotCh<m_c> > TPL_CALL not_ch() {
	return Rule<NotCh<m_c> >();
}

template <int m_c1, int m_c2>
__forceinline Rule<NotCh<m_c1, m_c2> > TPL_CALL not_ch() {
	return Rule<NotCh<m_c1, m_c2> >();
}

template <int m_c1, int m_c2, int m_c3>
__forceinline Rule<NotCh<m_c1, m_c2, m_c3> > TPL_CALL not_ch() {
	return Rule<NotCh<m_c1, m_c2, m_c3> >();
}

// -------------------------------------------------------------------------
// function ch

// Usage: ch<'a'>()			--- means: ch('a')
// Usage: ch<'a', 'b'>()	--- means: ch('a') | ch('b')

template <int m_c1, int m_c2 = m_c1, int m_c3 = m_c2>
class C_
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c1 == c || m_c2 == c || m_c3 == c;
	}
};

template <int m_c1, int m_c2>
class C_<m_c1, m_c2, m_c2>
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c1 == c || m_c2 == c;
	}
};

template <int m_c>
class C_<m_c, m_c, m_c>
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c == c;
	}
};

template <int m_c1, int m_c2 = m_c1, int m_c3 = m_c2>
class Ch : public EqCh<C_<m_c1, m_c2, m_c3> > {
};

template <int m_c>
__forceinline Rule<Ch<m_c> > TPL_CALL ch() {
	return Rule<Ch<m_c> >();
}

template <int m_c1, int m_c2>
__forceinline Rule<Ch<m_c1, m_c2> > TPL_CALL ch() {
	return Rule<Ch<m_c1, m_c2> >();
}

template <int m_c1, int m_c2, int m_c3>
__forceinline Rule<Ch<m_c1, m_c2, m_c3> > TPL_CALL ch() {
	return Rule<Ch<m_c1, m_c2, m_c3> >();
}

// -------------------------------------------------------------------------
// function ch()

// Usage: ch('a')
// Sorry that we can't use 'a' directly instead of ch('a') in all case.

class C1
{
private:
	int m_c;

public:
	C1(int c) : m_c(c) {}

	bool TPL_CALL operator()(int c) const {
		return m_c == c;
	}
};

class C2
{
private:
	int m_c1;
	int m_c2;

public:
	C2(int c1, int c2) : m_c1(c1), m_c2(c2) {}

	bool TPL_CALL operator()(int c) const {
		return m_c1 == c || m_c2 == c;
	}
};

class C3
{
private:
	int m_c1;
	int m_c2;
	int m_c3;

public:
	C3(int c1, int c2, int c3) : m_c1(c1), m_c2(c2), m_c3(c3) {}

	bool TPL_CALL operator()(int c) const {
		return m_c1 == c || m_c2 == c || m_c3 == c;
	}
};

typedef EqCh<C1> Ch1_;
typedef EqCh<C2> Ch2_;
typedef EqCh<C3> Ch3_;

__forceinline Rule<Ch1_> TPL_CALL ch(const int x) {
	return Rule<Ch1_>(x);
}

__forceinline Rule<Ch2_> TPL_CALL ch(const int c1, const int c2) {
	return Rule<Ch2_>(c1, c2);
}

__forceinline Rule<Ch3_> TPL_CALL ch(const int c1, const int c2, const int c3) {
	return Rule<Ch3_>(c1, c2, c3);
}

__forceinline Grammar<Gr<Ch1_> > TPL_CALL gr(char x) {
	return Grammar<Gr<Ch1_> >((unsigned char)x);
}

__forceinline Grammar<Gr<Ch1_> > TPL_CALL gr(wchar_t x) {
	return Grammar<Gr<Ch1_> >(x);
}

__forceinline Grammar<Gr<Ch1_> > TPL_CALL gr(int x) {
	return Grammar<Gr<Ch1_> >(x);
}

#define TPL_RULE_CH_BINARY_OP1_(op, Op, CharT, UCharT)								\
template <class T2> __forceinline													\
Rule< Op<Ch1_, T2> > TPL_CALL operator op(CharT x, const Rule<T2>& y)				\
	{ return ch((UCharT)x) op y; }													\
template <class T1> __forceinline													\
Rule< Op<T1, Ch1_> > TPL_CALL operator op(const Rule<T1>& x, CharT y)				\
	{ return x op ch((UCharT)y); }

#define TPL_GRAMMAR_CH_BINARY_OP1_(op, Op, CharT, UCharT)							\
template <class T2> __forceinline													\
Grammar< Op<Gr<Ch1_>, T2> > TPL_CALL operator op(CharT x, const Grammar<T2>& y)		\
	{ return ch((UCharT)x) op y; }													\
template <class T1> __forceinline													\
Grammar< Op<T1, Gr<Ch1_> > > TPL_CALL operator op(const Grammar<T1>& x, CharT y)	\
	{ return x op ch((UCharT)y); }

#define TPL_RULE_CH_BINARY_OP_(op, Op)												\
	TPL_RULE_CH_BINARY_OP1_(op, Op, char, unsigned char)							\
	TPL_RULE_CH_BINARY_OP1_(op, Op, wchar_t, wchar_t)

#define TPL_GRAMMAR_CH_BINARY_OP_(op, Op)											\
	TPL_GRAMMAR_CH_BINARY_OP1_(op, Op, char, unsigned char)							\
	TPL_GRAMMAR_CH_BINARY_OP1_(op, Op, wchar_t, wchar_t)

// -------------------------------------------------------------------------
// function space, alpha, ...

// Usage: space()		--- means: matching ONE Writespace Character
// Usage: alpha()		--- means: matching ONE Alpha Character
// Usage: ...

typedef ChRange<'0', '9'> Digit;
typedef ChRange<'a', 'z'> LowerAlpha;
typedef ChRange<'A', 'Z'> UpperAlpha;

typedef EqCh<std::CharType::IsSpace> Space;
typedef EqCh<std::CharType::IsAlpha> Alpha;
typedef EqCh<std::CharType::IsXDigit> XDigit;

typedef EqCh<std::CharType::IsCSymbolFirstChar> CSymbolFirstChar;
typedef EqCh<std::CharType::IsCSymbolNextChar> CSymbolNextChar;

typedef EqCh<std::CharType::IsXmlSymbolFirstChar> XmlSymbolFirstChar;
typedef EqCh<std::CharType::IsXmlSymbolNextChar> XmlSymbolNextChar;

inline Rule<Space> TPL_CALL space() {
	return Rule<Space>();
}

inline Rule<Alpha> TPL_CALL alpha() {
	return Rule<Alpha>();
}

inline Rule<LowerAlpha> TPL_CALL lower() {
	return Rule<LowerAlpha>();
}

inline Rule<UpperAlpha> TPL_CALL upper() {
	return Rule<UpperAlpha>();
}

inline Rule<Digit> TPL_CALL digit() {
	return Rule<Digit>();
}

inline Rule<XDigit> TPL_CALL xdigit() {
	return Rule<XDigit>();
}

// -------------------------------------------------------------------------
// $Log: $

NS_TPL_END

#endif /* TPL_REGEX_TERMINAL_H */