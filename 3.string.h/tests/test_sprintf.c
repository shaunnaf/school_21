#include "../s21_tests.h"

START_TEST(sprintf_c) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char c = 'a';
  wchar_t C = 'A';
  ck_assert_int_eq(s21_sprintf(str1, "%c%8c%-8c", c, c, c),
                   sprintf(str2, "%c%8c%-8c", c, c, c));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%lc%8lc%-8lc", C, C, C),
                   sprintf(str2, "%lc%8lc%-8lc", C, C, C));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int d = -75;
  short int sd = -23;
  long int ld = 123;
  long long int lld = 679;
  ck_assert_int_eq(s21_sprintf(str1, "%d%+d% d%8d%-8d%+8d% 8d%08d%.10d%*d", d,
                               d, d, d, d, d, d, d, d, 8, d),
                   sprintf(str2, "%d%+d% d%8d%-8d%+8d% 8d%08d%.10d%*d", d, d, d,
                           d, d, d, d, d, d, 8, d));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%hd%+hd% hd%8hd%-8hd%+8hd% 8hd%08hd%.10hd%*hd", sd, sd,
                  sd, sd, sd, sd, sd, sd, sd, 5, sd),
      sprintf(str2, "%hd%+hd% hd%8hd%-8hd%+8hd% 8hd%08hd%.10hd%*hd", sd, sd, sd,
              sd, sd, sd, sd, sd, sd, 5, sd));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%ld%+ld% ld%8ld%-8ld%+8ld% 8ld%08ld%.10ld%*ld", ld, ld,
                  ld, ld, ld, ld, ld, ld, ld, 10, ld),
      sprintf(str2, "%ld%+ld% ld%8ld%-8ld%+8ld% 8ld%08ld%.10ld%*ld", ld, ld, ld,
              ld, ld, ld, ld, ld, ld, 10, ld));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1,
                  "%lld%+lld% lld%8lld%-8lld%+8lld% 8lld%08lld%.10lld%*lld",
                  lld, lld, lld, lld, lld, lld, lld, lld, lld, 12, lld),
      sprintf(str2, "%lld%+lld% lld%8lld%-8lld%+8lld% 8lld%08lld%.10lld%*lld",
              lld, lld, lld, lld, lld, lld, lld, lld, lld, 12, lld));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_f) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  double f = -3.14;
  long double lf = 513867.131073515158957;
  ck_assert_int_eq(s21_sprintf(str1, "%f%+f% f%.1f", f, f, f, f),
                   sprintf(str2, "%f%+f% f%.1f", f, f, f, f));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%Lf%+Lf% Lf%.1Lf", lf, lf, lf, lf),
                   sprintf(str2, "%Lf%+Lf% Lf%.1Lf", lf, lf, lf, lf));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *s = "I'm on top of the world";
  ck_assert_int_eq(s21_sprintf(str1, "%s%-30s%.10s", s, s, s),
                   sprintf(str2, "%s%-30s%.10s", s, s, s));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_u) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  unsigned int u = 340;
  unsigned short su = 98;
  unsigned long lu = 431;
  unsigned long long llu = 4376;
  ck_assert_int_eq(s21_sprintf(str1, "%u%8u%-8u%08u%.1u", u, u, u, u, u),
                   sprintf(str2, "%u%8u%-8u%08u%.1u", u, u, u, u, u));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%hu%8hu%-8hu%08hu%.1hu", su, su, su, su, su),
      sprintf(str2, "%hu%8hu%-8hu%08hu%.1hu", su, su, su, su, su));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%lu%8lu%-8lu%08lu%.1lu", lu, lu, lu, lu, lu),
      sprintf(str2, "%lu%8lu%-8lu%08lu%.1lu", lu, lu, lu, lu, lu));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%llu%8llu%-8llu%08llu%.1llu", llu, llu, llu, llu, llu),
      sprintf(str2, "%llu%8llu%-8llu%08llu%.1llu", llu, llu, llu, llu, llu));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  double fg = -39.67;
  long double flg = 5.345;
  double eg = -39.677856753634;
  long double elg = 54.349893825975;
  ck_assert_int_eq(s21_sprintf(str1, "%g%+g% g%#g%8g%-8g%+8g% 8g%#8g%08g", fg,
                               fg, fg, fg, fg, fg, fg, fg, fg, fg),
                   sprintf(str2, "%g%+g% g%#g%8g%-8g%+8g% 8g%#8g%08g", fg, fg,
                           fg, fg, fg, fg, fg, fg, fg, fg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%Lg%+Lg% Lg%#Lg%8Lg%-8Lg%+8Lg% 8Lg%#8Lg%08Lg", flg,
                  flg, flg, flg, flg, flg, flg, flg, flg, flg),
      sprintf(str2, "%Lg%+Lg% Lg%#Lg%8Lg%-8Lg%+8Lg% 8Lg%#8Lg%08Lg", flg, flg,
              flg, flg, flg, flg, flg, flg, flg, flg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%g%+g% g%#g%8g%-8g%+8g% 8g%#8g%08g", eg,
                               eg, eg, eg, eg, eg, eg, eg, eg, eg),
                   sprintf(str2, "%g%+g% g%#g%8g%-8g%+8g% 8g%#8g%08g", eg, eg,
                           eg, eg, eg, eg, eg, eg, eg, eg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%Lg%+Lg% Lg%#Lg%8Lg%-8Lg%+8Lg% 8Lg%#8Lg%08Lg", elg,
                  elg, elg, elg, elg, elg, elg, elg, elg, elg),
      sprintf(str2, "%Lg%+Lg% Lg%#Lg%8Lg%-8Lg%+8Lg% 8Lg%#8Lg%08Lg", elg, elg,
              elg, elg, elg, elg, elg, elg, elg, elg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%G%+G% G%#G%8G%-8G%+8G% 8G%#8G%08G", fg,
                               fg, fg, fg, fg, fg, fg, fg, fg, fg),
                   sprintf(str2, "%G%+G% G%#G%8G%-8G%+8G% 8G%#8G%08G", fg, fg,
                           fg, fg, fg, fg, fg, fg, fg, fg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%LG%+LG% LG%#LG%8LG%-8LG%+8LG% 8LG%#8LG%08LG", flg,
                  flg, flg, flg, flg, flg, flg, flg, flg, flg),
      sprintf(str2, "%LG%+LG% LG%#LG%8LG%-8LG%+8LG% 8LG%#8LG%08LG", flg, flg,
              flg, flg, flg, flg, flg, flg, flg, flg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%G%+G% G%#G%8G%-8G%+8G% 8G%#8G%08G", eg,
                               eg, eg, eg, eg, eg, eg, eg, eg, eg),
                   sprintf(str2, "%G%+G% G%#G%8G%-8G%+8G% 8G%#8G%08G", eg, eg,
                           eg, eg, eg, eg, eg, eg, eg, eg));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%LG%+LG% LG%#LG%8LG%-8LG%+8LG% 8LG%#8LG%08LG", elg,
                  elg, elg, elg, elg, elg, elg, elg, elg, elg),
      sprintf(str2, "%LG%+LG% LG%#LG%8LG%-8LG%+8LG% 8LG%#8LG%08LG", elg, elg,
              elg, elg, elg, elg, elg, elg, elg, elg));
}
END_TEST

