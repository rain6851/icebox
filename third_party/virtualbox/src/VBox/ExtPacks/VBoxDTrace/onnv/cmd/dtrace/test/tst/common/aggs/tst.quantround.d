/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#pragma D option quiet

/*
 * This test verifies that the height of the ASCII quantization bars is
 * determined using rounding and not truncated integer arithmetic.
 */
tick-10ms
/i++ >= 27/
{
	exit(0);
}

tick-10ms
/i > 8/
{
	@ = quantize(2);
}

tick-10ms
/i > 2 && i <= 8/
{
	@ = quantize(1);
}

tick-10ms
/i <= 2/
{
	@ = quantize(0);
}