/* -*- mode: C -*-
 *
 *       File:         rec-write-field.c
 *       Date:         Sun Nov 14 13:11:01 2010
 *
 *       GNU recutils - rec_write_field unit tests.
 *
 */

/* Copyright (C) 2010, 2011, 2012 Jose E. Marchesi */

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
#include <string.h>
#include <stdio.h>
#include <check.h>
#include <stdlib.h>

#include <rec.h>

/*-
 * Test: rec_write_field_nominal
 * Unit: rec_write_field
 * Description:
 * + Write fields.
 */
START_TEST(rec_write_field_nominal)
{
  rec_writer_t writer;
  rec_field_t field;
  char *str;
  size_t str_size;

  field = rec_field_new ("foo", "value");
  fail_if (field == NULL);
  writer = rec_writer_new_str (&str, &str_size);
  fail_if (!rec_write_field (writer, field, NULL, REC_WRITER_NORMAL));
  rec_field_destroy (field);
  rec_writer_destroy (writer);
  fail_if (strcmp (str, "foo: value\n") != 0);
  free (str);
}
END_TEST

/*-
 * Test: rec_write_field_sexp
 * Unit: rec_write_field
 * Description:
 * + Write fields.
 */
START_TEST(rec_write_field_sexp)
{
  rec_writer_t writer;
  rec_field_t field;
  char *str;
  size_t str_size;

  field = rec_field_new ("foo", "value");
  fail_if (field == NULL);
  writer = rec_writer_new_str (&str, &str_size);
  fail_if (!rec_write_field (writer, field, NULL, REC_WRITER_SEXP));
  rec_field_destroy (field);
  rec_writer_destroy (writer);
  fail_if (strcmp (str, "(field  \"foo\" \"value\")\n") != 0);
  free (str);
}
END_TEST

/*-
 * Test: rec_write_field_rewrite
 * Unit: rec_write_field
 * Description:
 * + Write a field using a rewrite_to name.
 */
START_TEST(rec_write_field_rewrite)
{
  rec_writer_t writer;
  rec_field_t field;
  char *str;
  size_t str_size;

  field = rec_field_new ("foo", "value");
  fail_if (field == NULL);
  writer = rec_writer_new_str (&str, &str_size);
  fail_if (!rec_write_field (writer, field, "bar", REC_WRITER_NORMAL));
  rec_field_destroy (field);
  rec_writer_destroy (writer);
  fail_if (strcmp (str, "bar: value\n") != 0);
  free (str);
}
END_TEST

/*-
 * Test: rec_write_field_sexp_rewrite
 * Unit: rec_write_field
 * Description:
 * + Writea field in sexp format using a rewrite_to
 * + name.
 */
START_TEST(rec_write_field_sexp_rewrite)
{
  rec_writer_t writer;
  rec_field_t field;
  char *str;
  size_t str_size;

  field = rec_field_new ("foo", "value");
  fail_if (field == NULL);
  writer = rec_writer_new_str (&str, &str_size);
  fail_if (!rec_write_field (writer, field, "bar", REC_WRITER_SEXP));
  rec_field_destroy (field);
  rec_writer_destroy (writer);
  fail_if (strcmp (str, "(field  \"bar\" \"value\")\n") != 0);
  free (str);
}
END_TEST

/*
 * Test creation function
 */
TCase *
test_rec_write_field (void)
{
  TCase *tc = tcase_create ("rec_write_field");
  tcase_add_test (tc, rec_write_field_nominal);
  tcase_add_test (tc, rec_write_field_sexp);
  tcase_add_test (tc, rec_write_field_rewrite);
  tcase_add_test (tc, rec_write_field_sexp_rewrite);

  return tc;
}

/* End of rec-write-field.c */
