/*******************************************************************************
* Copyright 2005-2017 Intel Corporation All Rights Reserved.
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*******************************************************************************/

/*
 *
 * fftw_plan_dft_r2c - FFTW3 wrapper to MKL.
 *
 ******************************************************************************
 */

#include "fftw3_mkl.h"

fftw_plan
fftw_plan_dft_r2c(int rank, const int *n, double *in, fftw_complex *out,
                  unsigned flags)
{
    fftw_iodim64 dims64[MKL_MAXRANK];
    int i, inplace;

    if (rank > MKL_MAXRANK)
        return NULL;

    if (n == NULL)
        return NULL;

    for (i = 0; i < rank; ++i)
    {
        dims64[i].n = n[i];
    }

    /* compute strides, different for inplace and out-of-place */
    inplace = ((void *)in == (void *)out);
    if (rank > 0)
    {
        dims64[rank - 1].is = 1;
        dims64[rank - 1].os = 1;
    }
    if (rank > 1)
    {
        dims64[rank - 2].os = dims64[rank - 1].n / 2 + 1;
        dims64[rank - 2].is =
            (inplace ? dims64[rank - 2].os * 2 : dims64[rank - 1].n);
    }
    for (i = rank - 2; i > 0; --i)
    {
        dims64[i - 1].is = dims64[i].is * dims64[i].n;
        dims64[i - 1].os = dims64[i].os * dims64[i].n;
    }

    return fftw_plan_guru64_dft_r2c(rank, dims64, 0, NULL, in, out, flags);
}
