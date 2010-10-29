/* -*- mode: C -*- Time-stamp: "2010-10-29 15:30:49 jco"
 *
 *       File:         rec-field-name-part-str-p.c
 *       Date:         Fri Oct 29 15:26:11 2010
 *
 *       GNU recutils - rec_field_name_part_str_p unit tests.
 *
 */

/* Copyright (C) 2010 Jose E. Marchesi */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <check.h>

#include <rec.h>

/*-
 * Test: rec_field_name_part_str_p_nominal
 * Unit: rec_field_name_part_str_p
 * Description:
 * + Check field name parts.
 */
START_TEST(rec_field_name_part_str_p_nominal)
{
  fail_if (rec_field_name_part_str_p (""));
  fail_if (rec_field_name_part_str_p (":"));
  fail_if (rec_field_name_part_str_p ("-x"));
  fail_if (rec_field_name_part_str_p ("_x"));
  fail_if (rec_field_name_part_str_p ("0x"));
  fail_if (rec_field_name_part_str_p ("x%"));
  fail_if (!rec_field_name_part_str_p ("%"));
  fail_if (!rec_field_name_part_str_p ("ax"));
  fail_if (!rec_field_name_part_str_p ("Ax"));
}
END_TEST

/*
 * Test case creation function
 */
TCase *
test_rec_field_name_part_str_p (void)
{
  TCase *tc = tcase_create ("rec_field_name_part_str_p");
  tcase_add_test (tc, rec_field_name_part_str_p_nominal);

  return tc;
}


/* End of rec-field-name-part-str-p.c */