#include "stdafx.h"

// -------------------------------------------------------------------------
// xml_process

// What we use:
//	* Rules: RegExp, +, /, %, xml_symbol(), c_symbol(), integer(), ws(), skipws()
//	* Tags: LeafMark, NodeMark
//	* Matching: RegExp::match()
//	* Result Processing: Document::all(), []

void xml_process()
{
	using namespace tpl;

	std::BlockPool recycle;
	std::ScopeAlloc alloc(recycle);

	// ---- define source ----

	char buf[] = "<tag prop-1=1 prop-2 = -2>text</tag>";
	impl::Source source(buf, buf+sizeof(buf));

	// ---- define rules ----

	impl::LeafMark tagProp;
	impl::LeafMark tagValue;
	impl::LeafMark tagText;
	impl::NodeMark tagProps;

	impl::RegExp rProp( alloc, xml_symbol()/tagProp + skipws() + '=' + skipws() + integer()/tagValue );
	impl::RegExp rProps( alloc, rProp % ws() / tagProps );
	impl::RegExp rTagStart( alloc, '<' + xml_symbol()/"tag" + ws() + rProps + '>' );
	impl::RegExp rDoc( alloc, rTagStart + c_symbol()/tagText + "</tag>" );

	// ---- do match ----

	impl::Document doc;
	impl::Context context(alloc, doc);

	if (!rDoc.match(source, context)) {
		std::cout << "match failed\n";
		return;
	}

	// ---- print text ----

	std::cout << "Text: " << doc[tagText].stl_str() << "\n";

	// ---- print properties ----

	impl::Document::node_data vProps = doc[tagProps];
	for (impl::Document::cons it = vProps.all(); it; it = it.tl())
	{
		impl::Document::value_type item = it.hd();
		std::cout << (item.key() == tagProp ? "Prop: " : "Value: ");

		impl::Document::leaf_data vData = item.leaf();
		std::cout << vData.stl_str() << "\n";
	}
}