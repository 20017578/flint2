/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "nmod_poly.h"
#include "nmod_mat.h"
#include "ulong_extras.h"

int
main(void)
{
    slong m, n, rep;
    ulong mod;
    FLINT_TEST_INIT(state);

    flint_printf("minpoly....");
    fflush(stdout);

    

    for (rep = 0; rep < 1000 * flint_test_multiplier(); rep++)
    {
        nmod_mat_t A;
        nmod_poly_t f, g, q, r;

        m = n_randint(state, 10);
        n = m;

        mod = n_randprime(state, 6, 0);

        nmod_mat_init(A, m, n, mod);
        nmod_poly_init(f, mod);
        nmod_poly_init(g, mod);
        nmod_poly_init(q, mod);
        nmod_poly_init(r, mod);

        nmod_mat_randtest(A, state);
        
        nmod_mat_minpoly(f, A);
        nmod_mat_charpoly(g, A);

        nmod_poly_divrem(q, r, g, f);

        if (!nmod_poly_is_zero(r))
        {
            flint_printf("FAIL: minpoly(A) does not divide charpoly(BA).\n");
            flint_printf("Matrix A:\n"), nmod_mat_print_pretty(A), flint_printf("\n");
            flint_printf("mp(A) = "), nmod_poly_print_pretty(f, "X"), flint_printf("\n");
            flint_printf("cp(A) = "), nmod_poly_print_pretty(g, "X"), flint_printf("\n");
            abort();
        }

        nmod_mat_clear(A);
        nmod_poly_clear(f);
        nmod_poly_clear(g);
        nmod_poly_clear(q);
        nmod_poly_clear(r);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}