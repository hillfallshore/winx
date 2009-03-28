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
// Module: stdext/text/StringAlgo.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-8-18 18:56:07
// 
// $Id: StringAlgo.h,v 1.1 2006/10/18 12:13:39 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef STDEXT_TEXT_STRINGALGO_H
#define STDEXT_TEXT_STRINGALGO_H

#ifndef STDEXT_TEXT_BASICSTRING_H
#include "BasicString.h"
#endif

#ifndef STDEXT_TEXT_RANGE_H
#include "Range.h"
#endif

#ifndef STDEXT_CHARTYPE_H
#include "../CharType.h"
#endif

#ifndef STDEXT_MSVCRT_VARGS_H
#include "../msvcrt/vargs.h"
#endif

NS_STDEXT_BEGIN

// -------------------------------------------------------------------------
// codepage_t

enum codepage_t
{
	cp_auto		= 0,
	cp_utf7		= 65000,
	cp_utf8		= 65001,
	cp_shiftjis	= 932,
	cp_gbk		= 936,
	cp_big5		= 950,
	cp_1252		= 1252,
};

// -------------------------------------------------------------------------
// iconv

template <class StringT>
inline void winx_call iconv(
	codepage_t from, const char* str, size_t cch, StringT& dest)
{
	int cch2 = MultiByteToWideChar(from, 0, str, cch, NULL, 0);
	wchar_t* str2 = std::resize(dest, cch2);
	MultiByteToWideChar(from, 0, str, cch, str2, cch2);
}

template <class StringT>
inline void winx_call iconv(
	const wchar_t* str, size_t cch, codepage_t to, StringT& dest)
{
	int cch2 = WideCharToMultiByte(to, 0, str, cch, NULL, 0, NULL, NULL);
	char* str2 = std::resize(dest, cch2);
	WideCharToMultiByte(to, 0, str, cch, str2, cch2, NULL, NULL);
}

template <class AllocT>
inline BasicString<wchar_t> winx_call iconv(
	AllocT& alloc, codepage_t from, const char* str, size_t cch)
{
	int cch2 = MultiByteToWideChar(from, 0, str, cch, NULL, 0);
	wchar_t* str2 = STD_ALLOC_ARRAY(alloc, wchar_t, cch2);
	MultiByteToWideChar(from, 0, str, cch, str2, cch2);
	return BasicString<wchar_t>(str2, cch2);
}

template <class AllocT>
inline BasicString<char> winx_call iconv(
	AllocT& alloc, const wchar_t* str, size_t cch, codepage_t to)
{
	int cch2 = WideCharToMultiByte(to, 0, str, cch, NULL, 0, NULL, NULL);
	char* str2 = STD_ALLOC_ARRAY(alloc, char, cch2);
	WideCharToMultiByte(to, 0, str, cch, str2, cch2, NULL, NULL);
	return BasicString<char>(str2, cch2);
}

template <class AllocT>
__forceinline BasicString<wchar_t> winx_call iconv(
	AllocT& alloc, codepage_t from, const TempString<char>& str)
{
	return iconv(alloc, from, str.data(), str.size());
}

template <class AllocT>
__forceinline BasicString<char> winx_call iconv(
	AllocT& alloc, const TempString<wchar_t>& str, codepage_t to)
{
	return iconv(alloc, str.data(), str.size(), to);
}

// -------------------------------------------------------------------------
// upper/lower

template <class CharT, class AllocT, class TransT>
inline BasicString<CharT> winx_call transform(
	AllocT& alloc, const TempString<CharT>& str, const TransT& trans)
{
	size_t n = str.size();
	CharT* p = STD_NEW_ARRAY(alloc, CharT, n);
	std::transform(str.begin(), str.end(), p, trans);
	return BasicString<CharT>(p, n);
}

template <class AllocT>
__forceinline BasicString<char> winx_call upper(AllocT& alloc, const TempString<char>& str) {
	return std::transform(alloc, str, ToUpper<char>());
}

template <class AllocT>
__forceinline BasicString<wchar_t> winx_call upper(AllocT& alloc, const TempString<wchar_t>& str) {
	return std::transform(alloc, str, ToUpper<wchar_t>());
}

template <class AllocT>
__forceinline BasicString<char> winx_call lower(AllocT& alloc, const TempString<char>& str) {
	return std::transform(alloc, str, ToLower<char>());
}

template <class AllocT>
__forceinline BasicString<wchar_t> winx_call lower(AllocT& alloc, const TempString<wchar_t>& str) {
	return std::transform(alloc, str, ToLower<wchar_t>());
}