START_TEST(sprintf_e) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  double e1 = -25.23443278;
  long double le1 = 54.345;
  double e2 = -0.000000000119;
  long double le2 = 0.000000000065;
  ck_assert_int_eq(s21_sprintf(str1, "%e%+e% e%#e%8e%-8e%+8e% 8e%#8e%08e%.4e",
                               e1, e1, e1, e1, e1, e1, e1, e1, e1, e1, e1),
                   sprintf(str2, "%e%+e% e%#e%8e%-8e%+8e% 8e%#8e%08e%.4e", e1,
                           e1, e1, e1, e1, e1, e1, e1, e1, e1, e1));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%Le%+Le% Le%#Le%8Le%-8Le%+8Le% 8Le%#8Le%08Le%.4Le",
                  le1, le1, le1, le1, le1, le1, le1, le1, le1, le1, le1),
      sprintf(str2, "%Le%+Le% Le%#Le%8Le%-8Le%+8Le% 8Le%#8Le%08Le%.4Le", le1,
              le1, le1, le1, le1, le1, le1, le1, le1, le1, le1));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%E%+E% E%#E%8E%-8E%+8E% 8E%#8E%08E%.4E",
                               e1, e1, e1, e1, e1, e1, e1, e1, e1, e1, e1),
                   sprintf(str2, "%E%+E% E%#E%8E%-8E%+8E% 8E%#8E%08E%.4E", e1,
                           e1, e1, e1, e1, e1, e1, e1, e1, e1, e1));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%LE%+LE% LE%#LE%8LE%-8LE%+8LE% 8LE%#8LE%08LE%.4LE",
                  le1, le1, le1, le1, le1, le1, le1, le1, le1, le1, le1),
      sprintf(str2, "%LE%+LE% LE%#LE%8LE%-8LE%+8LE% 8LE%#8LE%08LE%.4LE", le1,
              le1, le1, le1, le1, le1, le1, le1, le1, le1, le1));

  ck_assert_int_eq(s21_sprintf(str1, "%e%+e% e%#e%8e%-8e%+8e% 8e%#8e%08e%.4e",
                               e2, e2, e2, e2, e2, e2, e2, e2, e2, e2, e2),
                   sprintf(str2, "%e%+e% e%#e%8e%-8e%+8e% 8e%#8e%08e%.4e", e2,
                           e2, e2, e2, e2, e2, e2, e2, e2, e2, e2));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%Le%+Le% Le%#Le%8Le%-8Le%+8Le% 8Le%#8Le%08Le%.4Le",
                  le2, le2, le2, le2, le2, le2, le2, le2, le2, le2, le2),
      sprintf(str2, "%Le%+Le% Le%#Le%8Le%-8Le%+8Le% 8Le%#8Le%08Le%.4Le", le2,
              le2, le2, le2, le2, le2, le2, le2, le2, le2, le2));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%E%+E% E%#E%8E%-8E%+8E% 8E%#8E%08E%.4E",
                               e2, e2, e2, e2, e2, e2, e2, e2, e2, e2, e2),
                   sprintf(str2, "%E%+E% E%#E%8E%-8E%+8E% 8E%#8E%08E%.4E", e2,
                           e2, e2, e2, e2, e2, e2, e2, e2, e2, e2));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%LE%+LE% LE%#LE%8LE%-8LE%+8LE% 8LE%#8LE%08LE%.4LE",
                  le2, le2, le2, le2, le2, le2, le2, le2, le2, le2, le2),
      sprintf(str2, "%LE%+LE% LE%#LE%8LE%-8LE%+8LE% 8LE%#8LE%08LE%.4LE", le2,
              le2, le2, le2, le2, le2, le2, le2, le2, le2, le2));
}
END_TEST

