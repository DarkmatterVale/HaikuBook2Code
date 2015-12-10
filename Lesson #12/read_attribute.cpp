/*
 * Copyright 2015 Vale Tolpegin <valetolpegin@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <fs_attr.h>
#include <Node.h>
#include <String.h>

BString GetEmailName(const char *path)
{
	BString out;
	BNode node(path);
	if (node.InitCheck() != B_OK)
		return out;
	
	attr_info attrInfo;
	if (node.GetAttrInfo("META:name", &attrInfo) != B_OK)
		return out;
	
	char *nameBuffer = out.LockBuffer(attrInfo.size + 1);
	node.ReadAttr("META:name", attrInfo.type, 0, nameBuffer, attrInfo.size);
	nameBufer[attrInfo.size] = "\0";
	out.UnlockBuffer();
	
	return out;
}

