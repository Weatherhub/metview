/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Piotr Kuchta
/// @date June 2015

#include <vector>

#include "eckit/utils/Translator.h"
#include "eckit/exception/Exceptions.h"

#include "ecml/core/ExecutionContext.h"
#include "ecml/core/Environment.h"

#include "ecml/misc/DynamicParametrisation.h"


using namespace std;
using namespace eckit;

namespace ecml {

DynamicParametrisation::DynamicParametrisation(ExecutionContext& context)
: context_(context)
{}

DynamicParametrisation::~DynamicParametrisation() {}

bool DynamicParametrisation::has(const std::string& name) const
{
    return context_.environment().lookupNoThrow(name);
}

bool DynamicParametrisation::get(const std::string& name, std::string& value) const
{
    bool r (has(name));
    if (r)
        value = context_.environment().lookup(name, "", context_);
    return r;
}

bool DynamicParametrisation::get(const std::string& name, bool& value) const
{
    bool r (has(name));
    if (r)
        value = Translator<string, bool>()(context_.environment().lookup(name, "", context_));
    return r;
}

bool DynamicParametrisation::get(const std::string& name, long& value) const
{
    bool r (has(name));
    if (r)
        value = Translator<string, long>()(context_.environment().lookup(name, "", context_));
    return r;
}

bool DynamicParametrisation::get(const std::string& name, size_t& value) const
{
    bool r (has(name));
    if (r)
        value = Translator<string, size_t>()(context_.environment().lookup(name, "", context_));
    return r;
}

bool DynamicParametrisation::get(const std::string& name, double& value) const
{
    bool r (has(name));
    if (r)
        value = Translator<string, double>()(context_.environment().lookup(name, "", context_));
    return r;
}

bool DynamicParametrisation::get(const std::string& name, std::vector<long>& value) const
{
    bool r (has(name));
    if (r)
    {
        value.clear();
        vector<string> values (context_.environment().lookupList(name, context_));
        for (size_t i(0); i < values.size(); ++i)
            value.push_back(Translator<string, long>()(values[i]));
    }
    return r;
}

bool DynamicParametrisation::get(const std::string& name, std::vector<double>& value) const
{
    bool r (has(name));
    if (r)
    {
        value.clear();
        vector<string> values (context_.environment().lookupList(name, context_));
        for (size_t i(0); i < values.size(); ++i)
            value.push_back(Translator<string, double>()(values[i]));
    }
    return r;
}



bool DynamicParametrisation::get(const std::string& name, int& value) const { NOTIMP; return false; }
bool DynamicParametrisation::get(const std::string& name, float& value) const { NOTIMP; return false; }
bool DynamicParametrisation::get(const std::string& name, std::vector<int>& value) const { NOTIMP; return false; }
bool DynamicParametrisation::get(const std::string& name, std::vector<size_t>& value) const { NOTIMP; return false; }
bool DynamicParametrisation::get(const std::string& name, std::vector<float>& value) const { NOTIMP; return false; }
bool DynamicParametrisation::get(const std::string& name, std::vector<std::string>& value) const { NOTIMP; return false; }


} // namespace ecml