// -------------------------------------------------------------------------
// trim/trimLeft/trimRight

template <class CharT>
inline BasicString<CharT> winx_call trimLeft(const BasicString<CharT>& s)
{
	typedef typename BasicString<CharT>::const_iterator iterator;
	const iterator last = s.end();
	const iterator first = std::find_if(s.begin(), last, CharType::NotIsSpace());
	return BasicString<CharT>(first, last-first);
}

template <class CharT>
inline BasicString<CharT> winx_call trimRight(const BasicString<CharT>& s)
{
	typedef typename BasicString<CharT>::const_iterator iterator;
	const CharType::NotIsSpace notSpace = CharType::NotIsSpace();
	const iterator first = s.begin();
	iterator last = s.end();
	while (first != last) {
		if (notSpace(*--last)) {
			++last;
			break;
		}
	}
	return BasicString<CharT>(first, last-first);
}

template <class CharT>
inline BasicString<CharT> winx_call trim(const BasicString<CharT>& s)
{
	typedef typename BasicString<CharT>::const_iterator iterator;
	const CharType::NotIsSpace notSpace = CharType::NotIsSpace();
	iterator last = s.end();
	const iterator first = std::find_if(s.begin(), last, notSpace);
	while (first != last) {
		if (notSpace(*--last)) {
			++last;
			break;
		}
	}
	return BasicString<CharT>(first, last-first);
}

// -------------------------------------------------------------------------
// explode

template <bool bEraseEmpty, class CharT, class AllocT, class SepIt>
inline
BasicArray<BasicString<CharT> >
winx_call explode(AllocT& alloc, SepIt sep, SepIt sepEnd, const BasicString<CharT>& s)
{
	typedef typename BasicString<CharT>::const_iterator iterator;
	
	struct Node {
		BasicString<CharT> s;
		const Node* prev;
	};
	
	const Node* lst = NULL;
	const iterator last = s.end();
	const size_t sepLen = std::distance(sep, sepEnd);
	size_t n = 0;
	iterator first = s.begin();	
	for (;;) {
		const iterator it = std::search(first, last, sep, sepEnd);
		if (!bEraseEmpty || it != first) {
			Node* p = (Node*)_alloca(sizeof(Node));
			p->s = BasicString<CharT>(first, it);
			p->prev = lst;
			lst = p;
			++n;
		}
		if (it == last)
			break;
		first = it + sepLen;
	}
	
	size_t i = n;
	BasicString<CharT>* arr = STD_ALLOC_ARRAY(alloc, BasicString<CharT>, n);
	while (i) {
		arr[--i] = lst->s;
		lst = lst->prev;
	}
	return BasicArray<BasicString<CharT> >(arr, n);
}

template <bool bEraseEmpty, class AllocT>
__forceinline
BasicArray<BasicString<char> >
winx_call explode(AllocT& alloc, const TempString<char>& sep, const BasicString<char>& s) {
	return explode<bEraseEmpty>(alloc, sep.begin(), sep.end(), s);
}

template <class AllocT>
__forceinline
BasicArray<BasicString<char> >
winx_call explode(AllocT& alloc, const TempString<char>& sep, const BasicString<char>& s) {
	return explode<true>(alloc, sep.begin(), sep.end(), s);
}

template <bool bEraseEmpty, class AllocT>
__forceinline
BasicArray<BasicString<wchar_t> >
winx_call explode(AllocT& alloc, const TempString<wchar_t>& sep, const BasicString<wchar_t>& s) {
	return explode<bEraseEmpty>(alloc, sep.begin(), sep.end(), s);
}

template <class AllocT>
__forceinline
BasicArray<BasicString<wchar_t> >
winx_call explode(AllocT& alloc, const TempString<wchar_t>& sep, const BasicString<wchar_t>& s) {
	return explode<true>(alloc, sep.begin(), sep.end(), s);
}

// -------------------------------------------------------------------------
// implode

template <class AllocT, class GlueIt, class Iterator>
inline
BasicString<typename iterator_traits_alter<Iterator>::value_type::value_type>
winx_call implode(AllocT& alloc, const GlueIt glue, size_t n, const Iterator first, const size_t count)
{
	typedef typename iterator_traits_alter<Iterator>::value_type ContainerT;
	typedef typename ContainerT::value_type ValueT;
	
	if (count < 2)
		return count ? BasicString<ValueT>(alloc, *first) : BasicString<ValueT>();
	
	Iterator it = first;
	size_t i, len = 0;
	for (i = 0; i < count; ++i)
		len += (*it++).size();

	len += (count-1)*n;
	it = first;
	ValueT* buf = STD_NEW_ARRAY(alloc, ValueT, len);
	for (i = 1; i < count; ++i) {
		const ContainerT& cont = *it++; 
		buf = std::copy(cont.begin(), cont.end(), buf);
		buf = std::copy(glue, glue+n, buf);
	}
	
	const ContainerT& cont = *it;
	buf = std::copy(cont.begin(), cont.end(), buf);
	return BasicString<ValueT>(buf-len, buf);
}

