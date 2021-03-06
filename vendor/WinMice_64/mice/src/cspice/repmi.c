/* repmi.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure REPMI  ( Replace marker with integer ) */
/* Subroutine */ int repmi_(char *in, char *marker, integer *value, char *out,
	 ftnlen in_len, ftnlen marker_len, ftnlen out_len)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer i_indx(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int zzrepsub_(char *, integer *, integer *, char *
	    , char *, ftnlen, ftnlen, ftnlen);
    extern integer lastnb_(char *, ftnlen), frstnb_(char *, ftnlen);
    integer mrkpos;
    char substr[11];
    extern /* Subroutine */ int intstr_(integer *, char *, ftnlen);

/* $ Abstract */

/*     Replace a marker with an integer. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     None. */

/* $ Keywords */

/*     CHARACTER */
/*     CONVERSION */
/*     STRING */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     IN         I   Input string. */
/*     MARKER     I   Marker to be replaced. */
/*     VALUE      I   Replacement value. */
/*     OUT        O   Output string. */
/*     MAXLI      P   Maximum length of an integer. */

/* $ Detailed_Input */

/*     IN             is an arbitrary character string. */

/*     MARKER         is an arbitrary character string. The first */
/*                    occurrence of MARKER in the input string is */
/*                    to be replaced by VALUE. */

/*                    Leading and trailing blanks in MARKER are NOT */
/*                    significant. In particular, no substitution is */
/*                    performed if MARKER is blank. */

/*     VALUE          is an arbitrary integer. */

/* $ Detailed_Output */

/*     OUT            is the string obtained by substituting the text */
/*                    representation of VALUE for the first occurrence */
/*                    of MARKER in the input string. */

/*                    OUT and IN must be identical or disjoint. */

/* $ Parameters */

/*     MAXLI          is the maximum expected length of the text */
/*                    representation of an integer. 11 characters are */
/*                    sufficient to hold any integer whose absolute */
/*                    value is less than 10 billion. */

/* $ Files */

/*     None. */

/* $ Exceptions */

/*     Error Free. */

/*     1) If OUT does not have sufficient length to accommodate the */
/*        result of the substitution, the result will be truncated on */
/*        the right. */

/*     2) If MARKER is blank, or if MARKER is not a substring of IN, */
/*        no substitution is performed. (OUT and IN are identical.) */

/* $ Particulars */

/*     This is one of a family of related routines for inserting values */
/*     into strings. They are typically to construct messages that */
/*     are partly fixed, and partly determined at run time. For example, */
/*     a message like */

/*        'Fifty-one pictures were found in directory [USER.DATA].' */

/*     might be constructed from the fixed string */

/*        '#1 pictures were found in directory #2.' */

/*     by the calls */

/*        CALL REPMCT ( STRING, '#1', N_PICS,  'C', STRING ) */
/*        CALL REPMC  ( STRING, '#2', DIR_NAME,     STRING ) */

/*     which substitute the cardinal text 'Fifty-one' and the character */
/*     string '[USER.DATA]' for the markers '#1' and '#2' respectively. */

/*     The complete list of routines is shown below. */

/*        REPMC    ( Replace marker with character string value ) */
/*        REPMD    ( Replace marker with double precision value ) */
/*        REPMF    ( Replace marker with formatted d.p. value ) */
/*        REPMI    ( Replace marker with integer value ) */
/*        REPMCT   ( Replace marker with cardinal text) */
/*        REPMOT   ( Replace marker with ordinal text ) */

/* $ Examples */

/*     1. Let */

/*           IN = 'Invalid operation value.  The value was #.' */

/*        Then following the call, */

/*           CALL REPMI ( IN, '#', 5, IN  ) */

/*        IN is */

/*           'Invalid operation value.  The value was 5.' */


/*     2. Let */

/*           IN = 'Left endpoint exceeded right endpoint. */
/*                 The left endpoint was:  XX.  The right */
/*                 endpoint was:  XX.' */

/*        Then following the call, */

/*           CALL REPMI ( IN, '  XX  ', 5, OUT ) */

/*        OUT is */

/*           'Left endpoint exceeded right endpoint.  The left */
/*            endpoint was:  5.  The right endpoint was:  XX. */


/*     3. Let */

/*           NUM    = 23 */
/*           CHANCE = 'fair' */
/*           SCORE  = 4.665D0 */

/*        Then following the sequence of calls, */

/*           CALL REPMI ( 'There are & routines that have a '  // */
/*          .             '& chance of meeting your needs.'    // */
/*          .             'The maximum score was &.', */
/*          .             '&', */
/*          .             NUM, */
/*          .             MSG  ) */

/*           CALL REPMC ( MSG, '&', CHANCE, MSG ) */

/*           CALL REPMF ( MSG, '&', SCORE, 4, 'F', MSG ) */

/*        MSG is */

/*           'There are 23 routines that have a fair chance of */
/*            meeting your needs.  The maximum score was 4.665.' */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 15-AUG-2002 (WLT) */

/*        The routine is now error free. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 30-AUG-1990 (NJB) (IMU) */

/* -& */
/* $ Index_Entries */

/*     replace marker with integer */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     If MARKER is blank, no substitution is possible. */

    if (s_cmp(marker, " ", marker_len, (ftnlen)1) == 0) {
	s_copy(out, in, out_len, in_len);
	return 0;
    }

/*     Locate the leftmost occurrence of MARKER, if there is one */
/*     (ignoring leading and trailing blanks). If MARKER is not */
/*     a substring of IN, no substitution can be performed. */

    i__1 = frstnb_(marker, marker_len) - 1;
    mrkpos = i_indx(in, marker + i__1, in_len, lastnb_(marker, marker_len) - 
	    i__1);
    if (mrkpos == 0) {
	s_copy(out, in, out_len, in_len);
	return 0;
    }

/*     Okay, MARKER is non-blank and has been found. Convert the */
/*     integer to text, and substitute the text for the marker. */

    intstr_(value, substr, (ftnlen)11);
    i__1 = mrkpos + lastnb_(marker, marker_len) - frstnb_(marker, marker_len);
    zzrepsub_(in, &mrkpos, &i__1, substr, out, in_len, lastnb_(substr, (
	    ftnlen)11), out_len);
    return 0;
} /* repmi_ */

