/*
 * XMLBuilder.cpp
 *
 *  Created on: 2016年6月21日
 *      Author: leezear
 */

#include "XBuilder.h"

namespace cp {

XBuilder::XBuilder(const string file_name, XmlReaderType type)
	: file_name_(file_name), type_(type) {
	if (initial()) {
		switch (type_) {
		case XRT_BM_PATH:
			break;
		case XRT_BM:
			break;
		default:
			break;
		}
	}
}

XBuilder::~XBuilder() {
	if (root_) {
		delete parser_;
		XMLPlatformUtils::Terminate();
	}
}

bool XBuilder::initial() {
	if (this->file_name_ == "") {
		return false;
	}

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException & toCatch) {
		// Do your failure processing here
		return false;
	}
	// Do your actual work with Xerces-C++ here.
	parser_ = new XercesDOMParser();
	parser_->setValidationScheme(XercesDOMParser::Val_Always);
	parser_->setDoNamespaces(true);

	parser_->parse(file_name_.c_str());
	//std::cout << file_name << std::endl;
	document_ = parser_->getDocument();
	root_ = document_->getDocumentElement();

	if (!root_) {
		delete (parser_);
		parser_ = nullptr;
		return false;
	}
	return true;
}

string XBuilder::GetBMFile() const {
	DOMNodeList *bmfile_list = root_->getElementsByTagName(XMLString::transcode("BMFile"));
	DOMNode *bmfile = bmfile_list->item(0);
	char* bm_name = XMLString::transcode(bmfile->getFirstChild()->getNodeValue());
	string bm_file(bm_name);
	XMLString::release(&bm_name);
	return bm_file;
}

//u32 XBuilder::getConstraintsCount() {
//	DOMNode *cons_node = root_->getElementsByTagName(XMLString::transcode("constraints"))->item(0);
//	const int num_cons = XMLString::parseInt(cons_node->getAttributes()->getNamedItem(XMLString::transcode("nbConstraints"))->getTextContent());
//	return num_cons;
//}

void XBuilder::generateDomains(XModel *model) const {
	DOMNode *doms_nodes = root_->getElementsByTagName(XMLString::transcode("domains"))->item(0);
	const int num_doms = XMLString::parseInt(
		doms_nodes->getAttributes()->getNamedItem(XMLString::transcode("nbDomains"))->getTextContent());
	DOMNodeList *dom_nodes = root_->getElementsByTagName(XMLString::transcode("domain"));

	for (int i = 0; i < num_doms; ++i) {
		DOMNode * node = dom_nodes->item(i);
		const int size = XMLString::parseInt(
			node->getAttributes()->getNamedItem(XMLString::transcode("nbValues"))->getTextContent());
		char* values = XMLString::transcode(node->getFirstChild()->getNodeValue());
		model->add(i, size, values);
		XMLString::release(&values);
	}
}

void XBuilder::generateVariables(XModel *model) const {
	DOMNode *vars_node = root_->getElementsByTagName(XMLString::transcode("variables"))->item(0);
	const int num_vars = XMLString::parseInt(
		vars_node->getAttributes()->getNamedItem(XMLString::transcode("nbVariables"))->getTextContent());
	DOMNodeList* var_nodes = root_->getElementsByTagName(XMLString::transcode("variable"));

	for (u32 i = 0; i < num_vars; ++i) {
		DOMNode * node = var_nodes->item(i);
		char * dom_id_str = XMLString::transcode(
			node->getAttributes()->getNamedItem(XMLString::transcode("domain"))->getTextContent());
		model->add(i, dom_id_str);
		XMLString::release(&dom_id_str);
	}
}

void XBuilder::generateRelations(XModel* model) const {
	DOMNode* relations_node = root_->getElementsByTagName(XMLString::transcode("relations"))->item(0);
	const int relations_count = XMLString::parseInt(
		relations_node->getAttributes()->getNamedItem(XMLString::transcode("nbRelations"))->getTextContent());
	DOMNodeList* relation_nodes = root_->getElementsByTagName(XMLString::transcode("relation"));

	for (int i = 0; i < relations_count; ++i) {
		DOMNode *node = relation_nodes->item(i);
		const int arity = XMLString::parseInt(
			node->getAttributes()->getNamedItem(XMLString::transcode("arity"))->getTextContent());
		char* semantics = XMLString::transcode(
			node->getAttributes()->getNamedItem(XMLString::transcode("semantics"))->getTextContent());
		const int size = XMLString::parseInt(
			node->getAttributes()->getNamedItem(XMLString::transcode("nbTuples"))->getTextContent());
		char* ts_str = XMLString::transcode(node->getFirstChild()->getNodeValue());
		model->add(i, arity, size, semantics, ts_str);
		XMLString::release(&semantics);
		XMLString::release(&ts_str);
	}
}

void XBuilder::generateConstraints(XModel* model) const {
	DOMNode* cons_node = root_->getElementsByTagName(XMLString::transcode("constraints"))->item(0);
	const int num_cons = XMLString::parseInt(
		cons_node->getAttributes()->getNamedItem(XMLString::transcode("nbConstraints"))->getTextContent());
	DOMNodeList* con_nodes = root_->getElementsByTagName(XMLString::transcode("constraint"));

	for (int i = 0; i < num_cons; ++i) {
		DOMNode * node = con_nodes->item(i);
		const int arity = XMLString::parseInt(
			node->getAttributes()->getNamedItem(XMLString::transcode("arity"))->getTextContent());
		char *scp_str = XMLString::transcode(
			node->getAttributes()->getNamedItem(XMLString::transcode("scope"))->getTextContent());
		char * rel_id = XMLString::transcode(
			node->getAttributes()->getNamedItem(XMLString::transcode("reference"))->getTextContent());
		model->add(i, rel_id, arity, scp_str);
	}
}

void XBuilder::GenerateXModelFromXml(XModel *model) const
{
	generateDomains(model);
	generateVariables(model);
	generateRelations(model);
	generateConstraints(model);
}

}