template <class AllocT, class Iterator>
__forceinline
BasicString<char>
winx_call implode(AllocT& alloc, const TempString<char>& glue, Iterator first, size_t count) {
	return implode(alloc, glue.begin(), glue.size(), first, count);
}

template <class AllocT, class Iterator>
__forceinline
BasicString<wchar_t>
winx_call implode(AllocT& alloc, const TempString<wchar_t>& glue, Iterator first, size_t count) {
	return implode(alloc, glue.begin(), glue.size(), first, count);
}

template <class AllocT, class Iterator>
__forceinline
BasicString<char>
winx_call implode(AllocT& alloc, const char glue, Iterator first, size_t count) {
	return implode(alloc, &glue, 1, first, count);
}

template <class AllocT, class Iterator>
__forceinline
BasicString<wchar_t>
winx_call implode(AllocT& alloc, const wchar_t glue, Iterator first, size_t count) {
	return implode(alloc, &glue, 1, first, count);
}

template <class AllocT, class ContainerT>
__forceinline
BasicString<char>
winx_call implode(AllocT& alloc, const TempString<char>& glue, const ContainerT& cont) {
	return implode(alloc, glue.begin(), glue.size(), cont.begin(), cont.size());
}

template <class AllocT, class ContainerT>
__forceinline
BasicString<wchar_t>
winx_call implode(AllocT& alloc, const TempString<wchar_t>& glue, const ContainerT& cont) {
	return implode(alloc, glue.begin(), glue.size(), cont.begin(), cont.size());
}

template <class AllocT, class ContainerT>
__forceinline
BasicString<char>
winx_call implode(AllocT& alloc, const char glue, const ContainerT& cont) {
	return implode(alloc, &glue, 1, cont.begin(), cont.size());
}

template <class AllocT, class ContainerT>
__forceinline
BasicString<wchar_t>
winx_call implode(AllocT& alloc, const wchar_t glue, const ContainerT& cont) {
	return implode(alloc, &glue, 1, cont.begin(), cont.size());
}

// -------------------------------------------------------------------------
// concat

template <class AllocT, class Iterator>
inline
BasicString<typename iterator_traits_alter<Iterator>::value_type::value_type>
winx_call concat(AllocT& alloc, const Iterator first, const size_t count)
{
	typedef typename iterator_traits_alter<Iterator>::value_type ContainerT;
	typedef typename ContainerT::value_type ValueT;

	Iterator it = first;
	size_t i, len = 0;
	for (i = 0; i < count; ++i)
		len += (*it++).size();

	it = first;
	ValueT* buf = STD_NEW_ARRAY(alloc, ValueT, len);
	for (i = 0; i < count; ++i) {
		const ContainerT& cont = *it++; 
		buf = std::copy(cont.begin(), cont.end(), buf);
	}

	return BasicString<ValueT>(buf-len, buf);
}

template <class AllocT, class ContainerT>
__forceinline
BasicString<typename ContainerT::value_type::value_type>
winx_call concat(AllocT& alloc, const ContainerT& cont) {
	return concat(alloc, cont.begin(), cont.size());
}

template <class AllocT, class CharT>
inline BasicString<CharT> winx_call __concatString(
	AllocT& alloc, const TempString<CharT>* val[], size_t count)
{
	size_t i, len = 0;
	for (i = 0; i < count; ++i)
		len += val[i]->size();

	CharT* buf = STD_NEW_ARRAY(alloc, CharT, len);
	for (i = 0; i < count; ++i)
		buf = std::copy(val[i]->begin(), val[i]->end(), buf);

	return BasicString<CharT>(buf-len, len);
}

WINX_VARGS_TFUNC_EP1_REF(
	BasicString<char>, concat, AllocT, const TempString<char>, __concatString);

WINX_VARGS_TFUNC_EP1_REF(
	BasicString<wchar_t>, concat, AllocT, const TempString<wchar_t>, __concatString);

NS_STDEXT_END

// -------------------------------------------------------------------------
// class TestStringAlgo

#if defined(STD_UNITTEST)

