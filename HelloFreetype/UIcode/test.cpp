#include "freetype.h"

int test(int argc, char **argv)
{
  char *filename;
  char *text;

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s font sample-text\n", argv[0]);
    exit(1);
  }

  filename = argv[1]; /* first argument     */
  text = argv[2];     /* second argument    */

  c_freetype ft;
  FT_Face face = ft.set_font(filename, 16, 16);
  ft.draw_single_char(0, 0, text[0], 0, 0, face, 0, 0);
  return 0;
}
