/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Antoine Elias
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*--------------------------------------------------------------------------*/
#include "data_structures_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "list.hxx"
#include "mlist.hxx"
#include "tlist.hxx"

extern "C"
{
#include "Scierror.h"
#include "MALLOC.h"
#include "localization.h"
#include "freeArrayOfString.h"
}

/*-----------------------------------------------------------------------------------*/
types::Function::ReturnValue sci_setfield(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 3)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "setfield", 2);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "setfield", 0);
        return types::Function::Error;
    }


    types::InternalType* pIndex = in[0];
    types::InternalType* pData = in[1];
    types::List* pL = in[2]->getAs<types::List>();

    if (pL->isList() == false && pL->isMList() == false && pL->isTList() == false)
    {
        Scierror(999, _("%s:  Wrong type for input argument #%d: List expected.\n"), "setfield", 3);
        return types::Function::Error;
    }

    if (pIndex->isString())
    {
        //insertion by fieldname
        types::String* pS = pIndex->getAs<types::String>();
        if ((pL->isMList() == false && pL->isTList() == false) || pS->getSize() != 1)
        {
            Scierror(999, _("%s: Not implemented in scilab...\n"), "setfield");
            return types::Function::Error;
        }

        types::TList* pT = pL->getAs<types::TList>();

        std::wstring stField = pS->get(0);
        if (pT->set(stField, pData) == false)
        {
            Scierror(999, _("%s: Invalid index.\n"), "setfield");
            return types::Function::Error;
        }
    }
    else
    {
        //insertion by index
        types::typed_list Args;
        Args.push_back(pIndex);
        pL->insert(&Args, pData);
    }

    return types::Function::OK;
}
/*-----------------------------------------------------------------------------------*/