template <class LogT>
class TestStringAlgo : public TestCase
{
	WINX_TEST_SUITE(TestStringAlgo);
		WINX_TEST(testConcat);
		WINX_TEST(testConcat2);
		WINX_TEST(testImplode);
		WINX_TEST(testExplode);
		WINX_TEST(testConv);
		WINX_TEST(testTrim);
//		WINX_TEST(testIconv);
	WINX_TEST_SUITE_END();

public:
	void testIconv(LogT& log)
	{
		std::ScopedAlloc alloc;

		std::WString s1 = std::iconv(alloc, std::cp_auto, "Hello, world!");
		AssertExp(s1 == L"Hello, world!");

		std::String s2 = std::iconv(alloc, s1, std::cp_utf8);
		AssertExp(s2 == "Hello, world!");
	}
	
	void testConv(LogT& log)
	{
		std::ScopedAlloc alloc;

		std::string s1 = "ABC";
		AssertExp(std::lower(alloc, s1) == "abc");
		
		std::String s2(alloc, "abc");
		AssertExp(std::upper(alloc, s2) == "ABC");
	}
	
	void testTrim(LogT& log)
	{
		std::ScopedAlloc alloc;
		std::String s(alloc, " \t Hello, world! \t\n");
		
		AssertExp(std::trim(s) == "Hello, world!");
		AssertExp(std::trimLeft(s) == "Hello, world! \t\n");
		AssertExp(std::trimRight(s) == " \t Hello, world!");
	}

	void testImplode(LogT& log)
	{
		std::AutoFreeAlloc alloc;

		std::list<std::string> lst;
		lst.push_back("Hello,");
		lst.push_back("world!");
		lst.push_back("I");
		lst.push_back("am");
		lst.push_back("xushiwei!\n");

		std::String s = std::implode(alloc, ' ', lst);
		AssertExp(s == "Hello, world! I am xushiwei!\n");
	
		s = std::implode(alloc, " -> ", lst);
		AssertExp(s == "Hello, -> world! -> I -> am -> xushiwei!\n");
	}
	
	void testExplode(LogT& log)
	{
		std::AutoFreeAlloc alloc;

		std::String s(alloc, "Hello, world!  I am xushiwei!");

		std::BasicArray<std::String> arr = std::explode(alloc, ' ', s);
		AssertExp(arr.size() == 5);
		AssertExp(
			arr[0] == "Hello," &&
			arr[1] == "world!" &&
			arr[2] == "I" &&
			arr[3] == "am" &&
			arr[4] == "xushiwei!");
		
		arr = std::explode<false>(alloc, ' ', s);
		AssertExp(arr.size() == 6);
		AssertExp(
			arr[0] == "Hello," &&
			arr[1] == "world!" &&
			arr[2] == "" &&
			arr[3] == "I" &&
			arr[4] == "am" &&
			arr[5] == "xushiwei!");
	}

	void testConcat2(LogT& log)
	{
		std::AutoFreeAlloc alloc;
		{
			std::list<std::string> lst;
			lst.push_back("Hello,");
			lst.push_back(" ");
			lst.push_back("world!");
		
			std::String s = std::concat(alloc, lst);
			AssertExp(s == "Hello, world!");
		}
		{
			std::vector<std::string> vec;
			vec.push_back("Hello,");
			vec.push_back(" ");
			vec.push_back("world!");
		
			std::String s = std::concat(alloc, vec);
			AssertExp(s == "Hello, world!");
		}
	}

	void testConcat(LogT& log)
	{
		std::ScopedAlloc alloc;

		std::String s[4];
		s[0].attach("Hello");
		s[1].assign(alloc, ", ");
		s[2] = std::String(alloc, "world");
		s[3].assign(alloc, 3, '!');

		std::String result = std::concat(alloc, s, countof(s));
		AssertExp(result == "Hello, world!!!");

		std::String result2 = std::concat(alloc, "Hello", "!!!");
		AssertExp(result2 == "Hello!!!");

		std::String result3 = std::concat(alloc, s[0], s[1], s[2], s[3]);
		AssertExp(result == result3);

		char s2buf[] = "world";
		std::vector<char> s2(s2buf, std::end(s2buf));
		std::string s1 = result2.stl_str();
		std::String result4 = std::concat(alloc, s1, " ", s2, "!!", "!");
		AssertExp(result4 == "Hello!!! world!!!");
	}
};

#endif // defined(STD_UNITTEST)

// -------------------------------------------------------------------------
// $Log: StringAlgo.h,v $

#endif /* STDEXT_TEXT_STRINGALGO_H */
