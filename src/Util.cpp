/*
 *
 * Copyright (C) 2009,2010,2011 Halon Security <support@halon.se>
 *
 * This file is part of libdkim++.
 *
 * libdkim++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libdkim++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with libdkim++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "Util.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

bool DKIM::Util::MatchWithWildCard(const std::string& pattern, const std::string& find)
{
	/**
	 * g= tag is allowed to include one single "*" character to match zero or more
	 * arbitrary characters. an empty g= does never match.
	 *
	 * This is behaviour is overridden in Validator.cpp if version is not included,
	 * to be compatible with DomainKeys (for now...)
	 */
	if (pattern == "") return false;
	if (pattern == "*") return true;
	if (pattern == find) return true;
	if (pattern.find("*") == std::string::npos) return false;
	if (pattern.size() > find.size()+1) return false;

	size_t wcc = pattern.find("*");
	if (pattern.substr(0, wcc) != find.substr(0, wcc)) return false;
	if (pattern.substr(wcc+1) != find.substr(find.size() - pattern.substr(wcc+1).size())) return false;
	return true;
}

std::string DKIM::Util::CanonMode2String(CanonMode mode)
{
	switch (mode)
	{
		case DKIM::DKIM_C_SIMPLE:
			return "simple";
		case DKIM::DKIM_C_RELAXED:
			return "relaxed";
	}
	return "unknown";
}

std::string DKIM::Util::Algorithm2String(Algorithm algorithm)
{
	switch (algorithm)
	{
		case DKIM::DKIM_A_SHA1:
			return "rsa-sha1";
		case DKIM::DKIM_A_SHA256:
			return "rsa-sha256";
	}
	return "unknown";
}

std::string DKIM::Util::StringFormat(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char* mem = 0x0;
	vasprintf(&mem, fmt, args);
	std::string result = mem;
	free(mem);
	va_end(args);
	return result;
}