START_TEST(sprintf_x) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  unsigned int x = 340;
  unsigned short sx = 98;
  unsigned long lx = 431;
  unsigned long long llx = 4376;
  ck_assert_int_eq(
      s21_sprintf(str1, "%x%#x%8x%-8x%#8x%08x%.1x", x, x, x, x, x, x, x),
      sprintf(str2, "%x%#x%8x%-8x%#8x%08x%.1x", x, x, x, x, x, x, x));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx%#hx%8hx%-8hx%#8hx%08hx%.1hx", sx, sx,
                               sx, sx, sx, sx, sx),
                   sprintf(str2, "%hx%#hx%8hx%-8hx%#8hx%08hx%.1hx", sx, sx, sx,
                           sx, sx, sx, sx));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%lx%#lx%8lx%-8lx%#8lx%08lx%.1lx", lx, lx,
                               lx, lx, lx, lx, lx),
                   sprintf(str2, "%lx%#lx%8lx%-8lx%#8lx%08lx%.1lx", lx, lx, lx,
                           lx, lx, lx, lx));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%llx%8llx%-8llx%08llx%.1llx", llx, llx, llx, llx, llx),
      sprintf(str2, "%llx%8llx%-8llx%08llx%.1llx", llx, llx, llx, llx, llx));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%X%#X%8X%-8X%#8X%08X%.1X", x, x, x, x, x, x, x),
      sprintf(str2, "%X%#X%8X%-8X%#8X%08X%.1X", x, x, x, x, x, x, x));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hX%#hX%8hX%-8hX%#8hX%08hX%.1hX", sx, sx,
                               sx, sx, sx, sx, sx),
                   sprintf(str2, "%hX%#hX%8hX%-8hX%#8hX%08hX%.1hX", sx, sx, sx,
                           sx, sx, sx, sx));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%lX%#lX%8lX%-8lX%#8lX%08lX%.1lX", lx, lx,
                               lx, lx, lx, lx, lx),
                   sprintf(str2, "%lX%#lX%8lX%-8lX%#8lX%08lX%.1lX", lx, lx, lx,
                           lx, lx, lx, lx));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%llX%8llX%-8llX%08llX%.1llX", llx, llx, llx, llx, llx),
      sprintf(str2, "%llX%8llX%-8llX%08llX%.1llX", llx, llx, llx, llx, llx));
}
END_TEST

START_TEST(sprintf_o) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  unsigned int o = 340;
  unsigned short so = 98;
  unsigned long lo = 431;
  unsigned long long llo = 4376;
  ck_assert_int_eq(
      s21_sprintf(str1, "%o%#o%8o%-8o%#8o%08o%.1o", o, o, o, o, o, o, o),
      sprintf(str2, "%o%#o%8o%-8o%#8o%08o%.1o", o, o, o, o, o, o, o));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%ho%#ho%8ho%-8ho%#8ho%08ho%.1ho", so, so,
                               so, so, so, so, so),
                   sprintf(str2, "%ho%#ho%8ho%-8ho%#8ho%08ho%.1ho", so, so, so,
                           so, so, so, so));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%lo%#lo%8lo%-8lo%#8lo%08lo%.1lo", lo, lo,
                               lo, lo, lo, lo, lo),
                   sprintf(str2, "%lo%#lo%8lo%-8lo%#8lo%08lo%.1lo", lo, lo, lo,
                           lo, lo, lo, lo));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(
      s21_sprintf(str1, "%llo%8llo%-8llo%08llo%.1llo", llo, llo, llo, llo, llo),
      sprintf(str2, "%llo%8llo%-8llo%08llo%.1llo", llo, llo, llo, llo, llo));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_p) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *s = "I'm on top of the world";
  char *p1 = s;
  char *p2 = NULL;
  ck_assert_int_eq(s21_sprintf(str1, "%p%-30p%p%-30p", p1, p1, p2, p2),
                   sprintf(str2, "%p%-30p%p%-30p", p1, p1, p2, p2));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_percent) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%%5555"), sprintf(str2, "%%5555"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *suite_sprintf(void) {
  Suite *s = suite_create("suite_sprintf");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, sprintf_c);
  tcase_add_test(tc, sprintf_d);
  tcase_add_test(tc, sprintf_f);
  tcase_add_test(tc, sprintf_s);
  tcase_add_test(tc, sprintf_u);
  tcase_add_test(tc, sprintf_g);
  tcase_add_test(tc, sprintf_e);
  tcase_add_test(tc, sprintf_x);
  tcase_add_test(tc, sprintf_o);
  tcase_add_test(tc, sprintf_p);
  tcase_add_test(tc, sprintf_percent);

  suite_add_tcase(s, tc);
  return s;
}